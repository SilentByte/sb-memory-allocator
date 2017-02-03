////
//// MIT License
////
//// Copyright © 2016 BY SILENT BYTE <https://silentbyte.com/>.
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
////

#include <sb/mem.hpp>
#include <gtest/gtest.h>

TEST(SBDataTest, CTor)
{
    sb::mem d {};

    EXPECT_EQ(d.ptr(), nullptr);
    EXPECT_EQ(d.size(), 0);
}

TEST(SBDataTest, CTorValue)
{
    void* address = reinterpret_cast<void*>(123456789);
    std::size_t size = 987654321;

    sb::mem d {address, size};

    EXPECT_EQ(d.ptr(), address);
    EXPECT_EQ(d.size(), size);
}

TEST(SBDataTest, Valid)
{
    EXPECT_FALSE((sb::mem{nullptr, 0}).valid());
    EXPECT_TRUE((sb::mem{reinterpret_cast<void*>(123456789), 128}).valid());
}

TEST(SBDataTest, Null)
{
    EXPECT_TRUE((sb::mem{nullptr, 0}).null());
    EXPECT_FALSE((sb::mem{reinterpret_cast<void*>(123456789), 128}).null());
}

TEST(SBDataTest, Clear)
{
    void* address = reinterpret_cast<void*>(123456789);
    std::size_t size = 987654321;

    sb::mem d {address, size};
    d.clear();

    EXPECT_EQ(d.ptr(), nullptr);
    EXPECT_EQ(d.size(), 0);
}

TEST(SBDataTest, BoolCompare)
{
    void* address = reinterpret_cast<void*>(123456789);
    std::size_t size = 987654321;

    sb::mem d1 {address, size};
    if(!d1)
        ADD_FAILURE();

    sb::mem d2 {};
    if(d2)
        ADD_FAILURE();
}

TEST(SBDataTest, Equals)
{
    void* address = reinterpret_cast<void*>(123456789);
    std::size_t size = 987654321;

    sb::mem d1 {address, size};
    sb::mem d2 {address, size};
    sb::mem d3 {};

    EXPECT_EQ(d1, d2);
    EXPECT_NE(d1, d3);
}

TEST(SBDataTest, Empty)
{
    void* address = reinterpret_cast<void*>(123456789);
    std::size_t size = 987654321;

    sb::mem d1 {};
    sb::mem d2 {};
    sb::mem d3 {address, size};

    ASSERT_EQ(d1, d2);
    ASSERT_NE(d1, d3);
}
