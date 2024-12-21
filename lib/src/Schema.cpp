#include <sqlito/Schema.h>

#include <iostream>

namespace SQLitor
{
  Schema::Schema(std::string name, std::vector<std::vector<std::string>> attributes)
  {
    _name = name;
    _attributesSize = attributes.size();
    _size = _name.size();

    for (const std::vector<std::string> &attribute : attributes)
    {
      if (attribute.size() != 2)
        throw std::invalid_argument("Atributo no válido.");

      AttributeType type = _getAttributeType(attribute[1]);

      if (type == AttributeType::UKNOWN)
        throw std::invalid_argument("Tipo de atributo no válido.");

      _attributes.push_back(attribute[0]);
      _attributeTypes.push_back(type);

      _size += attribute[0].size() + 1;
    }
  }

  Schema::~Schema() {}

  AttributeType Schema::_getAttributeType(std::string type)
  {
    if (type == "INTEGER")
      return AttributeType::INTEGER;
    else if (type == "STRING")
      return AttributeType::STRING;
    else if (type == "BOOLEAN")
      return AttributeType::BOOLEAN;
    else
      return AttributeType::UKNOWN;
  }

  char Schema::_getAttributeTypeString(AttributeType type)
  {
    switch (type)
    {
    case AttributeType::INTEGER:
      return 'I';
    case AttributeType::STRING:
      return 'S';
    case AttributeType::BOOLEAN:
      return 'B';
    default:
      return '_';
    }
  }

}