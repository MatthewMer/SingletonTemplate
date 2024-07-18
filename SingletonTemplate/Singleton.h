#pragma once
/* *****************************************************************
	Singleton template class to inherit from
***************************************************************** */

#include <memory>

template <class T>
class Singleton {
public:
	static T* s_GetInstance();
	static void s_ResetInstance();

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	// clone/assign protection
	Singleton& operator=(Singleton const&) = default;
	Singleton(Singleton const&) = default;

private:
	static std::unique_ptr<T> m_Instance;

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

	struct shared_enabler : public TImpl<T> {};
};

template <class T>
std::unique_ptr<T> Singleton<T>::m_Instance = nullptr;

template <class T>
T* Singleton<T>::s_GetInstance() {
	if (!m_Instance) {
		auto instance = std::make_unique<shared_enabler>();
		m_Instance = std::unique_ptr<T>(static_cast<T*>(instance.release()));
	}

	return m_Instance.get();
}

template <class T>
void Singleton<T>::s_ResetInstance() {
	if (m_Instance) {
		auto instance = std::make_unique<shared_enabler>();
		swap(*m_Instance, *static_cast<T*>(instance.get()));
		instance.release();
	}
}

template <class T>
void Singleton<T>::swap(T& lhs, T& rhs) {
	auto instance = std::make_unique<shared_enabler>();
	auto* tmp = static_cast<T*>(instance.get());
	*tmp = std::move(rhs);
	rhs = std::move(lhs);
	lhs = std::move(*tmp);
	instance.release();
}