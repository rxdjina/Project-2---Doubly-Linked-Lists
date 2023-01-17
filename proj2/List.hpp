#include <iostream>
#include "List.h"

using namespace cop4530;

// const_iterator class
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} {
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) {
    current = p;
}

template <typename T>
const T & List<T>::const_iterator::operator*() const {
    return retrieve();
}

template <typename T>
const T * List<T>::const_iterator::operator->() const {
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    List<T>::const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    List<T>::const_iterator old = *this;
    --(*this);
    return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const {
    return (current == rhs.current);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(*this == rhs);
}

template <typename T>
T & List<T>::const_iterator::retrieve() const {
    return current->data;
}

// iterator class
template <typename T>
List<T>::iterator::iterator() {
}

template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p} {
}

template <typename T>
T & List<T>::iterator::operator*() {
    return List<T>::const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const {
    return List<T>::const_iterator::operator*();
}

template <typename T>
T* List<T>::iterator::operator->() {
    return List<T>::const_iterator::operator->();
}

template <typename T>
const T* List<T>::iterator::operator->() const {
    this->current = this->current->next;
    return *this->data;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    List<T>::iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    List<T>::iterator old = *this;
    --(*this);
    return old;
}

// List class
template <typename T>
List<T>::List() {
    init();
}

template <typename T>
List<T>::List(const List &rhs) {
    init();

    for (auto &x : rhs) {
        push_back(x);
    }
}

template <typename T>
List<T>::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>
List<T>::List(int num, const T& val) {
    init();

    for (int i = 0; i < num; i++) {
        push_back(val);
    }
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
    init();

    while (start != end) {
        push_back(start.current->data);
        start++;
    }
}

template <typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
}

template <typename T>
void List<T>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;

    head->next = tail;
    tail->prev = head;
}

template <typename T>
const List<T> & List<T>::List::operator=(const List &rhs) {
    List copy = rhs;
    std::swap(*this, copy);

    return *this;
}

template <typename T>
List<T> & List<T>::List::operator=(List && rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    
    return *this;
}

template <typename T>
int List<T>::size() const {
    return theSize;
}

template <typename T>
bool List<T>::empty() const {
    return size() == 0; 
}

template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void List<T>::reverse() {
    if (head == NULL) {
        return;
    }

    Node *temp = head;
    head = tail;
    tail = temp;

    Node *temp2 = head;
    while (temp2 != NULL) {
        temp = temp2->prev;
        temp2->prev = temp2->next;
        temp2->next = temp;
        temp2 = temp2->next;
    }
}

template <typename T>
T & List<T>::front() {
    return *begin(); 
}

template <typename T>
const T & List<T>::front() const {
    return *begin();
}

template <typename T>
T & List<T>::back() {
    return *(--end());;
}

template <typename T>
const T & List<T>::back() const {
    return *(--end());
}

template <typename T>
void List<T>::push_front(const T & val) {
    insert(begin(), val); 
}

template <typename T>
void List<T>::push_front(T && val) {
    insert(begin(), std::move(val));  
}

template <typename T>
void List<T>::push_back(const T & val) {
    insert(end(), val); 
}

template <typename T>
void List<T>::push_back(T && val) {
    insert(end(), std::move(val)); 
}

template <typename T>
void List<T>::pop_front() {
    erase(begin()); 
}

template <typename T>
void List<T>::pop_back() {
    erase(--end()); 
}

template <typename T>
void List<T>::remove(const T &val) { 
    for (auto itr = begin(); itr != end(); itr++) {
        if (itr.current->data == val) {
            erase(itr);
        }
    }
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
    for ( auto itr = begin(); itr != end(); ++itr) {
		os << *itr << ofc; 
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head->next); 
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(tail); 
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(tail); 
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T &val) {
    Node *p = itr.current;
    theSize++;

    return iterator(p->prev = p->prev->next = new Node{ val, p->prev, p }); 
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) {
    Node *p = itr.current;
    theSize++;

    return iterator(p->prev = p->prev->next = new Node{ std::move(val), p->prev, p });
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
    Node *p = itr.current;

    iterator retVal( p->next );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    
    return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
    for(iterator itr = start; itr != end;) {
        itr = erase(itr);
    }

    return end;
}

// Overloading Comparison Operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
    if (lhs.size() == rhs.size()) {
        for (auto &itr : lhs) {
            for (auto &iter : rhs) {
                if (itr != iter) {
                    return false;
                }
            }
        }
        return true;

    } else {
        return false;
    }
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
    return (!(lhs == rhs));
}

// Overloading Ouput Operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
    l.print(os);
    return os;
}
