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

  CommandType Command::getType()
  {
    return _type;
  }

  std::string Command::getTable()
  {
    return _table;
  }

  std::vector<std::vector<std::string>> Command::getArguments()
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
}