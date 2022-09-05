#ifndef OTHER_STRING_H
#define OTHER_STRING_H

#include <iostream>

class String {
	size_t size_ = 0;
	size_t capacity_ = 0;//может уменьшиться только при присваивании, всегда равна степени 2
	char *data_ = nullptr;

public:
	String() = default;

	explicit String(size_t, char);

	String(const char*);

	String(char);

	String(const String&);

private:
	void expand(size_t);//увеличивает capacity

public:
	size_t size() const;

	size_t capacity() const;

	bool empty() const;

	void swap(String&);

	void resize(size_t);

	void resize(size_t, char);

	String& operator=(const String&);

	String& operator+=(const String&);

	friend bool operator<(const String&, const String&);

	friend bool operator==(const String&, const String&);

	void push_back(char);

	void pop_back();

	void clear();

	char& operator[](size_t);

	char operator[](size_t) const;

	char& front();

	char front() const;

	char& back();

	char back() const;

	String substr(size_t, size_t) const;

	long find(const String&) const;//первое вхождение слева, реализация КМП (-1 если не нашел)

	long rfind(const String&) const;//первое вхождение справа, реализация хеш (-1 если не нашел)

	~String();
};

std::istream& operator>>(std::istream&, String&);

std::ostream& operator<<(std::ostream&, const String&);

String operator+(const String&, const String&);

bool operator<(const String&, const String&);

bool operator>(const String&, const String&);

bool operator==(const String&, const String&);

bool operator!=(const String&, const String&);

bool operator<=(const String&, const String&);

bool operator>=(const String&, const String&);

#endif
