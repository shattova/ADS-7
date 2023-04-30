// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;

 private:
    struct Item {
        T data;
        Item* next;
        Item* prev;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);
};

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}

template <typename T>
void TPQueue<T>::push(const T& it) {
    if (head == nullptr) {
       head = create(it);
       tail = head;
    } else if (tail->data.prior >= it.prior) {
        if (tail->data.ch == it.ch) {
            tail->data = it;
        } else {
            tail->next = create(it);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = create(it);
        head = tail->prev;
        head->next = tail;
    } else {
        Item* temp = tail;
        while (temp != head && temp->data.prior < it.prior) {
        temp = temp->prev;
        }
        if (temp->data.prior > it.prior) {
            Item* cage = new Item;
            cage->next = temp->next;
            cage->prev = temp;
            cage->data = it;
            temp->next->prev = cage;
            temp->next = cage;
        }
        if (temp == head && temp->data.prior < it.prior) {
            head->prev = create(it);
            head = head->prev;
            head->next = temp;
        }
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Empty!");
    } else {
        Item* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
