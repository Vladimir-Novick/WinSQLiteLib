#include "pch.h"
#include "CppUnitTest.h"
#include "../SQLite19/sqlite3.h"
#include <iostream>
#include <fstream>

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
				sprintf(buff, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
				Logger::WriteMessage(buff);
			}
			printf("\n");
			return 0;
		}

		bool ExecSQL(sqlite3* db, char* sql, char* operation) {
			char buff[255];
			char* zErrMsg = 0;
			auto rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

			if (rc != SQLITE_OK) {
				sprintf(buff, "SQL error:%s -> %s\n", operation, zErrMsg);
				sqlite3_free(zErrMsg);
				Logger::WriteMessage(buff);
				Assert::AreEqual(0, 1, L"Exec error\n");
			}
			return true;
		}

		void CreateDatabase(sqlite3** db, char* fileName) {
			char* zErrMsg = 0;
			int rc;
			char* sql;
			char buff[300];
			
			/* Open database */
			_unlink(fileName);
			rc = sqlite3_open(fileName, db);

			if (rc) {
				sprintf(buff, "Can't open or create database: %s\n", sqlite3_errmsg(*db));

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

				ExecSQL(*db, sql, "CREATE table");
				sprintf(buff, "Table created successfully\n");
				Logger::WriteMessage(buff);
			
		}

		TEST_METHOD(Create_a_Table) {
			sqlite3* db;
			char* fileName = "Create_a_Table.db";
			CreateDatabase(&db, fileName);
			sqlite3_close(db);

		}


		TEST_METHOD(INSERT_Operation) {
			sqlite3* db;
			char* zErrMsg = 0;

			char* sql;
			char buff[255];

			char* fileName = "Insert_Table.db";
			CreateDatabase(&db, fileName);


			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			ExecSQL(db, sql, "INSERT");
			

				sprintf(buff, "INSERT created successfully\n");
				Logger::WriteMessage(buff);
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

		TEST_METHOD(SELECT_Operation)
		{
			sqlite3* db;
			char* zErrMsg = 0;

			char* sql;
			const char* data = "Callback function called";

			char buff[255];

			char* fileName = "Select_Table.db";
			CreateDatabase(&db, fileName);

			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			/* Execute SQL statement */
			ExecSQL(db, sql, "INSERT");

			/* Create SQL statement */
			sql = "SELECT * from COMPANY";

			ExecSQL(db, sql, "SELECT");
			sprintf(buff, "Select Operation done successfully\n");
			Logger::WriteMessage(buff);
			sqlite3_close(db);
		}
		


		TEST_METHOD(UPDATE_Operation)
		{
			sqlite3* db;
			char* zErrMsg = 0;

			char* sql;
			const char* data = "Callback function called";

			char buff[255];

			char* fileName = "Update_Table.db";
			CreateDatabase(&db, fileName);


			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			/* Execute SQL statement */

			ExecSQL(db, sql,"INSERT");

			sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
				"SELECT * from COMPANY";

			ExecSQL(db, sql,"UPDATE");

			sprintf(buff, "UPDATE Operation done successfully\n");
			Logger::WriteMessage(buff);

			sqlite3_close(db);
		}

		TEST_METHOD(DELETE_Operation)
		{
			sqlite3* db;
			char* zErrMsg = 0;

			char* sql;
			const char* data = "Callback function called";

			char buff[255];

			char* fileName = "delete_Table.db";
			CreateDatabase(&db, fileName);


			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			/* Execute SQL statement */

			ExecSQL(db, sql, "INSERT");

			sql = "DELETE from COMPANY where ID=2; " \
				"SELECT * from COMPANY";

			ExecSQL(db, sql, "DELETE");

			sprintf(buff, "DELETE Operation done successfully\n");
			Logger::WriteMessage(buff);

			sqlite3_close(db);
		}

		TEST_METHOD(DRAP_TABLE_Operation)
		{
			sqlite3* db;
			char* zErrMsg = 0;

			char* sql;
			const char* data = "Callback function called";

			char buff[255];

			char* fileName = "Update_Table.db";
			CreateDatabase(&db, fileName);


			sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
				"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
				"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
				"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

			/* Execute SQL statement */

			ExecSQL(db, sql, "INSERT");

			sql = "DROP TABLE COMPANY" ;

			ExecSQL(db, sql, "DROP");

			sprintf(buff, "DROP Operation done successfully\n");
			Logger::WriteMessage(buff);

			sqlite3_close(db);
		}


		void InsertFile(sqlite3* db,char *fileName)
		{
			std::ifstream file;
			char buff[255];
			file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
			if (!file) {
				Assert::AreEqual(0, 1, L"An error occurred opening the file\n");
			}
			file.seekg(0, std::ifstream::end);
			std::streampos size = file.tellg();
			file.seekg(0);

			char* buffer = new char[size];
			file.read(buffer, size);
			sqlite3_stmt* stmt = NULL;
				auto rc = sqlite3_prepare(db,
					"INSERT INTO ONE(ID, NAME, LABEL, GRP, FILE)"
					" VALUES(NULL, 'fedfsdfss', NULL, NULL, ?)",
					-1, &stmt, NULL);
				if (rc != SQLITE_OK) {
					sprintf(buff, "\nprepare failed:: %s\n", sqlite3_errmsg(db));
					Logger::WriteMessage(buff);
					Assert::AreEqual(0, 1, L"An error prepare sql statement\n");
				}
				else {
					// SQLITE_STATIC because the statement is finalized
					// before the buffer is freed:
					rc = sqlite3_bind_blob(stmt, 1, buffer, size, SQLITE_STATIC);
					if (rc != SQLITE_OK) {
						sprintf(buff, "\nbind blob failed:: %s\n", sqlite3_errmsg(db));
						Logger::WriteMessage(buff);
						Assert::AreEqual(0, 1, L"An error bind blob\n");
					}
					else {
						rc = sqlite3_step(stmt);
						if (rc != SQLITE_DONE) {
							sprintf(buff, "\nstep blob failed:: %s\n", sqlite3_errmsg(db));
							Logger::WriteMessage(buff);
							Assert::AreEqual(0, 1, L"An error step blob\n");
						}
					}
				}
				sqlite3_finalize(stmt);
		
			sqlite3_close(db);

			delete[] buffer;
		}


		TEST_METHOD(INSERT_File_To_BLOB)
		{
			sqlite3* db;
			char* zErrMsg = 0;
			char* sql;
			const char* data = "Callback function called";

			char buff[255];

			char* fileName = "BLOB_Table.db";
			CreateDatabase(&db, fileName);


			sql = "CREATE TABLE ONE ( " \
				" ID INTEGER PRIMARY KEY AUTOINCREMENT " \
				" NOT NULL, " \
				" NAME  CHAR(50)  NOT NULL, " \
				" LABEL CHAR(50), " \
				" GRP   CHAR(50), " \
				" FILE  BLOB " \
				" ); ";

			/* Execute SQL statement */

			ExecSQL(db, sql, "CREATE BLOB table data");

			InsertFile(db, "TUN_TAP interface.pdf");

			sprintf(buff, "BLOB  Operation done successfully\n");
			Logger::WriteMessage(buff);

			sqlite3_close(db);
		}


		int writeBig_BlobData(
			sqlite3* db,                   /* Database to insert data into */
			const char* zKey,              /* Null-terminated key string */
			const unsigned char* zBlob,    /* Pointer to blob of data */
			long nBlob                      /* Length of data pointed to by zBlob */
		) {
			const char* zSql = "INSERT INTO blobs(key, value) VALUES(?, ?)";
			sqlite3_stmt* pStmt;
			int rc;

			do {
				rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
				if (rc != SQLITE_OK) {
					return rc;
				}
				sqlite3_bind_text(pStmt, 1, zKey, -1, SQLITE_STATIC);
				sqlite3_bind_blob64(pStmt, 2, zBlob, nBlob, SQLITE_STATIC);

				/* Call sqlite3_step() to run the virtual machine. Since the SQL being
				** executed is not a SELECT statement, we assume no data will be returned.
				*/
				rc = sqlite3_step(pStmt);
				if (rc != SQLITE_DONE) {
					return rc; // Error
				}

				/* Finalize the virtual machine. This releases all memory and other
				** resources allocated by the sqlite3_prepare() call above.
				*/
				rc = sqlite3_finalize(pStmt);

				/* If sqlite3_finalize() returned SQLITE_SCHEMA, then try to execute
				** the statement again.
				*/
			} while (rc == SQLITE_SCHEMA);

			return rc;
		}

		TEST_METHOD(WRITE_BIG_BLOB_TEST) {
			sqlite3* db;

			const long dataLen = 32000000;
			unsigned char* data;
			data = (unsigned char* ) malloc(dataLen) ;

			for (long i = 0; i < dataLen; i++) {
				data[i]= 'a' + rand() % 26;
			}

			char buff[255];

			char* fileName = "WRITE_BLOB_TEST.db";
			CreateDatabase(&db, fileName);

			char* sqlCreateTable = "CREATE TABLE blobs(key TEXT PRIMARY KEY, value BLOB)";

			ExecSQL(db, sqlCreateTable, "CREATE BLOB table data");

			auto ret = writeBig_BlobData(db, "1111", data, dataLen);

			free( data);
			if (ret == SQLITE_OK) {
				sprintf(buff, "WRITE BIG BLOB  successfully\n");
				Logger::WriteMessage(buff);
			}
			else {
				sprintf(buff, "WRITE BIG BLOB  failed %d\n",ret);
				Logger::WriteMessage(buff);
			}

			

			sqlite3_close(db);

		}


		int readBig_BlobData(
			sqlite3* db,               /* Database containing blobs table */
			const char* zKey,          /* Null-terminated key to retrieve blob for */
			unsigned char** pzBlob,    /* Set *pzBlob to point to the retrieved blob */
			long* pnBlob                /* Set *pnBlob to the size of the retrieved blob */
		) {
			const char* zSql = "SELECT LENGTH(value),value FROM blobs WHERE key = ?";
			sqlite3_stmt* pStmt;
			int rc;

			/* In case there is no table entry for key zKey or an error occurs,
			** set *pzBlob and *pnBlob to 0 now.
			*/
			*pzBlob = 0;
			*pnBlob = 0;

			do {
				/* Compile the SELECT statement into a virtual machine. */
				rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
				if (rc != SQLITE_OK) {
					return rc;
				}

				/* Bind the key to the SQL variable. */
				sqlite3_bind_text(pStmt, 1, zKey, -1, SQLITE_STATIC);

				/* Run the virtual machine. We can tell by the SQL statement that
				** at most 1 row will be returned. So call sqlite3_step() once
				** only. Normally, we would keep calling sqlite3_step until it
				** returned something other than SQLITE_ROW.
				*/
				rc = sqlite3_step(pStmt);
				if (rc == SQLITE_ROW) {
					/* The pointer returned by sqlite3_column_blob() points to memory
					** that is owned by the statement handle (pStmt). It is only good
					** until the next call to an sqlite3_XXX() function (e.g. the
					** sqlite3_finalize() below) that involves the statement handle.
					** So we need to make a copy of the blob into memory obtained from
					** malloc() to return to the caller.
					*/
					*pnBlob = sqlite3_column_int64(pStmt, 0);
					*pzBlob = (unsigned char*)malloc(*pnBlob);
					memcpy(*pzBlob, sqlite3_column_blob(pStmt, 0), *pnBlob);
				}

				/* Finalize the statement (this releases resources allocated by
				** sqlite3_prepare() ).
				*/
				rc = sqlite3_finalize(pStmt);

				/* If sqlite3_finalize() returned SQLITE_SCHEMA, then try to execute
				** the statement all over again.
				*/
			} while (rc == SQLITE_SCHEMA);

			return rc;
		}


		TEST_METHOD(READ_BIG_BLOB_TEST) {
			sqlite3* db;

			const long dataLen = 32000000;
			long outDataLen = 0;
			unsigned char* data;
			unsigned char* outData = NULL;
			data = (unsigned char*)malloc(dataLen);
	

			for (long i = 0; i < dataLen; i++) {
				data[i] = 'a' + rand() % 26;
			}

			char buff[255];

			char* fileName = "WRITE_BLOB_TEST.db";
			CreateDatabase(&db, fileName);

			char* sqlCreateTable = "CREATE TABLE blobs(key TEXT PRIMARY KEY, value BLOB)";

			ExecSQL(db, sqlCreateTable, "CREATE BLOB table data");

			auto ret = writeBig_BlobData(db, "1111", data, dataLen);

			
			if (ret == SQLITE_OK) {
				sprintf(buff, "WRITE BIG BLOB  successfully\n");
				Logger::WriteMessage(buff);


				auto retOut = readBig_BlobData(db, "1111", &outData, &outDataLen);

			}
			else {
				sprintf(buff, "WRITE BIG BLOB  failed %d\n", ret);
				Logger::WriteMessage(buff);
			}

			free(data);
			free(outData);

			sqlite3_close(db);

		}

	};
}
