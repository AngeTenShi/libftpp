#ifndef SIGLETON_HPP
# define SIGLETON_HPP

#include <memory>

template <typename TType>
class Singleton
{
	public:
		static TType* instance()
		{
			if (!_instance)
				throw std::runtime_error("Instance not yet created");
			return _instance;
		}
		template <typename... TArgs>
		static void instantiate(TArgs&&... p_args)
		{
			if (_instance)
				throw std::runtime_error("Instance already created");
			_instance = new TType(std::forward<TArgs>(p_args)...);
		}
		~Singleton() { if(_instance) delete _instance; }
	protected:
		Singleton() = default;
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	private:
		static TType *_instance;
};

template <typename TType>
TType* Singleton<TType>::_instance = nullptr; // would be better to use std::unique_ptr<TType> instead of TType* but subject is * so I used *
#endif
