#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("DELETE FROM table_name");
  sql.execute("DELETE FROM table_name WHERE id = 1");
  sql.execute("DELETE FROM `table name` WHERE id = 1");
  sql.execute("DELETE FROM `table name` WHERE id = 1 AND name = 'John'");
  sql.execute("DELETE FROM `table name` WHERE `other table`.id = 1 AND name = 'John'");
  sql.execute("DELETE FROM `table name` WHERE other_table.id = 1 AND name = 'John'");

  return 0;
}