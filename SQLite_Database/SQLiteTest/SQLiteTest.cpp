#include "pch.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include "../SQLite19/sqlite3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SQLiteTest
{
	TEST_CLASS(SQLiteTest)
	{
	public:

		static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
			int i;
			char buff[255];
			for (i = 0; i < argc; i++) {
				sprintf(buff,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
				Logger::WriteMessage(buff);
			}
			printf("\n");
			return 0;
		}


		
		TEST_METHOD(Create_a_Table) {
			sqlite3* db;
			char* zErrMsg = 0;
			int rc;
			char* sql;
			char buff[300];
			char* fileName = "Create_a_Table.db";
			/* Open database */
			_unlink(fileName);
			rc = sqlite3_open(fileName, &db);

			if (rc) {
				sprintf(buff, "Can't open or create database: %s\n", sqlite3_errmsg(db));
				
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"Can't open database");
			}
			else {
				sprintf(buff, "Opened database successfully\n");
				Logger::WriteMessage(buff);
			}

			/* Create SQL statement */
			sql = "CREATE TABLE COMPANY("  \
				"ID INT PRIMARY KEY     NOT NULL," \
				"NAME           TEXT    NOT NULL," \
				"AGE            INT     NOT NULL," \
				"ADDRESS        CHAR(50)," \
				"SALARY         REAL );";

			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if (rc != SQLITE_OK) {
				sprintf(buff, "SQL error: %s\n", zErrMsg);
				Logger::WriteMessage(buff);
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"CREATE TABLE ERROR");
			}
			else {
				sprintf(buff, "Table created successfully\n");
				Logger::WriteMessage(buff);
			}
			sqlite3_close(db);

		}

		
		TEST_METHOD(INSERT_Operation) {
			sqlite3* db;
			char* zErrMsg = 0;
			int rc;
			char* sql;
			char buff[255];

			/* Open database */
			rc = sqlite3_open("INSERT_Operation.db", &db);

			if (rc) {
				sprintf(buff, "Can't open or create database: %s\n", sqlite3_errmsg(db));
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"Can't open database: %s\n");
			}
			else {
				sprintf(buff, "Opened database successfully\n");
				Logger::WriteMessage(buff);
			}

			sql = "CREATE TABLE COMPANY("  \
				"ID INT PRIMARY KEY     NOT NULL," \
				"NAME           TEXT    NOT NULL," \
				"AGE            INT     NOT NULL," \
				"ADDRESS        CHAR(50)," \
				"SALARY         REAL );";

			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if (rc != SQLITE_OK) {
				sprintf(buff, "SQL error: %s\n", zErrMsg);
				Logger::WriteMessage(buff);
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"CREATE TABLE ERROR");
			}

			/* Create SQL statement */
			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if (rc != SQLITE_OK) {
				sprintf(buff, "SQL error: %s\n", zErrMsg);
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"INSERT INTO ERROR\n");
			}
			else {
				sprintf(buff, "Records created successfully\n");
				Logger::WriteMessage(buff);
			}
			sqlite3_close(db);
		}

		TEST_METHOD(Connect_To_Database)
		{
			sqlite3* db;
			char* zErrMsg = 0;
			int rc;

			rc = sqlite3_open("test.db", &db);
            char buff[300];
			if (rc) {
				
				sprintf(buff, "\nCan't open database: %s", sqlite3_errmsg(db));
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"Can't open database\n");
			}
			else {
				sprintf(buff, "\nOpened database successfully");
				Logger::WriteMessage(buff);
			}
			sqlite3_close(db);
		}
	};
}
