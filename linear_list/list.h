#pragma once

namespace lyn {

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next_loc;
    };

    Node* head_loc;
    std::size_t list_size;

public:
    List() {
        this->head_loc = nullptr;
        this->list_size = 0;
    }
    ~List() {
        Node* curr = this->head_loc;
        while (curr != nullptr) {
            Node* next = curr->next_loc;
            delete curr;
            curr = next;
        }
    }

//~ Copy, Move & Assign
    List(const List& that) {
        this->head_loc = nullptr;
        this->list_size = 0;
        for (T item : that) {
            this->push_back(item);
        }
    }
    List(List&& that) {
        this->head_loc = that.head_loc;
        this->list_size = that.list_size;
        that.head_loc = nullptr;
        that.list_size = 0;
    }
    List<T> operator=(const List& that) { // on assign: copy (overwrite)
        if (this != &that) {
            Node* curr = this->head_loc;
            while (curr != nullptr) {
                Node* next = curr->next_loc;
                delete curr;
                curr = next;
            }
            this->head_loc = nullptr;
            this->list_size = 0;
            for (T item : that) {
                this->push_back(item);
            }
        }
        return *this;
    }

//~ Public Interface
    void push_front(T val) {
        Node* new_node = new Node{val, this->head_loc};
        this->head_loc = new_node;
        this->list_size++;
    }
    template<typename Fn>
    void remove_all(Fn predicate) {
        Node* curr = this->head_loc;
        Node* prev = nullptr;
        while (curr != nullptr) {
            Node* next = curr->next_loc;
            if (predicate(curr->data)) {
                if (prev == nullptr) {
                    this->head_loc = next;
                } else {
                    prev->next_loc = next;
                }
                delete curr;
                this->list_size--;
            } else {
                prev = curr;
            }
            curr = next;
        }
    }
    template<typename Fn>
    List<T> find_all(Fn predicate) {
        List<T> res;
        Node* curr = this->head_loc;
        while (curr != nullptr) {
            if (predicate(curr->data)) {
                res.push_front(curr->data);
            }
            curr = curr->next_loc;
        }
        return res;
    }
    template<typename Fn>
    List<T*> find_all_loc(Fn predicate) {
        List<T*> res;
        Node* curr = this->head_loc;
        while (curr != nullptr) {
            if (predicate(curr->data)) {
                res.push_front(&(curr->data));
            }
            curr = curr->next_loc;
        }
        return res;
    }
    template<typename Fn>
    void map_self(Fn fn) {
        Node* curr = this->head_loc;
        while (curr != nullptr) {
            fn(curr->data);
            curr = curr->next_loc;
        }
    }
    std::size_t size() const { return this->list_size; }

//~ Iterator Implementation
    class Iter {
    private:
        Node* curr;

    public:
        Iter(Node* curr) : curr(curr) {}

        T& operator*() { return this->curr->data; }
        Iter& operator++() { this->curr = this->curr->next_loc; return *this; }
        Iter operator++(int) { Iter result = *this; ++(*this); return result; }
        bool operator==(const Iter& that) { return this->curr == that.curr; }
        bool operator!=(const Iter& that) { return !(*this == that); }
    };
    Iter begin() { return Iter(this->head_loc); }
    Iter end() { return Iter(nullptr); }
};

}
