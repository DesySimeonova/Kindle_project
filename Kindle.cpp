
#include"Kindle.h"
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

void Kindle::copyFrom(const Kindle& other)
{
    users = new User[other.numOfUsers];
    for (size_t i = 0; i < other.numOfUsers; i++)
        users[i] = other.users[i];
    numOfUsers = other.numOfUsers;
    allocatedUsersCount = other.allocatedUsersCount;

    for (size_t i = 0; i < numOfBooks; i++)
        books[i] = other.books[i];
    numOfBooks = other.numOfBooks;
    allocatedBooksCount = other.allocatedBooksCount;
    currUser = other.currUser;

}

void Kindle::free()
{
    delete[] users;
    delete[] books;
}

void Kindle::resizeUsers()
{
    allocatedBooksCount *= 2;
    User* newUsers = new User[allocatedUsersCount];
    for (size_t i = 0; i < numOfUsers; i++)
        newUsers[i] = users[i];

    delete[] users;
    users = newUsers;
}

void Kindle::resizeBooks()
{
    allocatedBooksCount *= 2;
    Book* newBooks = new Book[allocatedBooksCount];
    for (size_t i = 0; i < numOfBooks; i++)
        newBooks[i] = books[i];

    delete[] books;
    books = newBooks;
}

Kindle::Kindle()
{
    allocatedUsersCount = 8;
    users = new User[allocatedUsersCount];
    numOfUsers = 0;

    allocatedBooksCount = 8;
    books = new Book[allocatedBooksCount];
    numOfBooks = 0;

}

Kindle::Kindle(const Kindle& other)
{
    copyFrom(other);
}

Kindle& Kindle::operator=(const Kindle& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

void Kindle::addUser(const MyString& username, const MyString& password)
{

    if (numOfUsers > allocatedUsersCount)
        resizeUsers();

    User newUser(username, password);

    users[numOfUsers] = newUser;
    numOfUsers++;


}


void Kindle::addBook()
{
   if (numOfBooks > allocatedBooksCount)
        resizeBooks();

    books[numOfBooks] = currUser.write();
    numOfBooks++;
}

size_t Kindle::getNumOfUsers()const
{
    return numOfUsers;
}

size_t Kindle::getNumOfBooks() const
{
    return numOfBooks;
}

User Kindle::getUsers(size_t i) const
{
    return users[i];
}

Book Kindle::getBook(size_t i) const
{
    return books[i];
}

Book Kindle::getBook(MyString title)const
{
    if (numOfBooks > 0)
    {
        for (int i = 0; i < numOfBooks; i++)
        {
            if (title == books[i].getTitle())
            {
                return books[i];
            }
        }
        cout << "There is no such book in Kindle!" << '\n';
    }
    else
        cout << "There is no books in Kindle!" << '\n';
}

void Kindle::signup()
{
    char username[20];
    std::cout << "Enter username: ";
    std::cin.getline(username, 20);

    char password[20];
    std::cout << "Enter password: ";
    std::cin.getline(password, 20);

    addUser(username, password);
    std::cout << "User has been registered!" <<std::endl;
}

bool file_exists(const MyString name)
{
    ifstream file(name.getString(), ios::_Nocreate);
    if (file.fail())
    {
        file.close();
        return false;
    }
    else
    {
        file.close();
        return true;
    }
}

char* getBookInfo(char* lineBuff, size_t iter1, size_t iter2, char ch)
{
    char* bookInfo = new char[30];
    size_t count = 0;
    bool isLastInfo = true;
    for (size_t k = iter1; k < iter2; k++)
    {
        if (lineBuff[k] == ch)
        {
            bookInfo[count] = '\0';
            isLastInfo = false;
            break;
        }
        else
        {
            bookInfo[count] = lineBuff[k];
            count++;
        }
    }
    if (isLastInfo)
        bookInfo[count] = '\0';

    return bookInfo;
}

void Kindle::readBook(const MyString& bookTitle)
{
    if (numOfBooks > 0) 
    {
        for (int i = 0; i < numOfBooks; i++) 
        {
            if (books[i].getTitle() == bookTitle)
            {
                cout << books[i]<<"\n";
                currUser.read(books[i]);
            }
        }
    }
    else {
        cout << "There is no books in Kindle!";
    }
}

void Kindle::writeBook() 
{
    addBook();
}


bool Kindle::loadKindle(const MyString& username, const MyString& password)
{
    if (numOfUsers > 0) {
        for (int i = 0; i < numOfUsers; i++) {
            if (users[i].getUsername() == username && users[i].getPassword() == password)
            {
                currUser = users[i];
                return true;
            }
        }
        std::cout << "There is no user with these username and password!" << '\n';
        return false;
    }
    else {
        throw std::logic_error("There is no users in Kindle!");
    }
   
}

void Kindle::workWithKindle(MyString& command)
{
    if(command=="read")
    {
        MyString book;
        cout << '\n' << "Please enter the title of the book you would like to read: "<<'\n';
        cin >> book;
        readBook(book);
    }
    else if (command == "write") 
    {
        addBook();
    }
    else if (command == "coments")
    {
        MyString book;
        cout << '\n' << "Please enter the title of the book you would like to see comments about: " << '\n';
        cin >> book;
        Book b = getBook(book);
        b.getComments();
    }
    else if (command == "addComment")
    {
        MyString book;
        cout << '\n' << "Please enter the title of the book you would like to add comment about: " << '\n';
        cin >> book;
        MyString comment;
        cout << "Please enter your comment: " << '\n';
        cin >> comment;
        Book b = getBook(book);
        currUser.addCommentOfBook(b, comment);
    }
   
}


Kindle::~Kindle()
{
    free();
}