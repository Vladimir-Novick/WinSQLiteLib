#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <WinSQLiteLib/WinSQLiteLib.h>
#include <WinSQLiteLib/Backup.h>
#include <WinSQLiteLib/Database.h>
#include <WinSQLiteLib/Statement.h>
#include <WinSQLiteLib/Exception.h>
#include <sstream>
#include <sqlite3.h>
#include <string.h>
#include "m_assert.h"

using namespace std;

using namespace SQLite;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseTest
{
	TEST_CLASS(BaseTest)
	{
	public:
		
		TEST_METHOD(SQLite_VERSION)
		{
			std::stringstream ss;
			ss << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << std::endl;
			ss << "WinSQliteLib version " << WIN_SQLITE_LIB_VERSION << std::endl;
			Logger::WriteMessage(ss.str().c_str());
		}

		TEST_METHOD(CreateDatabase_in_Memory)
		{
			// Create a new database
			
			SQLite::Database db(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
			int errorCode = db.getErrorCode();
			Assert::AreEqual<int>(0, errorCode, L"Unable create Database", LINE_INFO());
			int extCode =  db.getExtendedErrorCode();
			int ret = db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, msg TEXT, int INTEGER, double REAL, binary BLOB, empty TEXT)");
			bool ok = db.tableExists("test");
			Assert::AreEqual<bool>(true, ok, L"Unable create Tale", LINE_INFO());
		}

		TEST_METHOD(CreateDatabase)
		{
			// Create a new database

			remove("newDB.db3");
			SQLite::Database db("newDB.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
			int errorCode = db.getErrorCode();
			Assert::AreEqual<int>(errorCode, 0, L"Unable create Database", LINE_INFO());
			int extCode = db.getExtendedErrorCode();
			int ret = db.tryExec("CREATE TABLE test (id INTEGER PRIMARY KEY, msg TEXT, int INTEGER, double REAL, binary BLOB, empty TEXT)");
			bool ok = db.tableExists("test");
			Assert::AreEqual<bool>(true, ok, L"Unable create Table", LINE_INFO());
			
		}




		TEST_METHOD(BackupExecuteStepOne)
		{
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
			{
				SQLite::Database srcDB("backup_test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
				srcDB.exec("CREATE TABLE backup_test (id INTEGER PRIMARY KEY, value TEXT)");
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (1, \"first\")"));
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (2, \"second\")"));

				SQLite::Database destDB("backup_test.db3.backup", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
				SQLite::Backup backup(destDB, "main", srcDB, "main");
				int res = backup.executeStep(1); // backup only one page at a time
				EXPECT_EQ(SQLite::OK, res);
				const int total = backup.getTotalPageCount();
				EXPECT_EQ(2, total);
				int remaining = backup.getRemainingPageCount();
				EXPECT_EQ(1, remaining);
				res = backup.executeStep(1); // backup the second and last page
				EXPECT_EQ(SQLITE_DONE, res);
				remaining = backup.getRemainingPageCount();
				EXPECT_EQ(0, remaining);

				SQLite::Statement query(destDB, "SELECT * FROM backup_test ORDER BY id ASC");
				EXPECT_TRUE(query.executeStep());
				EXPECT_EQ(1, query.getColumn(0).getInt());
				EXPECT_STREQ("first", query.getColumn(1).getText());
				EXPECT_TRUE(query.executeStep());
				EXPECT_EQ(2, query.getColumn(0).getInt());
				EXPECT_STREQ("second", query.getColumn(1),L"getColumn");
			}
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
		}


		TEST_METHOD(BackupStepException)
		{
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
			{
				SQLite::Database srcDB("backup_test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
				srcDB.exec("CREATE TABLE backup_test (id INTEGER PRIMARY KEY, value TEXT)");
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (1, \"first\")"));
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (2, \"second\")"));
				{
					SQLite::Database destDB("backup_test.db3.backup", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
					(void)destDB;
				}
				{
					SQLite::Database destDB("backup_test.db3.backup", SQLite::OPEN_READONLY);
					SQLite::Backup backup(destDB, srcDB);
					bool ok = false;
					try {
						int k = backup.executeStep();
					}
					catch (...) {
						ok = true;
					}
					
				}
			}
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
		}


		TEST_METHOD(BackupExecuteStepAll)
		{
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
			{
				SQLite::Database srcDB("backup_test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
				srcDB.exec("CREATE TABLE backup_test (id INTEGER PRIMARY KEY, value TEXT)");
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (1, \"first\")"));
				EXPECT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (2, \"second\")"));

				SQLite::Database destDB("backup_test.db3.backup", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
				SQLite::Backup backup(destDB, srcDB);
				const int res = backup.executeStep(); // uses default argument "-1" => execute all steps at once
				EXPECT_EQ(res, SQLITE_DONE);
				const int total = backup.getTotalPageCount();
				EXPECT_EQ(2, total);
				const int remaining = backup.getRemainingPageCount();
				EXPECT_EQ(0, remaining);

				SQLite::Statement query(destDB, "SELECT * FROM backup_test ORDER BY id ASC");
				EXPECT_TRUE(query.executeStep());
				EXPECT_EQ(1, query.getColumn(0).getInt());
				EXPECT_STREQ("first", query.getColumn(1));
				EXPECT_TRUE(query.executeStep());
				EXPECT_EQ(2, query.getColumn(0).getInt());
				EXPECT_STREQ("second", query.getColumn(1));
			}
			remove("backup_test.db3");
			remove("backup_test.db3.backup");
		}

	};
}
