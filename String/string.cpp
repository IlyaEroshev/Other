#include "string.h"
#include <cstring>
#include <algorithm>
#include <utility>

String::String(size_t n, char c = '\0') {
	expand(n);
	std::memset(data_, c, n);
	size_ = n;
}

String::String(const char *p) {
	size_t n = std::strlen(p);
	expand(n);
	std::memcpy(data_, p, n);
	size_ = n;
}

String::String(char c): String(1u, c) {}

String::String(const String &s): size_(s.size_), capacity_(s.capacity_), data_(new char[capacity_]) {
	std::memcpy(data_, s.data_, size_);
}

void String::expand(size_t new_size) {
	if(capacity_ >= new_size) return;
	if(!capacity_) capacity_ = 8u;
	while(capacity_ < new_size)
		capacity_ <<= 1u;

	char *temp = data_;
	data_ = new char[capacity_];
	std::memcpy(data_, temp, size_);
	delete[] temp;
}

size_t String::size() const {
	return size_;
}

size_t String::capacity() const {
	return capacity_;
}

bool String::empty() const {
	return !size_;
}

void String::swap(String &s) {
	std::swap(size_, s.size_);
	std::swap(capacity_, s.capacity_);
	std::swap(data_, s.data_);
}

void String::resize(size_t new_size) {
	expand(new_size);
	size_ = new_size;
}

void String::resize(size_t new_size, char c) {
	expand(new_size);
	if(size_ < new_size)
		std::memset(data_ + size_, c, new_size-size_);
	size_ = new_size;
}

String& String::operator=(const String &s) {
	if(s.capacity_ == capacity_) {//capacity = степени 2
		size_ = s.size_;
		std::memcpy(data_, s.data_, size_);
	}
	else {
		String copy = s;
		swap(copy);
	}
	return *this;
}

String& String::operator+=(const String &s) {
	expand(size_ + s.size_);
	std::memcpy(data_ + size_, s.data_, s.size_);
	size_ += s.size_;
	return *this;
}

void String::push_back(char c) {
	expand(size_+1u);
	data_[size_++] = c;
}

void String::pop_back() {
	if(size_) --size_;
}

void String::clear() {
	size_ = 0u;
}

char& String::operator[](size_t i) {
	return data_[i];
}

char String::operator[](size_t i) const {
	return data_[i];
}

char& String::front() {
	return data_[0u];
}

char String::front() const {
	return data_[0u];
}

char& String::back() {
	return data_[size_ - 1u];
}

char String::back() const {
	return data_[size_ - 1u];
}

String String::substr(size_t pos, size_t count) const {
	String res = String();
	if(pos >= size_) return res;
	if(pos + count > size_)
		count = size_ - pos;
	res.expand(count);
	std::memcpy(res.data_, data_+pos, count);
	res.size_ = count;
	return res;
}

long String::find(const String &pattern) const {//КМП
	long *p = new long[pattern.size_];//Префикс-функция от pattern
	p[0] = -1;
	long k = -1;
	for(size_t i = 1; i < pattern.size_; ++i) {//вычисление p
		while (k != -1 && pattern.data_[k+1] != pattern.data_[i])
			k = p[k];
		if(pattern.data_[k+1] == pattern.data_[i])
			++k;
		p[i] = k;
	}

	long res = -1;
	k = -1;
	for(size_t i = 0; i < size_; ++i) {//поиск ответа
		while (k != -1 && pattern.data_[k+1] != data_[i])
			k = p[k];
		if (pattern.data_[k+1] == data_[i])
			++k;
		if (static_cast<size_t>(k + 1) == pattern.size_) { //первое вхождение
			res = i - k;
			break;
		}
	}
	delete[] p;
	return res;
}

//вспомогательные функции для rfind()
namespace rfind_sup_func {
	using ull = unsigned long long;
	using p_ull = std::pair<ull, ull>;
	using std::make_pair;

	p_ull operator+(const p_ull &a, const p_ull &b) {
		return make_pair(a.first + b.first, a.second + b.second);
	}

	p_ull operator-(const p_ull &a, const p_ull &b) {
		return make_pair(a.first - b.first, a.second - b.second);
	}

