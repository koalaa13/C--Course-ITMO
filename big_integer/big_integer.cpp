#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned int u_int;

ll const NUMBER_SYSTEM = (1ll << 32);

class big_integer {
	vector<u_int> data;
	bool sign;

public:
	friend const bool operator== (big_integer const &a, u_int const &b);
	
public:
	friend const bool operator== (u_int const &a, big_integer const &b);

public:
	friend const bool operator!= (big_integer const &a, u_int const &b);

public:
	friend const bool operator!= (u_int const &a, big_integer const &b);

public:
	friend const big_integer operator* (big_integer const &a, u_int const &b);

public:
	friend const big_integer operator* (u_int const &a, big_integer const &b);

public:
	friend big_integer& operator*= (big_integer &a, u_int const &b);

public:
	friend const big_integer operator+ (big_integer const &a, u_int const &b);

public:
	friend const big_integer operator+ (u_int const &a, big_integer const &b);

public:
	friend big_integer& operator+= (big_integer &a, u_int const &b);

public:
	friend u_int operator/= (big_integer &a, u_int const &b);

public:
	big_integer() {
		sign = false;
		data.resize(1, 0);
	}

public:
	big_integer(int const &n) {
		sign = n < 0;
		data.resize(1);
		data[0] = abs(n);
	}

public:
	big_integer(big_integer const &other) {
		data.resize(other.data.size());
		for (size_t i = 0; i < data.size(); ++i) {
			data[i] = other.data[i];
		}
		sign = other.sign;
	}

public:
	explicit big_integer(string const &s) {
		if (s.empty()) {
			data.resize(1, 0);
			sign = false;
		} else {
			data.resize(1, 0);
			sign = s[0] == '-';
			for (size_t i = sign; i < s.length(); ++i) {
				*this *= 10;
				*this += (u_int)(s[i] - '0');
			}
		}
	}

public:
	~big_integer() {}

public:
	string to_string() const {
		string res = "";
		big_integer copy = *this;
		while (copy != 0) {
			u_int mod = copy /= 10;
			res += (char)(mod + '0');
		}
		if (sign) {
			res += '-';
		}
		reverse(res.begin(), res.end());
		return res;
	}

public:
	big_integer& operator= (big_integer const &other) {
		sign = other.sign;
		data.resize(other.data.size());
		for (size_t i = 0; i < data.size(); ++i) {
			data[i] = other.data[i];
		}
		return *this;
	}

public:
	bool operator== (big_integer const &other) const {
		if (sign != other.sign || data.size() != other.data.size()) {
			return false;
		}
		for (size_t i = 0; i < data.size(); ++i) {
			if (data[i] != other.data[i]) {
				return false;
			}
		}
		return true;
	}

public:
	bool operator!= (big_integer const &other) const {
		return !(*this == other);
	}

public:
	bool operator< (big_integer const &other) const {
		bool other_sign = other.sign;
		if (sign && !other_sign) {
			return true;
		}
		if (!sign && other_sign) {
			return false;
		}
		bool res;
		size_t our_size = data.size(), other_size = other.data.size();
		if (our_size != other_size) {
			res = our_size < other_size;
		} else {
			res = true;
			int i = our_size - 1;
			for (; i >= 0; --i) {
				if (data[i] != other.data[i]) {
					res = data[i] < other.data[i];
					break;
				}
			}
			if (i == -1) {
				return false;
			}
		}
		if (sign) {
			res = !res;
		}
		return res;
	}

public:
	bool operator<= (big_integer const &other) const {
		return *this < other || *this == other;
	}

public:
	bool operator> (big_integer const &other) const {
		return !(*this <= other);
	}

public:
	bool operator >= (big_integer const &other) const {
		return !(*this < other);
	}

public:
	friend const big_integer operator+ (big_integer const &a, big_integer const &b);

public:
	friend const big_integer operator- (big_integer const &a, big_integer const &b);

public:
	friend const big_integer operator- (big_integer const &a);
};

const bool operator== (big_integer const &a, u_int const &b) {
	if (a.data[0] != b) {
		return false;
	}
	for (size_t i = 1; i < a.data.size(); ++i) {
		if (a.data[i] > 0) {
			return false;
		}
	}
	return true;
}

const bool operator== (u_int const &a, big_integer const &b) {
	return b == a;
}

const big_integer operator* (big_integer const &a, u_int const &b) {
	ll prev = 0ll;
	big_integer res = a;
	for (size_t i = 0; i < res.data.size(); ++i) {
		ll cur = (ll)res.data[i] * (ll)b + prev;
		res.data[i] = (u_int)(cur % NUMBER_SYSTEM);
		prev = cur / NUMBER_SYSTEM;
	}
	if (prev) {
		res.data.push_back(prev % NUMBER_SYSTEM);
	}
	return res;
}

const big_integer operator* (u_int const &a, big_integer const &b) {
	return b * a;
}

big_integer& operator*= (big_integer &a, u_int const &b) {
	a = a * b;
	return a;
}

const bool operator!= (big_integer const &a, u_int const &b) {
	return !(a == b);
}

const bool operator!= (u_int const &a, big_integer const &b) {
	return !(a == b);
}

const big_integer operator+ (big_integer const &a, u_int const &b) {
	ll prev = (ll)b;
	big_integer res = a;
	for (size_t i = 0; i < res.data.size(); ++i) {
		ll cur = res.data[i] + prev;
		res.data[i] = (u_int)(cur % NUMBER_SYSTEM);
		prev = cur / NUMBER_SYSTEM;
		if (prev == 0) {
			break;
		}
	}
	if (prev) {
		res.data.push_back(prev % NUMBER_SYSTEM);
	}
	return res;
}

const big_integer operator+ (u_int const &a, big_integer const &b) {
	return b + a;
}

big_integer& operator+= (big_integer &a, u_int const &b) {
	a = a + b;
	return a;
}

const ll make_long_from_int(u_int const &a, u_int const &b) {
	return (ll)a * NUMBER_SYSTEM + (ll)b;
}

u_int operator/= (big_integer &a, u_int const &b) {
	u_int prev = 0;
	for (int i = a.data.size() - 1; i >= 0; --i) {
		ll cur = make_long_from_int(prev, a.data[i]);
		prev = (u_int)(cur % (ll)b);
		a.data[i] = (u_int)(cur / (ll)b);
	}
	return prev;
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
			ll cur = (ll)prev;
			if (i < a_size) {
				cur += (ll)a.data[i];
			}
			if (i < b_size) {
				cur += (ll)b.data[i];
			}
			res.data[i] = (u_int)(cur % NUMBER_SYSTEM);
			prev = (u_int)(cur / NUMBER_SYSTEM);
		}
		if (prev) {
			res.data.push_back((u_int)prev);
		}
	}
	if (res.sign == true && res == 0) {
		res.sign = false;
	}
	return res;
}

const big_integer operator- (big_integer const &a, big_integer const &b) {
	big_integer res;
	if (a.sign == b.sign) {
		
	} else {
		if (a.sign) {
			res = -a + b;
		} else {
			res = a + -b;
		}
	}
	if (res.sign == true && res == 0) {
		res.sign = false;
	}
	return res;
}

const big_integer operator- (big_integer const &a) {
	if (a == 0) {
		return a;
	}
	big_integer res = a;
	res.sign ^= true;
	return res;
}

int main() {
	big_integer a("-2120318371963912012301001931763152367"), b("-3");
	swap(a, b);
	cout << a.to_string() << "\n" << b.to_string();


	return 0;
}