#ifndef OTHER_M_H
#define OTHER_M_H

struct M;

M pow(const M &a, ull d);

struct M {
	typedef unsigned long long ull;
	typedef unsigned long ul;
	static const ul mod = 1000000007ul;
	//ull можно заменить на __int128
	ull value = 0ul;

	M() = default;

	M(ull value): value(value) {}

	operator unsigned long long() const {
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
};

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

M pow(const M &a, ull d) {
	if(!d) return 1ul % M::mod;
	M res = pow(a, d >> 1);
	res *= res;
	if(d & 1u) res *= a;
	return res;
}

std::istream& operator>>(std::istream &in, M &a) {
	in >> a.value;
	a.value %= M::mod;
	return in;
}

#endif //OTHER_M_H
