#ifndef WORK2_VECTOR_H
#define WORK2_VECTOR_H

#include <iostream>

template<typename T>
class Vector {
    void addMemory() {
        capacity_ = capacity_ * 2 + 1;
        T *tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
        delete[] tmp;
    }

    T *arr_;
    size_t size_{};
    size_t capacity_{};

public:
    Vector() {
        arr_ = new T[1];
        capacity_ = 1;
    }

    ~Vector() {
        delete[] arr_;
    }

    [[nodiscard]] bool isEmpty() const {
        return size_ == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    void pushBack(const T &value) {
        if (size_ >= capacity_) addMemory();
        arr_[size_++] = value;
    }

    void popBack() {
        if (size_) {
            arr_[size_ - 1].~T();
            --size_;
        }
    }

    void clear() {
        while (size_)
            popBack();
    }

    const T *begin() const {
        return &arr_[0];
    }

    const T *end() const {
        return &arr_[size_];
    }

    const T *data() { return arr_; }
};



#endif
