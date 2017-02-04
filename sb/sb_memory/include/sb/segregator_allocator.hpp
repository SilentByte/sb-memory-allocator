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

#ifndef SB_MEMORY_SEGREGATOR_ALLOCATOR_HPP
#	define SB_MEMORY_SEGREGATOR_ALLOCATOR_HPP

#include <cstddef>
#include <sb/mem.hpp>

namespace sb
{
    template<std::size_t threshold, typename LowerAllocator, typename UpperAllocator>
    class segregator_allocator : private LowerAllocator, private UpperAllocator
    {
        public:
            data allocate(std::size_t size)
            {
                if(size <= threshold)
                    return LowerAllocator::allocate(size);
                else
                    return UpperAllocator::allocate(size);
            }

            void deallocate(const data& d)
            {
                if(d.size <= threshold)
                    LowerAllocator::deallocate(d);
                else
                    UpperAllocator::deallocate(d);
            }

            void collect()
            {
                LowerAllocator::collect();
                UpperAllocator::collect();
            }

            bool owns(const data& d) const
            {
                return d.size <= threshold
                       ? LowerAllocator::owns(d)
                       : UpperAllocator::owns(d);
            }
    };
}

#endif
