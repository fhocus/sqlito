/**
 * @file sqlito.h
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

#include <sqlito/Disk.h>
#include <sqlito/DiskManager.h>
#include <sqlito/Parser.h>
#include <sqlito/Command.h>
#include <string>

namespace SQLito
{
  class SQLito
  {
  private:
    std::string _databaseFolder;
    std::string _diskName;
    DiskManager *_diskManager;
    Parser *_parser;

    void _createTable(Command *);
    bool _verifyTable(std::string);

  public:
    SQLito();
    SQLito(std::string);
    ~SQLito();

    void setDatabaseFolder(std::string);
    std::string getDatabaseFolder();

    void execute(std::string);
  };
}