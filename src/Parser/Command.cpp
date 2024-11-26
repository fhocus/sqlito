#include "Parser/Command.hpp"

#include <iostream>

namespace SQLito
{
    namespace Parser
    {
        namespace Command
        {
            Command::Command(CommandType type, CommandAttributes attributes)
            {
                _type = type;
                _attributes = attributes;
            }

            CommandType Command::getType() const
            {
                return _type;
            }

            CommandAttributes Command::getAttributes() const
            {
                return _attributes;
            }

            std::ostream &operator<<(std::ostream &stream, const CommandType &type)
            {
                stream << "CommandType(";
                switch (type)
                {
                case CommandType::SET:
                    stream << "SET";
                    break;
                case CommandType::JOIN:
                    stream << "JOIN";
                    break;
                case CommandType::UNION:
                    stream << "UNION";
                    break;
                case CommandType::RENAMING:
                    stream << "RENAMING";
                    break;
                case CommandType::CARTESIAN:
                    stream << "CARTESIAN";
                    break;
                case CommandType::SELECTION:
                    stream << "SELECTION";
                    break;
                case CommandType::DIFFERENCE:
                    stream << "DIFFERENCE";
                    break;
                case CommandType::PROJECTION:
                    stream << "PROJECTION";
                    break;
                case CommandType::INTERSECTION:
                    stream << "INTERSECTION";
                    break;
                case CommandType::CREATE_TABLE:
                    stream << "CREATE_TABLE";
                    break;
                default:
                    stream << "UNKNOWN";
                    break;
                }
                stream << ")";
                return stream;
            }

            std::ostream &operator<<(std::ostream &stream, const CommandAttributes &attributes)
            {
                stream << "CommandAttributes(";
                for (int i = 0; i < attributes.size(); i++)
                {
                    stream << "Attribute(";
                    for (int j = 0; j < attributes[i].size(); j++)
                    {
                        if (attributes[i][j].size() > 0)
                            stream << attributes[i][j];
                        else
                            stream << "NULL";
                        if (j != attributes[i].size() - 1)
                            stream << ", ";
                    }
                    stream << ")";
                    if (i != attributes.size() - 1)
                        stream << ", ";
                }
                stream << ")";
                return stream;
            }

            std::ostream &operator<<(std::ostream &stream, const Command &command)
            {
                stream << "Command(";
                stream << command.getType();
                stream << ", ";
                stream << command.getAttributes();
                stream << ")";
                return stream;
            }
        } // namespace Command
    } // namespace Parser
} // namespace SQLito
