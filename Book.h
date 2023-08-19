#pragma once
#include "MyString.h"
#include "Page.h"

class Book
{
	MyString title;
	MyString author;
	Page* pages;
	size_t numOfPages;
	size_t allocatedPagesCount;
	MyString* comments;
	size_t numOfComments;
	size_t allocatedCommentsCounts;

	void copyFrom(const Book&);
	void free();
	void resizePages();
	void resizeComments();

public:
	Book();
	Book(const MyString& title, const MyString& author, const MyString& content, size_t numOfPages);
	Book(const Book&);
	Book& operator=(const Book&);

	MyString getTitle() const;
	const MyString getAuthor() const;
	const MyString getPage(size_t numOfPage) const;
	void getComments()const;

	void addComment(const MyString&);
	friend std::ostream& operator<<(std::ostream&, const Book&);


	~Book();

}; 
