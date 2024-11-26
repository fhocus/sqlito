#include <iostream>
#include "SQLito.hpp"

int main()
{
    std::cout << "CREATE TABLE" << std::endl;
    for (auto command : SQLito::Parser::Parser::process("CREATE TABLE Persona (id INT, name VARCHAR(255), age INT);"))
    {
        std::cout << *command << std::endl;
    }

    std::cout << std::endl;

    std::cout << "INSERT INTO" << std::endl;
    for (auto command : SQLito::Parser::Parser::process("INSERT INTO Persona VALUES (1, 'Juan', 25), (2, 'Jose', 21);"))
    {
        std::cout << *command << std::endl;
    }
    std::cout << std::endl;

    for (auto command : SQLito::Parser::Parser::process("INSERT INTO Persona (name, age) VALUES ('Juan', 25), ('Jose', 21);"))
    {
        std::cout << *command << std::endl;
    }
    std::cout << std::endl;

    std::cout << "UPDATE" << std::endl;
    for (auto command : SQLito::Parser::Parser::process("UPDATE Persona SET age = 26 WHERE id = 1 AND name = 'Juan' OR name = 'Jose Alaya';"))
    {
        std::cout << *command << std::endl;
    }
    std::cout << std::endl;

    std::cout << "DELETE" << std::endl;
    for (auto command : SQLito::Parser::Parser::process("DELETE FROM Persona;"))
    {
        std::cout << *command << std::endl;
    }
    std::cout << std::endl;

    for (auto command : SQLito::Parser::Parser::process("DELETE FROM Persona WHERE id = 1 AND name = 'Juan' OR name = 'Jose Alaya';"))
    {
        std::cout << *command << std::endl;
    }
    std::cout << std::endl;

    return 0;
}