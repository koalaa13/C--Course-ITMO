#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template<class T>
class Vector {
	size_t sz, cap;
	T *arr;

public:
	Vector() noexcept {
		sz = cap = 0;
		arr = (T*)malloc(sz * sizeof(T));
	}

private:
	void check_alloc(string const &mess) {
		if (arr == NULL) {
			throw mess;
		}
	}

public:
	Vector(size_t const &length, T const &value) {
		try {
			sz = cap = length;
			arr = (T*)malloc(cap * sizeof(T));
			check_alloc("Error while allocating memory when creating vector");
			fill(arr, arr + cap, value);
		} catch (...) {
			throw;
		}
	}

public:
	Vector(size_t const &length) {
		try {
			sz = cap = length;
			arr = (T*)malloc(sz * sizeof(T));
			check_alloc("Error while allocating memory when creating vector");
		} catch (...) {
			throw;
		}
	}

public:
	Vector(Vector const &other) {
		try {
			cap = other.size();
			arr = (T*)malloc(cap * sizeof(T));
			check_alloc("Error while allocating memory when creating vector");
			for (sz = 0; sz < cap; ++sz) {
				arr[sz] = other[sz];
			}
		} catch (...) {
			throw;
		}
	}

public:
	~Vector() noexcept {
		free(arr);
	}

public:
	size_t size() const noexcept {
		return sz;
	}

public:
	T const& operator[] (size_t const &ind) const noexcept {
		return arr[ind];
	}

public:
	T& operator[] (size_t const &ind) noexcept {
		return arr[ind];
	}

public:
	Vector& operator= (Vector<T> const &other) {
		try {
			sz = cap = other.size();
			arr = (T*)realloc(arr, cap * sizeof(T));
			check_alloc("Error while allocating memory when assigning vector to another one");
			for (size_t i = 0; i < sz; ++i) {
				arr[i] = other[i];
			}
		} catch (...) {
			throw;
		}
	}

private:
	void change_capacity(size_t const &new_cap) {
		try {
			cap = new_cap;
			arr = (T*)realloc(arr, cap * sizeof(T));
			check_alloc("Error: can't allocate enough memory for vector");
		} catch (...) {
			throw;
		}
	}

private:
	void increase_cap() {
		try {
			if (sz == cap) {
				change_capacity((cap + (cap == 0)) * 2);
			}
		} catch (...) {
			throw;
		}
	}

private:
	void decrease_cap() noexcept {
		if (4 * sz <= cap) {
			change_capacity(cap / 2);
		}
	}

public:
	void insert(size_t const& pos, T const &value) {
		try {
			increase_cap();
			for (size_t i = sz++; i > pos; --i) {
				arr[i] = arr[i - 1];
			}
			arr[pos] = value;
		} catch (...) {
			throw;
		}
	}

public:
	void erase(size_t const &pos) {
		try {
			sz--;
			for (size_t i = pos; i < sz; ++i) {
				arr[i] = arr[i + 1];
			}
			decrease_cap();
		} catch (...) {
			throw;
		}
	}

public:
	void erase(size_t const &first, size_t const &last) {
		try {
			for (size_t i = first, j = last; j < sz; ++i, ++j) {
				arr[i] = arr[j];
			}
			sz -= last - first;
			decrease_cap();
		} catch (...) {
			throw;
		}
	}

public:
	bool empty() const noexcept {
		return sz == 0;
	}

public:
	T& back() noexcept {
		return arr[sz - 1];
	}

public:
	T const& back() const noexcept {
		return arr[sz - 1];
	}

public:
	T& front() noexcept {
		return arr[0];
	}

public:
	T const& front() const noexcept {
		return arr[0];
	}

public:
	void push_back(T const &value) {
		try {
			increase_cap();
			arr[sz++] = value;
		} catch(...) {
			throw;
		}
	}

public:
	void pop_back() noexcept {
		sz--;
		decrease_cap();
	}

public:
	size_t capacity() const noexcept {
		return cap;
	}

public:
	void reserve(size_t const &need) {
		try {
			change_capacity(need);
		} catch (...) {
			throw;
		}
	}

public:
	void shrink_to_fit() {
		try {
			change_capacity(sz);
		} catch (...) {
			throw;
		}
	}

public:
	void print() {
		for (size_t i = 0; i < sz; ++i) {
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
};


int main() {
	

	return 0;
}