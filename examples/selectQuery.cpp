#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("SELECT id, `first name` FROM `table name` LEFT JOIN table ON table.id = `table name`.id LEFT JOIN table ON table.id = `table name`.id WHERE id = 1;");

  return 0;
}