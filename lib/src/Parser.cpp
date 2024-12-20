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
    _commandStream.clear();
    _commandStream.str(_command);

    std::string token;

    _getNextContent(token);

    if (token == "CREATE")
      return _createQuery();
    else if (token == "INSERT")
      return _insertQuery();
    else if (token == "SELECT")
      return _selectQuery();
    else if (token == "DELETE")
      return _deleteQuery();
    else if (token == "UPDATE")
      return _updateQuery();

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

    while (std::getline(fieldsStream, fieldName, ','))
    {
      fieldStream.clear();
      fieldStream.str(fieldName);
      _getNextContent(fieldName, fieldStream);

      argumentFields.push_back(fieldName);
    }

    _getNextContent(token);

    if (token != "VALUES")
    {
      delete command;
      return commands;
    }

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

  std::queue<Command *> Parser::_selectQuery()
  {
    return _selectTableQuery();
  }

  std::queue<Command *> Parser::_selectTableQuery()
  {
    std::queue<Command *> commands;
    std::string token, tableName;
    std::vector<std::vector<std::string>> arguments;
    Command *commandProjection, *command;

    commandProjection = new Command();
    commandProjection->setType(CommandType::PROJECTION);
    _getSelectContent(arguments);

    _getNextContent(token);
    if (token != "FROM")
    {
      delete commandProjection;
      return commands;
    }

    _getNextContent(tableName);

    for (std::vector<std::string> &argument : arguments)
    {
      for (std::string &field : argument)
      {
        if (field == "_")
          field = tableName;
      }
    }

    commandProjection->setTable(tableName);
    commandProjection->setArguments(arguments);
    arguments.clear();

    command = new Command();
    command->setType(CommandType::SET);
    command->setTable(tableName);
    commands.push(command);

    int rest;

    do
    {
      rest = _getJoinContent(commands, tableName);

      if (rest == 0)
        break;
      else if (rest == -1)
        return std::queue<Command *>();
    } while (rest == 1);

    _getNextContent(token);
    if (token == "WHERE")
    {
      command = new Command();
      _getWhereContent(arguments, tableName);
      command->setType(CommandType::SELECTION);
      command->setTable(tableName);
      command->setArguments(arguments);
      commands.push(command);
    }

    commands.push(commandProjection);

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

    if (_getNextContent(token))
      if (token == "WHERE")
      {
        command = new Command();
        _getWhereContent(arguments, tableName);
        command->setType(CommandType::SELECTION);
        command->setTable(tableName);
        command->setArguments(arguments);
        commands.push(command);
      }

    command = new Command();
    command->setType(CommandType::DELETE_TABLE);
    command->setTable(tableName);
    commands.push(command);

    return commands;
  }

  std::queue<Command *> Parser::_updateQuery()
  {
    return _updateTableQuery();
  }

  std::queue<Command *> Parser::_updateTableQuery()
  {
    std::queue<Command *> commands;
    std::string token, tableName;
    std::vector<std::vector<std::string>> arguments;

    _getNextContent(tableName);
    _getNextContent(token);

    if (token != "SET")
      return std::queue<Command *>();

    Command *command = new Command();
    command->setType(CommandType::SET);
    command->setTable(tableName);
    commands.push(command);

    command = new Command();
    _getSetContent(arguments, tableName);
    command->setType(CommandType::MODIFY);
    command->setTable(tableName);
    command->setArguments(arguments);
    commands.push(command);

    arguments.clear();

    _getNextContent(token);

    if (token == "WHERE")
    {
      command = new Command();
      _getWhereContent(arguments, tableName);
      command->setType(CommandType::SELECTION);
      command->setTable(tableName);
      command->setArguments(arguments);
      commands.push(command);
    }

    command = new Command();
    command->setType(CommandType::UPDATE_TABLE);
    command->setTable(tableName);
    commands.push(command);

    return commands;
  }

  int Parser::_getNextContent(std::string &content)
  {
    content.clear();
    _commandStream >> std::ws;

    char c;
    _commandStream >> c;

    if (_commandStream.fail())
      return 0;

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
      _commandStream.unget();
      while (_commandStream.get(c))
      {
        if (c == ',' || c == '.' || c == ' ')
        {
          _commandStream.unget();
          break;
        }
        content += c;
      }
      return 1;
    }
  }

  int Parser::_getNextContent(std::string &content, std::stringstream &stream)
  {
    content.clear();
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
      stream.unget();
      while (stream.get(c))
      {
        if (c == ',' || c == '.' || c == ' ')
        {
          stream.unget();
          break;
        }
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
      std::string auxTableName = "";
      argument.push_back(logicOperator);

      _getWhereComponentContent(fieldTable, fieldName, mainTableName);

      if (fieldTable != mainTableName)
        auxTableName = fieldTable;

      argument.push_back(fieldTable);
      argument.push_back(fieldName);

      _getNextContent(comparisonOperator);
      argument.push_back(comparisonOperator);

      _getWhereComponentContent(fieldTable, fieldValue, mainTableName);

      if (fieldTable == mainTableName && !auxTableName.empty())
        argument.push_back(auxTableName);
      else
        argument.push_back(fieldTable);
      argument.push_back(fieldValue);

      arguments.push_back(argument);
      argument.clear();
      auxTableName.clear();

      if (!_getNextContent(logicOperator))
        break;
    }

    return 1;
  }

  int Parser::_getWhereComponentContent(std::string &first, std::string &second, std::string &defaultFirst)
  {
    std::stringstream tokenStream;
    std::string token;
    int rest = _getNextContent(first);

    char c;
    _commandStream.get(c);
    if (c == '.')
      _getNextContent(second);
    else
    {
      _commandStream.unget();
      second = first;
      first = defaultFirst;
    }

    return 1;
  }

  int Parser::_getSetContent(std::vector<std::vector<std::string>> &arguments, std::string &mainTableName)
  {
    _commandStream >> std::ws;
    std::string fieldTable, fieldName, comparisonOperator, fieldValue;
    std::vector<std::string> argument;
    char delimiter = ',';

    while (delimiter == ',')
    {
      std::string auxTableName = "";
      _getSetComponentContent(fieldTable, fieldName, mainTableName);

      if (fieldTable != mainTableName)
        auxTableName = fieldTable;

      argument.push_back(fieldTable);
      argument.push_back(fieldName);

      _getNextContent(comparisonOperator);
      argument.push_back(comparisonOperator);

      _getSetComponentContent(fieldTable, fieldValue, mainTableName);

      if (fieldTable == mainTableName && !auxTableName.empty())
        argument.push_back(auxTableName);
      else
        argument.push_back(fieldTable);
      argument.push_back(fieldValue);

      arguments.push_back(argument);
      argument.clear();

      _commandStream >> delimiter;
      if (_commandStream.fail())
        break;
    }

    _commandStream.unget();

    return 1;
  }

  int Parser::_getSetComponentContent(std::string &first, std::string &second, std::string &defaultFirst)
  {
    std::stringstream tokenStream;
    std::string token;
    int rest = _getNextContent(first);

    char c;
    _commandStream.get(c);
    if (c == '.')
      _getNextContent(second);
    else
    {
      _commandStream.unget();
      second = first;
      first = defaultFirst;
    }

    return 1;
  }

  int Parser::_getSelectContent(std::vector<std::vector<std::string>> &arguments)
  {
    _commandStream >> std::ws;
    std::string fieldTable, fieldName;
    std::vector<std::string> argument;
    char delimiter = ',';

    while (delimiter == ',')
    {
      _getSelectComponentContent(fieldTable, fieldName);

      argument.push_back(fieldTable);
      argument.push_back(fieldName);

      arguments.push_back(argument);
      argument.clear();

      _commandStream >> delimiter;

      if (_commandStream.fail())
        break;
    }

    _commandStream.unget();

    return 1;
  }

  int Parser::_getSelectComponentContent(std::string &first, std::string &second)
  {
    std::stringstream tokenStream;
    std::string token;
    int rest = _getNextContent(first);

    char c;
    _commandStream.get(c);
    if (c == '.')
      _getNextContent(second);
    else
    {
      _commandStream.unget();
      second = first;
      first = "_";
    }

    return 1;
  }

  int Parser::_getJoinContent(std::queue<Command *> &commands, std::string &mainTableName)
  {
    std::string token, tableName, fieldTable, fieldName, fieldValue;
    std::vector<std::vector<std::string>> arguments;
    std::vector<std::string> argument;
    Command *commandSet, *commandJoin;
    char c;

    auto marker = _commandStream.tellg();
    _getNextContent(token);

    if (token != "LEFT" && token != "RIGHT" && token != "JOIN")
    {
      _commandStream.seekg(marker);
      return 0;
    }

    marker = _commandStream.tellg();
    if (token != "JOIN")
    {
      _getNextContent(token);
      if (token != "JOIN")
      {
        _commandStream.seekg(marker);
        return -1;
      }
    }

    _getNextContent(tableName);
    arguments.push_back({mainTableName});

    commandSet = new Command();
    commandSet->setType(CommandType::SET);
    commandSet->setTable(tableName);
    commands.push(commandSet);

    _getNextContent(token);

    if (token != "ON")
    {
      _commandStream.seekg(marker);
      return -1;
    }

    _getNextContent(fieldTable);
    _commandStream.get(c);
    _getNextContent(fieldName);

    argument.push_back(fieldTable);
    argument.push_back(fieldName);

    _getNextContent(token);
    argument.push_back(token);

    _getNextContent(fieldTable);
    _commandStream.get(c);
    _getNextContent(fieldValue);
    argument.push_back(fieldTable);
    argument.push_back(fieldValue);

    arguments.push_back(argument);

    commandJoin = new Command();
    commandJoin->setType(CommandType::JOIN);
    commandJoin->setTable(tableName);
    commandJoin->setArguments(arguments);
    commands.push(commandJoin);

    return 1;
  }
}