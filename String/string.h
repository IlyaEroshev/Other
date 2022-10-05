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

	String(std::initializer_list<char>);

private:
	void expand(size_t);//увеличивает capacity

public:
	inline size_t size() const;

	inline size_t capacity() const;

	inline bool empty() const;

	inline void swap(String&);

	inline void resize(size_t);

	inline void resize(size_t, char);

	inline String& operator=(const String&);

	inline String& operator+=(const String&);

	friend inline bool operator<(const String&, const String&);

	friend inline bool operator==(const String&, const String&);

	inline void push_back(char);

	inline void pop_back();

	inline void clear();

	inline char& operator[](size_t);

	inline char operator[](size_t) const;

	inline char& front();

	inline char front() const;

	inline char& back();

	inline char back() const;

	String substr(size_t, size_t) const;

	long find(const String&) const;//первое вхождение слева, реализация КМП (-1 если не нашел)

	long rfind(const String&) const;//первое вхождение справа, реализация хеш (-1 если не нашел)

	~String();
};

inline std::istream& operator>>(std::istream&, String&);

inline std::ostream& operator<<(std::ostream&, const String&);

inline String operator+(const String&, const String&);

bool operator<(const String&, const String&);

inline bool operator>(const String&, const String&);

bool operator==(const String&, const String&);

inline bool operator!=(const String&, const String&);

inline bool operator<=(const String&, const String&);

inline bool operator>=(const String&, const String&);

#endif
