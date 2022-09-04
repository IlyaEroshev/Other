#include "String.h"
#include <cstdint>

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
};

char& String::back() {
	return data_[size_ - 1u];
}

char String::back() const {
	return data_[size_ - 1u];
}

String::~String() {
	delete[] data_;
}


std::istream& operator>>(std::istream &s, String &str) {
	str.clear();
	char c;
	s.get(c);
	while(!iscntrl(c)) {
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