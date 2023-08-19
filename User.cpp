
#include "User.h"
#include <iostream>

void User::copyFrom(const User& other)
{
	username = other.username;
	password = other.password;

	readBooks = new Book[other.allocatedReadBooksCount];
	for (size_t i = 0; i < other.numOfReadBooks; i++)
		readBooks[i] = other.readBooks[i];
	numOfReadBooks = other.numOfReadBooks;
	allocatedReadBooksCount = other.allocatedReadBooksCount;

	writtenBooks = new Book[other.numOfWrittenBooks];
	for (size_t i = 0; i < other.numOfWrittenBooks; i++)
		writtenBooks[i] = other.writtenBooks[i];
	numOfWrittenBooks = other.numOfWrittenBooks;
	allocatedWrittenBooksCount = other.allocatedWrittenBooksCount;

}

void User::free()
{
	delete[] readBooks;
	delete[] writtenBooks;
}

void User::resizeReadBooks()
{
	allocatedReadBooksCount *= 2;
	Book* newReadBooks = new Book[allocatedReadBooksCount];

	for (int i = 0; i < numOfReadBooks; i++)
		newReadBooks[i] = readBooks[i];


	delete[] readBooks;
	readBooks = newReadBooks;
}

void User::resizeWrittenBooks()
{
	allocatedWrittenBooksCount *= 2;
	Book* newWrittenBooks = new Book[allocatedWrittenBooksCount];

	for (size_t i = 0; i < numOfWrittenBooks; i++)
		newWrittenBooks[i] = writtenBooks[i];

	delete[] writtenBooks;
	writtenBooks = newWrittenBooks;
}


User::User()
{
	username = "";
	password = "";

	allocatedReadBooksCount = 8;
	readBooks = new Book[allocatedReadBooksCount];
	numOfReadBooks = 0;

	allocatedWrittenBooksCount = 8;
	writtenBooks = new Book[allocatedWrittenBooksCount];
	numOfWrittenBooks = 0;
}

User::User(const MyString username, const MyString password)
{
	this->username = username;
	this->password = password;

	allocatedReadBooksCount = 8;
	readBooks = new Book[allocatedReadBooksCount];
	numOfReadBooks = 0;

	allocatedWrittenBooksCount = 8;
	writtenBooks = new Book[allocatedWrittenBooksCount];
	numOfWrittenBooks = 0;
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

const Book* User::getWrittenBooks() const
{
	return writtenBooks;
}

MyString User::getUsername() const
{
	return username;
}

MyString User::getPassword() const
{
	return password;
}

const size_t User::getNumOfReadBooks() const
{
	return numOfReadBooks;
}

const size_t User::getNumOfWrittenBooks() const
{
	return numOfWrittenBooks;
}

const Book* User::getReadBooks() const
{
	return readBooks;
}

void User::getCommentsOfBook(const Book& book) const 
{
	book.getComments();
}


void User::setUsername(const MyString& username)
{
	if (!(this->username == username))
	{
		this->username = username;
	}
}

void User::setPassword(const MyString& password)
{
	if (!(this->password == password))
	{
		this->password = password;
	}
}

void User::addReadBook(const Book& newReadBook)
{
	if (numOfReadBooks > allocatedReadBooksCount)
		resizeReadBooks();

	readBooks[numOfReadBooks] = newReadBook;
	numOfReadBooks++;
}

void User::addCommentOfBook(Book& book, const MyString& comment) const
{
	book.addComment(comment);
}

void User::addWrittenBook(const Book& newWrittenBook)
{
	if (numOfWrittenBooks > allocatedWrittenBooksCount)
		resizeWrittenBooks();

	readBooks[numOfWrittenBooks] = newWrittenBook;
	numOfReadBooks++;
}

void User::read(const Book& book)
{
	for (size_t i = 0; i < numOfReadBooks; i++)
	{
		if (!(readBooks[i].getTitle() == book.getTitle()))
		{
			addReadBook(book);
		}
	}

	size_t numOfPage;
	char command;
	std::cout << "Num of page to be visualize: ";
	std::cin >> numOfPage;
	std::cout << std::endl;
	visualizationOfPage(book, numOfPage);
	std::cout << std::endl;
	std::cin >> command;
	while (command != 'q')
	{
		if (command == 'n')
		{
			numOfPage++;
			visualizationOfPage(book, numOfPage);
		}

		if (command == 'p' && numOfPage != 1)
		{
			numOfPage--;
			visualizationOfPage(book, numOfPage);
		}
		
	}

}

const MyString User::visualizationOfPage(const Book& book, size_t numOfPage) const
{
	return book.getPage(numOfPage);
}

Book User::write()
{
	MyString title;
	std::cout << "Enter title: ";
	std::cin >> title;
	std::cout << std::endl;

	size_t pagesCount;
	std::cout << "Enter pages count: ";
	std::cin >> pagesCount;
	std::cout << std::endl;

	MyString content;
	std::cin >> content;
	while (!(content == "quit"))
	{
		std::cin >> content;
	}

	Book b(title, username, content, pagesCount);
	addWrittenBook(b);
	return b;
}

User::~User()
{
	delete[] readBooks;
	delete[] writtenBooks;
}