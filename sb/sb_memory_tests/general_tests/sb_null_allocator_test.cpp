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

#include <sb/null_allocator.hpp>
#include <gtest/gtest.h>

TEST(SBNullAllocatorTest, Allocate)
{
	sb::null_allocator na;

	auto d = na.allocate(1024);

	EXPECT_EQ(d.ptr(), nullptr);
	EXPECT_EQ(d.size(), 0);
}

TEST(SBNullAllocatorTest, Deallocate)
{
	sb::null_allocator na;

	auto d = na.allocate(0);

	EXPECT_EQ(d.ptr(), nullptr);
	EXPECT_EQ(d.size(), 0);

	na.deallocate(d);

	EXPECT_EQ(d.ptr(), nullptr);
	EXPECT_EQ(d.size(), 0);
}

TEST(SBNullAllocatorTest, Owns)
{
	sb::null_allocator na;

	auto d = na.allocate(0);

	EXPECT_TRUE(na.owns(d));
	EXPECT_TRUE(na.owns(sb::data{}));

	na.deallocate(d);
}
