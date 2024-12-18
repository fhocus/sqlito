#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("SELECT * FROM table_name");
  sql.execute("SELECT id, name FROM table_name");
  sql.execute("SELECT id, name FROM table_name WHERE id = 1");
  sql.execute("SELECT id, name FROM `table name` WHERE id = 1");
  sql.execute("SELECT id, `first name` FROM `table name` WHERE id = 1");
  sql.execute("SELECT id, `first name` FROM `table name` LEFT JOIN table ON table.id = `table name`.id WHERE id = 1; SELECT id, `first name` FROM `table name` WHERE id = 1");

  return 0;
}