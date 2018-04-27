//
// Created by dmitr on 4/23/2018.
//

#ifndef PRACTICE_TASK_1_CLASSES_FLIST_H
#define PRACTICE_TASK_1_CLASSES_FLIST_H


#include <exception>
#include <stdexcept>
#define NULL_PTR 0
template <class T>
class CycleList {
private:
    struct Node;
public:
    class iterator {  //iterator Interface
        friend class CycleList;
    public:
        iterator(const iterator& it) : node_(it.node_) {}

        iterator& operator=(const iterator& it) {
            this->node_ = it.node_;
        }

        bool operator==(const iterator& other) const {
            if(this == &other)
                return true;
            return this->node_ == other.node_;
        }

        bool operator!=(const iterator& other) const {
            return !(operator==(other));
        }

        T& operator*() {
            if(node_) {
                return node_->data_;
            } else
                throw std::length_error("The list is empty");
        }

        iterator operator++(int i) {
            iterator it(*this);
            ++(*this);
            return it;
        }

        iterator operator++() {
            if(node_) {
                if (node_ == node_->next_)
                {
                    node_ = 0;
                    return iterator(0);
                }
                if (start_ == 0) {
                    start_ = node_;
                    node_ = node_->next_;
                }
                else {
                    if (start_ == node_->next_) {
                        node_ = 0;
                        return iterator(0);
                    } else  {
                        node_ = node_->next_;
                    }
                }
            }
            return *this;
        }
    private:
        iterator(Node* node) :  node_(node), start_(0) {}

    private:
        Node* start_;
        Node* node_;
    };
public:
    CycleList() : head_(NULL_PTR), length_(0) {}  //Default constructor
    ~CycleList() {  //Destructor
        clear();
    }

    bool is_empty() const { return head_ == NULL_PTR; }  //checks, if CycleList is empty

    void clear() {
        if(head_) {
            while(head_->next_ != head_) {
                pop_front();
            }
            delete head_->next_;
            head_ = 0;
            length_ = 0;
        }
    }

    CycleList<T>& push_front(const T &a) {  //push to head
        ++length_;
        if(head_ == 0)
            return first_push(a);
        if(Node* temp = new Node(a))
        {
            temp->next_ = head_;
            head_ = temp;
            return *this;
        } else
            throw std::bad_alloc();
    }

    void pop_front() {  //take from head
        if(head_) {
            Node *newhead = head_->next_;
            delete head_;
            head_ = (head_ == newhead) ? 0 : newhead;
        } else
            throw std::length_error("The list is empty");
    }

    iterator erase(iterator it) {
        if (it == iterator(0)) {
            return it;
        }

        length_--;

        if(it == begin()) {
            pop_front();
            return iterator(head_);
        }

        iterator i = begin();
        for(; i.node_->next_ != it.node_; ++i);
        Node* next = it.node_->next_;
        delete it.node_;
        i.node_->next_ = next;

        return iterator(next);
    }

    iterator begin() const {
        return iterator(head_);
    }
    iterator last() const {
        return iterator(0);
    }
    int length() const {  //get length
        return length_;
    }

private:
    CycleList<T>& first_push(const T &a) {
        if(Node* first = new Node(a))
        {
            head_ = first;
            head_->next_ = head_;
            return *this;
        } else
            throw std::bad_alloc();
    }

private:
    struct Node {
        Node() : data_(T()), next_(NULL_PTR) {}
        Node(const T &a) : data_(a), next_(NULL_PTR){}
        T data_;
        Node* next_;
    };
    Node* head_;
    size_t  length_;
/*
    Node* tail_;
    int length_;*/
};

/*int main() {
    CycleList<int> a;
    a.push_front(5).push_front(6).push_front(7);
    a.remove(1);
    for(CycleList<int>::iterator i(a.begin()); i != a.last(); i++) {
        std::cout << *i << std::endl;
    }
    return 0;
}*/

#endif //PRACTICE_TASK_1_CLASSES_FLIST_H
