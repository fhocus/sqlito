#include "Parser/Parser.hpp"

#include <sstream>
#include <iostream>

void _extract_content(std::istringstream &stream, std::string &content)
{
    stream >> std::ws;
    char c;
    stream >> c;
    if (c == '(')
    {
        int count = 1;
        while (count > 0)
        {
            stream.get(c);
            if (c == '(')
                count++;
            else if (c == ')')
                count--;
            if (count > 0)
                content += c;
        }
    }
    else if (c == '\'' || c == '"')
    {
        char quote = c;
        std::getline(stream, content, quote);
    }
    else
    {
        stream.seekg(-1, std::ios_base::cur);
        stream >> content;
    }
}

void _extract_content(std::istringstream &stream, std::string &content, char end)
{
    stream >> std::ws;
    char c;
    stream >> c;
    while (c != end)
    {
        content += c;
        stream >> c;
        if (stream.fail())
            break;
    }
    stream.seekg(-1, std::ios_base::cur);
}

void _extract_content(std::istringstream &stream, std::string &content, char start, char end)
{
    char c;
    while (c != start)
    {
        stream >> c;
        if (stream.fail())
            return;
    }

    int count = 1;
    while (count > 0)
    {
        stream.get(c);
        if (stream.fail())
            return;
        if (c == start)
            count++;
        else if (c == end)
            count--;
        if (count > 0)
            content += c;
    }
}

