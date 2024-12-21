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

    std::fstream getFile(std::string filename, int mode)
    {
      std::fstream file(filename, mode);
      return file;
    }
  }
}