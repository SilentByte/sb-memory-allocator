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

#ifndef SB_MEMORY_STACK_ALLOCATOR_HPP
#   define SB_MEMORY_STACK_ALLOCATOR_HPP

#include <cassert>
#include <cstdlib>

#include <sb/mem.hpp>
#include <sb/memalign.hpp>
#include <sb/memdefs.hpp>

namespace sb
{
    template<memsize stack_size, memsize stack_alignment = sb::default_alignment>
    class stack_allocator
    {
        private:
            static_assert(stack_alignment < stack_size, "Alignment must be less than stack size.");
            static_assert(stack_alignment > 0, "Alignment must be greater than zero.");

        public:
            constexpr static memsize max_size = stack_size;
            constexpr static memsize alignment = stack_alignment;

        private:
            alignas(stack_alignment) char _buffer[stack_size];
            char* _ptr;

        public:
            stack_allocator()
                : _ptr {_buffer}
            {
                //
            }

        public:
            mem allocate(memsize size) noexcept
            {
                if(size == 0) {
                    return {};
                }

                memsize aligned = align(stack_alignment, size);

                // Check if stack memory is exhausted.
                if(aligned + this->_ptr > this->_buffer + stack_size)
                    return {};

                mem m {this->_ptr, aligned};
                this->_ptr += aligned;

                return m;
            }

            void deallocate(mem& m) noexcept
            {
                if(m.null()) {
                    return;
                }

                assert(this->owns(m));

                if(this->_ptr == static_cast<char*>(m.ptr()) + m.size())
                    this->_ptr = static_cast<char*>(m.ptr());

                m.clear();
            }

            void collect() noexcept
            {
                // Reset pointer to beginning of the buffer.
                this->_ptr = this->_buffer;
            }

            memsize available() const noexcept
            {
                return stack_size - (this->_ptr - this->_buffer);
            }

            bool owns(const mem& m) const noexcept
            {
                return m.valid()
                       && m.ptr() >= this->_buffer
                       && m.ptr() < this->_buffer + stack_size;
            }
    };
}

#endif
