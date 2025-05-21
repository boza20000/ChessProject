#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "String.h"
#include <cstring>
#include <string> 

void String::free()
{
	delete[] string;
	string = nullptr;
	length = 0;
}

void String::copyFrom(const String& str)
{
	this->length = str.length;
	this->string = new char[str.length + 1];
	strcpy(this->string, str.string);
}

String::String()
{
	setString("");
}

String::String(const char* str)
{
	setString(str);
}

String::String(const String& str)
{
	copyFrom(str);
}

String& String::operator=(const String& str)
{
	if (this != &str) {
		free();
		copyFrom(str);
	}
	return *this;
}

String& String::operator=(const char* str)
{
	if (str != this->string) {
		setString(str);
	}
	return *this;
}

String::~String()
{
	free();
}

void String::setString(const char* str)
{
	free();
	if (str != nullptr) {
		setLen(strlen(str));
		string = new char[length + 1];
		strcpy(string, str);
	}
	else {
		string = new char[1];
		string[0] = '\0';
		length = 0;
	}
}

char* String::getString() const
{
	return string;
}

void String::setLen(const size_t length)
{
	this->length = length;
}

size_t String::getLen() const
{
	return length;
}

bool String::operator==(const String& other) const
{
	if (this->length != other.length) return false;
	for (size_t i = 0; i < this->length; i++) {
		if (this->string[i] != other.string[i]) {
			return false;
		}
	}
	return true;
}

char String::getSymbol(int index) const
{
	if (index < 0 || static_cast<size_t>(index) >= length) {
		throw std::out_of_range("Index out of range");
	}
	return string[index];
}

bool String::starts_with(const String& str) const
{
	if (str.getLen() > this->getLen()) return false;
	for (size_t i = 0; i < str.getLen(); i++) {
		if (str.getString()[i] != this->string[i]) {
			return false;
		}
	}
	return true;
}

char& String::operator[](size_t index)
{
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}
	return string[index];
}

const char& String::operator[](size_t index) const
{
	if (index >= length) {
		throw std::out_of_range("Index out of range");
	}
	return string[index];
}

std::istream& String::getline(std::istream& is, String& str)
{
	String temp;
	//std::getline(is, temp); 
	return is;
}

String String::getFirstWord()const
{
	size_t i = 0;
	while (string[i] != ' ' && string[i] != '\0') {
		i++;
	}
	return get(i);
}

const char* String::c_str() const
{
	return string;
}

String String::get(size_t start, size_t end) const
{
	String result;
	if (start < end && end <= length) {
		size_t newLen = end - start;
		char* buffer = new char[newLen + 1];
		for (size_t i = 0; i < newLen; ++i) {
			buffer[i] = string[start + i];
		}
		buffer[newLen] = '\0';
		result.setString(buffer);
		delete[] buffer;
	}
	return result;
}

String String::get(size_t start) const
{
	return get(start, length);
}

std::istream& operator>>(std::istream& is, String& other)
{
	char buffer[1024];
	is >> buffer;
	other = buffer;
	return is;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
	os << other.getString();
	return os;
}
