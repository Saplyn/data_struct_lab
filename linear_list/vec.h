#pragma once

#include <cstring>

namespace lyn {

template<typename T>
class Vec {
private:
    T* head_loc;
    std::size_t vec_size;
    std::size_t capacity;

private:
    void expand() {
        T* new_head_loc = new T[this->capacity * 2];
        std::memcpy(new_head_loc, this->head_loc, sizeof(T) * this->capacity);
        delete[] this->head_loc;
        this->head_loc = new_head_loc;
        this->capacity *= 2;
    }

public:
    Vec() {
        this->capacity = 16;
        this->vec_size = 0;
        this->head_loc = new T[this->capacity];
    }
    Vec(std::size_t capacity) {
        this->capacity = capacity;
        this->vec_size = 0;
        this->head_loc = new T[this->capacity];
    }
    ~Vec() {
        delete[] this->head_loc;
    }

//~ Copy, Move & Assign
    Vec(const Vec& that) {
        this->capacity = that.capacity;
        this->vec_size = that.vec_size;
        this->head_loc = new T[this->capacity];
        std::memcpy(this->head_loc, that.head_loc, sizeof(T) * this->vec_size);
    }
    Vec(Vec&& that) {
        this->capacity = that.capacity;
        this->vec_size = that.vec_size;
        this->head_loc = that.head_loc;
        that.head_loc = nullptr;
    }
    Vec<T> operator=(const Vec& that) { // on assign: copy (overwrite)
        if (this != &that) {
            delete[] this->head_loc;
            this->capacity = that.capacity;
            this->vec_size = that.vec_size;
            this->head_loc = new T[this->capacity];
            std::memcpy(this->head_loc, that.head_loc, sizeof(T) * this->vec_size);
        }
        return *this;
    }

//~ Public Interface
    void push_back(T val) {
        if (this->vec_size == this->capacity) {
            this->expand();
        }
        this->head_loc[this->vec_size++] = val;
    }
    void remove_all(bool (*predicate)(const T&)) {
        for (int i = 0; i < this->vec_size; i++) {
            if (predicate(this->head_loc[i])) {
                std::swap(this->head_loc[i], this->head_loc[--this->vec_size]);
            }
        }
    }
    Vec<T> find_all(bool (*predicate)(const T&)) {
        Vec<T> res;
        for (int i = 0; i < this->vec_size; i++) {
            if (predicate(this->head_loc[i])) {
                res.push_back(this->head_loc[i]);
            }
        }
        return res;
    }
    void map_self(void (*fn)(T&)) {
        for (int i = 0; i < this->vec_size; i++) {
            fn(this->head_loc[i]);
        }
    }

//~ Iterator Implementation
public:
    class Iter {
    private:
        T* ptr;

    public:
        Iter(T* ptr) : ptr(ptr) {}

        T& operator*() { return *this->ptr; }
        Iter& operator++() { this->ptr++; return *this; }
        Iter operator++(int) { Iter temp = *this; this->ptr++; return temp; }
        bool operator==(const Iter& that) { return this->ptr == that.ptr; }
        bool operator!=(const Iter& that) { return !(*this == that); }
    };
    Iter begin() { return Iter(this->head_loc); }
    Iter end() { return Iter(this->head_loc + this->vec_size); }
};

}
