/**
 * @file Utils/File.h
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
#include <filesystem>
#include <fstream>

namespace SQLito
{
  namespace Utils
  {
    bool createDirectory(std::string);
    bool deleteDirectory(std::string);
    bool createFile(std::string);
    bool createFile(std::string, std::string);
    std::ifstream readFile(std::string);
  }
}