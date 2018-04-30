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
        iterator() : node_(0) {}  //default constructor

        iterator(const iterator& it) : node_(it.node_) {}  //copy constructor

        iterator& operator=(const iterator& it) {  //operator = overload
            this->node_ = it.node_;
            return *this;
        }

        bool operator==(const iterator& other) const {  //operator == overload
            return this->node_ == other.node_;  //if nodes are equal return true;
        }

        bool operator!=(const iterator& other) const {  //operator != overload;
            return !(operator==(other));
        }

        T& operator*() {  //operator* overload
            if(node_) {  //if node is not empty
                return node_->data_;  //return node date reference
            } else
                throw std::logic_error("The node is empty");
        }

        iterator operator++(int i) {  //postfix operator++ overload
            iterator it(*this);
            ++(*this);
            return it;
        }

        iterator operator++() {  //prefix operator++ overload
            if (node_) {  //if node is not empty
                node_ = node_->next_;  //move to the next node
                return *this;  //return iterator
            } else
                throw std::length_error("The list is empty");
        }
    private:
        iterator(Node* node) :  node_(node) {}

    private:
        Node* node_;
    };
public:
    CycleList() : head_(NULL_PTR), tail_(NULL_PTR), length_(0) {}  //Default constructor
    ~CycleList() {  //Destructor
        clear();
    }

    bool is_empty() const { return head_ == NULL_PTR; }  //checks, if CycleList is empty

    void clear() {
        while(!is_empty())  //deleting elements, while list is not empty
            pop_front();
    }

    CycleList<T>& push_front(const T &a) {  //push to head
        if(is_empty())  //check if list is not empty
            return first_push(a);  //if empty, call special first_push function
        if(Node* newhead = new Node(a))  //else try to make new node
        {
            newhead->next_ = head_;  //in case of success, make it head
            head_ = newhead;
            tail_->next_ = newhead;  //redefine tail pointer to new head
            ++length_;      // increase length
            return *this;
        } else
            throw std::bad_alloc();
    }

    void pop_front() {  //delete head element
        if(!is_empty()) {  //check if head is not empty
            Node *newhead = head_->next_;
            delete head_;
            if (head_ == newhead) {  //check if there was only one element in the list
                head_ = NULL_PTR;   //if true, make head and tail zero values
                tail_ = NULL_PTR;
            } else {
                head_ = newhead;
                tail_->next_ = newhead;
            }
            --length_;  //in case of success, decreasing length of the list
        } else
            throw std::length_error("The list is empty");
    }

    iterator erase(iterator it) {
        if (it == iterator(0))  //check if iterator is valid;
            throw std::logic_error("Invalid iterator");
        if (is_empty())  //check if list is not empty
            throw std::length_error("The list is empty");

        if(it == begin()) {  //in case of deleting the first element
            pop_front();  //delete first element, the length decreases automatically
            return iterator(head_);  //return iterator pointing to the next element
        }

        --length_;  //decreasing length

        iterator previous = begin();
        for(; previous.node_->next_ != it.node_; ++previous);  //get iterator to the element, preceding the current

        if(it.node_ == tail_) {  //in case of deleting the last element (tail)
            Node* next = it.node_->next_;  //remember the pointer to the next element, following the current
            delete it.node_;  //delete the current
            previous.node_->next_ = next;  //assign to previous the next
            tail_ = previous.node_; //make the previous tail
            return iterator(next);  //return iterator to the next element
        }


        Node* next = it.node_->next_;  //remember the pointer to the next element, following the current
        delete it.node_;  //delete the current
        previous.node_->next_ = next;
        return iterator(next);
    }

    iterator begin() const {
        return iterator(head_);
    }

    int length() const {  //get length
        return length_;
    }

private:
    CycleList<T>& first_push(const T &a) {
        if(Node* first = new Node(a))  //try to make new node
        {                               //in case of success
            head_ = first;              //make first head
            tail_ = first;              //make first tail
            head_->next_ = head_;       //assign head->next pointer to the next element (in this case next element = head)
            tail_->next_ = head_;       //assign tail->next pointer to the head
            ++length_;                  //increase length
            return *this;
        } else
            throw std::bad_alloc();
    }

private:
    struct Node {   //struct node definition
        Node() : data_(T()), next_(NULL_PTR) {}  //default constructor
        Node(const T &a) : data_(a), next_(NULL_PTR){}
        T data_;
        Node* next_;
    };
    Node* head_;  //pointer to the head node
    Node* tail_;  //pointer to the tail node
    size_t  length_;  //length of the list

};


#endif //PRACTICE_TASK_1_CLASSES_FLIST_H
