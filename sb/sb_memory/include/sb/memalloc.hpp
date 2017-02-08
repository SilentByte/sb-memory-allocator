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

#ifndef SB_MEMORY_MEMALLOC_HPP
#	define SB_MEMORY_MEMALLOC_HPP

#include <memory>
#include <sb/mem.hpp>
#include <sb/memdefs.hpp>

namespace sb
{
    template<typename T, typename Allocator>
    class default_fixed_size_deallocator
    {
        private:
            Allocator& allocator;

        public:
            default_fixed_size_deallocator(Allocator& allocator, sb::memsize)
                : allocator {allocator}
            {
                //
            }

        public:
            void operator()(T* ptr)
            {
                ptr->~T();

                sb::mem m {ptr, sizeof(T)};
                allocator.deallocate(m);
            }
    };

    template<typename T, typename Allocator>
    class default_flexible_size_deallocator
    {
        private:
            Allocator& allocator;
            sb::memsize size;

        public:
            default_flexible_size_deallocator(Allocator& allocator, sb::memsize size)
                : allocator {allocator}, size {size}
            {
                //
            }

        public:
            void operator()(T* ptr)
            {
                ptr->~T();

                sb::mem m {ptr, this->size};
                allocator.deallocate(m);
            }
    };

    template<typename T, typename Allocator>
    using default_deallocator = typename std::conditional<Allocator::exact_size_allocation,
        default_fixed_size_deallocator<T, Allocator>,
        default_flexible_size_deallocator<T, Allocator>>::type;

    template<typename T, typename Allocator, typename ...Args>
    std::unique_ptr<T, default_deallocator<T, Allocator>> unique_allocate(Allocator& allocator, Args&& ...args)
    {
        constexpr sb::memsize type_size = sizeof(T);

        mem buffer = allocator.allocate(type_size);
        try {
            T* ptr = new(buffer.ptr()) T(std::forward<Args>(args)...);

            return std::unique_ptr<T, default_deallocator<T, Allocator>>
                (ptr, default_deallocator<T, Allocator> {allocator, type_size});
        }
        catch(...) {
            allocator.deallocate(buffer);
            throw;
        }
    }

    template<typename T, typename Allocator, typename ...Args>
    std::shared_ptr<T> shared_allocate(Allocator& allocator, Args&& ...args)
    {
        constexpr sb::memsize type_size = sizeof(T);

        mem buffer = allocator.allocate(type_size);
        try {
            T* ptr = new(buffer.ptr()) T(std::forward<Args>(args)...);

            return std::shared_ptr<T>(ptr, default_deallocator<T, Allocator>
                {allocator, type_size});
        }
        catch(...) {
            allocator.deallocate(buffer);
            throw;
        }
    };
}

#endif
