#pragma once

#include "User.h"
#include "Book.h"

class Kindle
{
private:
	User* users;
	size_t numOfUsers;
	size_t allocatedUsersCount;
	Book* books;
	size_t numOfBooks;
	size_t allocatedBooksCount;
	User currUser;

	void copyFrom(const Kindle&);
	void free();
	void resizeUsers();
	void resizeBooks();
	void addUser(const MyString& username, const MyString& password);
	Book getBook(size_t i) const;
	Book getBook(MyString title)const;
	void addBook();

public:
	Kindle();
	Kindle(const Kindle&);
	Kindle& operator=(const Kindle&);



	size_t getNumOfUsers()const;
	size_t getNumOfBooks() const;
	User getUsers(size_t i) const;
	void readBook(const MyString& bookTitle);
	void writeBook();



	bool loadKindle(const MyString& username, const MyString& password);
	void workWithKindle(MyString& command);
	void signup();




	~Kindle();
};