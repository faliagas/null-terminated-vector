// Null Terminated Vector implementation

// Copyright (C) 2022 A. Faliagas, apostol.faliagas@gmain.com
//
// Based on bits/stl_vector.h and bits/vector.tcc of the
// GNU ISO C++ Library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively. If not, see
// <http://www.gnu.org/licenses/>.

#ifndef __NULL_TERMINATED_PTR_VECTOR_HPP__
#define __NULL_TERMINATED_PTR_VECTOR_HPP__ 1

#include "nullTerminatedVector.hpp"

namespace i1
{

  template<typename _Tp>
    struct _NTPV_element
    {
      _Tp* __ptr;
      _NTPV_element() : __ptr() {}
      _NTPV_element(_Tp* __p) : __ptr(__p) {}
      static constexpr _NTPV_element
      null_terminator() noexcept
      { return _NTPV_element{reinterpret_cast<_Tp*>(1)}; }
      bool
      is_null() const noexcept
      { return __ptr == null_terminator().__ptr; }
      _NTPV_element&
      operator=(_Tp* __p) noexcept
      { __ptr = __p; return *this; }
      operator _Tp*() noexcept { return __ptr; }
      operator const _Tp*() const noexcept { return __ptr; }
    };

  /**
   *  @brief Helper class for @c null_terminated_vector with pointer elements
   *
   *  @tparam _Tp Type of element
   *  @tparam _Alloc Allocator type, defaults to allocator<_Tp>
   *
   *  Meets the requirements of @c null_terminated_vector
   */
  template<typename _P, typename _Alloc = std::allocator<_NTPV_element<_P>>,
                        typename _VAlloc = std::allocator<_P*>>
    class null_terminated_ptr_vector
    : public null_terminated_vector<_NTPV_element<_P>, _Alloc>
    {
    protected:
      typedef _NTPV_element<_P>                          _Tp;

    public:
      typedef null_terminated_vector<_Tp, _Alloc>        _Base;

    protected:
      typedef typename _Base::_Tp_alloc_type             _Tp_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>  _Alloc_traits;

    public:
      typedef _P*                                        value_type;
      typedef _Tp                                        element_type;
      typedef _Alloc                                     allocator_type;
      typedef typename _Base::pointer                    pointer;
      typedef typename _Base::const_pointer              const_pointer;
      typedef value_type&                                reference;
      typedef const value_type&                          const_reference;
      typedef typename _Base::iterator                   iterator;
      typedef typename _Base::const_iterator             const_iterator;
      typedef typename _Base::const_reverse_iterator     const_reverse_iterator;
      typedef typename _Base::reverse_iterator           reverse_iterator;
      typedef typename _Base::size_type                  size_type;
      typedef typename _Base::difference_type            difference_type;

      null_terminated_ptr_vector() = default;

      /**
       *  @brief  Create %null_terminated_ptr_vector with no elements
       *  @param  __a  An allocator object.
       */
      explicit
      null_terminated_ptr_vector(const allocator_type& __a) noexcept
      : _Base(__a) { }

      /**
       *  @brief  Create %null_terminated_ptr_vector with default
       *          constructed elements
       *  @param  __n  The number of elements to create
       *  @param  __a  An allocator
       *
       *  This constructor fills the %null_terminated_ptr_vector with
       *  @a __n default constructed elements.
       */
      explicit
      null_terminated_ptr_vector(size_type __n,
                                 const allocator_type& __a = allocator_type())
      : _Base(__n, __a) { }

      /**
       *  @brief  Create %null_terminated_ptr_vector with copies of
       *          exemplar element
       *  @param  __n  The number of elements to create
       *  @param  __value  An element to copy
       *  @param  __a  An allocator
       *
       *  This constructor fills the %null_terminated_ptr_vector with
       *  @a __n copies of @a __value.
       */
      null_terminated_ptr_vector(size_type __n, const value_type& __p,
                                 const allocator_type& __a = allocator_type())
      : _Base(__n, _Tp(__p), __a) { }

      /**
       *  @brief  Copy constructor
       *  @param  __x  A %null_terminated_ptr_vector of identical element
       *          and allocator types
       *
       *  All the elements of @a __x are copied.
       *
       *  The newly-created %null_terminated_ptr_vector uses a copy
       *  of @a __x 's allocator object (unless the allocator traits
       *  dictate a different object.)
       */
      null_terminated_ptr_vector(const null_terminated_ptr_vector& __x)
      : _Base(__x) { }

      /**
       *  @brief Move constructor
       *
       *  The newly-created %null_terminated_ptr_vector contains the
       *  exact contents of the moved instance.
       *  The contents of the moved instance are a valid, but unspecified
       *  %null_terminated_ptr_vector.
       */
      null_terminated_ptr_vector(null_terminated_ptr_vector&&) noexcept
        = default;

      /**
       *  Copy constructor with alternative allocator
       */
      null_terminated_ptr_vector(const null_terminated_ptr_vector& __x,
                                 const allocator_type& __a)
      : _Base(__x, __a) { }

      /**
       *  Move constructor with alternative allocator
       */
      null_terminated_ptr_vector(null_terminated_ptr_vector&& __rv,
                                 const allocator_type& __m)
      : null_terminated_ptr_vector(__rv, __m) { }

      /**
       *  @brief  Builds %null_terminated_ptr_vector from initializer list
       *  @param  __l  An initializer_list
       *  @param  __a  An allocator
       *
       *  Create a %null_terminated_ptr_vector consisting of copies of
       *  the elements in the initializer_list @a __l.
       *
       *  This will call the element type's copy constructor N times
       *  (where N is @a __l.size()) and do no memory reallocation.
       */
      null_terminated_ptr_vector(std::initializer_list<value_type> __l,
                                 const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
        this->_M_range_initialize(__l.begin(), __l.end(),
                            std::random_access_iterator_tag());
      }

      /**
       *  @brief  Build %null_terminated_ptr_vector from range
       *  @param  __first  An input iterator
       *  @param  __last  An input iterator
       *  @param  __a  An allocator
       *
       *  Create a %null_terminated_ptr_vector consisting of copies of
       *  the elements in the range [first,last).
       *
       *  If the iterators are forward, bidirectional, or
       *  random-access, then this will call the element's copy
       *  constructor N times (where N is distance(first,last)) and do
       *  no memory reallocation.  But if only input iterators are
       *  used, then this will do at most 2N calls to the copy
       *  constructor, and logN memory reallocations.
       */
      template<typename _InputIterator,
               typename = std::_RequireInputIter<_InputIterator>>
        null_terminated_ptr_vector(_InputIterator __first,
                                   _InputIterator __last,
                                   const allocator_type& __a = allocator_type())
        : _Base(__first, __last, __a) { }

      /**
       *  @brief  Assignment operator
       *  @param  __x %null_terminated_ptr_vector of identical element and
       *          allocator types
       *
       *  All the elements of @a __x are copied, but any unused capacity
       *  in @a __x will not be copied.
       *
       *  Whether the allocator is copied depends on the allocator traits.
       */
      null_terminated_ptr_vector&
      operator=(const null_terminated_ptr_vector& __x)
      {
        *static_cast<_Base*>(this) = __x;
        return *this;
      }

      /**
       *  @brief  Move assignment operator
       *  @param  __x  %null_terminated_ptr_vector of identical element
       *          and allocator types
       *
       *  The contents of @a __x are moved into this %null_terminated_ptr_vector
       *  (without copying, if the allocators permit it).
       *  Afterwards @a __x is a valid, but unspecified %null_terminated_ptr_vector.
       *
       *  Whether the allocator is moved depends on the allocator traits.
       */
      null_terminated_ptr_vector&
      operator=(null_terminated_ptr_vector&& __x)
        noexcept(_Alloc_traits::_S_nothrow_move()) = default;

      /**
       *  @brief  List assignment operator
       *  @param  __l  An initializer_list
       *
       *  This function fills a %null_terminated_ptr_vector with copies
       *  of the elements in the initializer list @a __l.
       *
       *  Note that the assignment completely changes the
       *  %null_terminated_ptr_vector and that the resulting
       *  %null_terminated_ptr_vector's size is the same as the number
       *  of elements assigned.
       */
      null_terminated_ptr_vector&
      operator=(std::initializer_list<_Tp> __l)
      {
        *static_cast<_Base*>(this) = __l;
        return *this;
      }

      null_terminated_ptr_vector&
      operator=(std::vector<_Tp, _Alloc>&& __x) noexcept
      {
        *static_cast<_Base*>(this) = __x;
        return *this;
      }

      /**
       *  @brief Move constructor @c from std::vector
       *
       *  The newly-created %null_terminated_ptr_vector contains the
       *  exact contents of the moved instance.
       *  The contents of the moved instance are a valid, but unspecified
       *  %vector.
       */
      null_terminated_ptr_vector(std::vector<value_type, _VAlloc>&& __x) noexcept
      : _Base(allocator_type())
      { *this = std::move(__x); }

      null_terminated_ptr_vector&
      operator=(std::vector<value_type, _VAlloc>&& __x) noexcept
      {
        *static_cast<_Base*>(this) = reinterpret_cast<
            std::vector<_Tp, _Alloc>&&>(std::move(__x));
        return *this;
      }

      std::vector<_Tp, _Alloc>&
      convert_to(std::vector<value_type, _VAlloc>& __x)
      {
        return _Base::convert_to(reinterpret_cast<std::vector<_Tp, _Alloc>&>(__x));
      }

      /**
       *  @brief  Assigns a given value to a %null_terminated_vector.
       *  @param  __n  Number of elements to be assigned.
       *  @param  __val  Value to be assigned.
       *
       *  This function fills a %null_terminated_vector with @a __n copies
       *  of the given value.  Note that the assignment completely changes
       *  the %null_terminated_vector and that the resulting
       *  %null_terminated_vector's size is the same as the number of
       *  elements assigned.
       */
      void
      assign(size_type __n, const value_type& __val)
      { _Base::assign(__n, _Tp(__val)); }

      /**
       *  @brief  Assigns a range to a %null_terminated_vector.
       *  @param  __first  An input iterator.
       *  @param  __last   An input iterator.
       *
       *  This function fills a %null_terminated_vector with copies of
       *  the elements in the range [__first,__last).
       *
       *  Note that the assignment completely changes the
       *  %null_terminated_vector and that the resulting
       *  %null_terminated_vector's size is the same as the number of
       *  elements assigned.
       */
      template<typename _InputIterator,
               typename = std::_RequireInputIter<_InputIterator>>
        void
        assign(_InputIterator __first, _InputIterator __last)
        { _Base::assign(__first, __last); }

      /**
       *  @brief  Assigns an initializer list to a %null_terminated_vector.
       *  @param  __l  An initializer_list.
       *
       *  This function fills a %null_terminated_vector with copies of
       *  the elements in the initializer list @a __l.
       *
       *  Note that the assignment completely changes the
       *  %null_terminated_vector and that the resulting
       *  %null_terminated_vector's size is the same as the number
       *  of elements assigned.
       */
      void
      assign(std::initializer_list<value_type> __l)
      {
        this->_M_assign_aux(__l.begin(), __l.end(),
                            std::random_access_iterator_tag());
      }

      /// Get a copy of the memory allocation object.
      // using _Base::get_allocator;

      // iterators

      // element access
      /**
       *  @brief  Subscript access to the data contained in the
       *          %null_terminated_vector.
       *  @param __n The index of the element for which data should be
       *  accessed.
       *  @return  Read/write reference to data.
       *
       *  This operator allows for easy, array-style, data access.
       *  Note that data access with this operator is unchecked and
       *  out_of_range lookups are not defined. (For checked lookups
       *  see at().)
       */
      reference
      operator[](size_type __n) noexcept
      { return (reference)_Base::operator[](__n); }

      /**
       *  @brief Subscript access to the data contained in the
       *         %null_terminated_vector.
       *  @param __n The index of the element for which data should be
       *  accessed.
       *  @return  Read-only (constant) reference to data.
       *
       *  This operator allows for easy, array-style, data access.
       *  Note that data access with this operator is unchecked and
       *  out_of_range lookups are not defined. (For checked lookups
       *  see at().)
       */
      const_reference
      operator[](size_type __n) const noexcept
      { return (const_reference)_Base::operator[](__n); }

      //
      /**
       *  @brief  Provides access to the data contained in the
       *          %null_terminated_vector.
       *  @param __n The index of the element for which data should be
       *          accessed.
       *  @return  Read/write reference to data.
       *  @throw  std::out_of_range  If @a __n is an invalid index.
       *
       *  This function provides for safer data access. The parameter is
       *  first checked that it is in the range of the %null_terminated_vector.
       *  The function throws out_of_range if the check fails.
       */
      reference
      at(size_type __n)
      { return (reference)_Base::at(__n); }

      /**
       *  @brief  Provides access to the data contained in the
       *          %null_terminated_vector.
       *  @param __n The index of the element for which data should be
       *  accessed.
       *  @return  Read-only (constant) reference to data.
       *  @throw  std::out_of_range  If @a __n is an invalid index.
       *
       *  This function provides for safer data access. The parameter is
       *  first checked that it is in the range of the %null_terminated_vector.
       *  The function throws out_of_range if the check fails.
       */
      const_reference
      at(size_type __n) const
      { return _Base::at(__n); }

      /**
       *  Returns a read/write reference to the data at the first
       *  element of the %null_terminated_vector.
       */
      reference
      front() noexcept
      { return _Base::front().__ptr; }

      /**
       *  Returns a read-only (constant) reference to the data at the first
       *  element of the %null_terminated_vector.
       */
      const_reference
      front() const noexcept
      { return _Base::front().__ptr; }

      /**
       *  Returns a read/write reference to the data at the last
       *  element of the %null_terminated_vector.
       */
      reference
      back() noexcept
      { return _Base::back().__ptr; }

      /**
       *  Returns a read-only (constant) reference to the data at the
       *  last element of the %null_terminated_vector.
       */
      const_reference
      back() const noexcept
      { return _Base::back().__ptr; }

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // DR 464. Suggestion for new member functions in standard containers.
      // data access
      /**
       *   Returns a pointer such that [data(), data() + size()) is a valid
       *   range. For a non-empty %null_terminated_vector, data() == &front().
       */
      value_type*
      data() noexcept
      { return &_Base::data()->__ptr; }

      const value_type*
      data() const noexcept
      { return &_Base::data()->__ptr; }

      // [23.2.4.3] modifiers
      /**
       *  @brief  Add data to the end of the %null_terminated_vector.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the end of the %null_terminated_vector and assigns
       *  the given data to it.  Due to the nature of a %null_terminated_vector
       *  this operation can be done in constant time if the
       *  %null_terminated_vector has preallocated space available.
       */
      void
      push_back(const value_type& __x)
      { _Base::push_back(_Tp(__x)); }

      void
      push_back(value_type&& __x)
      { _Base::push_back(_Tp(__x)); }

      /**
       *  @brief  Inserts given value into %null_terminated_vector
       *          before specified iterator.
       *  @param  __position  A const_iterator into the %null_terminated_vector.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given value before
       *  the specified location.  Note that this kind of operation
       *  could be expensive for a %null_terminated_vector and if it is
       *  frequently used the user should consider using std::list.
       */
      iterator
      insert(const_iterator __position, const value_type& __x)
      { return _Base::insert(__position, _Tp(__x)); }

      /**
       *  @brief  Inserts given rvalue into %null_terminated_vector
       *          before specified iterator.
       *  @param  __position  A const_iterator into the %null_terminated_vector.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given rvalue before
       *  the specified location.  Note that this kind of operation
       *  could be expensive for a %null_terminated_vector and if it
       *  is frequently used the user should consider using std::list.
       */
      iterator
      insert(const_iterator __position, value_type&& __x)
      { return _Base::insert(__position, _Tp(__x)); }

      /**
       *  @brief  Inserts an initializer_list into the %null_terminated_vector.
       *  @param  __position  An iterator into the %null_terminated_vector.
       *  @param  __l  An initializer_list.
       *
       *  This function will insert copies of the data in the
       *  initializer_list @a l into the %null_terminated_vector before
       *  the location specified by @a position.
       *
       *  Note that this kind of operation could be expensive for a
       *  %null_terminated_vector and if it is frequently used the
       *  user should consider using std::list.
       */
      iterator
      insert(const_iterator __position, std::initializer_list<value_type> __l)
      {
        auto __offset = __position - this->cbegin();
        _M_range_insert(this->begin() + __offset, __l.begin(), __l.end(),
                        std::random_access_iterator_tag());
        return this->begin() + __offset;
      }

      /**
       *  @brief  Inserts a number of copies of given data into the
       *          %null_terminated_vector.
       *  @param  __position  A const_iterator into the %null_terminated_vector.
       *  @param  __n  Number of elements to be inserted.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a specified number of copies of
       *  the given data before the location specified by @a position.
       *
       *  Note that this kind of operation could be expensive for a
       *  %null_terminated_vector and if it is frequently used the user
       *  should consider using std::list.
       */
      iterator
      insert(const_iterator __position, size_type __n, const value_type& __x)
      { return _Base::insert(__position, __n, _Tp(__x)); }

      /**
       *  @brief  Inserts a range into the %null_terminated_vector.
       *  @param  __position  A const_iterator into the %null_terminated_vector.
       *  @param  __first  An input iterator.
       *  @param  __last   An input iterator.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert copies of the data in the range
       *  [__first,__last) into the %null_terminated_vector before the
       *  location specified by @a pos.
       *
       *  Note that this kind of operation could be expensive for a
       *  %null_terminated_vector and if it is frequently used the user should
       *  consider using std::list.
       */
      template<typename _InputIterator,
               typename = std::_RequireInputIter<_InputIterator>>
        iterator
        insert(const_iterator __position, _InputIterator __first,
               _InputIterator __last)
        { return _Base::insert(__position, __first, __last); }

    };

} // namespace i1

#endif /* __NULL_TERMINATED_PTR_VECTOR_HPP__ */
