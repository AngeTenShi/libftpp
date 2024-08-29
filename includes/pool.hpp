#ifndef POOL_HPP
#define POOL_HPP

#include <cstddef>
#include <cstdlib>
#include <memory>
#include <vector>

template <typename TType>
class Pool {
	public:
		class Object
		{
			public:
				Object(TType *object, Pool *pool) : object(object), pool(pool) {};
				~Object()
				{
					if (object)
						pool->release(object);
				}
				Object(const Object&) = delete;
				Object& operator=(const Object&) = delete;
				TType *operator->()
				{
					return (object);
				}
			private:
				TType *object;
				Pool *pool;
		};

		Pool() = default;
		Pool(const std::size_t &numberOfObjectStored)
		{
			resize(numberOfObjectStored);
		}
		~Pool() = default;
		void resize(const std::size_t &numberOfObjectStored)
		{
			objects.reserve(numberOfObjectStored);
			for (std::size_t i = 0; i < numberOfObjectStored; i++)
			{
				objects.emplace_back(static_cast<TType *>(std::malloc(sizeof(TType))));
			}
		}
		template <typename ...TArgs>
		Object acquire(TArgs &&...args)
		{
			if (objects.empty())
				resize(1);
			TType *object = objects.back();
			objects.pop_back();
			new (object) TType(std::forward<TArgs>(args)...);
			return (Object(object, this));
		}

	private:
		std::vector<TType *> objects;
		void release(TType *object)
		{
			if (object == nullptr)
				return;
			object->~TType();
			objects.emplace_back(object);
		}
};
#endif
