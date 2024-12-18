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
  class Command
  {
  private:
    std::string _command;
    std::string _table;
    std::vector<std::string> _arguments;

  public:
    Command();
    ~Command();
  };
}