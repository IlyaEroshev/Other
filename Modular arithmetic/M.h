#include <iostream>
#include <vector>

template <uint32_t mod>
class M{//uint64_t можно заменить на __int128
	uint64_t value;
public:
	M(): value(0ull) {}

	M(long long value) {
		value %= mod;
		if(value < 0) value += mod;
		this->value = value;
	}

	uint32_t get_mod() const {
		return mod;
	}

	uint64_t get_value() const {
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

	inline static M F(long n) {//факториал n
		static std::vector<M> fucts(2, 1);
		if(fucts.size() < n)
			fucts.push_back(F(n-1));
		return fucts[n];
	}

	inline static M A(long n, long k) {//кол-во размещений из n по k
		return F(n) / F(n-k);
	}

	inline static M C(long n, long k) {//кол-во сочетаний из n по k
		return F(n) / (F(k) * F(n-k));
	}
};

template <uint32_t mod>
M<mod> operator+(const M<mod> &a, const M<mod> &b) {
	M<mod> res = a;
	res += b;
	return res;
}

template <uint32_t mod>
M<mod> operator-(const M<mod> &a, const M<mod> &b) {
	M<mod> res = a;
	res -= b;
	return res;
}

template <uint32_t mod>
M<mod> operator*(const M<mod> &a, const M<mod> &b) {
	M<mod> res = a;
	res *= b;
	return res;
}

template <uint32_t mod>
M<mod> operator/(const M<mod> &a, const M<mod> &b) {
	M<mod> res = a;
	res /= b;
	return res;
}

template <uint32_t mod>
M<mod> pow(M<mod> a, uint64_t d) {
	M<mod> res = (d & 1u) ? a : M<mod>(1);
	d >>= 1;
	while(d) {
		a *= a;
		if(d & 1u) res *= a;
		d >>= 1;
	}
	return res;
}

template <uint32_t mod>
std::istream& operator>>(std::istream &in, M<mod> &a) {
	long long value;
	in >> value;
	a = M<mod>(value);
	return in;
}

template <uint32_t mod>
std::ostream& operator<<(std::ostream &out, const M<mod> &a) {
	return out << a.get_value();
}