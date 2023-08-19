#include "MyString.h"
#include <cstring>
#pragma warning (disable:4996)

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	str = new char[size + 1];
	strcpy(str, other.str);
}

void MyString::free()
{
	delete[] str;
}

MyString::MyString()
{
	size = 0;
	str = new char[1];
	str[0] = '\0';
}
MyString::MyString(const char* data)
{
	size = strlen(data);
	str = new char[size + 1];
	strcpy(str, data);
}
MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
MyString::~MyString()
{
	free();
}

size_t MyString::getSize() const
{
	return size;
}
const char* MyString::getString() const
{
	return str;
}
void MyString::setString(const char* data)
{
	delete[] str;
	size = strlen(data);
	str = new char[size + 1];
	strcpy(str, data);
}
void MyString::concat(const MyString& other)
{
	size = size + other.size;
	char* temp = new char[size + 1];
	strcpy(temp, str);
	strcat(temp, other.str);

	delete[] str;
	str = temp;
}

MyString& MyString::operator+=(const MyString& other)
{
	concat(other.str);
	return *this;
}
bool MyString::operator==(const MyString& other)
{
	return strcmp(str, other.str) == 0;
}

std::ostream& operator<<(std::ostream& out, const MyString& str)
{
	out << str.str;
	return out;
}

std::istream& operator>>(std::istream& in, MyString& str)
{
	delete[] str.str;
	char buffer[1024];
	in >> buffer;

	str.size = strlen(buffer);
	str.str = new char[str.size + 1];
	strcpy(str.str, buffer);

	return in;
}



MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString temp(lhs);
	temp += rhs;
	return temp;
}