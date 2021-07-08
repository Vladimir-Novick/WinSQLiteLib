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
#include <WinSQLiteLib/VariadicBind.h>
#include <sstream>
#include <sqlite3.h>
#include <string.h>
#include "m_assert.h"
#include <vector>

using namespace std;

using namespace SQLite;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <cstdio>

namespace BaseTest
{
    TEST_CLASS(ExceptionTest)
    {
    public:

#if (__cplusplus >= 201103L) || ( defined(_MSC_VER) && (_MSC_VER >= 1800) ) // c++11: Visual Studio 2013
TEST_METHOD(VariadicBindinvalid)
{
    // Create a new database
    SQLite::Database db(":memory:", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    EXPECT_EQ(0, db.exec("DROP TABLE IF EXISTS test"));
    EXPECT_EQ(0,
            db.exec(
                    "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT DEFAULT 'default') "));
    EXPECT_EQ(0,
            db.exec(
                    "CREATE TABLE test2 (id INTEGER PRIMARY KEY, value TEXT DEFAULT 'default') "));
    EXPECT_TRUE(db.tableExists("test"));
    EXPECT_TRUE(db.tableExists("test2"));

    {
        SQLite::Statement query(db, "INSERT INTO test VALUES (?, ?)");

        // bind one argument less than expected - should be fine.
        // the unspecified argument should be set to null, not the default.
        SQLite::bind(query, 1);
        EXPECT_EQ(1, query.exec());
        query.reset();

        // bind all arguments - should work just fine
        SQLite::bind(query, 2, "two");
        EXPECT_EQ(1, query.exec());
        query.reset();

        // bind too many arguments - should throw.
        EXPECT_THROW(SQLite::bind(query, 3, "three", 0), SQLite::Exception);
        EXPECT_EQ(1, query.exec());
    }
    // make sure the content is as expected
    {
        SQLite::Statement query(db, std::string{"SELECT id, value FROM test ORDER BY id"});
        std::vector<std::pair<int, std::string> > results;
        while (query.executeStep())
        {
            const int id = query.getColumn(0);
            std::string value = query.getColumn(1);
            results.emplace_back( id, std::move(value) );
        }
        EXPECT_EQ(std::size_t(3), results.size());

        EXPECT_EQ(std::make_pair(1,std::string{""}), results.at(0));
        EXPECT_EQ(std::make_pair(2,std::string{"two"}), results.at(1));
        EXPECT_EQ(std::make_pair(3,std::string{"three"}), results.at(2));
    }
    #if (__cplusplus >= 201402L) || ( defined(_MSC_VER) && (_MSC_VER >= 1900) ) // c++14: Visual Studio 2015
    {
        SQLite::Statement query(db, "INSERT INTO test2 VALUES (?, ?)");

        // bind one argument less than expected - should be fine.
        // the unspecified argument should be set to null, not the default.
        SQLite::bind(query, std::make_tuple(1));
        EXPECT_EQ(1, query.exec());
        query.reset();

        // bind all arguments - should work just fine
        SQLite::bind(query, std::make_tuple(2, "two"));
        EXPECT_EQ(1, query.exec());
        query.reset();

        // bind too many arguments - should throw.
        EXPECT_THROW(SQLite::bind(query, std::make_tuple(3, "three", 0)), SQLite::Exception);
        EXPECT_EQ(1, query.exec());
    }
    // make sure the content is as expected
    {
        SQLite::Statement query(db, std::string{"SELECT id, value FROM test2 ORDER BY id"});
        std::vector<std::pair<int, std::string> > results;
        while (query.executeStep())
        {
            const int id = query.getColumn(0);
            std::string value = query.getColumn(1);
            results.emplace_back( id, std::move(value) );
        }
        EXPECT_EQ(std::size_t(3), results.size());

        EXPECT_EQ(std::make_pair(1,std::string{""}), results.at(0));
        EXPECT_EQ(std::make_pair(2,std::string{"two"}), results.at(1));
        EXPECT_EQ(std::make_pair(3,std::string{"three"}), results.at(2));
    }
    #endif // c++14
}
#endif // c++11

    };
}