namespace SQLito
{
    namespace Parser
    {
        /**
         * Process the query and return a list of commands.
         * @param query The query to process.
         * @return A list of commands.
         */
        std::vector<Command::Command *> Parser::process(const std::string &query)
        {
            std::vector<Command::Command *> commands;
            Command::CommandAttributes attributes;
            Command::Command *command;

            std::istringstream query_stream(query);
            std::string query_token;

            query_stream >> query_token;

            if (query_token == "CREATE")
            {
                query_stream >> query_token;
                if (query_token != "TABLE")
                    throw std::runtime_error("Invalid command.");

                std::string table_name;
                _extract_content(query_stream, table_name);

                attributes.push_back({table_name});

                std::string fields;
                _extract_content(query_stream, fields, '(', ')');

                std::istringstream fields_stream(fields);
                std::string field;
                std::string field_name, field_type, field_type_size;
                while (std::getline(fields_stream, field, ','))
                {
                    std::istringstream field_stream(field);
                    _extract_content(field_stream, field_name);
                    _extract_content(field_stream, field_type, '(');
                    _extract_content(field_stream, field_type_size, '(', ')');
                    attributes.push_back({field_name, field_type, field_type_size});
                }

                command = new Command::Command(Command::CommandType::CREATE_TABLE, attributes);
                commands.push_back(command);
                attributes.clear();
            }
            else if (query_token == "INSERT")
            {
                query_stream >> query_token;
                if (query_token != "INTO")
                    throw std::runtime_error("Invalid command.");

                std::string table_name;
                _extract_content(query_stream, table_name);
                attributes.push_back({table_name});
                attributes.push_back({"*"});

                command = new Command::Command(Command::CommandType::PROJECTION, attributes);
                commands.push_back(command);
                attributes.clear();

                command = new Command::Command(Command::CommandType::UNION, attributes);
                commands.push_back(command);
                attributes.clear();

                std::string token;
                _extract_content(query_stream, token);

                if (token != "VALUES")
                {
                    attributes.push_back({"FIELDS"});
                    std::istringstream fields_stream(token);
                    std::vector<std::string> fields;
                    std::string field;
                    std::string field_name;
                    while (std::getline(fields_stream, field, ','))
                    {
                        std::istringstream field_stream(field);
                        _extract_content(field_stream, field_name);
                        fields.push_back(field_name);
                    }
                    attributes.push_back(fields);
                    query_stream >> token;
                }

                attributes.push_back({"VALUES"});

                char c = ',';
                while (c == ',')
                {
                    std::string values_content;
                    _extract_content(query_stream, values_content);

                    std::istringstream values_stream(values_content);
                    std::vector<std::string> values;
                    std::string value;
                    std::string value_content;
                    while (std::getline(values_stream, value, ','))
                    {
                        std::istringstream value_stream(value);
                        _extract_content(value_stream, value_content);
                        values.push_back(value_content);
                    }
                    attributes.push_back(values);

                    query_stream >> c;
                    if (query_stream.fail())
                        break;
                }

                command = new Command::Command(Command::CommandType::UNION, attributes);
                commands.push_back(command);
                attributes.clear();
            }
            else if (query_token == "UPDATE")
            {
                std::string table_name;
                _extract_content(query_stream, table_name);
                attributes.push_back({table_name});
                attributes.push_back({"*"});

                command = new Command::Command(Command::CommandType::PROJECTION, attributes);
                commands.push_back(command);
                attributes.clear();

                command = new Command::Command(Command::CommandType::UNION, attributes);
                commands.push_back(command);
                attributes.clear();

                query_stream >> query_token;
                if (query_token != "SET")
                    throw std::runtime_error("Invalid command.");

                Command::CommandAttributes attributes_set;

                char c = ',';
                std::string field_name, field_operator, field_value;
                while (c == ',')
                {
                    _extract_content(query_stream, field_name);
                    _extract_content(query_stream, field_operator);
                    _extract_content(query_stream, field_value);
                    attributes_set.push_back({field_name, field_operator, field_value});
                    query_stream >> std::ws;
                    query_stream >> c;
                    if (query_stream.fail())
                        break;
                }

                query_stream.seekg(-1, std::ios_base::cur);

                Command::Command *command_set = new Command::Command(Command::CommandType::SET, attributes_set);

                query_stream >> query_token;
                if (query_token == "WHERE")
                {
                    std::string operator_logic = OPERATOR_AND;
                    std::string field_name, field_operator, field_value;
                    attributes.push_back({"PRIMARY"});
                    while (operator_logic == OPERATOR_AND || operator_logic == OPERATOR_OR)
                    {
                        _extract_content(query_stream, field_name);
                        _extract_content(query_stream, field_operator);
                        _extract_content(query_stream, field_value);
                        attributes.push_back({operator_logic});
                        attributes.push_back({field_name, field_operator, field_value});
                        query_stream >> std::ws;
                        query_stream >> operator_logic;
                        if (query_stream.fail())
                            break;
                    }

                    command = new Command::Command(Command::CommandType::SELECTION, attributes);
                    commands.push_back(command);
                }

                commands.push_back(command_set);
            }
            else if (query_token == "DELETE")
            {
                query_stream >> query_token;
                if (query_token != "FROM")
                    throw std::runtime_error("Invalid command.");

                std::string table_name;
                _extract_content(query_stream, table_name);
                attributes.push_back({table_name});
                attributes.push_back({"*"});

                command = new Command::Command(Command::CommandType::PROJECTION, attributes);
                commands.push_back(command);
                attributes.clear();

                query_stream >> query_token;
                if (query_token == "WHERE")
                {
                    command = new Command::Command(Command::CommandType::UNION, attributes);
                    commands.push_back(command);
                    attributes.clear();

                    attributes.push_back({table_name});
                    attributes.push_back({"*"});

                    command = new Command::Command(Command::CommandType::PROJECTION, attributes);
                    commands.push_back(command);
                    attributes.clear();

                    std::string operator_logic = OPERATOR_AND;
                    std::string field_name, field_operator, field_value;
                    attributes.push_back({"SECONDARY"});
                    while (operator_logic == OPERATOR_AND || operator_logic == OPERATOR_OR)
                    {
                        _extract_content(query_stream, field_name);
                        _extract_content(query_stream, field_operator);
                        _extract_content(query_stream, field_value);
                        attributes.push_back({operator_logic});
                        attributes.push_back({field_name, field_operator, field_value});
                        query_stream >> std::ws;
                        query_stream >> operator_logic;
                        if (query_stream.fail())
                            break;
                    }

                    command = new Command::Command(Command::CommandType::SELECTION, attributes);
                    commands.push_back(command);
                    attributes.clear();
                }

                command = new Command::Command(Command::CommandType::DIFFERENCE, attributes);
                commands.push_back(command);
            }

            return commands;
        }
    } // namespace Parser
} // namespace SQLito
