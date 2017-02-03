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

#ifndef SB_MEMORY_ALIGN_HPP
#	define SB_MEMORY_ALIGN_HPP

#include <cstddef>

namespace sb
{
    inline constexpr std::size_t align(std::size_t alignment, std::size_t size)
    {
//          // Extended Version for C++14.
//          std::size_t mod = size % alignment;
//          if(mod == 0) {
//              return size;
//          }
//          else {
//              return size + (alignment - mod);
//          }

        return size + ((size % alignment == 0)
                       ? 0 : (alignment - (size % alignment)));
    }
}

#endif