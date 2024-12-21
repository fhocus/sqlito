#include <sqlito/SQLito.h>
#include <sqlito/utils/File.h>
#include <sqlito/utils/Converter.h>
#include <queue>

namespace SQLito
{
  SQLito::SQLito()
  {
    SQLito("database");
  }

  SQLito::SQLito(std::string databaseFolder)
  {
    _databaseFolder = databaseFolder;
    _diskName = "disk";
    _diskManager = new DiskManager();
    _parser = new Parser();

    Utils::createDirectory(_databaseFolder);
    _diskManager->saveDisk(_databaseFolder, _diskName);
    _diskManager->loadDisk(_databaseFolder, _diskName);
  }

  SQLito::~SQLito()
  {
    delete _diskManager;
  }

  void SQLito::setDatabaseFolder(std::string databaseFolder)
  {
    _databaseFolder = databaseFolder;
  }

  std::string SQLito::getDatabaseFolder()
  {
    return _databaseFolder;
  }

  void SQLito::execute(std::string command)
  {
    std::queue<Command *> commands = _parser->parse(command);

    while (!commands.empty())
    {
      Command *command = commands.front();
      commands.pop();

      std::cout << *command << std::endl;

      switch (command->getType())
      {
      case CommandType::CREATE_TABLE:
        _createTable(command);
        break;
      default:
        break;
      }
    }
  }

  void SQLito::_createTable(Command *command)
  {
    if (_verifyTable(command->getTable()))
    {
      std::cout << "[x] Table already exists." << std::endl;
      return;
    }

    unsigned int tableSize = 4;
    std::fstream schemasFile = Utils::getFile(_databaseFolder + "/" + _diskName + "/schemas", std::ios::out | std::ios::app | std::ios::binary);
    unsigned int tableNameSize = command->getTable().size();

    tableSize += tableNameSize;

    schemasFile.close();

    std::cout << "[-] Table created." << std::endl;
  }

  bool SQLito::_verifyTable(std::string tableName)
  {
    bool rest = false;
    std::string c;
    std::fstream schemasFile = Utils::getFile(_databaseFolder + "/" + _diskName + "/schemas", std::ios::in | std::ios::binary);
    schemasFile >> c;

    if (c.size() == 0)
      schemasFile.close();

    return rest;
  }
}