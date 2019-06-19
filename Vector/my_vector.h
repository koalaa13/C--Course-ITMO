//
// Created by koalaa13 on 6/15/19.
//

#ifndef EXAM_MY_VECTOR_H
#define EXAM_MY_VECTOR_H

#include <iostream>
#include <cstddef>
#include <memory>

template<typename T>
class my_vector {
    union {
        size_t *big_data;
        T small_data;
    };
    bool small;

    size_t &sz() const noexcept {
        return *big_data;
    }

    size_t &cap() const noexcept {
        return *(big_data + 1);
    }

    size_t &refs() const noexcept {
        return *(big_data + 2);
    }

    bool is_big() const noexcept {
        return !small && big_data != nullptr;
    }

    void make_default() noexcept {
        small = false;
        big_data = nullptr;
    }

    void change_cap(size_t new_cap) {
        size_t cur_size = size();
        if (new_cap < 2) {
            if (new_cap == 0 || cur_size == 0) {
                clear_data();
            } else {
                T new_small_data(front());
                clear_data();
                small = true;
                try {
                    new(&small_data) T(new_small_data);
                } catch (...) {
                    make_default();
                    throw;
                }
            }
        } else {
            size_t *new_data = reinterpret_cast<size_t *>(operator new[](3 * sizeof(size_t) + new_cap * sizeof(T)));
            size_t new_size = new_cap < cur_size ? new_cap : cur_size, i = 0;
            try {
                divide();
                *new_data = new_size;
                *(new_data + 1) = new_cap;
                *(new_data + 2) = 1;
                if (small) {
                    new(reinterpret_cast<T *>(new_data + 3)) T(small_data);
                } else {
                    T *p = reinterpret_cast<T *>(new_data + 3);
                    for (; i < new_size; ++i, ++p) {
                        new(p) T((*this)[i]);
                    }
                }
                clear_data();
                big_data = new_data;
            } catch (...) {
                delete_if_exception(new_data, i);
                operator delete[](big_data);
                throw;
            }
        }
    }

    void clear_data() {
        if (small) {
            small_data.~T();
        } else {
            if (big_data != nullptr) {
                if (refs() == 1) {
                    for (size_t i = 0; i < sz(); ++i) {
                        (*this)[i].~T();
                    }
                    operator delete[](big_data);
                } else {
                    refs()--;
                }
            }
        }
        make_default();
    }

    void divide() {
        if (is_big() && refs() > 1) {
            size_t i = 0, cur_sz = sz();
            size_t *new_data = reinterpret_cast<size_t *>(operator new[](3 * sizeof(size_t) + cap() * sizeof(T)));
            *new_data = *big_data;
            *(new_data + 1) = *(big_data + 1);
            *(new_data + 2) = 1;
            try {
                T *p = reinterpret_cast<T *>(big_data + 3);
                for (; i < cur_sz; ++i, ++p) {
                    new(reinterpret_cast<T *>(new_data + 3) + i) T(*p);
                }
            } catch (...) {
                delete_if_exception(new_data, i);
                operator delete[](new_data);
                throw;
            }
            refs()--;
            big_data = new_data;
        }
    }

    template<typename U>
    void swap_big_and_small(my_vector<U> &b) {
        U tmp(small_data);
        small = false;
        big_data = b.big_data;
        small_data.~U();
        b.big_data = nullptr;
        b.small = true;
        new(&b.small_data) U(tmp);
    }

    void delete_if_exception(size_t *p, size_t end) {
        for (size_t j = 0; j < end; ++j) {
            (*(reinterpret_cast<T *>(p + 3) + j)).~T();
        }
    }

public:
    typedef T value_type;
    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<T *> reverse_iterator;
    typedef std::reverse_iterator<T const *> const_reverse_iterator;

    my_vector() noexcept : big_data(nullptr), small(false) {};

    my_vector(my_vector const &other) : small(other.small) {
        if (small) {
            try {
                new(&small_data) T(other.small_data);
            } catch (...) {
                make_default();
                throw;
            }
        } else {
            big_data = other.big_data;
            if (big_data != nullptr) {
                refs()++;
            }
        }
    }

    ~my_vector() {
        clear_data();
    }

    my_vector(size_t new_size, T const &elem) : big_data(nullptr), small(false) {
        if (new_size == 1) {
            small = true;
            try {
                new(&small_data) T(elem);
            } catch (...) {
                make_default();
                throw;
            }
        } else {
            change_cap(new_size);
            for (size_t i = 0; i < new_size; ++i) {
                push_back(elem);
            }
        }
    }

    template<typename InputIterator>
    my_vector(InputIterator first, InputIterator second) : big_data(nullptr), small(false) {
        while (first != second) {
            push_back(*first);
            first++;
        }
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator second) {
        clear_data();
        while (first != second) {
            push_back(*first);
            first++;
        }
    }

    my_vector &operator=(my_vector const &other) {
        clear_data();
        small = other.small;
        if (small) {
            try {
                new(&small_data) T(other.small_data);
            } catch (...) {
                make_default();
                throw;
            }
        } else {
            big_data = other.big_data;
            if (big_data != nullptr) {
                refs()++;
            }
        }
        return *this;
    }

    T const &operator[](size_t ind) const noexcept {
        if (small) {
            return small_data;
        }
        return *(reinterpret_cast<T *>(big_data + 3) + ind);
    }

    T &operator[](size_t ind) {
        if (small) {
            return small_data;
        }
        divide();
        return *(reinterpret_cast<T *>(big_data + 3) + ind);
    }

