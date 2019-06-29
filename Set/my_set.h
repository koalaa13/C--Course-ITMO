//
// Created by koalaa13 on 6/29/19.
//

#ifndef EXAM_SET_MY_SET_H
#define EXAM_SET_MY_SET_H

#include <iterator>
#include <iostream>

template<typename T>
class my_set {
    struct node_base {
        node_base *left;
        node_base *right;
        node_base *par;

        node_base() noexcept {
            left = nullptr;
            right = nullptr;
            par = nullptr;
        }

        bool is_left() const noexcept {
            return par->left == this;
        }

        bool is_right() const noexcept {
            return par->right == this;
        }
    };

    struct node : node_base {
        T value;

        node(T const &val) : value(val) {}
    };

    node_base fake;

    template<typename U>
    class my_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        node_base *data;
        friend my_set;

        explicit my_iterator(node_base *new_data) : data(new_data) {}

    public:
        my_iterator() = default;

        my_iterator(my_iterator<T> const &other) : data(other.data) {};

        my_iterator &operator=(my_iterator const &other) = default;

        U &operator*() const {
            return static_cast<node * >(data)->value;
        }

        U *operator->() const {
            return &static_cast<node *>(data)->value;
        }

        my_iterator &operator++() {
            node_base *cur = data;
            if (data->right != nullptr) {
                cur = data->right;
                while (cur->left != nullptr) {
                    cur = cur->left;
                }
            } else {
                if (data->is_left()) {
                    if (cur->par != nullptr) {
                        cur = cur->par;
                    }
                } else {
                    while (cur->par != nullptr && cur->is_right()) {
                        cur = cur->par;
                    }
                    if (cur->par != nullptr) {
                        cur = cur->par;
                    }
                }
            }
            data = cur;
            return *this;
        }

        my_iterator operator++(int) {
            my_iterator copy = *this;
            ++(*this);
            return copy;
        }

        my_iterator &operator--() {
            node_base *cur = data;
            if (data->left != nullptr) {
                cur = data->left;
                while (cur->right != nullptr) {
                    cur = cur->right;
                }
            } else {
                if (data->is_right()) {
                    if (cur->par != nullptr) {
                        cur = cur->par;
                    }
                } else {
                    while (cur->par != nullptr && cur->is_left()) {
                        cur = cur->par;
                    }
                    if (cur->par != nullptr) {
                        cur = cur->par;
                    }
                }
            }
            data = cur;
            return *this;
        }

        my_iterator operator--(int) {
            my_iterator copy = *this;
            --(*this);
            return copy;
        }

        friend bool operator==(my_iterator const &a, my_iterator const &other) noexcept {
            return a.data == other.data;
        }

        friend bool operator!=(my_iterator const &a, my_iterator const &other) noexcept {
            return a.data != other.data;
        }
    };

    my_iterator<T const> rec_upper_bound(T const &value, node_base *p) const {
        if (p == nullptr) {
            return end();
        }

        if (static_cast<node *>(p)->value <= value) {
            return rec_upper_bound(value, p->right);
        } else {
            my_iterator<T const> res = rec_upper_bound(value, p->left);
            if (res == end()) {
                return my_iterator<T const>(p);
            } else {
                return res;
            }
        }
    }

