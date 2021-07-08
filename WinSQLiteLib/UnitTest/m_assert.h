#pragma once

#include "CppUnitTest.h"
#include <utility>
#include <string.h>
#include <functional>
#include <vector>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;




#define EXPECT_NO_THROW(stmt, value) \
        { \
        { \
            const wchar_t* message = L"EXPECT_NO_THROW"; \
            try { \
               stmt; \
            } \
            catch (...) { \
                 Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
            } \
        } \
    }\

#define EXPECT_THROW(stmt, etype) \
        { \
        { \
            const wchar_t* message = L"EXPECT_THROW"; \
            bool ok = false; \
            try { \
                stmt; \
            } \
            catch (etype& ex) { \
                ok = true;  \
            } \
            if (!ok){ \
                Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
            } \
        } \
    }\

#define EXPECT_EQ(val1, val2) \
          { \
                const wchar_t* message = L"EXPECT_EQ"; \
                if (val1 != val2) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \

#define ASSERT_EQ(val1, val2) \
          { \
                const wchar_t* message = L"ASSERT_EQ"; \
                if (val1 == val2) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \

#define EXPECT_TRUE(val1) \
          { \
                const wchar_t* message = L"EXPECT_TRUE"; \
                if (val1 != true) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \

#define ASSERT_TRUE(val1) \
          { \
                const wchar_t* message = L"ASSERT_TRUE"; \
                if (val1 == true) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \


#define EXPECT_FALSE(val1) \
          { \
                const wchar_t* message = L"EXPECT_FALSE"; \
                if (val1 != false) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \

#define EXPECT_STREQ(val1,val2) \
          { \
                const wchar_t* message = L"EXPECT_STREQ"; \
                if (strcmp(val1,val2) != 0 ) { \
                    \
                        Assert::AreEqual<bool>(true, false, message, LINE_INFO()); \
                } \
            } \





