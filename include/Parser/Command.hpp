#ifndef SQLITO_PARSER_COMMAND_HPP
#define SQLITO_PARSER_COMMAND_HPP

#include <string>
#include <vector>

namespace SQLito
{
    namespace Parser
    {
        namespace Command
        {
            enum CommandType
            {
                SET,
                JOIN,
                UNION,
                RENAMING,
                CARTESIAN,
                SELECTION,
                DIFFERENCE,
                PROJECTION,
                INTERSECTION,
                CREATE_TABLE,
            };

            typedef std::vector<std::vector<std::string>> CommandAttributes;

            class Command
            {
            private:
                CommandType _type;
                CommandAttributes _attributes;

            public:
                Command(CommandType, CommandAttributes);
                ~Command() = default;

                CommandType getType() const;
                CommandAttributes getAttributes() const;
            }; // class Command

            std::ostream &operator<<(std::ostream &, const CommandType &);
            std::ostream &operator<<(std::ostream &, const CommandAttributes &);
            std::ostream &operator<<(std::ostream &, const Command &);
        } // namespace Command
    } // namespace Parser
} // namespace SQLito

#endif // SQLITO_PARSER_COMMAND_HPP