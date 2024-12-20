/**
 * @file Command.cpp
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#include <sqlito/Command.h>

namespace SQLito
{
  Command::Command() {}

  Command::~Command() {}

  CommandType Command::getType() const
  {
    return _type;
  }

  std::string Command::getTypeString() const
  {
    switch (getType())
    {
    case CommandType::CREATE_TABLE:
      return "CREATE TABLE";
    case CommandType::CREATE_DATABASE:
      return "CREATE DATABASE";
    case CommandType::CREATE_INDEX:
      return "CREATE INDEX";
    case CommandType::INSERT_TABLE:
      return "INSERT TABLE";
    case CommandType::DELETE_TABLE:
      return "DELETE TABLE";
    case CommandType::UPDATE_TABLE:
      return "UPDATE TABLE";
    case CommandType::SELECTION:
      return "SELECTION";
    case CommandType::PROJECTION:
      return "PROJECTION";
    case CommandType::MODIFY:
      return "MODIFY";
    case CommandType::JOIN:
      return "JOIN";
    case CommandType::SET:
      return "SET";
    default:
      return "UNKNOWN";
    }
  }

  std::string Command::getTable() const
  {
    return _table;
  }

  std::vector<std::vector<std::string>> Command::getArguments() const
  {
    return _arguments;
  }

  void Command::setType(CommandType type)
  {
    _type = type;
  }

  void Command::setTable(std::string table)
  {
    _table = table;
  }

  void Command::setArguments(std::vector<std::vector<std::string>> arguments)
  {
    _arguments = arguments;
  }

  std::ostream &operator<<(std::ostream &os, const Command &command)
  {
    os << "Command (" << "\n";
    os << "\tType: " << command.getTypeString() << "\n";
    os << "\tTable: " << command.getTable() << "\n";
    os << "\tArguments: [" << "\n";

    for (const std::vector<std::string> &argument : command.getArguments())
    {
      os << "\t\t[ ";
      for (int i = 0; i < argument.size() - 1; i++)
      {
        os << argument[i] << ", ";
      }
      os << argument[argument.size() - 1] << " ]" << "\n";
    }

    os << "\t]" << "\n";

    os << ")";
    return os;
  }
}