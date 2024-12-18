/**
 * @file sqlito.h
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
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
#include <string>

namespace SQLito
{
  class SQLito
  {
  private:
    std::string _databaseFolder;
    DiskManager *_diskManager;
    Parser *_parser;

  public:
    SQLito();
    SQLito(std::string);
    ~SQLito();

    void setDatabaseFolder(std::string);
    std::string getDatabaseFolder();

    void execute(std::string);
  };
}