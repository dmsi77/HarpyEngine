// id_vec.hpp

#pragma once

#include <vector>
#include "object.hpp"
#include "log.hpp"
#include "types.hpp"

namespace realware
{
	class cApplication;

	class cIdVecObject : public cObject
	{
	public:
		explicit cIdVecObject(const std::string& id, cApplication* app) : _id(id), _app(app) {}
		~cIdVecObject() = default;

		inline const std::string& GetID() const { return _id; }
		inline cApplication* GetApplication() const { return _app; }

	protected:
		std::string _id = "";
		cApplication* _app = nullptr;

	private:
		types::boolean _isDeleted = types::K_FALSE;
	};

	template <typename T>
	class cIdVec : public cObject
	{
	public:
		explicit cIdVec(const cApplication* const app, const types::usize maxObjectCount);
		~cIdVec();

		template<typename... Args>
		T* Add(const std::string& id, Args&&... args);
		T* Add(const T& object);
		T* Find(const std::string& id);
		void Delete(const std::string& id);

		inline T* GetObjects() { return _objects; }
		inline types::usize GetObjectCount() { return _objectCount; }
		inline types::usize GetMaxObjectCount() { return _maxObjectCount; }

	private:
		cApplication* _app = nullptr;
		types::usize _objectCount = 0;
		types::usize _maxObjectCount = 0;
		T* _objects = nullptr;
	};

	template<typename T>
	cIdVec<T>::cIdVec(const cApplication* const app, const types::usize maxObjectCount) : _app((cApplication*)app), _maxObjectCount(maxObjectCount)
	{
		_objects = (T*)std::malloc(sizeof(T) * _maxObjectCount);
	}

	template<typename T>
	cIdVec<T>::~cIdVec()
	{
		std::free(_objects);
	}

	template<typename T>
	template<typename... Args>
	T* cIdVec<T>::Add(const std::string& id, Args&&... args)
	{
		if (_objectCount >= _maxObjectCount)
		{
			Print("Error: object count limit '" + std::to_string(_maxObjectCount) + "' exceeded!");

			return nullptr;
		}

		types::usize index = _objectCount;
		new (&_objects[index]) T(id, _app, std::forward<Args>(args)...);
		_objectCount += 1;

		return &_objects[index];
	}

	template<typename T>
	T* cIdVec<T>::Add(const T& object)
	{
		if (_objectCount >= _maxObjectCount)
		{
			Print("Error: object count limit '" + std::to_string(_maxObjectCount) + "' exceeded!");

			return nullptr;
		}

		types::usize index = _objectCount;
		_objects[index] = object;
		_objectCount += 1;

		return &_objects[index];
	}

	template<typename T>
	T* cIdVec<T>::Find(const std::string& id)
	{
		for (types::usize i = 0; i < _objectCount; i++)
		{
			if (_objects[i].GetID() == id)
				return &_objects[i];
		}

		return nullptr;
	}

	template<typename T>
	void cIdVec<T>::Delete(const std::string& id)
	{
		for (types::usize i = 0; i < _objectCount; i++)
		{
			if (_objects[i].GetID() == id)
			{
				const T& last = _objects[_objectCount - 1];
				_objects[i] = last;
				_objectCount -= 1;
			}
		}
	}
}