#include <iostream>
#include "List.h"
#include "Memory.h"

// MyMemoryBlock Class
MyMemoryBlock::MyMemoryBlock(int ind, int len) {
    index = ind;
    length = len;
}

int MyMemoryBlock::get_length() {
    return length;
}

int MyMemoryBlock::get_index() {
    return index;
}

int MyMemoryBlock::allocate_mem(int len) {
    if (len > length) {
        return -1;
    } else if (len <= length) {
        length -= len;
        return len;
    }
}

void MyMemoryBlock::free_mem(int len) {
    length += len;
}

// Memory Block Class
template <typename T>
MyMemory<T>::MyMemory::MyMemory(int num, int len) {
    for (int i = 0; i < num; i++) {
        mlist.push_back(len);
    }

    MyMemoryBlock::allocate_mem(len);
    resize(num - 1, len);
}

template <typename T>
MyMemory<T>::MyMemory::~MyMemory() {
    clear();
}
template <typename T>
void MyMemory<T>::MyMemory::resize(int num, int len) {
    if (length > 0) {
        
    } 

    max_index = num;
    block_size = len;
}

template <typename T>
int MyMemory<T>::MyMemory::req_mem(int len) {
    for (auto itr = mlist.begin(); itr != mlist.end(); itr++) {
        if (itr.current->data == len) {
            allocate_mem(len);

            if (itr.current->data < 1) {
                mlist.erase(itr);
            }

            return itr.current->data;
        }
    }

    return -1;
}

template <typename T>
bool MyMemory<T>::MyMemory::release_mem(int ind, int len) {
    for (auto itr = mlist.begin(); itr != mlist.end(); itr++) {
        if (itr.current->data == len) {
            free_mem(len);
        }
    }

    for (int i = 0; i < len; i++) {
        mlist.insert(mlist.begin(), ind);
    }
    
    bool valid_index = (ind >=0) && (ind <= max_index);
    bool valid_length = (len >=0) && (ind <= len);

    if (valid_index && valid_length) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
void MyMemory<T>:: MyMemory::merge_mem() {
    auto itr = mlist.begin();

    int i = itr.current->data;
    int j = itr.next->data;

    for (itr != mlist.end(); itr++) {
        if (i + j <= block_size) {
            i += j;
            itr.next = itr.erase(itr);
        } else {
            idx = itr.current->data;
            len = 0;
        }

        i = itr.current->data;
        j = itr.next->data;
    }
}

template <typename T>
void MyMemory<T>::MyMemory::dump() {
    mlist.print();
}