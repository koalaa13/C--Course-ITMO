#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int u_int;
typedef long long ll;
typedef unsigned long long u_ll;

class big_integer {
	vector<u_int> data;
	bool sign;

	void delete_zeroes();
	vector<u_int> make_two_complement() const;
	big_integer(vector<u_int> const &d, bool const &s);
	big_integer(vector<u_int> const &arr);
	u_ll make_long_from_int(u_int const &a, u_int const &b) const;
	bool eq_short (u_int const &b) const; 
	bool not_eq_short (u_int const &b) const; 
	big_integer mul_long_short (u_int const &b) const; 
	void mul_eq_long_short (u_int const &b); 
	void add_eq_long_short (u_int const &b); 
	u_int divide_eq_long_short (u_int const &b); 
	void swap(big_integer &other);

public:
	big_integer();
	big_integer(int const &n);
	big_integer(big_integer const &other);
	explicit big_integer(string const &s);
	friend string to_string(big_integer const &a);
	
	big_integer& operator= (big_integer const &other);

	friend const bool operator== (big_integer const &a, big_integer const &b);
	friend const bool operator!= (big_integer const &a, big_integer const &b);
	friend const bool operator< (big_integer const &a, big_integer const &b);
	friend const bool operator<= (big_integer const &a, big_integer const &b);
	friend const bool operator> (big_integer const &a, big_integer const &b);
	friend const bool operator>= (big_integer const &a, big_integer const &b);

	friend const big_integer operator+ (big_integer const &a, big_integer const &b);
	friend const big_integer operator- (big_integer const &a, big_integer const &b);
	friend const big_integer operator- (big_integer const &a);
	friend const big_integer operator+ (big_integer const &a);

	friend ostream& operator<< (ostream& os, big_integer const &number);
	
	friend const big_integer operator* (big_integer const &a, big_integer const &b);
	friend big_integer& operator+= (big_integer &a, big_integer const &b);
	friend big_integer& operator-= (big_integer &a, big_integer const &b);
	friend big_integer& operator*= (big_integer &a, big_integer const &b);

	friend const big_integer& operator++ (big_integer &a);
	friend const big_integer operator++ (big_integer &a, int);
	friend const big_integer& operator-- (big_integer &a);
	friend const big_integer operator-- (big_integer &a, int);

	friend const big_integer operator& (big_integer const &a, big_integer const &b);
	friend const big_integer operator| (big_integer const &a, big_integer const &b);
	friend const big_integer operator^ (big_integer const &a, big_integer const &b);
	friend big_integer& operator&= (big_integer &a, big_integer const &b);
	friend big_integer& operator|= (big_integer &a, big_integer const &b);
	friend big_integer& operator^= (big_integer &a, big_integer const &b);
	friend const big_integer operator~ (big_integer const &a);

	friend const big_integer operator<< (big_integer const &a, u_int const &shift);
	friend const big_integer operator>> (big_integer const &a, u_int const &shift);
	friend big_integer& operator>>= (big_integer &a, u_int const &shift);
	friend big_integer& operator<<= (big_integer &a, u_int const &shift);

	friend const big_integer operator/ (big_integer const &a, big_integer const &b);
	friend const big_integer operator% (big_integer const &a, big_integer const  &b);
	friend big_integer& operator/= (big_integer &a, big_integer const &b);
	friend big_integer& operator%= (big_integer &a, big_integer const &b);
};