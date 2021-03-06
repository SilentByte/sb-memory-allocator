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

#ifndef SB_MEMORY_ALLOCATION_EXCEPTION_HPP
#	define SB_MEMORY_ALLOCATION_EXCEPTION_HPP

#include <stdexcept>
#include <sstream>
#include <string>
#include <sb/memdefs.hpp>

namespace sb
{
    class allocation_exception : public std::runtime_error
    {
        private:
            static std::string format_message(memsize size, const char* message)
            {
                std::ostringstream ss {""};
                ss << "(" << size << ") "
                   << (message != nullptr) ? message : "Failed to allocate memory.";

                return ss.str();
            }

        public:
            allocation_exception(memsize size, const char* message = nullptr)
                : std::runtime_error {format_message(size, message)}
            {
                //
            }
    };
}

#endif
