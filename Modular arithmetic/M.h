template <uint32_t mod>
class ModularArithmetic{//uint64_t можно заменить на __int128
	uint64_t value;
public:
	inline ModularArithmetic(): value(0ull) {}

	inline ModularArithmetic(long long value) {
		value %= mod;
		if(value < 0) value += mod;
		this->value = value;
	}

	inline uint32_t get_mod() const {
		return mod;
	}

	inline uint64_t get_value() const {
		return value;
	}

	inline ModularArithmetic& operator+=(const ModularArithmetic &a) {
		value += a.value;
		value %= mod;
		return *this;
	}

	inline ModularArithmetic& operator-=(const ModularArithmetic &a) {
		value += mod - a.value;
		value %= mod;
		return *this;
	}

	inline ModularArithmetic& operator*=(const ModularArithmetic &a) {
		value *= a.value;
		value %= mod;
		return *this;
	}

	inline ModularArithmetic& operator/=(const ModularArithmetic &a) {
		ModularArithmetic inv_a = pow(a, mod - 2);
		return *this *= inv_a;
	}

	inline static ModularArithmetic F(long n) {//факториал n
		static std::vector<ModularArithmetic> fucts(2, 1);
		if(fucts.size() <= n)
			fucts.push_back(F(n-1) * ModularArithmetic(n));
		return fucts[n];
	}

	inline static ModularArithmetic A(long n, long k) {//кол-во размещений из n по k
		return F(n) / F(n-k);
	}

	inline static ModularArithmetic C(long n, long k) {//кол-во сочетаний из n по k
		return F(n) / (F(k) * F(n-k));
	}
};

template <uint32_t mod>
inline ModularArithmetic<mod> operator+(const ModularArithmetic<mod> &a, const ModularArithmetic<mod> &b) {
	ModularArithmetic<mod> res = a;
	res += b;
	return res;
}

template <uint32_t mod>
inline ModularArithmetic<mod> operator-(const ModularArithmetic<mod> &a, const ModularArithmetic<mod> &b) {
	ModularArithmetic<mod> res = a;
	res -= b;
	return res;
}

template <uint32_t mod>
inline ModularArithmetic<mod> operator*(const ModularArithmetic<mod> &a, const ModularArithmetic<mod> &b) {
	ModularArithmetic<mod> res = a;
	res *= b;
	return res;
}

template <uint32_t mod>
inline ModularArithmetic<mod> operator/(const ModularArithmetic<mod> &a, const ModularArithmetic<mod> &b) {
	ModularArithmetic<mod> res = a;
	res /= b;
	return res;
}

template <uint32_t mod>
inline ModularArithmetic<mod> pow(ModularArithmetic<mod> a, uint64_t d) {
	ModularArithmetic<mod> res = (d & 1u) ? a : ModularArithmetic<mod>(1);
	d >>= 1;
	while(d) {
		a *= a;
		if(d & 1u) res *= a;
		d >>= 1;
	}
	return res;
}

template <uint32_t mod>
inline std::istream& operator>>(std::istream &in, ModularArithmetic<mod> &a) {
	long long value;
	in >> value;
	a = ModularArithmetic<mod>(value);
	return in;
}

template <uint32_t mod>
inline std::ostream& operator<<(std::ostream &out, const ModularArithmetic<mod> &a) {
	return out << a.get_value();
}
