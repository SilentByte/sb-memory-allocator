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

#include <sb/heap_allocator.hpp>

#include <algorithm>
#include <gtest/gtest.h>

TEST(SBHeapAllocatorTest, Allocate)
{
    std::size_t size = 1024;
    sb::heap_allocator ha;

    auto m = ha.allocate(size);

    EXPECT_NE(m.ptr(), nullptr);
    EXPECT_EQ(m.size(), size);

    ha.deallocate(m);
}

TEST(SBHeapAllocatorTest, AllocateMultiple)
{
    std::vector<std::size_t> v {1, 2, 3, 4, 5, 8, 13, 16, 20, 24, 1000, 2000, 10000};
    sb::heap_allocator ha;

    std::for_each(v.begin(), v.end(), [&ha](const std::size_t& size) {
        auto m = ha.allocate(size);

        EXPECT_NE(m.ptr(), nullptr);
        EXPECT_EQ(m.size(), size);

        ha.deallocate(m);
    });
}

TEST(SBHeapAllocatorTest, AllocateNull)
{
    std::size_t size = 0;
    sb::heap_allocator ha;

    auto m = ha.allocate(size);

    EXPECT_EQ(m.ptr(), nullptr);
    EXPECT_EQ(m.size(), 0);

    ha.deallocate(m);
}

TEST(SBHeapAllocatorTest, Deallocate)
{
    std::size_t size = 1024;
    sb::heap_allocator ha;

    auto m = ha.allocate(size);

    EXPECT_NE(m.ptr(), nullptr);
    EXPECT_EQ(m.size(), size);

    ha.deallocate(m);

    EXPECT_EQ(m.ptr(), nullptr);
    EXPECT_EQ(m.size(), 0);
}
