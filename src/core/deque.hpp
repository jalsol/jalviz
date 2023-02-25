#ifndef _CORE_DEQUE_HPP_
#define _CORE_DEQUE_HPP_

#include <memory>
#include <cstddef>

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
    void remove_only_element();
public:
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
void Deque<T>::remove_only_element() {
    delete m_head;
    m_head = nullptr;
    m_tail = nullptr;
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
        remove_only_element();
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
        remove_only_element();
        return;
    }

    m_head = m_head->next;
    delete m_head->prev;
    m_head->prev = nullptr;
    --m_size;
}

#endif // _CORE_DEQUE_HPP_
