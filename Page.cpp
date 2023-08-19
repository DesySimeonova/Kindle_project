#include "Page.h"

Page::Page()
{
	content = "";
	num = 0;
}

Page::Page(const MyString& str, size_t num)
{
	content = str;
	this->num = num;
}

MyString Page::getContent() const
{
	return content;
}

size_t Page::getNum() const
{
	return num;
}

void Page::setContent(const MyString& str)
{
	content = str;
}

void Page::setNum(size_t num)
{
	this->num = num;
}

std::ostream& operator<<(std::ostream& out, const Page& p) {
	out <<p.getContent();
	return out;
}