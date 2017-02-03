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

#include <sb/throw_allocator.hpp>

#include <gtest/gtest.h>
#include <sb/stack_allocator.hpp>

class custom_exception
{
    public:
        custom_exception(std::size_t size)
        {
            //
        }
};

TEST(SBThrowAllocatorTest, AllocateThrow)
{
    sb::throw_allocator<sb::stack_allocator<100>> a;
    EXPECT_THROW(a.allocate(200), sb::allocation_exception);
}

TEST(SBThrowAllocatorTest, AllocateThrowCustom)
{
    sb::throw_allocator<sb::stack_allocator<100>, custom_exception> a;
    EXPECT_THROW(a.allocate(200), custom_exception);
}

TEST(SBThrowAllocatorTest, AllocateNoThrow)
{
    sb::throw_allocator<sb::stack_allocator<100>> a;
    EXPECT_NO_THROW(a.allocate(50));
}
