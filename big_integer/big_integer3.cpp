#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

typedef long long ll;
typedef unsigned int u_int;
typedef unsigned long long u_ll;

u_ll const NUMBER_SYSTEM = (1ll << 32);

class big_integer {
	vector<u_int> data;
	bool sign;

	void delete_zeroes() {
		while (data.size() > 1 && data.back() == 0) {
			data.pop_back();
		}
	}

	u_ll make_long_from_int(u_int const &a, u_int const &b) const {
		return (u_ll)a * NUMBER_SYSTEM + (u_ll)b;
	}

	bool operator== (u_int const &b) const {
		return data.size() == 1 && data[0] == b;
	}

	bool operator!= (u_int const &b) const {
		return !(*this == b);
	}

	big_integer operator* (u_int const &b) const {
		u_ll prev = 0;
		big_integer res = *this;
		for (size_t i = 0; i < res.data.size(); ++i) {
			u_ll cur = (u_ll)res.data[i] * (u_ll)b + prev;
			res.data[i] = (u_int)(cur % NUMBER_SYSTEM);
			prev = cur / NUMBER_SYSTEM;
		}
		if (prev) {
			res.data.push_back(prev % NUMBER_SYSTEM);
		}
		res.delete_zeroes();
		return res;
	}

	void operator*= (u_int const &b) {
		*this = *this * b;
	}

	void operator+= (u_int const &b) {
		u_ll prev = (u_ll)b;
		for (size_t i = 0; i < data.size(); ++i) {
			u_ll cur = data[i] + prev;
			data[i] = (u_int)(cur % NUMBER_SYSTEM);
			prev = cur / NUMBER_SYSTEM;
			if (prev == 0) {
				break;
			}
		}
		if (prev) {
			data.push_back(prev % NUMBER_SYSTEM);
		}
		delete_zeroes();
	}

	void operator-= (u_int const &b) {
		if (sign) {
			
		} else {

		}
	}

	u_int operator/= (u_int const &b) {
		u_int prev = 0;
		for (ptrdiff_t i = data.size() - 1; i >= 0; --i) {
			u_ll cur = make_long_from_int(prev, data[i]);
			prev = (u_int)(cur % (u_ll)b);
			data[i] = (u_int)(cur / (u_ll)b);
		}
		delete_zeroes();
		return prev;
	}

public:
	big_integer() {
		sign = false;
		data.resize(1, 0);
	}

	big_integer(int const &n) {
		data.resize(1);
		sign = n < 0;
		data[0] = abs(n);
	}

	big_integer(big_integer const &other) {
		data.resize(other.data.size());
		for (size_t i = 0; i < data.size(); ++i) {
			data[i] = other.data[i];
		}
		sign = other.sign;
	}

	explicit big_integer(string const &s) {
		if (s.empty()) {
			data.resize(1, 0);
			sign = false;
		} else {
			data.resize(1, 0);
			if (s == "-0") {
				sign = false;
				return;
			} 
			sign = s[0] == '-';
			for (size_t i = sign; i < s.length(); ++i) {
				*this *= 10;
				*this += (u_int)(s[i] - '0');
			}
			delete_zeroes();
		}
	}

	~big_integer() {}

	string to_string() const {
		string res = "";
		big_integer copy = *this;
		while (copy != 0) {
			u_int mod = copy /= 10;
			res += (char)(mod + '0');
		}
		if (res.empty()) {
			res = "0";
		}
		if (sign) {
			res += '-';
		}
		reverse(res.begin(), res.end());
		return res;
	}

	big_integer& operator= (big_integer const &other) {
		sign = other.sign;
		data.resize(other.data.size());
		for (size_t i = 0; i < data.size(); ++i) {
			data[i] = other.data[i];
		}
		return *this;
	}

	friend const bool operator== (big_integer const &a, big_integer const &b);

	friend const bool operator!= (big_integer const &a, big_integer const &b);

	friend const bool operator< (big_integer const &a, big_integer const &b);
	
	friend const bool operator<= (big_integer const &a, big_integer const &b);

	friend const bool operator> (big_integer const &a, big_integer const &b);

	friend const bool operator>= (big_integer const &a, big_integer const &b);

	friend const big_integer operator+ (big_integer const &a, big_integer const &b);

	friend const big_integer operator- (big_integer const &a, big_integer const &b);

	friend const big_integer operator- (big_integer const &a);

	void swap(big_integer &other) {
		bool buff = sign;
		sign = other.sign;
		other.sign = buff;
		data.swap(other.data);
	}

	friend const big_integer operator+ (big_integer const &a);

	friend ostream& operator<< (ostream& os, big_integer const &number);

	friend const big_integer operator* (big_integer const &a, big_integer const &b);

	friend big_integer& operator+= (big_integer &a, big_integer const &b);

	friend big_integer& operator-= (big_integer &a, big_integer const &b);

	friend big_integer& operator*= (big_integer &a, big_integer const &b);

	friend const big_integer& operator++ (big_integer &a);

	friend const big_integer& operator++ (big_integer &a, int);

	friend const big_integer& operator-- (big_integer &a);

	friend const big_integer& operator-- (big_integer &a, int);
};

const bool operator== (big_integer const &a, big_integer const &b) {
	if (a.sign != b.sign || a.data.size() != b.data.size()) {
		return false;
	}
	for (size_t i = 0; i < a.data.size(); ++i) {
		if (a.data[i] != b.data[i]) {
			return false;
		}
	}
	return true;
}

const bool operator!= (big_integer const &a, big_integer const &b) {
	return !(a == b);
}

