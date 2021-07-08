/**
 * @file    WinSQLiteLib.h
 * @ingroup SQLiteCpp
 * @brief   SQLiteC++ is a smart and simple C++ SQLite3 wrapper. This file is only "easy include" for other files.
 *
 * Include this main header file in your project to gain access to all functionality provided by the wrapper.
 *
 * Copyright (c) 2012-2020 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 * Copyright (c) 2019-2021 Vladimir Novick ( https://www.linkedin.com/in/vladimirnovick/ )
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
/**
 * @defgroup SQLiteCpp SQLiteC++
 * @brief    SQLiteC++ is a smart and simple C++ SQLite3 wrapper. This file is only "easy include" for other files.
 */
#pragma once


// Include useful headers of SQLiteC++
#include <WinSQLiteLib/Assertion.h>
#include <WinSQLiteLib/Exception.h>
#include <WinSQLiteLib/Database.h>
#include <WinSQLiteLib/Statement.h>
#include <WinSQLiteLib/SavePoint.h>
#include <WinSQLiteLib/Column.h>
#include <WinSQLiteLib/Transaction.h>


/**
 * @brief Version numbers for SQLiteC++ are provided in the same way as sqlite3.h
 *
 */
#define WIN_SQLITE_LIB_VERSION           "3.36.00"   // 3.36.0
#define WIN_SQLITE_LIB_VERSION_NUMBER     3001001    // 3.1.1
