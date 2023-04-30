#ifndef CORE_BASE_LIST_HPP_
#define CORE_BASE_LIST_HPP_

#include <cstddef>
#include <initializer_list>
#include <memory>

namespace core {

/**
 * @brief The base container for implementing other data structures
 * @tparam T the type of the elements
 */

template<typename T>
class BaseList {
public:
    /**
     * @brief Default constructor
     */
    BaseList() = default;

    /**
     * @brief Constructs the container with the contents of the initializer list
     * @param init_list The initializer list
     */
    BaseList(std::initializer_list<T> init_list);

    /**
     * @brief Copy constructor
     * @param rhs The other container
     */
    BaseList(const BaseList& rhs);

    /**
     * @brief Copy assignment operator
     * @param rhs The other container
     */
    BaseList& operator=(const BaseList& rhs);

    /**
     * @brief Move constructor
     * @param rhs The other container
     */
    BaseList(BaseList&& rhs) noexcept;

    /**
     * @brief Move assignment operator
     * @param rhs The other container
     */
    BaseList& operator=(BaseList&& rhs) noexcept;

    /**
     * @brief Destructor
     */
    ~BaseList();

    /**
     * @brief Check whether the container is empty
     * @retval true The container is empty
     * @retval false The container is not empty
     */
    [[nodiscard]] bool empty() const;

    /**
     * @brief Returns the size of the container
     * @return The size of the container
     */
    [[nodiscard]] std::size_t size() const;

protected:
    struct Node;  // Forward declaration
    using Node_ptr = Node*;

    /**
     * @brief The node of the list
     */
    struct Node {
        T data{};
        Node_ptr prev{};
        Node_ptr next{};
    };

    /**
     * @brief The head of the list
     */
    Node_ptr m_head{nullptr};

    /**
     * @brief The tail of the list
     */
    Node_ptr m_tail{nullptr};

    /**
     * @brief The size of the list
     */
    std::size_t m_size{};

    /**
     * @brief Initializes the first element of the container
     * @param elem The first element of the container
     */
    void init_first_element(const T& elem);

    /**
     * @brief Frees all elements in the container
     *
     */
    void clean_up();

    /**
     * @brief Copies data from another container
     *
     * @param rhs Tnother container
     */
    void copy_data(const BaseList& rhs);

    /**
     * @brief Pushes the element to the back of the container
     * @param elem The element to be pushed into the back
     */
    void push_back(const T& elem);

    /**
     * @brief Pushes the element to the front of the container
     * @param elem The element to be pushed into the front
     */
    void push_front(const T& elem);

    /**
     * @brief Returns the reference to the element at the back of the container
     * @return T& The reference to the element at the back of the container
     */
    T& back() const;

    /**
     * @brief Returns the reference to the element at the front of the container
     * @return T& The reference to the element at the front of the container
     */
    T& front() const;

    /**
     * @brief Removes the element at the back of the container
     */
    void pop_front();

    /**
     * @brief Removes the element at the front of the container
     */
    void pop_back();
};

template<typename T>
BaseList<T>::BaseList(const BaseList& rhs) {
    copy_data(rhs);
}

template<typename T>
BaseList<T>::BaseList(std::initializer_list<T> init_list) {
    for (const auto& elem : init_list) {
        push_back(elem);
    }
}

template<typename T>
BaseList<T>& BaseList<T>::operator=(const BaseList& rhs) {
    if (this != &rhs) {
        copy_data(rhs);
    }

    return *this;
}

template<typename T>
BaseList<T>::BaseList(BaseList&& rhs) noexcept
    : m_head{rhs.m_head}, m_tail{rhs.m_tail}, m_size{rhs.m_size} {
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
}

template<typename T>
BaseList<T>& BaseList<T>::operator=(BaseList&& rhs) noexcept {
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
BaseList<T>::~BaseList() {
    clean_up();
}

template<typename T>
bool BaseList<T>::empty() const {
    return m_size == 0;
}

template<typename T>
std::size_t BaseList<T>::size() const {
    return m_size;
}

template<typename T>
void BaseList<T>::init_first_element(const T& elem) {
    m_head = new Node{elem, nullptr, nullptr};
    m_tail = m_head;
    m_size = 1;
}

template<typename T>
void BaseList<T>::clean_up() {
    Node_ptr ptr{nullptr};

    while (m_head != nullptr) {
        ptr = m_head->next;
        delete m_head;
        m_head = ptr;
    }

    m_tail = m_head;
    m_size = 0;
}

template<typename T>
void BaseList<T>::copy_data(const BaseList& rhs) {
    for (Node_ptr ptr = rhs.m_head; ptr != nullptr; ptr = ptr->next) {
        push_back(ptr->data);
    }
}

template<typename T>
void BaseList<T>::push_back(const T& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_tail->next = new Node{elem, m_tail, nullptr};
    m_tail = m_tail->next;
    ++m_size;
}

template<typename T>
void BaseList<T>::push_front(const T& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_head->prev = new Node{elem, nullptr, m_head};
    m_head = m_head->prev;
    ++m_size;
}

template<typename T>
T& BaseList<T>::back() const {
    return m_tail->data;
}

template<typename T>
T& BaseList<T>::front() const {
    return m_head->data;
}

template<typename T>
void BaseList<T>::pop_back() {
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
void BaseList<T>::pop_front() {
    if (size() <= 1) {
        clean_up();
        return;
    }

    m_head = m_head->next;
    delete m_head->prev;
    m_head->prev = nullptr;
    --m_size;
}

}  // namespace core

#endif  // CORE_BASE_LIST_HPP_
