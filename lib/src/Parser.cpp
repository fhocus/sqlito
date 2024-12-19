/**
 * @file Parser.cpp
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#include <sqlito/Parser.h>
#include <sstream>
#include <iostream>
#include <vector>

namespace SQLito
{
  Parser::Parser() {}

  Parser::~Parser() {}

  std::queue<Command *> Parser::parse(std::string command)
  {
    _command = command;
    _commandStream.str(_command);

    std::string token;

    _getNextContent(token);

    if (token == "CREATE")
      return _createQuery();
    else if (token == "INSERT")
      return _insertQuery();
    else if (token == "DELETE")
      return _deleteQuery();

    return std::queue<Command *>();
  }

  std::queue<Command *> Parser::_createQuery()
  {
    std::string token;
    _getNextContent(token);

    if (token == "TABLE")
      return _createTableQuery();
    else if (token == "DATABASE")
      return _createDatabaseQuery();
    else if (token == "INDEX")
      return _createIndexQuery();

    return std::queue<Command *>();
  }

  std::queue<Command *> Parser::_createTableQuery()
  {
    std::queue<Command *> commands;
    std::string tableName, fields, field, fieldName, fieldType;
    std::stringstream fieldsStream, fieldStream;
    std::vector<std::vector<std::string>> arguments;

    Command *command = new Command();
    command->setType(CommandType::CREATE_TABLE);

    _getNextContent(tableName);
    command->setTable(tableName);

    _getBetweenContent(fields);
    fieldsStream.str(fields);

    while (std::getline(fieldsStream, field, ','))
    {
      fieldStream.clear();
      fieldStream.str(field);
      _getNextContent(fieldName, fieldStream);
      _getNextContent(fieldType, fieldStream);

      arguments.push_back({fieldName, fieldType});
    }

    command->setArguments(arguments);

    commands.push(command);

    return commands;
  }

  std::queue<Command *> Parser::_createDatabaseQuery()
  {
    std::queue<Command *> commands;
    std::string databaseName, fields, field, fieldName, fieldValue;
    std::stringstream fieldsStream, fieldStream;
    std::vector<std::vector<std::string>> arguments;

    Command *command = new Command();
    command->setType(CommandType::CREATE_DATABASE);

    _getNextContent(databaseName);
    command->setTable(databaseName);

    _getBetweenContent(fields);
    fieldsStream.str(fields);

    while (std::getline(fieldsStream, field, ','))
    {
      fieldStream.clear();
      fieldStream.str(field);
      _getNextContent(fieldName, fieldStream);
      _getNextContent(fieldValue, fieldStream);

      arguments.push_back({fieldName, fieldValue});
    }

    command->setArguments(arguments);

    commands.push(command);

    return commands;
  }

  std::queue<Command *> Parser::_createIndexQuery()
  {
    std::queue<Command *> commands;
    return commands;
  }

  std::queue<Command *> Parser::_insertQuery()
  {
    std::string token;
    _getNextContent(token);

    if (token == "INTO")
      return _insertTableQuery();

    return std::queue<Command *>();
  }

  std::queue<Command *> Parser::_insertTableQuery()
  {
    std::queue<Command *> commands;
    std::string token, tableName, fields, fieldName, values, value;
    std::stringstream fieldsStream, fieldStream, valuesStream, valueStream;
    std::vector<std::string> argumentFields, argumentValues;
    std::vector<std::vector<std::string>> arguments;

    Command *command = new Command();
    command->setType(CommandType::INSERT_TABLE);

    _getNextContent(tableName);
    command->setTable(tableName);

    _getBetweenContent(fields);
    fieldsStream.str(fields);

    std::cout << fields << std::endl;

    while (std::getline(fieldsStream, fieldName, ','))
    {
      fieldStream.clear();
      fieldStream.str(fieldName);
      _getNextContent(fieldName, fieldStream);

      argumentFields.push_back(fieldName);
    }

    _getNextContent(token);

    if (token != "VALUES")
      return commands;

    _getBetweenContent(values);
    valuesStream.str(values);

    while (std::getline(valuesStream, value, ','))
    {
      valueStream.clear();
      valueStream.str(value);
      _getNextContent(value, valueStream);

      argumentValues.push_back(value);
    }

    arguments.push_back(argumentFields);
    arguments.push_back(argumentValues);

    command->setArguments(arguments);

    commands.push(command);

    return commands;
  }

  std::queue<Command *> Parser::_deleteQuery()
  {
    std::string token;
    _getNextContent(token);

    if (token == "FROM")
      return _deleteTableQuery();

    return std::queue<Command *>();
  }

  std::queue<Command *> Parser::_deleteTableQuery()
  {
    std::queue<Command *> commands;
    std::string token, tableName;
    std::vector<std::vector<std::string>> arguments;

    _getNextContent(tableName);
    Command *command = new Command();
    command->setType(CommandType::SET);
    command->setTable(tableName);
    commands.push(command);

    std::cout << tableName << std::endl;

    _getNextContent(token);

    std::cout << token << std::endl;

    if (token == "WHERE")
    {
      command = new Command();
      command->setType(CommandType::SELECTION);
      std::cout << tableName << std::endl;
      _getWhereContent(arguments, tableName);
    }

    command = new Command();
    command->setType(CommandType::DELETE_TABLE);
    command->setTable(tableName);
    commands.push(command);

    return commands;
  }

  int Parser::_getNextContent(std::string &content)
  {
    _commandStream >> std::ws;

    if (_commandStream.eof())
      return 0;

    char c;
    _commandStream >> c;

    if (c == '\'' || c == '"' || c == '`')
    {
      std::getline(_commandStream, content, c);
      switch (c)
      {
      case '\'':
        return 2;
      case '"':
        return 3;
      case '`':
        return 4;
      default:
        return -1;
      }
    }
    else
    {
      content = c;
      while (_commandStream.get(c))
      {
        if (c == ',' || c == '.' || c == ' ')
          break;
        content += c;
      }
      return 1;
    }
  }

  int Parser::_getNextContent(std::string &content, std::stringstream &stream)
  {
    stream >> std::ws;

    char c;
    stream >> c;

    if (c == '\'' || c == '"' || c == '`')
    {
      std::getline(stream, content, c);
      switch (c)
      {
      case '\'':
        return 2;
      case '"':
        return 3;
      case '`':
        return 4;
      default:
        return -1;
      }
    }
    else
    {
      content = c;
      while (stream.get(c))
      {
        if (c == ',' || c == '.' || c == ' ')
          break;
        content += c;
      }
      return 1;
    }
  }

  int Parser::_getBetweenContent(std::string &content)
  {
    _commandStream >> std::ws;

    char c;
    _commandStream >> c;

    if (c == '(')
    {
      int level = 1;

      while (_commandStream.get(c))
      {
        if (c == '(')
          level++;
        else if (c == ')')
          level--;

        if (level == 0)
          break;

        content += c;
      }

      return 1;
    }
    return -1;
  }

  int Parser::_getWhereContent(std::vector<std::vector<std::string>> &arguments, std::string &mainTableName)
  {
    _commandStream >> std::ws;
    std::string logicOperator = "AND", fieldTable, fieldName, comparisonOperator, fieldValue;
    std::vector<std::string> argument;

    while (logicOperator == "AND" || logicOperator == "OR")
    {
      argument.push_back(logicOperator);

      _getWhereComponentContent(fieldTable, fieldName, mainTableName);

      argument.push_back(fieldTable);
      argument.push_back(fieldName);

      std::cout << fieldTable << " " << fieldName << std::endl;

      _getNextContent(comparisonOperator);
      argument.push_back(comparisonOperator);

      _getWhereComponentContent(fieldTable, fieldValue, mainTableName);
      argument.push_back(fieldTable);
      argument.push_back(fieldValue);
      std::cout << fieldTable << " " << fieldValue << std::endl;

      arguments.push_back(argument);
      argument.clear();

      _getNextContent(logicOperator);
    }

    return 1;
  }

  int Parser::_getWhereComponentContent(std::string &first, std::string &second, std::string &defaultFirst)
  {
    std::stringstream tokenStream;
    std::string token;
    int rest = _getNextContent(first);

    if (rest == 1)
    {
      if (first.find('.') != std::string::npos)
      {
        tokenStream.str(first);
        std::getline(tokenStream, token, '.');
        std::stringstream tmpStream(token);
        _getNextContent(first, tmpStream);
        std::getline(tokenStream, token, '.');
        tmpStream.clear();
        tmpStream.str(token);
        _getNextContent(second, tmpStream);
      }
      else
      {
        second = first;
        first = defaultFirst;
      }
    }
    else if (rest == 2)
    {
      char c;
      _commandStream >> c;
      if (c == '.')
        _getNextContent(second);
    }
    else
      return -1;

    return 1;
  }
}