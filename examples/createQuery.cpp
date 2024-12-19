#include <iostream>
#include <sqlito/SQLito.h>

int main()
{
  SQLito::SQLito sql("db");

  sql.execute("CREATE TABLE table_name (id INTEGER, name TEXT, age INTEGER, alive BOOLEAN)");
  sql.execute("CREATE TABLE `table name` (id INTEGER, `full name` TEXT, age INTEGER, alive BOOLEAN)");
  sql.execute("CREATE DATABASE database_name (PLATTERS 2, TRACKS 8, SECTORS 8, SECTOR_SIZE 1024)");
  sql.execute("CREATE INDEX index_name ON table_name (id)");

  return 0;
}