#include <iostream>
#include <sqlito/SQLito.h>

void clearConsole()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void printBanner()
{
  std::cout << std::endl;
  std::cout << "  /######   /######  /##       /##   /##              " << std::endl;
  std::cout << " /##__  ## /##__  ##| ##      |__/  | ##              " << std::endl;
  std::cout << "| ##  \\__/| ##  \\ ##| ##       /## /######    /###### " << std::endl;
  std::cout << "|  ###### | ##  | ##| ##      | ##|_  ##_/   /##__  ##" << std::endl;
  std::cout << " \\____  ##| ##  | ##| ##      | ##  | ##    | ##  \\ ##" << std::endl;
  std::cout << " /##  \\ ##| ##/## ##| ##      | ##  | ## /##| ##  | ##" << std::endl;
  std::cout << "|  ######/|  ######/| ########| ##  |  ####/|  ######/" << std::endl;
  std::cout << " \\______/  \\____ ###|________/|__/   \\___/   \\______/ " << std::endl;
  std::cout << "                \\__/                                  " << std::endl;
  std::cout << std::endl;
  std::cout << "Authors:" << std::endl;
  std::cout << "- Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>" << std::endl;
  std::cout << "- Johan Lizarve <jlizarve@unsa.edu.pe>" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "[-] Welcome!" << std::endl;
  std::cout << std::endl;
}

int main()
{
  SQLito::SQLito sql("db");

  clearConsole();
  printBanner();

  while (true)
  {
    std::cout << "[*] ";
    std::string command;
    std::getline(std::cin, command);

    std::cout << std::endl;
    sql.execute(command);
    std::cout << std::endl;
  }

  return 0;
}