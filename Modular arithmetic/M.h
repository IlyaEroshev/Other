#ifndef OTHER_M_H
#define OTHER_M_H

#include <iostream>

class M;

M pow(M, uint64_t);

class M {//uint64_t можно заменить на __int128
	uint64_t value = 0ul;
public:
	static uint32_t mod;//модуль только простое число

	M() = default;

	explicit M(uint64_t value): value(value % mod) {}

	operator uint64_t() const {
		return value;
	}

	M& operator+=(const M &a) {
		value += a.value;
		value %= mod;
		return *this;
	}

	M& operator-=(const M &a) {
		value += mod - a.value;
		value %= mod;
		return *this;
	}

	M& operator*=(const M &a) {
		value *= a.value;
		value %= mod;
		return *this;
	}

	M& operator/=(const M &a) {
		M inv_a = pow(a, mod - 2);
		return *this *= inv_a;
	}

	friend std::istream& operator>>(std::istream&, M&);
};

uint32_t M::mod = 1'000'000'007;

M operator+(const M &a, const M &b) {
	M res = a;
	res += b;
	return res;
}

M operator-(const M &a, const M &b) {
	M res = a;
	res -= b;
	return res;
}

M operator*(const M &a, const M &b) {
	M res = a;
	res *= b;
	return res;
}

M operator/(const M &a, const M &b) {
	M res = a;
	res /= b;
	return res;
}

M pow(M a, uint64_t d) {
	M res = (d & 1u) ? a : M(1);
	d >>= 1;
	while(d) {
		a *= a;
		if(d & 1u) res *= a;
		d >>= 1;
	}
	return res;
}

std::istream& operator>>(std::istream &in, M &a) {
	in >> a.value;
	a.value %= M::mod;
	return in;
}

#endif