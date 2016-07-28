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

#ifndef SB_MEMORY_DATA_HPP
#	define SB_MEMORY_DATA_HPP

#include <cstddef>
#include <utility>

namespace sb
{
	class data
	{
		private:
			void* _ptr;
			std::size_t _size;

		public:
			data() noexcept
				: _ptr {nullptr}, _size {0}
			{
				//
			}

			data(void* ptr, std::size_t size) noexcept
				: _ptr {ptr}, _size {size}
			{
				//
			}

			data(const data& d) noexcept
				: _ptr {d._ptr}, _size {d._size}
			{
				//
			}

			data(data&& d) noexcept
			{
				*this = std::move(d);
			}

		public:
			void* ptr() const noexcept
			{
				return this->_ptr;
			}

			std::size_t size() const noexcept
			{
				return this->_size;
			}

			bool valid() const noexcept
			{
				return this->_ptr != nullptr;
			}

			bool null() const noexcept
			{
				return this->_ptr == nullptr;
			}

			void clear() noexcept
			{
				this->_ptr = nullptr;
				this->_size = 0;
			}

		public:
			data& operator=(const data& d) = default;

			data& operator=(data&& d)
			{
				this->_ptr = d._ptr;
				this->_size = d._size;

				d.clear();
				return *this;
			}

			bool operator==(const data& rhs) const
			{
				return this->_ptr == rhs._ptr
					&& this->_size == rhs._size;
			}

			bool operator!=(const data& rhs) const
			{
				return !(*this == rhs);
			}

			explicit operator bool() const
			{
				return this->valid();
			}
	};
}

#endif
