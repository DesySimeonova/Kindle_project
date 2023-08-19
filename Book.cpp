#include "Book.h"
#include <iostream>


void Book::copyFrom(const Book& other)
{
	title = other.title;
	author = other.author;

	if (numOfPages > 0)
		pages = new Page[other.numOfPages];
	for (size_t i = 0; i < other.numOfPages; i++)
		pages[i] = other.pages[i];
	numOfPages = other.numOfPages;
	allocatedPagesCount = other.allocatedPagesCount;

	if (numOfComments > 0)
		comments = new MyString[other.numOfComments];
	for (size_t i = 0; i < other.numOfComments; i++)
		comments[i] = other.comments[i];
	numOfComments = other.numOfComments;
	allocatedCommentsCounts = other.allocatedCommentsCounts;

}

void Book::free()
{
	if (pages != nullptr)
		delete[] pages;
	if (comments != nullptr)
		delete[] comments;
}

void Book::resizePages()
{
	allocatedPagesCount *= 2;
	Page* newPages = new Page[allocatedPagesCount];

	for (int i = 0; i < numOfPages; i++) {
		newPages[i] = pages[i];
	}

	delete[] pages;
	pages = newPages;

}

void Book::resizeComments()
{
	allocatedCommentsCounts *= 2;
	MyString* newComments = new MyString[allocatedCommentsCounts];

	for (size_t i = 0; i < numOfComments; i++)
		newComments[i] = comments[i];

	delete[] comments;
	comments = newComments;

}

Book::Book()
{

	title = "";
	author = "";

	allocatedPagesCount = 8;
	//pages = new Page[allocatedPagesCount];
	pages = nullptr;
	numOfPages = 0;

	allocatedCommentsCounts = 8;
	//comments = new MyString[allocatedCommentsCounts];
	comments = nullptr;
	numOfComments = 0;

}

void indexOfLastSpaceInPage(const MyString& str, size_t& sizeOfPage)
{
	size_t i = sizeOfPage;
	for (i = sizeOfPage; i < str.getSize(); i++)
	{
		if (str.getString()[i] == ' ')
		{
			sizeOfPage = i;
			return;
		}
	}

	
}

MyString getPageContent(const MyString& content, size_t firstIndex, size_t lastIndex)
{
	size_t newPageSize = (lastIndex + 1) - firstIndex;
	char* newPageContent = new char[newPageSize];
	size_t newPageIter = 0;
	for (size_t i = firstIndex; i < lastIndex; i++)
	{
		newPageContent[newPageIter] = content.getString()[i];
		newPageIter++;
	}
	
	MyString newPage(newPageContent);

	delete[] newPageContent;

	return newPage;
}

Book::Book(const MyString& title, const MyString& author, const MyString& content, size_t numOfPages)
{
	this->title = title;
	this->author = author;


	allocatedPagesCount = 8;
	pages = new Page[allocatedPagesCount]; 
	this->numOfPages = numOfPages;

	allocatedCommentsCounts = 8;
	comments = new MyString[allocatedCommentsCounts];
	this->numOfComments = numOfComments;

	/////////////////////

	
	size_t pageSize = content.getSize() / numOfPages;
	size_t firstIndex = 0;
	size_t lastIndex = pageSize;
	indexOfLastSpaceInPage(content, lastIndex);

	for (size_t i = 0; i < numOfPages; i++)
	{
		pages[i].setContent(getPageContent(content, firstIndex, lastIndex));
		firstIndex = lastIndex + 1;
		lastIndex = pageSize * 2;

	}

}

Book::Book(const Book& other)
{
	copyFrom(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}


std::ostream& operator<<(std::ostream& ofs, const Book& book)
{
	return ofs << book.title;
}

MyString Book::getTitle() const
{
	return title;
}

const MyString Book::getAuthor() const
{
	return author;
}

const MyString Book::getPage(size_t numOfPage) const
{
	return pages[numOfPage].getContent();
}

void Book::getComments()const
{
	if (numOfComments > 0) {
		for (int i = 0; i < numOfComments; i++) {
			std::cout << comments[i] << '\n';
		}
	}
	else
		std::cout << "There is no comments for this book." << '\n';
}

void Book::addComment(const MyString& comment)
{
	if (numOfComments <= allocatedCommentsCounts) {
		resizeComments();
	}
	comments[numOfComments] = comment;
	numOfComments++;
}

std::ostream& operator<<(std::ostream& out, const Book& book) {

	out << "Content:\n";
	for (size_t i = 0; i < book.numOfPages; i++) {
		out << "Page " << (i + 1) << ":\n";
		out << book.pages[i] << "\n";
	}

	return out;
}



Book::~Book()
{
	free();
}