public:

    typedef T value_type;
    typedef my_iterator<T const> iterator;
    typedef my_iterator<T const> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    my_set() noexcept : fake() {}

    my_set(my_set const &other) : fake() {
        my_set copy;
        for (T const &i : other) {
            copy.insert(i);
        }
        swap(copy, *this);
    }

    iterator begin() noexcept {
        node_base *cur = &fake;
        while (cur->left != nullptr) {
            cur = cur->left;
        }
        return iterator(cur);
    }

    const_iterator begin() const noexcept {
        node_base *cur = const_cast<node_base *>(&fake);
        while (cur->left != nullptr) {
            cur = cur->left;
        }
        return const_iterator(cur);
    }

    iterator end() noexcept {
        return iterator(&fake);
    }

    const_iterator end() const noexcept {
        return const_iterator(const_cast<node_base *>(&fake));
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_iterator find(T const &elem) const noexcept {
        node_base *cur = fake.left;
        while (cur != nullptr) {
            if (static_cast<node *>(cur)->value == elem) {
                return const_iterator(cur);
            }
            if (static_cast<node *>(cur)->value < elem) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return end();
    }

    my_set<T> &operator=(my_set<T> const &other) {
        if (this == &other) {
            return *this;
        }
        my_set<T> copy(other);
        swap(*this, copy);
        return *this;
    }

    std::pair<iterator, bool> insert(T const &elem) {
        // std::cerr << "insert " << elem << '\n';
        iterator it = find(elem);
        if (it != end()) {
            return std::make_pair(it, false);
        }
        bool lr = false; // l = 0, r = 1
        node_base *last = &fake;
        node_base *cur = fake.left;
        while (cur != nullptr) {
            last = cur;
            if (static_cast<node *>(cur)->value < elem) {
                cur = cur->right;
                lr = true;
            } else {
                cur = cur->left;
                lr = false;
            }
        }
        node *new_node = new node(elem);
        new_node->par = last;
        if (lr) {
            last->right = new_node;
        } else {
            last->left = new_node;
        }
        return std::make_pair(iterator(static_cast<node_base *>(new_node)), true);
    }

    bool empty() const noexcept {
        return fake.left == nullptr;
    }

    template<typename U>
    friend void swap(my_set<U> &a, my_set<U> &b);

    const_iterator lower_bound(T const &elem) const {
        const_iterator it = find(elem);
        if (it != end()) {
            return it;
        }
        return upper_bound(elem);
    }

    const_iterator upper_bound(T const &elem) const {
        return rec_upper_bound(elem, fake.left);
    }

    iterator erase(const_iterator pos) noexcept {
        // std::cerr << "erase " << *pos << '\n';
        node_base *cur = pos.data;
        pos++;
        if (cur->left == nullptr && cur->right == nullptr) {
            if (cur->is_left()) {
                cur->par->left = nullptr;
            } else {
                cur->par->right = nullptr;
            }
            delete static_cast<node *>(cur);
        } else {
            if (cur->left == nullptr && cur->right != nullptr) {
                if (cur->is_left()) {
                    cur->par->left = cur->right;
                } else {
                    cur->par->right = cur->right;
                }
                cur->right->par = cur->par;
                delete static_cast<node *>(cur);
            } else {
                if (cur->left != nullptr && cur->right == nullptr) {
                    if (cur->is_left()) {
                        cur->par->left = cur->left;
                    } else {
                        cur->par->right = cur->left;
                    }
                    cur->left->par = cur->par;
                    delete static_cast<node *>(cur);
                } else {
                    node_base *mn = cur->right;
                    while (mn->left != nullptr) {
                        mn = mn->left;
                    }
                    if (cur->right == mn) {
                        if (cur->is_left()) {
                            cur->par->left = mn;
                        } else {
                            cur->par->right = mn;
                        }
                        mn->par = cur->par;
                        mn->left = cur->left;
                        cur->left->par = mn;
                    } else {
                        if (cur->is_left()) {
                            cur->par->left = mn;
                        } else {
                            cur->par->right = mn;
                        }
                        if (mn->is_left()) {
                            mn->par->left = mn->right;
                        } else {
                            mn->par->right = mn->right;
                        }
                        if (mn->right != nullptr) {
                            mn->right->par = mn->par;
                        }
                        mn->par = cur->par;
                        mn->left = cur->left;
                        cur->left->par = mn;
                        mn->right = cur->right;
                        cur->right->par = mn;
                    }
                    delete static_cast<node *>(cur);
                }
            }
        }
        return pos;
    }

    void clear() noexcept {
        while (!empty()) {
            // std::cerr << "clearing\n";
            erase(begin());
        }
    }

    ~my_set() {
        clear();
    }
};

template<typename U>
void swap(my_set<U> &a, my_set<U> &b) {
    if (!a.empty() && !b.empty()) {
        std::swap(a.fake.left, b.fake.left);
        std::swap(a.fake.left->par, b.fake.left->par);
    } else {
        if (a.empty() && !b.empty()) {
            a.fake.left = b.fake.left;
            b.fake.left->par = &a.fake;
            b.fake.left = nullptr;
        } else {
            if (!a.empty() && b.empty()) {
                b.fake.left = a.fake.left;
                a.fake.left->par = &b.fake;
                a.fake.left = nullptr;
            }
        }
    }
}

#endif //EXAM_SET_MY_SET_H
