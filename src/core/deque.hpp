#ifndef _CORE_DEQUE_HPP_
#define _CORE_DEQUE_HPP_

#include <memory>
#include <cstddef>
#include <initializer_list>

template<typename T>
class Deque {
private:
    struct Node;
    using Node_ptr = Node*;

    struct Node {
        T data{};
        Node_ptr prev{};
        Node_ptr next{};
    };

    Node_ptr m_head{nullptr};
    Node_ptr m_tail{nullptr};
    std::size_t m_size{};

    void init_first_element(const T& elem);
    void clean_up();
    void copy_data(const Deque& rhs);
public:
    Deque() = default;
    Deque(std::initializer_list<T> init_list);
    Deque(const Deque& rhs);
    Deque& operator=(const Deque& rhs);
    Deque(Deque&& rhs) noexcept;
    Deque& operator=(Deque&& rhs) noexcept;
    ~Deque();

    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::size_t size() const;

    void push_back(const T& elem);
    void push_front(const T& elem);

    T& back() const;
    T& front() const;

    void pop_front();
    void pop_back();
};

template<typename T>
Deque<T>::Deque(const Deque& rhs) {
    copy_data(rhs);
}

template<typename T>
Deque<T>::Deque(std::initializer_list<T> init_list) {
    for (const auto& elem : init_list) {
        push_back(elem);
    }
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque& rhs) {
    if (this != &rhs) {
        copy_data(rhs);
    }

    return *this;
}

template<typename T>
Deque<T>::Deque(Deque&& rhs) noexcept {
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    m_size = rhs.m_size;

    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque&& rhs) noexcept {
    if (this != &rhs) {
        clean_up();

        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        m_size = rhs.m_size;

        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
        rhs.m_size = 0;
    }

    return *this;
}

template<typename T>
Deque<T>::~Deque() {
    clean_up();
}

template<typename T>
bool Deque<T>::empty() const {
    return m_size == 0;
}

template<typename T>
std::size_t Deque<T>::size() const {
    return m_size;
}

template<typename T>
void Deque<T>::init_first_element(const T& elem) {
    m_head = new Node{elem, nullptr, nullptr};
    m_tail = m_head;
    m_size = 1;
}

template<typename T>
void Deque<T>::clean_up() {
    Node_ptr ptr = nullptr;

    while (m_head != nullptr) {
        ptr = m_head->next;
        delete m_head;
        m_head = ptr;
    }

    m_tail = m_head;
    m_size = 0;
}

template<typename T>
void Deque<T>::copy_data(const Deque& rhs) {
    for (Node_ptr ptr = rhs.m_head; ptr != nullptr; ptr = ptr->next) {
        push_back(ptr->data);
    }
}

template<typename T>
void Deque<T>::push_back(const T& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_tail->next = new Node{elem, m_tail, nullptr};
    m_tail = m_tail->next;
    ++m_size;
}

template<typename T>
void Deque<T>::push_front(const T& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_head->prev = new Node{elem, nullptr, m_head};
    m_head = m_head->prev;
    ++m_size;
}

template<typename T>
T& Deque<T>::back() const {
    return m_tail->data;
}

template<typename T>
T& Deque<T>::front() const {
    return m_head->data;
}

template<typename T>
void Deque<T>::pop_back() {
    if (size() <= 1) {
        clean_up();
        return;
    }

    m_tail = m_tail->prev;
    delete m_tail->next;
    m_tail->next = nullptr;
    --m_size;
}

template<typename T>
void Deque<T>::pop_front() {
    if (size() <= 1) {
        clean_up();
        return;
    }

    m_head = m_head->next;
    delete m_head->prev;
    m_head->prev = nullptr;
    --m_size;
}

#endif // _CORE_DEQUE_HPP_
