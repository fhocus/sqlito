/**
 * @file Command.h
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 * @author Johan Lizarve <jlizarve@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#pragma once

#include <iostream>
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
    UPDATE_TABLE,
    SELECTION,
    PROJECTION,
    MODIFY,
    JOIN,
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

    CommandType getType() const;
    std::string getTypeString() const;
    std::string getTable() const;
    std::vector<std::vector<std::string>> getArguments() const;

    void setType(CommandType);
    void setTable(std::string);
    void setArguments(std::vector<std::vector<std::string>>);

    friend std::ostream &operator<<(std::ostream &, const Command &);
  };
}