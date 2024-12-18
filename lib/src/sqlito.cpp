#include <sqlito/SQLito.h>
#include <sqlito/utils/File.h>

namespace SQLito
{
  SQLito::SQLito()
  {
    SQLito("database");
  }

  SQLito::SQLito(std::string databaseFolder)
  {
    _databaseFolder = databaseFolder;
    _diskManager = new DiskManager();
    _parser = new Parser();

    Utils::createDirectory(_databaseFolder);
    _diskManager->saveDisk(_databaseFolder, "disk");
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
    _parser->parse(command);
  }
}