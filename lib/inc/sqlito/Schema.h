/**
 * @file Schema.h
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
#include <vector>

namespace SQLitor
{
  enum class AttributeType
  {
    INTEGER,
    STRING,
    BOOLEAN,
    UKNOWN,
  };

  class Schema
  {
  private:
    std::string _name;
    std::vector<std::string> _attributes;
    std::vector<AttributeType> _attributeTypes;
    unsigned int _size;
    size_t _attributesSize;

    AttributeType _getAttributeType(std::string);
    char _getAttributeTypeString(AttributeType);

  public:
    Schema(std::string, std::vector<std::vector<std::string>>);
    ~Schema();

    std::string getName() const;
    std::vector<std::string> getAttributes() const;
    std::vector<AttributeType> getAttributeTypes() const;
    size_t getSize() const;

    std::string toString();
    friend std::ostream &operator<<(std::ostream &, const Schema &);
  };
}
