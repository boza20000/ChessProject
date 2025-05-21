#pragma once
#pragma once
#include <istream>

class String
{
private:
	char* string;
	size_t length;
	void free();
	void copyFrom(const String& str);

public:
	String();
	String(const char* str);
	String(const String& str);
	String& operator=(const char* str);
	String& operator=(const String& str);

	~String();
	void setString(const char* str);
	char* getString() const;
	void setLen(const size_t length);
	size_t getLen() const;
	bool operator==(const String& other) const;
	friend std::istream& operator>>(std::istream&, String& other);
	friend std::ostream& operator<<(std::ostream&, const String& other);
	char getSymbol(int index) const;
	bool starts_with(const String& str) const;
	const char* c_str() const;
	String get(size_t start, size_t end) const;
	String get(size_t start) const;
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	std::istream& getline(std::istream& is, String& str);
	String getFirstWord()const;
};

