#pragma once
/* *****************************************************************
	Singleton template class to inherit from
***************************************************************** */

#include <memory>

template <class T>
class Singleton {
public:
	static std::weak_ptr<T> s_GetInstance();
	static void s_ResetInstance();

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	// clone/assign protection
	Singleton& operator=(Singleton const&) = default;
	Singleton(Singleton const&) = default;

private:
	static std::shared_ptr<T> m_Instance;

	// move construction/assign
	Singleton(Singleton&&) noexcept = default;
	Singleton& operator=(Singleton&&) noexcept = default;

	static void swap(T& lhs, T& rhs);

	struct hidden {};
	virtual void inaccessible(hidden n) = 0;
	template <class T>
	class TImpl : public T {
		void inaccessible(hidden) override {};
	};

	struct shared_enabler : TImpl<T> {};
};

template <class T>
std::shared_ptr<T> Singleton<T>::m_Instance;

template <class T>
std::weak_ptr<T> Singleton<T>::s_GetInstance() {
	if (!m_Instance) {
		m_Instance = std::static_pointer_cast<T>(std::make_shared<shared_enabler>());
	}

	return m_Instance;
}

template <class T>
void Singleton<T>::s_ResetInstance() {
	if (m_Instance) {
		auto tmp = std::static_pointer_cast<T>(std::make_shared<shared_enabler>());
		swap(*m_Instance, *tmp);
	}
}

template <class T>
void Singleton<T>::swap(T& lhs, T& rhs) {
	auto tmp = std::static_pointer_cast<T>(std::make_shared<shared_enabler>());
	*tmp = std::move(rhs);
	rhs = std::move(lhs);
	lhs = std::move(*tmp);
}