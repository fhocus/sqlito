/**
 * @file Parser.h
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

namespace SQLito
{
  class Parser
  {
  public:
    Parser();
    ~Parser();

    int parse(std::string);
  };
}