const bool operator< (big_integer const &a, big_integer const &b) {
	if (a.sign && !b.sign) {
		return true;
	}
	if (!a.sign && b.sign) {
		return false;
	}
	bool res = false;
	size_t a_size = a.data.size(), b_size = b.data.size();
	if (a_size != b_size) {
		res = a_size < b_size;
	} else {
		res = true;
		ptrdiff_t i = a_size - 1;
		for (; i >= 0; --i) {
			if (a.data[i] != b.data[i]) {
				res = a.data[i] < b.data[i];
				break;
			}
		}
		if (i == -1) {
			return false;
		}
	}
	return res ^ a.sign;
}

const bool operator<= (big_integer const &a, big_integer const &b) {
	return a < b || a == b;
}

const bool operator> (big_integer const &a, big_integer const &b) {
	return !(a <= b);
}

const bool operator>= (big_integer const &a, big_integer const &b) {
	return !(a < b);
}

const big_integer operator+ (big_integer const &a, big_integer const &b) {
	big_integer res;
	if (a.sign != b.sign) {
		if (a.sign) {
			res = b - -a;
		} else {
			res = a - -b;
		}
	} else {
		res.sign = a.sign;
		u_int prev = 0;
		size_t a_size = a.data.size(), b_size = b.data.size();
		res.data.resize(max(a_size, b_size));
		for (size_t i = 0; i < max(a_size, b_size); ++i) {
			u_ll cur = (u_ll)prev;
			if (i < a_size) {
				cur += (u_ll)a.data[i];
			}
			if (i < b_size) {
				cur += (u_ll)b.data[i];
			}
			res.data[i] = (u_int)(cur % NUMBER_SYSTEM);
			prev = (u_int)(cur / NUMBER_SYSTEM);
		}
		if (prev) {
			res.data.push_back((u_int)prev);
		}
	}
	if (res == 0) {
		res.sign = false;
	}
	res.delete_zeroes();
	return res;
}

const big_integer operator- (big_integer const &a, big_integer const &b) {
	big_integer res;
	if (a.sign == b.sign) {
		big_integer subt;
		if (a.sign) {
			res = b;
			subt = a;
			res.sign ^= true;
			subt.sign ^= true;
		} else {
			res = a;
			subt = b;
		}
		bool swap_sign = false;
		if (res < subt) {
			swap_sign = true;
			res.swap(subt);
		}
		bool borrowed = false;
		for (size_t i = 0; i < res.data.size(); ++i) {
			ll first = (ll)res.data[i], second = 0ll;
			if (subt.data.size() > i) {
				second = (ll)subt.data[i];
			}
			first -= second + borrowed;
			if (first < 0) {
				borrowed = true;
				first += NUMBER_SYSTEM;
			} else {
				borrowed = false;
			}
			res.data[i] = (u_int)first;
		}
		res.sign ^= swap_sign;
	} else {
		if (a.sign) {
			res = -a + b;
		} else {
			res = a + -b;
		}
	}
	if (res == 0) {
		res.sign = false;
	}
	res.delete_zeroes();
	return res;
}

const big_integer operator- (big_integer const &a) {
	big_integer res = a;
	res.sign ^= true;
	return res;
}

const big_integer operator+ (big_integer const &a) {
	big_integer res = a;
	return res;
}

ostream& operator<< (ostream& os, big_integer const &number) {
	os << number.to_string();
	return os;
}

const big_integer operator* (big_integer const &a, big_integer const &b) {
	big_integer res;
	const u_int mul = (1 << 16);
	for (ptrdiff_t i = b.data.size() - 1; i >= 0; --i) {
		res *= mul;
		res *= mul;
		res += a * b.data[i];
	}
	res.sign = a.sign ^ b.sign;
	if (res == 0) {
		res.sign = false;
	}
	return res;
}

big_integer& operator+= (big_integer &a, big_integer const &b) {
	return a = a + b;
}

big_integer& operator-= (big_integer &a, big_integer const &b) {
	return a = a - b;
}

big_integer& operator*= (big_integer &a, big_integer const &b) {
	return a = a * b;
}

const big_integer& operator++ (big_integer &a) {
	if (a.sign) {
		a.sign ^= true;
		--a;
		a.sign ^= true;
	} else {
		bool was = true;
		for (size_t i = 0; i < a.data.size(); ++i) {
			u_ll cur = (u_ll)a.data[i] + (u_ll)was;
			if (cur == NUMBER_SYSTEM) {
				a.data[i] = 0;
			} else {
				a.data[i]++;
				was = false;
				break;
			}
		}
		if (was) {
			a.data.push_back(1);
		}
	}
	if (a == 0) {
		a.sign = false;
	}
	a.delete_zeroes();
	return a;
}

const big_integer& operator++ (big_integer &a, int) {
	big_integer res = a;
	++a;
	return res;
}

const big_integer& operator-- (big_integer &a) {
	if (a.sign) {
		a.sign ^= true;
		++a;
		a.sign ^= true;
	} else {
		if (a == 0) {
			a.sign = true;
			a.data[0] = 1;
		} else {
			ptrdiff_t i = 0;
			while (a.data[i] == 0) {
				++i;
			}
			a.data[i--]--;
			for (; i >= 0; --i) {
				a.data[i] = (u_int)(NUMBER_SYSTEM - 1);
			}
		}
	}
	if (a == 0) {
		a.sign = false;
	}
	a.delete_zeroes();
	return a;
}

const big_integer& operator-- (big_integer &a, int) {
	big_integer res = a;
	--a;
	return res;
}

char rnd() {
	return (char)((rand() % 10) + '0');
}

int main() {
	/*string s1 = "", s2 = "";
	for (size_t i = 0; i < 10000; ++i) {
		s1 += rnd();
		s2 += rnd();
	}
	big_integer a(s1), b(s2);
	a + b;
	cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";*/
	return 0;
}