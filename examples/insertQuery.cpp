#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("INSERT INTO table_name (id, name, age, alive) VALUES (1, 'John', 20, true)");
  sql.execute("INSERT INTO `table name` (id, `full name`, age, alive) VALUES (1, 'John Mamani', 20, true)");

  return 0;
}