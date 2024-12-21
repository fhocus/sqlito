/**
 * @file Parser.h
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

#include <sqlito/Command.h>
#include <queue>
#include <string>
#include <sstream>

namespace SQLito
{
  class Parser
  {
  private:
    std::string _command;
    std::stringstream _commandStream;

    std::queue<Command *> _createQuery();
    std::queue<Command *> _createTableQuery();
    std::queue<Command *> _createDatabaseQuery();
    std::queue<Command *> _createIndexQuery();

    std::queue<Command *> _insertQuery();
    std::queue<Command *> _insertTableQuery();

    std::queue<Command *> _selectQuery();
    std::queue<Command *> _selectTableQuery();

    std::queue<Command *> _deleteQuery();
    std::queue<Command *> _deleteTableQuery();

    std::queue<Command *> _updateQuery();
    std::queue<Command *> _updateTableQuery();

    int _getNextContent(std::string &);
    int _getNextContent(std::string &, std::stringstream &);
    int _getBetweenContent(std::string &);
    int _getWhereContent(std::vector<std::vector<std::string>> &, std::string &);
    int _getWhereComponentContent(std::string &, std::string &, std::string &);
    int _getSetContent(std::vector<std::vector<std::string>> &, std::string &);
    int _getSetComponentContent(std::string &, std::string &, std::string &);
    int _getSelectContent(std::vector<std::vector<std::string>> &);
    int _getSelectComponentContent(std::string &, std::string &);
    int _getJoinContent(std::queue<Command *> &, std::string &);

  public:
    Parser();
    ~Parser();

    std::queue<Command *> parse(std::string);
  };
}