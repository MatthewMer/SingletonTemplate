#pragma once
/* *****************************************************************
	Singleton template class to inherit from
***************************************************************** */

#include <memory>

template <class T>
class Singleton {
public:
	static std::shared_ptr<T> s_GetInstance();
	static void s_ResetInstance();

protected:
	~Singleton() = default;
	Singleton() = default;

	// clone/assign protection
	Singleton& operator=(Singleton const&) = default;
	Singleton(Singleton const&) = default;

private:
	static std::weak_ptr<T> m_Instance;

	// move construction/assign
	Singleton(Singleton&&) noexcept = default;
	Singleton& operator=(Singleton&&) noexcept = default;

	static void swap(T& lhs, T& rhs);
};

template <class T>
std::weak_ptr<T> Singleton<T>::m_Instance;

template <class T>
std::shared_ptr<T> Singleton<T>::s_GetInstance() {
	auto ptr = m_Instance.lock();

	if (!ptr) {
		struct shared_enabler : T {};
		ptr = std::static_pointer_cast<T>(std::make_shared<shared_enabler>());
		m_Instance = ptr;
	}

	return ptr;
}

template <class T>
void Singleton<T>::s_ResetInstance() {
	auto ptr = m_Instance.lock();

	if (ptr) {
		T tmp;
		swap(*ptr, tmp);
	}
}

template <class T>
void Singleton<T>::swap(T& lhs, T& rhs) {
	T tmp = std::move(rhs);
	rhs = std::move(lhs);
	lhs = std::move(tmp);
}