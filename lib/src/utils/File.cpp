#include <sqlito/utils/File.h>

namespace SQLito
{
  namespace Utils
  {
    bool createDirectory(std::string directory)
    {
      return std::filesystem::create_directories(directory);
    }

    bool deleteDirectory(std::string directory)
    {
      return std::filesystem::remove_all(directory);
    }

    bool createFile(std::string filename)
    {
      std::ofstream file(filename);

      if (file.is_open())
      {
        file.close();
        return 1;
      }

      return 0;
    }

    bool createFile(std::string filename, std::string content)
    {
      std::ofstream file(filename);

      if (file.is_open())
      {
        file << content;
        file.close();
        return 1;
      }

      return 0;
    }

    std::ifstream readFile(std::string filename)
    {
      std::ifstream file(filename);
      return file;
    }
  }
}