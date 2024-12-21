/**
 * @file Utils/Converter.h
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

#include <string>
#include <cstring>

namespace SQLito
{
  namespace Utils
  {
    template <typename T>
    std::string toBytes(T value)
    {
      std::string result(sizeof(T), '\0');
      std::memcpy(&result[0], &value, sizeof(T));
      return result;
    }

    template <>
    std::string toBytes<std::string>(std::string value)
    {
      return value;
    }

    template <typename T>
    T fromBytes(std::string bytes)
    {
      if (bytes.size() != sizeof(T))
        throw std::invalid_argument("Tamaño de bytes no coincide con el tipo T.");

      T value;
      std::memcpy(&value, bytes.data(), sizeof(T));
      return value;
    }
  }
}
