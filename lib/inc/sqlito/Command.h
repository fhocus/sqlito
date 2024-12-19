/**
 * @file Command.h
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#pragma once

#include <string>
#include <vector>

namespace SQLito
{
  enum class CommandType
  {
    CREATE_TABLE,
    CREATE_DATABASE,
    CREATE_INDEX,
    INSERT_TABLE,
    DELETE_TABLE,
    SELECTION,
    SET,
  };

  class Command
  {
  private:
    CommandType _type;
    std::string _table;
    std::vector<std::vector<std::string>> _arguments;

  public:
    Command();
    ~Command();

    CommandType getType();
    std::string getTable();
    std::vector<std::vector<std::string>> getArguments();

    void setType(CommandType);
    void setTable(std::string);
    void setArguments(std::vector<std::vector<std::string>>);
  };
}