#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");
  std::cout << sql.getDatabaseFolder() << std::endl;

  return 0;
}