//
// Created by koalaa13 on 9/14/19.
//

#ifndef MY_UNORDERED_SET_MY_UNORDERED_SET_H
#define MY_UNORDERED_SET_MY_UNORDERED_SET_H

#include <vector>

template<class T>
class my_unordered_set {
    static const size_t START_COUNT_BUCKETS = 16;
    std::vector<std::vector<T>> table;
    size_t cnt_buckets, cnt_elems;

    size_t get_hash(T const &value) {
        return std::hash<T>()(value) % cnt_buckets;
    }

    size_t find_not_empty_bucket(int i) {
        ++i;
        while (i < table.size() && table[i].empty()) {
            ++i;
        }
        return static_cast<size_t>(i);
    }

    template<class U>
    struct my_iterator : std::iterator<std::forward_iterator_tag, U> {
        my_iterator() = default;

        my_iterator(my_iterator const &other) = default;

        my_iterator &operator=(my_iterator const &other) = default;

        U &operator*() const {
            return data[bucket][ind_in_bucket];
        }

        U *operator->() const {
            return &data[bucket][ind_in_bucket];
        }

        my_iterator &operator++() {
            if (ind_in_bucket + 1 != data[bucket].size()) {
                ind_in_bucket++;
            } else {
                ++bucket;
                while (bucket < data.size() && data[bucket].empty()) {
                    ++bucket;
                }
                ind_in_bucket = 0;
            }
            return *this;
        }

        my_iterator operator++(int) {
            my_iterator copy = *this;
            ++(*this);
            return copy;
        }

        friend bool operator==(my_iterator const &a, my_iterator const &b) noexcept {
            return a.bucket == b.bucket && a.ind_in_bucket == b.ind_in_bucket;
        }

        friend bool operator!=(my_iterator const &a, my_iterator const &b) noexcept {
            return !(a == b);
        }

    private:
        std::vector<std::vector<T>> const &data;
        size_t bucket, ind_in_bucket;
        friend my_unordered_set;

        explicit my_iterator(std::vector<std::vector<T>> const &d, size_t const &b, size_t const &i) : data(d),
                                                                                                       bucket(b),
                                                                                                       ind_in_bucket(
                                                                                                               i) {}
    };

    void rebuild() {
        cnt_buckets *= 2;
        std::vector<std::vector<T>> new_table(cnt_buckets);
        for (my_iterator<T const> it = begin(); it != end(); ++it) {
            size_t hash = get_hash(*it);
            new_table[hash].push_back(*it);
        }
        table.swap(new_table);
    }

public:
    typedef T value_type;
    typedef my_iterator<T const> iterator;
    typedef my_iterator<T const> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() noexcept {
        return iterator(table, find_not_empty_bucket(-1), 0);
    }

    const_iterator begin() const noexcept {
        return const_iterator(table, find_not_empty_bucket(-1), 0);
    }

    iterator end() noexcept {
        return iterator(table, table.size(), 0);
    }

    const_iterator end() const noexcept {
        return const_iterator(table, table.size(), 0);
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

    my_unordered_set() : table(START_COUNT_BUCKETS), cnt_buckets(START_COUNT_BUCKETS), cnt_elems(0) {}

    my_unordered_set(my_unordered_set const &other) = default;

    my_unordered_set &operator=(my_unordered_set const &other) = default;

    iterator find(T const &value) noexcept {
        size_t hash = get_hash(value), ind = 0;
        for (T const &i : table[hash]) {
            if (i == value) {
                return iterator(table, hash, ind);
            }
            ind++;
        }
        return end();
    }

    std::pair<iterator, bool> insert(T const &value) {
        iterator it = find(value);
        if (it != end()) {
            return std::make_pair(it, false);
        } else {
            size_t hash = std::hash<T>()(value);
            table[hash % cnt_buckets].push_back(value);
            cnt_elems++;
            if (2 * table[hash % cnt_buckets].size() > cnt_elems) {
                rebuild();
            }
            return std::make_pair(iterator(table, hash % cnt_buckets, table[hash % cnt_buckets].size() - 1), true);
        }
    }

    void erase(T const &value) {
        iterator it = find(value);
        if (it != end()) {
            size_t hash = get_hash(value);
            size_t ind = 0;
            for (; ind < table[hash].size() && table[hash][ind] != value; ++ind) {}
            table[hash].erase(table[hash].begin() + ind);
        }
    }
};

#endif //MY_UNORDERED_SET_MY_UNORDERED_SET_H
