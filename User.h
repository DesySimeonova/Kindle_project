#pragma once

#include "Book.h"

class User
{
	MyString username;
	MyString password;
	Book* readBooks;
	size_t numOfReadBooks;
	size_t allocatedReadBooksCount;
	Book* writtenBooks;
	size_t numOfWrittenBooks;
	size_t allocatedWrittenBooksCount;


	void copyFrom(const User&);
	void free();
	void resizeReadBooks();
	void resizeWrittenBooks();

public:

	User();
	User(const MyString username, const MyString password);
	User(const User&);
	User& operator=(const User&);

	MyString getUsername() const;
	MyString getPassword() const;
	const Book* getReadBooks() const;
	const Book* getWrittenBooks() const;
	const size_t getNumOfReadBooks() const;
	const size_t getNumOfWrittenBooks() const;
	void getCommentsOfBook(const Book& book) const;

	void setUsername(const MyString&);
	void setPassword(const MyString&);
	void addReadBook(const Book& newReadBook);
	void addWrittenBook(const Book& newWrittenBook);
	void addCommentOfBook(Book& book, const MyString& comment)const;
	const MyString visualizationOfPage(const Book& book, size_t numOfPage) const;
	

	void read(const Book& book);
	Book write();

	~User();

};