    size_t size() const noexcept {
        return small ? 1 : big_data == nullptr ? 0 : sz();
    }

    size_t capacity() const noexcept {
        return small ? 1 : big_data == nullptr ? 0 : cap();
    }

    T &front() {
        return (*this)[0];
    }

    T const &front() const noexcept {
        return (*this)[0];
    }

    T &back() {
        return (*this)[size() - 1];
    }

    T const &back() const noexcept {
        return (*this)[size() - 1];
    }

    void reserve(size_t new_cap) {
        if (new_cap <= 1 || (is_big() && cap() >= new_cap)) {
            return;
        }
        change_cap(new_cap);
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    void shrink_to_fit() {
        if (small || big_data == nullptr || cap() == sz()) {
            return;
        }
        change_cap(size());
    }

    void push_back(T const &elem) {
        divide();
        if (!small && big_data == nullptr) {
            small = true;
            try {
                new(&small_data) T(elem);
            } catch (...) {
                make_default();
                throw;
            }
        } else {
            size_t cur_size = size();
            if (small || capacity() == cur_size) {
                reserve(2 * cur_size);
            }
            new(reinterpret_cast<T *>(big_data + 3) + cur_size) T(elem);
            sz()++;
        }
    }

    void resize(size_t new_size, T const &elem) {
        clear_data();
        change_cap(new_size);
        for (size_t i = 0; i < new_size; ++i) {
            push_back(elem);
        }
    }

    void clear() noexcept {
        clear_data();
    }

    void pop_back() {
        if (small || big_data == nullptr) {
            clear_data();
        } else {
            divide();
            (*this).back().~T();
            sz()--;
            if (sz() == 0) {
                clear_data();
            }
        }
    }

    iterator begin() noexcept {
        divide();
        return small ? &small_data : big_data == nullptr ? nullptr : &((*this)[0]);
    }

    iterator end() noexcept {
        divide();
        if (small) {
            iterator res = &small_data;
            return ++res;
        } else {
            return big_data == nullptr ? nullptr : reinterpret_cast<T *>(big_data + 3) + sz();
        }
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_iterator begin() const noexcept {
        return const_iterator(small ? &small_data : big_data == nullptr ? nullptr : &((*this)[0]));
    }

    const_iterator end() const noexcept {
        if (small) {
            const_iterator res = &small_data;
            return ++res;
        } else {
            return const_iterator(big_data == nullptr ? nullptr : reinterpret_cast<T *>(big_data + 3) + sz());
        }
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    T *data() {
        return begin();
    }

    template<typename U>
    friend bool operator==(my_vector<U> const &a, my_vector<U> const &b) noexcept;

    template<typename U>
    friend bool operator<(my_vector<U> const &a, my_vector<U> const &b) noexcept;

    template<typename U>
    friend bool operator!=(my_vector<U> const &a, my_vector<U> const &b) noexcept;


    template<typename U>
    friend bool operator<=(my_vector<U> const &a, my_vector<U> const &b) noexcept;


    template<typename U>
    friend bool operator>(my_vector<U> const &a, my_vector<U> const &b) noexcept;


    template<typename U>
    friend bool operator>=(my_vector<U> const &a, my_vector<U> const &b) noexcept;

    template<typename U>
    friend void swap(my_vector<U> &a, my_vector<U> &b);

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, my_vector<U> const &array) noexcept;

    iterator insert(const_iterator pos, T const &elem) {
        divide();
        size_t ind = 0, i = 0;
        const_iterator cur_pos = begin();
        while (cur_pos != pos) {
            cur_pos++;
            ind++;
        }
        size_t cur_size = size();
        size_t *new_data = reinterpret_cast<size_t *>(operator new[](3 * sizeof(size_t) + (cur_size + 1) * sizeof(T)));
        *new_data = cur_size + 1;
        *(new_data + 1) = cur_size + 1;
        *(new_data + 2) = 1;
        try {
            for (; i < ind; ++i) {
                new(reinterpret_cast<T *>(new_data + 3) + i) T((*this)[i]);
            }
            new(reinterpret_cast<T *>(new_data + 3) + ind) T(elem);
            for (i = ind + 1; i <= cur_size; ++i) {
                new(reinterpret_cast<T *>(new_data + 3) + i) T((*this)[i - 1]);
            }
            clear_data();
            big_data = new_data;
        } catch (...) {
            delete_if_exception(new_data, i);
            operator delete[](new_data);
            throw;
        }
        return begin() + ind;
    }
};

template<typename U>
bool operator==(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

template<typename U>
bool operator<(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

template<typename U>
bool operator!=(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    return !(a == b);
}

template<typename U>
bool operator<=(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    return a == b || a < b;
}

template<typename U>
bool operator>(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    return !(a <= b);
}

template<typename U>
bool operator>=(const my_vector<U> &a, const my_vector<U> &b) noexcept {
    return !(a < b);
}

template<typename U>
void swap(my_vector<U> &a, my_vector<U> &b) {
    if (a.small) {
        if (b.small) {
            std::swap(a.small_data, b.small_data);
        } else {
            a.swap_big_and_small(b);
        }
    } else {
        if (b.small) {
            b.swap_big_and_small(a);
        } else {
            std::swap(a.big_data, b.big_data);
        }
    }

}

template<typename U>
std::ostream &operator<<(std::ostream &os, const my_vector<U> &array) noexcept {
    for (auto i : array) {
        os << i << ' ';
    }
    return os;
}

#endif //EXAM_MY_VECTOR_H