	p_ull operator*(const p_ull &a, const p_ull &b) {
		return make_pair(a.first * b.first, a.second * b.second);
	}

	p_ull operator%(const p_ull &a, const p_ull &b) {
		return make_pair(a.first % b.first, a.second % b.second);
	}

	//двойной хеш справа налево
	p_ull calc_dhash(const char *begin, const char *end, p_ull b, p_ull q) {
		p_ull res(0ull, 0ull);
		if(begin == end) return res;
		const char *it = end;
		do {
			--it;
			unsigned char c = static_cast<unsigned char>(*it);
			res = (res * b + make_pair(c, c)) % q;
		} while (it != begin);
		return res;
	}

	p_ull bin_pow(p_ull a, ull p, p_ull q) {//основание, степень, модуль
		p_ull res = make_pair(1ull, 1ull) % q;
		if (p >> 1) {
			res = bin_pow(a, p >> 1, q);
			res = res * res % q;
		}
		if(p & 1)
			res = res * a % q;
		return res;
	}

	bool equal(const char *text, const char *pattern, size_t sz) {//равенство строк
		for(size_t i = 0; i < sz; ++i)
			if(text[i] != pattern[i]) return false;
		return true;
	}
}

long String::rfind(const String &pattern) const {//двойной хеш
	if(size_ < pattern.size_) return -1;
	if(pattern.size_ == 0) return size_-1;
	using namespace rfind_sup_func;

	p_ull b(257, 263);//основание
	p_ull q(4'294'967'291, 4'194'256'151);//модуль
	char *begin = pattern.data_, *end = begin + pattern.size_;
	p_ull pattern_hash = calc_dhash(begin, end, b, q);
	p_ull p_b = bin_pow(b, pattern.size_-1, q);//b^(pattern.size_-1) % q

	//хеш текущего отрезка data_
	end = data_ + size_, begin = end - pattern.size_;
	p_ull cur_hash = calc_dhash(begin, end, b, q);

	for(size_t i = size_ - pattern.size_; i > 0; --i) {
		if(cur_hash == pattern_hash)
			if (equal(data_ + i, pattern.data_, pattern.size_))//проверка
				return i;
		unsigned char c = static_cast<unsigned char>(data_[i-1+pattern.size_]);//символ справа
		p_ull c_hash = make_pair(c, c) * p_b % q;//его hash
		cur_hash = (cur_hash + q - c_hash) % q;//удаляем
		c = static_cast<unsigned char>(data_[i-1]);//принимаем символ слева
		cur_hash = (cur_hash * b + make_pair(c, c)) % q;
	}

	if(cur_hash == pattern_hash)
		if(equal(data_, pattern.data_, pattern.size_))//проверка
			return 0;
	return -1;
}

String::~String() {
	delete[] data_;
}

std::istream& operator>>(std::istream &s, String &str) {
	str.clear();
	char c;
	s.get(c);
	while(!iscntrl(c) && !isspace(c)) {
		str.push_back(c);
		s.get(c);
	}
	return s;
}

std::ostream& operator<<(std::ostream &s, const String &str) {
	size_t sz = str.size();
	for(size_t i = 0u; i < sz; ++i)
		s << str[i];
	return s;
	//return s << str.data_;//пользователь может вставить в середину строки \0
}

String operator+(const String &s1, const String &s2) {
	String res = s1;
	res += s2;
	return res;
}

bool operator<(const String &s1, const String &s2) {
	int rc = std::memcmp(s1.data_, s2.data_, std::min(s1.size_, s2.size_));
	return (rc < 0) || (rc == 0 && s1.size_ < s2.size_);
}

bool operator>(const String &s1, const String &s2) {
	return s2 < s1;
}

bool operator==(const String &s1, const String &s2) {
	//return !(s1 < s2 || s1 > s2);//красиво, но долго
	if(s1.size_ != s2.size_) return false;
	int rc = std::memcmp(s1.data_, s2.data_, s1.size_);
	return rc == 0;
}

bool operator!=(const String &s1, const String &s2) {
	return !(s1 == s2);
}

bool operator<=(const String &s1, const String &s2) {
	return !(s1 > s2);
}

bool operator>=(const String &s1, const String &s2) {
	return !(s1 < s2);
}
