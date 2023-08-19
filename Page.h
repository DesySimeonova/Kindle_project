#pragma once
#include "MyString.h"

class Page
{
	MyString content;
	size_t num;

public:

	Page();
	Page(const MyString& str, size_t num);

	MyString getContent() const;
	size_t getNum() const;

	void setContent(const MyString& str);
	void setNum(size_t num);
	friend std::ostream& operator<<(std::ostream&, const Page&);

}; 
