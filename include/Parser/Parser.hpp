#ifndef SQLITO_PARSER_HPP
#define SQLITO_PARSER_HPP

#include <string>
#include <vector>
#include "Command.hpp"

namespace SQLito
{
    namespace Parser
    {
        const std::string OPERATOR_AND = "AND";
        const std::string OPERATOR_OR = "OR";

        class Parser
        {
        public:
            static std::vector<Command::Command *> process(const std::string &);
        }; // class Parser
    } // namespace Parser
} // namespace SQLito

#endif // SQLITO_PARSER_HPP