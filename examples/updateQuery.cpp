#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("UPDATE table_name SET name = 'John'");
  sql.execute("UPDATE table_name SET name = 'John' WHERE id = 1");
  sql.execute("UPDATE `table name` SET name = 'John' WHERE id = 1");
  sql.execute("UPDATE `table name` SET `other table`.name = 'John', id = 3 WHERE id = 1 AND `other table`.id = 2");

  return 0;
}