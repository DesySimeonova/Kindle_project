#pragma once
#include <fstream>

class MyString
{
private:

	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();

public:


	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	bool operator==(const MyString& other);
	MyString& operator+=(const MyString& other);
	

	~MyString();

	void setString(const char* data);

	size_t getSize() const;
	void concat(const MyString& other);
	const char* getString() const;
	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&);

}; 