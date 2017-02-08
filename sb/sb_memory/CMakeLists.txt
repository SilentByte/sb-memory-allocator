##
## MIT License
##
## Copyright © 2016 BY SILENT BYTE <https://silentbyte.com/>.
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##

cmake_minimum_required(VERSION 2.8.7)
project(sb_memory)

add_definitions(-std=c++11)

set(HEADER_FILES
        include/sb/allocation_exception.hpp
        include/sb/fallback_allocator.hpp
        include/sb/heap_allocator.hpp
        include/sb/mem.hpp
        include/sb/memalign.hpp
        include/sb/memalloc.hpp
        include/sb/memdefs.hpp
        include/sb/memout.hpp
        include/sb/null_allocator.hpp
        include/sb/segregator_allocator.hpp
        include/sb/singleton_allocator.hpp
        include/sb/stack_allocator.hpp
        include/sb/throw_allocator.hpp)

add_library(sb_memory STATIC ${HEADER_FILES})
set_target_properties(sb_memory PROPERTIES LINKER_LANGUAGE CXX)
