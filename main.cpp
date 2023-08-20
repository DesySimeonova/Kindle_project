
#include <iostream>
#include "MyString.h"
#include "Kindle.h"

int main()
{
    Kindle kindle;
    MyString username;
    MyString password;
    std::cout << "Please enter your username:" << '\n';
    std::cin >> username;
    std::cout << "Please enter your password:" << '\n';
    std::cin >> password;
    MyString command;
    if (!kindle.loadKindle(username, password))
        command = "exit";
    else
    {
        std::cout << ">";
        std::cin >> command;
    }
    while (!(command == "exit"))
    {
        std::cout << ">";
        std::cin >> command;
        kindle.workWithKindle(command);

    }
}