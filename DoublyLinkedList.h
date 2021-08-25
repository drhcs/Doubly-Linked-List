#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#define NULL 0

template<class T>
struct Node {

    T val_;
    Node * next_;
    Node * prev_;

    explicit Node(T val) {
        val_ = val;
        next_ = nullptr;
        prev_ = nullptr;
    }

    Node(T val, Node * next, Node * prev) {
        val_ = val;
        next_ = next;
        prev_ = prev;
    }
};

template <class T>
class DoublyLinkedList {

    Node<T> * head_;
    Node<T> * tail_;
    int size_;

    void DeleteRecursively(Node<T> * head) {
        if (head == nullptr)
        {
            return;
        }

        DeleteRecursively(head->next_);

        delete head;
    }

public:

    DoublyLinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    ~DoublyLinkedList() {
        Clear();
    }

    Node<T> * InsertFront(T val) {
        if (Empty())
        {
            head_ = new Node<T>(val);
            tail_ = head_;
        }
        else
        {
            head_->prev_ = new Node<T>(val, head_, nullptr);
            head_ = head_->prev_;
        }
        size_++;
        return head_;
    }

    Node<T> * InsertBack(T val) {
        if (Empty())
        {
            tail_ = new Node<T>(val);
            head_ = tail_;
        }
        else
        {
            tail_->next_ = new Node<T>(val, nullptr, tail_);
            tail_ = tail_->next_;
        }
        size_++;
        return tail_;
    }

    T RemoveFront() {
        if (Empty())
        {
            return NULL;
        }

        Node<T> * to_remove = head_;
        T val = head_->val_;

        head_ = head_->next_;
        if (size_ == 1)
        {
            tail_ = nullptr;
        }
        else
        {
            head_->prev_ = nullptr;
        }
        size_--;

        delete to_remove;
        return val;
    }

    T RemoveBack() {
        if (Empty())
        {
            return NULL;
        }

        Node<T> * to_remove = tail_;
        T val = tail_->val_;

        tail_ = tail_->prev_;
        if (size_ == 1)
        {
            head_ = nullptr;
        }
        else
        {
            tail_->next_ = nullptr;
        }
        size_--;

        delete to_remove;
        return val;
    }

    T Remove(T val) {
        Node<T> * to_remove = Find(val);
        if (Empty() || !to_remove)
        {
            return NULL;
        }

        if (val == head_->val_)
        {
            return RemoveFront();
        }
        else if (val == tail_->val_)
        {
            return RemoveBack();
        }
        else
        {
            to_remove->prev_->next_ = to_remove->next_;
            to_remove->next_->prev_ = to_remove->prev_;
            delete to_remove;

            size_--;
            return val;
        }
    }

    Node<T> * Find(T val) {
        Node<T> * itr = head_;
        while (itr != nullptr && itr->val_ != val)
        {
            itr = itr->next_;
        }
        return itr;
    }

    Node<T> * Head() {
        return head_;
    }

    Node<T> * Tail() {
        return tail_;
    }

    int Size() {
        return size_;
    }

    bool Empty() {
        return size_ == 0;
    }

    void Clear() {
        DeleteRecursively(head_);
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

};

#endif
