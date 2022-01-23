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

#ifndef __NULL_TERMINATED_VECTOR_HPP__
#define __NULL_TERMINATED_VECTOR_HPP__ 1

#if __cplusplus < 201103L
# error at least c++11 is required
#endif

#include <initializer_list>
#include <vector>

namespace i1
{

  /// See bits/stl_deque.h's _Deque_base for an explanation.
  template<typename _Tp, typename _Alloc>
    struct _Vector_base
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Tp>::other _Tp_alloc_type;
      typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
               pointer;

      struct _Vector_impl_data
      {
        pointer _M_start;

        _Vector_impl_data() _GLIBCXX_NOEXCEPT
        : _M_start()
        { }

        _Vector_impl_data(_Vector_impl_data&& __x) noexcept
        : _M_start(__x._M_start)
        { __x._M_start = pointer(); }

        void
        _M_copy_data(_Vector_impl_data const& __x) _GLIBCXX_NOEXCEPT
        { _M_start = __x._M_start; }

        void
        _M_swap_data(_Vector_impl_data& __x) _GLIBCXX_NOEXCEPT
        {
          // Do not use std::swap(_M_start, __x._M_start), etc as it loses
          // information used by TBAA.
          _Vector_impl_data __tmp;
          __tmp._M_copy_data(*this);
          _M_copy_data(__x);
          __x._M_copy_data(__tmp);
        }
      }; // _Vector_impl_data

      struct _Vector_impl
        : public _Tp_alloc_type, public _Vector_impl_data
      {
        _Vector_impl() _GLIBCXX_NOEXCEPT_IF(
            std::is_nothrow_default_constructible<_Tp_alloc_type>::value)
        : _Tp_alloc_type()
        { }

        _Vector_impl(_Tp_alloc_type const& __a) _GLIBCXX_NOEXCEPT
        : _Tp_alloc_type(__a)
        { }

        // Not defaulted, to enforce noexcept(true) even when
        // !is_nothrow_move_constructible<_Tp_alloc_type>.
        _Vector_impl(_Vector_impl&& __x) noexcept
        : _Tp_alloc_type(std::move(__x)), _Vector_impl_data(std::move(__x))
        { }

        _Vector_impl(_Tp_alloc_type&& __a) noexcept
        : _Tp_alloc_type(std::move(__a))
        { }

        _Vector_impl(_Tp_alloc_type&& __a, _Vector_impl&& __rv) noexcept
        : _Tp_alloc_type(std::move(__a)), _Vector_impl_data(std::move(__rv))
        { }

#define _GLIBCXX_ASAN_ANNOTATE_REINIT
#define _GLIBCXX_ASAN_ANNOTATE_GROW(n)
#define _GLIBCXX_ASAN_ANNOTATE_GREW(n)
#define _GLIBCXX_ASAN_ANNOTATE_SHRINK(n)
#define _GLIBCXX_ASAN_ANNOTATE_BEFORE_DEALLOC
      }; // _Vector_impl

    public:
      typedef _Alloc allocator_type;

      _Tp_alloc_type&
      _M_get_Tp_allocator() _GLIBCXX_NOEXCEPT
      { return this->_M_impl; }

      const _Tp_alloc_type&
      _M_get_Tp_allocator() const _GLIBCXX_NOEXCEPT
      { return this->_M_impl; }

      allocator_type
      get_allocator() const _GLIBCXX_NOEXCEPT
      { return allocator_type(_M_get_Tp_allocator()); }

      _Vector_base() = default;

      _Vector_base(const allocator_type& __a) _GLIBCXX_NOEXCEPT
      : _M_impl(__a) { }

      // Kept for ABI compatibility.
#if !_GLIBCXX_INLINE_VERSION
      _Vector_base(size_t __n)
      : _M_impl()
      { _M_create_storage(__n); }
#endif

      _Vector_base(size_t __n, const allocator_type& __a)
      : _M_impl(__a)
      { _M_create_storage(__n); }

      _Vector_base(_Vector_base&&) = default;

      // Kept for ABI compatibility.
# if !_GLIBCXX_INLINE_VERSION
      _Vector_base(_Tp_alloc_type&& __a) noexcept
      : _M_impl(std::move(__a)) { }

      _Vector_base(_Vector_base&& __x, const allocator_type& __a)
      : _M_impl(__a)
      {
        if (__x.get_allocator() == __a)
          this->_M_impl._M_swap_data(__x._M_impl);
        else
          {
            size_t __n = __x.size();
            _M_create_storage(__n);
          }
      }
# endif

      _Vector_base(const allocator_type& __a, _Vector_base&& __x)
      : _M_impl(_Tp_alloc_type(__a), std::move(__x._M_impl))
      { }

      ~_Vector_base() _GLIBCXX_NOEXCEPT
      {
        _M_deallocate(_M_impl._M_start, 16); // TODO
      }

    public:
      _Vector_impl _M_impl;

      pointer
      _M_allocate(size_t __n)
      {
        typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
        return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
      }

      void
      _M_deallocate(pointer __p, size_t __n)
      {
        typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
        if (__p)
          _Tr::deallocate(_M_impl, __p, __n);
      }

    protected:
      void
      _M_create_storage(size_t __n)
      {
        this->_M_impl._M_start = this->_M_allocate(__n);
      }
    }; // _Vector_base

  template<typename _Iterator, typename _Container>
    class __null_terminated_vector_iterator :
        public __gnu_cxx::__normal_iterator<_Iterator, _Container>
    {
      typedef typename __gnu_cxx::__normal_iterator<_Iterator, _Container>
                                                            __normal_iterator;

    public:
      typedef typename __normal_iterator::value_type        value_type;
      typedef typename __normal_iterator::difference_type   difference_type;
      typedef typename __normal_iterator::reference         reference;
      typedef typename __normal_iterator::pointer           pointer;

      _GLIBCXX_CONSTEXPR __null_terminated_vector_iterator() _GLIBCXX_NOEXCEPT
          = default;

      explicit
      __null_terminated_vector_iterator(const _Iterator& __i) _GLIBCXX_NOEXCEPT
      : __normal_iterator(__i) { }

      // Allow iterator to const_iterator conversion
      template<typename _Iter>
        __null_terminated_vector_iterator(
            const __null_terminated_vector_iterator<_Iter,
              typename __gnu_cxx::__enable_if<
                std::__are_same<_Iter, typename _Container::pointer>::__value,
                  _Container>::__type>& __i) _GLIBCXX_NOEXCEPT
           : __normal_iterator(__i) { }

      explicit operator bool() const noexcept
      { return !this->_M_current->is_null(); }

      friend bool operator==(const __null_terminated_vector_iterator& a,
                             const __null_terminated_vector_iterator& b)
      { return a._M_current == b._M_current; }

      friend bool operator!=(const __null_terminated_vector_iterator& a,
                             const __null_terminated_vector_iterator& b)
      { return a._M_current != b._M_current; }

      size_t back_size() const noexcept
      {
        size_t __n = 0;
        for (auto it = *this; it; ++it)
          ++__n;
        return __n;
      }

      __null_terminated_vector_iterator&
      operator++() _GLIBCXX_NOEXCEPT
      {
        __normal_iterator::operator++();
        return *this;
      }

      __null_terminated_vector_iterator
      operator++(int) _GLIBCXX_NOEXCEPT
      {
        __null_terminated_vector_iterator tmp = *this;
        ++(*this);
        return tmp;
      }

      __null_terminated_vector_iterator
      operator+(difference_type i) const
      { return __null_terminated_vector_iterator(this->_M_current + i); }

      __null_terminated_vector_iterator
      operator-(difference_type i) const
      { return __null_terminated_vector_iterator(this->_M_current - i); }

      friend __null_terminated_vector_iterator
      operator+(difference_type i, const __null_terminated_vector_iterator& it)
      { return __null_terminated_vector_iterator(it._M_current+i); }

      friend __null_terminated_vector_iterator
      operator-(difference_type i, const __null_terminated_vector_iterator& it)
      { return __null_terminated_vector_iterator(it._M_current-i); }


    }; // __null_terminated_vector_iterator

  /**
   *  @brief A standard container which offers fixed time access to
   *  individual elements in any order.
   *
   *  @ingroup sequences
   *
   *  @tparam _Tp  Type of element.
   *  @tparam _Alloc  Allocator type, defaults to allocator<_Tp>.
   *
   *  Meets the requirements of a <a href="tables.html#65">container</a>, a
   *  <a href="tables.html#66">reversible container</a>, and a
   *  <a href="tables.html#67">sequence</a>, including the
   *  <a href="tables.html#68">optional sequence requirements</a> with the
   *  %exception of @c push_front and @c pop_front.
   *
   *  In some terminology a %null_terminated_vector can be described as a dynamic
   *  C-style array, it offers fast and efficient access to individual
   *  elements in any order and saves the user from worrying about
   *  memory and size allocation.  Subscripting ( @c [] ) access is
   *  also provided as with C-style arrays.
  */
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class null_terminated_vector : protected _Vector_base<_Tp, _Alloc>
    {
#ifdef _GLIBCXX_CONCEPT_CHECKS
      // Concept requirements.
      typedef typename _Alloc::value_type                _Alloc_value_type;
      __glibcxx_class_requires2(_Tp, _Alloc_value_type, _SameTypeConcept)
#endif

      static_assert(std::is_same<typename std::remove_cv<_Tp>::type, _Tp>::value,
      "i1::null_terminated_vector must have a non-const, non-volatile value_type");
#ifdef __STRICT_ANSI__
      static_assert(std::is_same<typename _Alloc::value_type, _Tp>::value,
      "i1::null_terminated_vector must have the same value_type as its allocator");
#endif

      typedef _Vector_base<_Tp, _Alloc>                  _Base;
      typedef typename _Base::_Tp_alloc_type             _Tp_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type>  _Alloc_traits;

    public:
      typedef _Tp                                        value_type;
      typedef typename _Base::pointer                    pointer;
      typedef typename _Alloc_traits::const_pointer      const_pointer;
      typedef typename _Alloc_traits::reference          reference;
      typedef typename _Alloc_traits::const_reference    const_reference;
//      typedef __gnu_cxx::__normal_iterator<pointer, vector>  iterator;
//      typedef __gnu_cxx::__normal_iterator<const_pointer, vector> const_iterator;
      typedef __null_terminated_vector_iterator<pointer,
                  null_terminated_vector>                iterator;
      typedef __null_terminated_vector_iterator<
                  const_pointer, null_terminated_vector> const_iterator;
      typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;
      typedef std::reverse_iterator<iterator>            reverse_iterator;
      typedef size_t                                     size_type;
      typedef ptrdiff_t                                  difference_type;
      typedef _Alloc                                     allocator_type;

    private:
      static constexpr bool
      _S_nothrow_relocate(std::true_type)
      {
        return noexcept(std::__relocate_a(std::declval<pointer>(),
                                          std::declval<pointer>(),
                                          std::declval<pointer>(),
                                          std::declval<_Tp_alloc_type&>()));
      }

      static constexpr bool
      _S_nothrow_relocate(std::false_type)
      { return false; }

      static constexpr bool
      _S_use_relocate()
      {
        // Instantiating std::__relocate_a might cause an error outside the
        // immediate context (in __relocate_object_a's noexcept-specifier),
        // so only do it if we know the type can be move-inserted into *this.
        return _S_nothrow_relocate(std::__is_move_insertable<_Tp_alloc_type>{});
      }

      static pointer
      _S_do_relocate(pointer __first, pointer __last, pointer __result,
                     _Tp_alloc_type& __alloc, std::true_type) noexcept
      {
        return std::__relocate_a(__first, __last, __result, __alloc);
      }

      static pointer
      _S_do_relocate(pointer, pointer, pointer __result,
                     _Tp_alloc_type&, std::false_type) noexcept
      { return __result; }

      static pointer
      _S_relocate(pointer __first, pointer __last, pointer __result,
                  _Tp_alloc_type& __alloc) noexcept
      {
        using __do_it = std::__bool_constant<_S_use_relocate()>;
        return _S_do_relocate(__first, __last, __result, __alloc, __do_it{});
      }

    protected:
      using _Base::_M_allocate;
      using _Base::_M_deallocate;
      using _Base::_M_impl;
      using _Base::_M_get_Tp_allocator;

    public:
      // [23.2.4.1] construct/copy/destroy
      // (assign() and get_allocator() are also listed in this section)

      /**
       *  @brief  Creates a %null_terminated_vector with no elements.
       */
      null_terminated_vector()
      : null_terminated_vector(0) { }

      /**
       *  @brief  Creates a %null_terminated_vector with no elements.
       *  @param  __a  An allocator object.
       */
      explicit
      null_terminated_vector(const allocator_type& __a) _GLIBCXX_NOEXCEPT
      : null_terminated_vector(0, __a) { }

      /**
       *  @brief  Creates a %null_terminated_vector with default
       *          constructed elements.
       *  @param  __n  The number of elements to initially create.
       *  @param  __a  An allocator.
       *
       *  This constructor fills the %null_terminated_vector with
       *  @a __n default constructed elements.
       */
      explicit
      null_terminated_vector(size_type __n,
                             const allocator_type& __a = allocator_type())
      : _Base(_S_check_init_len(__n+1, __a), __a)
      {
        _M_default_initialize(__n);
      }

      /**
       *  @brief  Creates a %null_terminated_vector with copies of
       *          an exemplar element.
       *  @param  __n  The number of elements to initially create.
       *  @param  __value  An element to copy.
       *  @param  __a  An allocator.
       *
       *  This constructor fills the %null_terminated_vector with
       *  @a __n copies of @a __value.
       */
      null_terminated_vector(size_type __n, const value_type& __value,
             const allocator_type& __a = allocator_type())
      : _Base(_S_check_init_len(__n+1, __a), __a)
      {
        _M_fill_initialize(__n, __value);
      }

      /**
       *  @brief  %Vector copy constructor.
       *  @param  __x  A %null_terminated_vector of identical element
       *          and allocator types.
       *
       *  All the elements of @a __x are copied, but any unused capacity
       *  in @a __x  will not be copied (i.e. capacity() == size() in
       *  the new %null_terminated_vector).
       *
       *  The newly-created %null_terminated_vector uses a copy of
       *  the allocator object used by @a __x (unless the allocator
       *  traits dictate a different object).
       */
      null_terminated_vector(const null_terminated_vector& __x)
      : _Base(__x.size()+1,
        _Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
      {
        std::__uninitialized_copy_a(__x.begin(), __x.end(),
                                    this->_M_impl._M_start,
                                    _M_get_Tp_allocator());
        const value_type __null_terminator = _Tp::null_terminator();
        std::__uninitialized_fill_n_a(this->_M_impl._M_start + __x.size(), 1,
                                      __null_terminator,
                                      _M_get_Tp_allocator());
      }

      /**
       *  @brief  %Vector move constructor.
       *
       *  The newly-created %null_terminated_vector contains the
       *  exact contents of the moved instance.
       *  The contents of the moved instance are a valid, but unspecified
       *  %null_terminated_vector.
       */
      null_terminated_vector(null_terminated_vector&&) noexcept = default;

      /**  Copy constructor with alternative allocator */
      null_terminated_vector(const null_terminated_vector& __x,
                             const allocator_type& __a)
      : _Base(__x.size()+1, __a)
      {
        std::__uninitialized_copy_a(__x.begin(), __x.end(),
                                    this->_M_impl._M_start,
                                    _M_get_Tp_allocator());
        const value_type __null_terminator = _Tp::null_terminator();
        std::__uninitialized_fill_n_a(this->_M_impl._M_start + __x.size(), 1,
                                      __null_terminator,
                                      _M_get_Tp_allocator());
      }

    private:
      null_terminated_vector(null_terminated_vector&& __rv,
                             const allocator_type& __m,
                             std::true_type) noexcept
      : _Base(__m, std::move(__rv))
      { }

      null_terminated_vector(null_terminated_vector&& __rv,
                             const allocator_type& __m,
                             std::false_type)
      : _Base(__m)
      {
        if (__rv.get_allocator() == __m)
          this->_M_impl._M_swap_data(__rv._M_impl);
        else if (!__rv.empty())
          {
            const auto __n = __rv.size();
            this->_M_create_storage(__n+1);
            std::__uninitialized_move_a(__rv.begin(), __rv.end(),
                                        this->_M_impl._M_start,
                                        _M_get_Tp_allocator());
            __rv.clear();
            const value_type __null_terminator = _Tp::null_terminator();
            std::__uninitialized_fill_n_a(this->_M_impl._M_start + __n, 1,
                                          __null_terminator,
                                          _M_get_Tp_allocator());
          }
      }

    public:
      /// Move constructor with alternative allocator
      null_terminated_vector(null_terminated_vector&& __rv,
                             const allocator_type& __m)
      noexcept( noexcept(null_terminated_vector(
          std::declval<null_terminated_vector&&>(),
          std::declval<const allocator_type&>(),
          std::declval<typename _Alloc_traits::is_always_equal>())) )
      : null_terminated_vector(std::move(__rv), __m,
                               typename _Alloc_traits::is_always_equal{})
      { }

      /**
       *  @brief  Builds a %null_terminated_vector from an initializer list.
       *  @param  __l  An initializer_list.
       *  @param  __a  An allocator.
       *
       *  Create a %null_terminated_vector consisting of copies of
       *  the elements in the initializer_list @a __l.
       *
       *  This will call the element type's copy constructor N times
       *  (where N is @a __l.size()) and do no memory reallocation.
       */
      null_terminated_vector(std::initializer_list<value_type> __l,
             const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
        _M_range_initialize(__l.begin(), __l.end(),
                            std::random_access_iterator_tag());
      }

      /**
       *  @brief  Builds a %null_terminated_vector from a range.
       *  @param  __first  An input iterator.
       *  @param  __last  An input iterator.
       *  @param  __a  An allocator.
       *
       *  Create a %null_terminated_vector consisting of copies of
       *  the elements from [first,last).
       *
       *  If the iterators are forward, bidirectional, or
       *  random-access, then this will call the elements' copy
       *  constructor N times (where N is distance(first,last)) and do
       *  no memory reallocation.  But if only input iterators are
       *  used, then this will do at most 2N calls to the copy
       *  constructor, and logN memory reallocations.
       */
      template<typename _InputIterator,
               typename = std::_RequireInputIter<_InputIterator>>
        null_terminated_vector(_InputIterator __first, _InputIterator __last,
               const allocator_type& __a = allocator_type())
        : _Base(__a)
        {
          _M_range_initialize(__first, __last,
                              std::__iterator_category(__first));
        }

      /**
       *  The dtor only erases the elements, and note that if the
       *  elements themselves are pointers, the pointed-to memory is
       *  not touched in any way.  Managing the pointer is the user's
       *  responsibility.
       */
      ~null_terminated_vector() _GLIBCXX_NOEXCEPT
      {
        const auto __n = this->size();
        std::_Destroy(this->_M_impl._M_start,
                      this->_M_impl._M_start + __n+1,
                      _M_get_Tp_allocator());
        _GLIBCXX_ASAN_ANNOTATE_BEFORE_DEALLOC;
      }

      /**
       *  @brief  %Vector assignment operator.
       *  @param  __x  A %null_terminated_vector of identical element and
       *          allocator types.
       *
       *  All the elements of @a __x are copied, but any unused capacity
       *  in @a __x will not be copied.
       *
       *  Whether the allocator is copied depends on the allocator traits.
       */
      null_terminated_vector&
      operator=(const null_terminated_vector& __x)
      {
        if (&__x != this)
          {
            _GLIBCXX_ASAN_ANNOTATE_REINIT;
            const size_type __len = this->size();
            if (_Alloc_traits::_S_propagate_on_copy_assign())
              {
                if (!_Alloc_traits::_S_always_equal()
                    && _M_get_Tp_allocator() != __x._M_get_Tp_allocator())
                  {
                    // replacement allocator cannot free existing storage
                    this->clear();
                    _M_deallocate(this->_M_impl._M_start, __len+1);
                    this->_M_impl._M_start = nullptr;
                  }
                std::__alloc_on_copy(_M_get_Tp_allocator(),
                                     __x._M_get_Tp_allocator());
              }
            const size_type __xlen = __x.size();
            pointer __tmp = _M_allocate_and_copy(__xlen+1, __x.begin(),
                                                 __x.end()+1);
            std::_Destroy(this->_M_impl._M_start,
                          this->_M_impl._M_start+__len+1,
                          _M_get_Tp_allocator());
            _M_deallocate(this->_M_impl._M_start, __len+1);
            this->_M_impl._M_start = __tmp;
          }
        return *this;
      }

      /**
       *  @brief  %Vector move assignment operator.
       *  @param  __x  A %null_terminated_vector of identical element
       *          and allocator types.
       *
       *  The contents of @a __x are moved into this %null_terminated_vector
       *  (without copying, if the allocators permit it).
       *  Afterwards @a __x is a valid, but unspecified %null_terminated_vector.
       *
       *  Whether the allocator is moved depends on the allocator traits.
       */
      null_terminated_vector&
      operator=(null_terminated_vector&& __x)
        noexcept(_Alloc_traits::_S_nothrow_move())
      {
        constexpr bool __move_storage =
            _Alloc_traits::_S_propagate_on_move_assign() ||
            _Alloc_traits::_S_always_equal();
        _M_move_assign(std::move(__x), std::__bool_constant<__move_storage>());
        return *this;
      }

      /**
       *  @brief  %Vector list assignment operator.
       *  @param  __l  An initializer_list.
       *
       *  This function fills a %null_terminated_vector with copies
       *  of the elements in the initializer list @a __l.
       *
       *  Note that the assignment completely changes the
       *  %null_terminated_vector and that the resulting
       *  %null_terminated_vector's size is the same as the number
       *  of elements assigned.
       */
      null_terminated_vector&
      operator=(std::initializer_list<value_type> __l)
      {
        this->_M_assign_aux(__l.begin(), __l.end(),
                            std::random_access_iterator_tag());
        return *this;
      }

      class __std_vector : public std::vector<_Tp, _Alloc>
      {
      public:
        void reset()
        {
          this->_M_impl._M_start =
          this->_M_impl._M_finish =
          this->_M_impl._M_end_of_storage = nullptr;
        }

        pointer steal()
        { return this->_M_impl._M_start; }

        void force(pointer __start, size_type __n)
        {
          _M_set_them_free();
          this->_M_impl._M_start = __start;
          this->_M_impl._M_finish =
          this->_M_impl._M_end_of_storage = __start + (__n+1);
          this->pop_back();
        }

      private:
        void _M_set_them_free()
        {
          this->clear();
          _M_deallocate(this->_M_impl._M_start,
            this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
        }
      };

      null_terminated_vector&
      operator=(std::vector<_Tp, _Alloc>&& __x) noexcept
      {
        __x.push_back(_Tp::null_terminator());
        __x.shrink_to_fit();
        const auto __len = this->size();
        this->clear();
        _M_deallocate(this->_M_impl._M_start, __len+1);
        this->_M_impl._M_start = static_cast<__std_vector&&>(__x).steal();
        static_cast<__std_vector&&>(__x).reset();
        return *this;
      }

      std::vector<_Tp, _Alloc>&
      convert_to(std::vector<_Tp, _Alloc>& __x)
      {
        static_cast<__std_vector&>(__x).force(this->_M_impl._M_start, size());
        this->_M_impl._M_start = this->_M_allocate(1);
        this->_M_default_initialize(0);
        return __x;
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
      { _M_fill_assign(__n, __val); }

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
        { _M_assign_dispatch(__first, __last, std::__false_type()); }

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
      using _Base::get_allocator;

      // iterators
      /**
       *  Returns a read/write iterator that points to the first
       *  element in the %null_terminated_vector. Iteration is done
       *  in ordinary element order.
       */
      iterator
      begin() _GLIBCXX_NOEXCEPT
      { return iterator(this->_M_impl._M_start); }

      /**
       *  Returns a read-only (constant) iterator that points to the
       *  first element in the %null_terminated_vector. Iteration is
       *  done in ordinary element order.
       */
      const_iterator
      begin() const _GLIBCXX_NOEXCEPT
      { return const_iterator(this->_M_impl._M_start); }

      /**
       *  Returns a read/write iterator that points one past the last
       *  element in the %null_terminated_vector. Iteration is done
       *  in ordinary element order.
       */
      iterator
      end() _GLIBCXX_NOEXCEPT
      { return iterator(this->_M_impl._M_start + this->size()); }

      /**
       *  Returns a read-only (constant) iterator that points one past
       *  the last element in the %null_terminated_vector. Iteration is
       *  done in ordinary element order.
       */
      const_iterator
      end() const _GLIBCXX_NOEXCEPT
      { return const_iterator(this->_M_impl._M_start + this->size()); }

      /**
       *  Returns a read/write reverse iterator that points to the
       *  last element in the %null_terminated_vector. Iteration is done
       *  in reverse element order.
       */
      reverse_iterator
      rbegin() _GLIBCXX_NOEXCEPT
      { return reverse_iterator(end()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points
       *  to the last element in the %null_terminated_vector. Iteration is
       *  done in reverse element order.
       */
      const_reverse_iterator
      rbegin() const _GLIBCXX_NOEXCEPT
      { return const_reverse_iterator(end()); }

      /**
       *  Returns a read/write reverse iterator that points to one
       *  before the first element in the %null_terminated_vector. Iteration
       *  is done in reverse element order.
       */
      reverse_iterator
      rend() _GLIBCXX_NOEXCEPT
      { return reverse_iterator(begin()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points
       *  to one before the first element in the %null_terminated_vector.
       *  Iteration is done in reverse element order.
       */
      const_reverse_iterator
      rend() const _GLIBCXX_NOEXCEPT
      { return const_reverse_iterator(begin()); }

      /**
       *  Returns a read-only (constant) iterator that points to the
       *  first element in the %null_terminated_vector. Iteration is
       *  done in ordinary element order.
       */
      const_iterator
      cbegin() const noexcept
      { return const_iterator(this->_M_impl._M_start); }

      /**
       *  Returns a read-only (constant) iterator that points one past
       *  the last element in the %null_terminated_vector. Iteration is
       *  done in ordinary element order.
       */
      const_iterator
      cend() const noexcept
      { return const_iterator(this->_M_impl._M_start + this->size()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points
       *  to the last element in the %null_terminated_vector. Iteration
       *  is done in reverse element order.
       */
      const_reverse_iterator
      crbegin() const noexcept
      { return const_reverse_iterator(end()); }

      /**
       *  Returns a read-only (constant) reverse iterator that points
       *  to one before the first element in the %null_terminated_vector.
       *  Iteration is done in reverse element order.
       */
      const_reverse_iterator
      crend() const noexcept
      { return const_reverse_iterator(begin()); }

      // [23.2.4.2] capacity
      /**  Returns the number of elements in the %null_terminated_vector.  */
      size_type
      size() const _GLIBCXX_NOEXCEPT
      {
        size_type __n = 0;
        for (auto it = begin(); it; ++it) ++__n;
        return __n;
      }

      /**  Returns the size() of the largest possible %null_terminated_vector. */
      size_type
      max_size() const _GLIBCXX_NOEXCEPT
      { return _S_max_size(_M_get_Tp_allocator()); }

      /**
       *  @brief  Resizes the %null_terminated_vector to the specified
       *          number of elements.
       *  @param  __new_size  Number of elements the %null_terminated_vector
       *          should contain.
       *
       *  This function will %resize the %null_terminated_vector to the
       *  specified number of elements.  If the number is smaller than the
       *  %null_terminated_vector's current size the %null_terminated_vector
       *  is truncated, otherwise default constructed elements are appended.
       */
      void
      resize(size_type __new_size)
      {
        const auto __size = size();
        if (__new_size > __size)
          _M_default_append(__new_size - __size);
        else if (__new_size < __size)
          _M_erase_at_end(this->_M_impl._M_start + __new_size, __size);
      }

      /**
       *  @brief  Resizes the %null_terminated_vector to the specified
       *          number of elements.
       *  @param  __new_size  Number of elements the %null_terminated_vector
       *          should contain.
       *  @param  __x  Data with which new elements should be populated.
       *
       *  This function will %resize the %null_terminated_vector to the
       *  specified number of elements.  If the number is smaller than the
       *  %null_terminated_vector's current size the %null_terminated_vector
       *  is truncated, otherwise the %null_terminated_vector is extended
       *  and new elements are populated with given data.
       */
      void
      resize(size_type __new_size, const value_type& __x)
      {
        const auto __size = size();
        if (__new_size > __size)
          _M_fill_insert(end(), __new_size - __size, __x);
        else if (__new_size < __size)
          _M_erase_at_end(this->_M_impl._M_start + __new_size, __size);
      }

      /**  A non-binding request to reduce capacity() to size().  */
      void
      shrink_to_fit()
      { _M_shrink_to_fit(); }

      /**
       *  Returns the total number of elements that the %null_terminated_vector
       *  can hold before needing to allocate more memory.
       */
      size_type
      capacity() const _GLIBCXX_NOEXCEPT
      { return this->size() + 1; }

      /**
       *  Returns true if the %null_terminated_vector is empty. (Thus begin()
       *  would equal end().)
       */
      _GLIBCXX_NODISCARD bool
      empty() const _GLIBCXX_NOEXCEPT
      { return begin()->is_null(); }

      /**
       *  @brief  Attempt to preallocate enough memory for specified
       *          number of elements.
       *  @param  __n  Number of elements required.
       *  @throw  std::length_error  If @a n exceeds @c max_size().
       *
       *  This function attempts to reserve enough memory for the
       *  %null_terminated_vector to hold the specified number of elements.
       *  If the number requested is more than max_size(), length_error is
       *  thrown.
       *
       *  The advantage of this function is that if optimal code is a
       *  necessity and the user can determine the number of elements
       *  that will be required, the user can reserve the memory in
       *  %advance, and thus prevent a possible reallocation of memory
       *  and copying of %null_terminated_vector data.
       */
      void
      reserve(size_type __n);

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
      operator[](size_type __n) _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_subscript(__n);
        return *(this->_M_impl._M_start + __n);
      }

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
      operator[](size_type __n) const _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_subscript(__n);
        return *(this->_M_impl._M_start + __n);
      }

    protected:
      /// Safety check used only from at().
      void
      _M_range_check(size_type __n) const
      {
        if (__n >= this->size())
          __throw_out_of_range_fmt(__N("null_terminated_vector::_M_range_check: __n "
                                       "(which is %zu) >= this->size() "
                                       "(which is %zu)"),
                                   __n, this->size());
      }

    public:
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
      {
        _M_range_check(__n);
        return (*this)[__n];
      }

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
      {
        _M_range_check(__n);
        return (*this)[__n];
      }

      /**
       *  Returns a read/write reference to the data at the first
       *  element of the %null_terminated_vector.
       */
      reference
      front() _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_nonempty();
        return *begin();
      }

      /**
       *  Returns a read-only (constant) reference to the data at the first
       *  element of the %null_terminated_vector.
       */
      const_reference
      front() const _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_nonempty();
        return *begin();
      }

      /**
       *  Returns a read/write reference to the data at the last
       *  element of the %null_terminated_vector.
       */
      reference
      back() _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_nonempty();
        return (*this)[size() - 1];
      }

      /**
       *  Returns a read-only (constant) reference to the data at the
       *  last element of the %null_terminated_vector.
       */
      const_reference
      back() const _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_nonempty();
        return (*this)[size() - 1];
      }

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // DR 464. Suggestion for new member functions in standard containers.
      // data access
      /**
       *   Returns a pointer such that [data(), data() + size()) is a valid
       *   range. For a non-empty %null_terminated_vector, data() == &front().
       */
      _Tp*
      data() _GLIBCXX_NOEXCEPT
      { return _M_data_ptr(this->_M_impl._M_start); }

      const _Tp*
      data() const _GLIBCXX_NOEXCEPT
      { return _M_data_ptr(this->_M_impl._M_start); }

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
      {
        _M_realloc_insert(end(), __x);
      }

      void
      push_back(value_type&& __x)
      { emplace_back(std::move(__x)); }

      template<typename... _Args>
#if __cplusplus > 201402L
      reference
#else
      void
#endif
      emplace_back(_Args&&... __args)
      {
        _M_realloc_insert(end(), std::forward<_Args>(__args)...);
#if __cplusplus > 201402L
        return back();
#endif
      }

      /**
       *  @brief  Removes last element.
       *
       *  This is a typical stack operation. It shrinks
       *  the %null_terminated_vector by one.
       *
       *  Note that no data is returned, and if the last element's
       *  data is needed, it should be retrieved before pop_back() is
       *  called.
       */
      void
      pop_back() _GLIBCXX_NOEXCEPT
      {
        __glibcxx_requires_nonempty();
        const auto __size = this->size();
        std::swap(this->_M_impl._M_start[__size - 1],
                  this->_M_impl._M_start[__size]);
        _Alloc_traits::destroy(this->_M_impl, &this->_M_impl._M_start[__size]);
        _GLIBCXX_ASAN_ANNOTATE_SHRINK(1);
      }

      /**
       *  @brief  Inserts an object in %null_terminated_vector before
       *          specified iterator.
       *  @param  __position  A const_iterator into the %null_terminated_vector.
       *  @param  __args  Arguments.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert an object of type T constructed
       *  with T(std::forward<Args>(args)...) before the specified location.
       *  Note that this kind of operation could be expensive for a
       *  %null_terminated_vector and if it is frequently used the user
       *  should consider using std::list.
       */
      template<typename... _Args>
        iterator
        emplace(const_iterator __position, _Args&&... __args)
        { return _M_emplace_aux(__position, std::forward<_Args>(__args)...); }

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
      {
        const size_type __n = __position - begin();
        _M_realloc_insert(begin() + (__position - cbegin()), __x);
        return iterator(this->_M_impl._M_start + __n);
      }

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
      { return _M_insert_rval(__position, std::move(__x)); }

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
        auto __offset = __position - cbegin();
        _M_range_insert(begin() + __offset, __l.begin(), __l.end(),
                        std::random_access_iterator_tag());
        return begin() + __offset;
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
      {
        difference_type __offset = __position - cbegin();
        _M_fill_insert(begin() + __offset, __n, __x);
        return begin() + __offset;
      }

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
        {
          difference_type __offset = __position - cbegin();
          _M_insert_dispatch(begin() + __offset,
                             __first, __last, std::__false_type());
          return begin() + __offset;
        }

      /**
       *  @brief  Remove element at given position.
       *  @param  __position  Iterator pointing to element to be erased.
       *  @return  An iterator pointing to the next element (or end()).
       *
       *  This function will erase the element at the given position and thus
       *  shorten the %null_terminated_vector by one.
       *
       *  Note This operation could be expensive and if it is
       *  frequently used the user should consider using std::list.
       *  The user is also cautioned that this function only erases
       *  the element, and that if the element is itself a pointer,
       *  the pointed-to memory is not touched in any way.  Managing
       *  the pointer is the user's responsibility.
       */
      iterator
      erase(const_iterator __position)
      { return _M_erase(begin() + (__position - cbegin())); }

      /**
       *  @brief  Remove a range of elements.
       *  @param  __first  Iterator pointing to the first element to be erased.
       *  @param  __last  Iterator pointing to one past the last element to be
       *                  erased.
       *  @return  An iterator pointing to the element pointed to by @a __last
       *           prior to erasing (or end()).
       *
       *  This function will erase the elements in the range
       *  [__first,__last) and shorten the %null_terminated_vector accordingly.
       *
       *  Note This operation could be expensive and if it is
       *  frequently used the user should consider using std::list.
       *  The user is also cautioned that this function only erases
       *  the elements, and that if the elements themselves are
       *  pointers, the pointed-to memory is not touched in any way.
       *  Managing the pointer is the user's responsibility.
       */
      iterator
      erase(const_iterator __first, const_iterator __last)
      {
        const auto __beg = begin();
        const auto __cbeg = cbegin();
        return _M_erase(__beg + (__first - __cbeg), __beg + (__last - __cbeg));
      }

      /**
       *  @brief  Swaps data with another %null_terminated_vector.
       *  @param  __x  A %null_terminated_vector of the same element and
       *          allocator types.
       *
       *  This exchanges the elements between two vectors in constant time.
       *  (Three pointers, so it should be quite fast.)
       *  Note that the global std::swap() function is specialized such that
       *  std::swap(v1,v2) will feed to this function.
       *
       *  Whether the allocators are swapped depends on the allocator traits.
       */
      void
      swap(null_terminated_vector& __x) _GLIBCXX_NOEXCEPT
      {
        __glibcxx_assert(_Alloc_traits::propagate_on_container_swap::value
                         || _M_get_Tp_allocator() == __x._M_get_Tp_allocator());
        this->_M_impl._M_swap_data(__x._M_impl);
        _Alloc_traits::_S_on_swap(_M_get_Tp_allocator(),
                                  __x._M_get_Tp_allocator());
      }

      /**
       *  Erases all the elements.  Note that this function only erases the
       *  elements, and that if the elements themselves are pointers, the
       *  pointed-to memory is not touched in any way.  Managing the pointer
       *  is the user's responsibility.
       */
      void
      clear() _GLIBCXX_NOEXCEPT
      { _M_erase_at_end(this->_M_impl._M_start); }

    protected:
      /**
       *  Memory expansion handler.  Uses the member allocation function to
       *  obtain @a n bytes of memory, and then copies [first,last) into it.
       */
      template<typename _ForwardIterator>
        pointer
        _M_allocate_and_copy(size_type __n,
                             _ForwardIterator __first, _ForwardIterator __last)
        {
          pointer __result = this->_M_allocate(__n);
          __try
            {
              std::__uninitialized_copy_a(__first, __last, __result,
                                          _M_get_Tp_allocator());
              return __result;
            }
          __catch(...)
            {
              _M_deallocate(__result, __n);
              __throw_exception_again;
            }
        }


      // Internal constructor functions follow.

      // Called by the range constructor to implement [23.1.1]/9

      // Called by the second initialize_dispatch above
      template<typename _InputIterator>
        void
        _M_range_initialize(_InputIterator __first, _InputIterator __last,
                            std::input_iterator_tag)
        {
          __try {
            for (; __first != __last; ++__first)
              emplace_back(*__first);
          } __catch(...) {
            clear();
            __throw_exception_again;
          }
      }

      // Called by the second initialize_dispatch above
      template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
                            std::forward_iterator_tag)
        {
          const size_type __n = std::distance(__first, __last);
          this->_M_impl._M_start
            = this->_M_allocate(_S_check_init_len(__n+1, _M_get_Tp_allocator()));
          std::__uninitialized_copy_a(__first, __last,
                                      this->_M_impl._M_start,
                                      _M_get_Tp_allocator());
          const value_type __null_terminator = _Tp::null_terminator();
          std::__uninitialized_fill_n_a(this->_M_impl._M_start + __n, 1,
                                        __null_terminator,
                                        _M_get_Tp_allocator());
        }

      // Called by the first initialize_dispatch above and by the
      // null_terminated_vector(n,value,a) constructor.
      void
      _M_fill_initialize(size_type __n, const value_type& __value)
      {
          std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
                                        _M_get_Tp_allocator());
          const value_type __null_terminator = _Tp::null_terminator();
          std::__uninitialized_fill_n_a(this->_M_impl._M_start + __n, 1,
                                        __null_terminator,
                                        _M_get_Tp_allocator());
      }

      // Called by the null_terminated_vector(n) constructor.
      void
      _M_default_initialize(size_type __n)
      {
          std::__uninitialized_default_n_a(this->_M_impl._M_start, __n,
                                           _M_get_Tp_allocator());
          const value_type __null_terminator = _Tp::null_terminator();
          std::__uninitialized_fill_n_a(this->_M_impl._M_start + __n, 1,
                                        __null_terminator,
                                        _M_get_Tp_allocator());
      }

      // Internal assign functions follow.  The *_aux functions do the actual
      // assignment work for the range versions.

      // Called by the range assign to implement [23.1.1]/9

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename _Integer>
        void
        _M_assign_dispatch(_Integer __n, _Integer __val, std::__true_type)
        { _M_fill_assign(__n, __val); }

      // Called by the range assign to implement [23.1.1]/9
      template<typename _InputIterator>
        void
        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
                           std::__false_type)
        { _M_assign_aux(__first, __last, std::__iterator_category(__first)); }

      // Called by the second assign_dispatch above
      template<typename _InputIterator>
        void
        _M_assign_aux(_InputIterator __first, _InputIterator __last,
                      std::input_iterator_tag)
        {
          pointer __cur(this->_M_impl._M_start);
          for (; __first != __last && !__cur->is_null(); ++__cur, (void)++__first)
            *__cur = *__first;
          if (__first == __last)
            _M_erase_at_end(__cur);
          else
            _M_range_insert(end(), __first, __last,
                            std::__iterator_category(__first));
        }

      // Called by the second assign_dispatch above
      template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
                      std::forward_iterator_tag)
        {
          const size_type __len = std::distance(__first, __last);
          const size_type __size = size();
          // _S_check_init_len(__len, _M_get_Tp_allocator()); // TODO
          pointer __tmp(_M_allocate_and_copy(__len+1, __first, __last));
          __tmp[__len] = _Tp::null_terminator();
          std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_start+__size+1,
                        _M_get_Tp_allocator());
          _GLIBCXX_ASAN_ANNOTATE_REINIT;
          _M_deallocate(this->_M_impl._M_start, __size+1);
          this->_M_impl._M_start = __tmp;
        }

      // Called by assign(n,t), and the range assign when it turns out
      // to be the same thing.
      void
      _M_fill_assign(size_type __n, const value_type& __val)
      //
      {
        null_terminated_vector __tmp(__n, __val, _M_get_Tp_allocator());
        __tmp._M_impl._M_swap_data(this->_M_impl);
      }

      // Internal insert functions follow.

      // Called by the range insert to implement [23.1.1]/9

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 438. Ambiguity in the "do the right thing" clause
      template<typename _Integer>
        void
        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
                           std::__true_type)
        { _M_fill_insert(__pos, __n, __val); }

      // Called by the range insert to implement [23.1.1]/9
      template<typename _InputIterator>
        void
        _M_insert_dispatch(iterator __pos, _InputIterator __first,
                           _InputIterator __last, std::__false_type)
        {
          _M_range_insert(__pos, __first, __last,
                          std::__iterator_category(__first));
        }

      // Called by the second insert_dispatch above
      template<typename _InputIterator>
        void
        _M_range_insert(iterator __pos, _InputIterator __first,
                        _InputIterator __last, std::input_iterator_tag)
        {
          const auto __end = end();
          if (__pos == __end)
            {
              for (; __first != __last; ++__first)
                insert(__end++, *__first);
            }
          else if (__first != __last)
            {
              null_terminated_vector __tmp(__first, __last, _M_get_Tp_allocator());
              insert(__pos,
                     _GLIBCXX_MAKE_MOVE_ITERATOR(__tmp.begin()),
                     _GLIBCXX_MAKE_MOVE_ITERATOR(__tmp.end()));
            }
        }

      // Called by the second insert_dispatch above
      template<typename _ForwardIterator>
        void
        _M_range_insert(iterator __pos, _ForwardIterator __first,
                        _ForwardIterator __last, std::forward_iterator_tag)
        {
          if (__first != __last)
            {
              const size_type __tail = __pos.back_size();
              const size_type __head = std::distance(begin(), __pos);
              const size_type __size = __tail + __head;
              const size_type __n = std::distance(__first, __last);
              const size_type __len = __size + __n;
              // _M_check_len(__n, "vector::_M_range_insert"); // TODO
              pointer __new_start(this->_M_allocate(__len+1));
              pointer __new_finish(__new_start);
              __try
                {
                  __new_finish
                    = std::__uninitialized_move_if_noexcept_a
                    (this->_M_impl._M_start, __pos.base(),
                     __new_start, _M_get_Tp_allocator());
                  __new_finish
                    = std::__uninitialized_copy_a(__first, __last,
                                                  __new_finish,
                                                  _M_get_Tp_allocator());
                  __new_finish
                    = std::__uninitialized_move_if_noexcept_a
                    (__pos.base(), __pos.base() + (__tail+1),
                     __new_finish, _M_get_Tp_allocator());
                }
              __catch(...)
                {
                  std::_Destroy(__new_start, __new_finish,
                                _M_get_Tp_allocator());
                  _M_deallocate(__new_start, __len+1);
                  __throw_exception_again;
                }
              std::_Destroy(this->_M_impl._M_start,
                            this->_M_impl._M_start + (__size+1),
                            _M_get_Tp_allocator());
              _GLIBCXX_ASAN_ANNOTATE_REINIT;
              _M_deallocate(this->_M_impl._M_start, __size+1);
              this->_M_impl._M_start = __new_start;
            }
        }

      // Called by insert(p,n,x), and the range insert when it turns out to be
      // the same thing.
      void
      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);

      // Called by resize(n).
      void
      _M_default_append(size_type __n);

      bool
      _M_shrink_to_fit();

      // A value_type object constructed with _Alloc_traits::construct()
      // and destroyed with _Alloc_traits::destroy().
      struct _Temporary_value
      {
        template<typename... _Args>
          explicit
          _Temporary_value(null_terminated_vector* __vec, _Args&&... __args)
          : _M_this(__vec)
          {
            _Alloc_traits::construct(_M_this->_M_impl, _M_ptr(),
                                     std::forward<_Args>(__args)...);
          }

        ~_Temporary_value()
        { _Alloc_traits::destroy(_M_this->_M_impl, _M_ptr()); }

        value_type&
        _M_val() { return *_M_ptr(); }

      private:
        _Tp*
        _M_ptr() { return reinterpret_cast<_Tp*>(&__buf); }

        null_terminated_vector* _M_this;
        typename std::aligned_storage<sizeof(_Tp), alignof(_Tp)>::type __buf;
      };

      // Called by insert(p,x) and other functions when insertion needs to
      // reallocate or move existing elements. _Arg is either _Tp& or _Tp.
      template<typename _Arg>
        void
        _M_insert_aux(iterator __position, _Arg&& __arg);

      template<typename... _Args>
        void
        _M_realloc_insert(iterator __position, _Args&&... __args)
        {
          const size_type __size = size();
          const size_type __len = __size + 1;
          pointer __old_start = this->_M_impl._M_start;
          pointer __old_finish = __old_start + __size;
          const size_type __elems_before = __position ? __position - begin()
                                                      : __size;
          pointer __new_start(this->_M_allocate(__len+1));
          pointer __new_finish(__new_start);
          __try
            {
              // The order of the three operations is dictated by the C++11
              // case, where the moves could alter a new element belonging
              // to the existing vector.  This is an issue only for callers
              // taking the element by lvalue ref (see last bullet of C++11
              // [res.on.arguments]).
              _Alloc_traits::construct(this->_M_impl,
                                       __new_start + __elems_before,
                                       std::forward<_Args>(__args)...);
              __new_finish = pointer();
              if _GLIBCXX17_CONSTEXPR (_S_use_relocate())
                {
                  __new_finish = _S_relocate(__old_start, __position.base(),
                                             __new_start, _M_get_Tp_allocator());

                  ++__new_finish;

                  __new_finish = _S_relocate(__position.base(), __old_finish+1,
                                             __new_finish, _M_get_Tp_allocator());
                }
              else
                {
                  __new_finish
                    = std::__uninitialized_move_if_noexcept_a
                    (__old_start, __position.base(),
                     __new_start, _M_get_Tp_allocator());
                  ++__new_finish;
                  __new_finish
                    = std::__uninitialized_move_if_noexcept_a
                    (__position.base(), __old_finish+1,
                     __new_finish, _M_get_Tp_allocator());
                }
            }
          __catch(...)
            {
              if (!__new_finish)
                _Alloc_traits::destroy(this->_M_impl,
                                       __new_start + __elems_before);
              else
                std::_Destroy(__new_start, __new_finish+1, _M_get_Tp_allocator());
              _M_deallocate(__new_start, __len+1);
              __throw_exception_again;
            }
          if _GLIBCXX17_CONSTEXPR (!_S_use_relocate())
            std::_Destroy(__old_start, __old_finish+1, _M_get_Tp_allocator());
          _GLIBCXX_ASAN_ANNOTATE_REINIT;
          _M_deallocate(__old_start, __size+1);
          this->_M_impl._M_start = __new_start;
        }

      // Either move-construct at the end, or forward to _M_insert_aux.
      iterator
      _M_insert_rval(const_iterator __position, value_type&& __v)
      {
        const auto __n = __position - cbegin();
        _M_realloc_insert(begin() + __n, std::move(__v));
        return iterator(this->_M_impl._M_start + __n);
      }

      // Try to emplace at the end, otherwise forward to _M_insert_aux.
      template<typename... _Args>
        iterator
        _M_emplace_aux(const_iterator __position, _Args&&... __args)
        {
          const auto __n = __position - cbegin();
          _M_realloc_insert(begin() + __n, std::forward<_Args>(__args)...);
          return iterator(this->_M_impl._M_start + __n);
        }

      // Emplacing an rvalue of the correct type can use _M_insert_rval.
      iterator
      _M_emplace_aux(const_iterator __position, value_type&& __v)
      { return _M_insert_rval(__position, std::move(__v)); }

      // Called by _M_fill_insert, _M_insert_aux etc.
      size_type
      _M_check_len(size_type __n, const char* __s) const
      {
        if (max_size() - size() < __n)
          std::__throw_length_error(__N(__s));

        const size_type __len = size() + (std::max)(size(), __n);
        return (__len < size() || __len > max_size()) ? max_size() : __len;
      }

      // Called by constructors to check initial size.
      static size_type
      _S_check_init_len(size_type __n, const allocator_type& __a)
      {
        if (__n > _S_max_size(_Tp_alloc_type(__a)))
          std::__throw_length_error(
              __N("cannot create std::null_terminated_vector larger than max_size()"));
        return __n;
      }

      static size_type
      _S_max_size(const _Tp_alloc_type& __a) _GLIBCXX_NOEXCEPT
      {
        // std::distance(begin(), end()) cannot be greater than PTRDIFF_MAX,
        // and realistically we can't store more than PTRDIFF_MAX/sizeof(T)
        // (even if std::allocator_traits::max_size says we can).
        const size_t __diffmax
          = __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(_Tp);
        const size_t __allocmax = _Alloc_traits::max_size(__a);
        return (std::min)(__diffmax, __allocmax);
      }

      // Internal erase functions follow.

      // Called by erase(q1,q2), clear(), resize(), _M_fill_assign,
      // _M_assign_aux.
      void
      _M_erase_at_end(pointer __pos) _GLIBCXX_NOEXCEPT
      {
        size_type __n = iterator(__pos).back_size();
        if (__n)
          {
            std::swap(__pos[0], __pos[__n]);
            std::_Destroy(__pos + 1, __pos + (__n+1),
                          _M_get_Tp_allocator());
            _GLIBCXX_ASAN_ANNOTATE_SHRINK(__n);
          }
      }

      iterator
      _M_erase(iterator __position)
      {
        const auto __n = __position.back_size();
        _GLIBCXX_MOVE3(__position + 1, __position + (__n+1), __position);
        auto __finish = __position.base() + __n;
        _Alloc_traits::destroy(this->_M_impl, __finish);
        _GLIBCXX_ASAN_ANNOTATE_SHRINK(1);
        return __position;
      }

      iterator
      _M_erase(iterator __first, iterator __last)
      {
        if (__first != __last)
          {
            const auto __n = __last.back_size();
            if (__n) // __last != end()
              _GLIBCXX_MOVE3(__last, __last + (__n+1), __first);
            _M_erase_at_end(__first.base() + __n);
          }
        return __first;
      }

    private:
      // Constant-time move assignment when source object's memory can be
      // moved, either because the source's allocator will move too
      // or because the allocators are equal.
      void
      _M_move_assign(null_terminated_vector&& __x, std::true_type) noexcept
      {
        null_terminated_vector __tmp(get_allocator());
        this->_M_impl._M_swap_data(__x._M_impl);
        __tmp._M_impl._M_swap_data(__x._M_impl);
        std::__alloc_on_move(_M_get_Tp_allocator(), __x._M_get_Tp_allocator());
      }

      // Do move assignment when it might not be possible to move source
      // object's memory, resulting in a linear-time operation.
      void
      _M_move_assign(null_terminated_vector&& __x, std::false_type)
      {
        if (__x._M_get_Tp_allocator() == this->_M_get_Tp_allocator())
          _M_move_assign(std::move(__x), std::true_type());
        else
          {
            // The rvalue's allocator cannot be moved and is not equal,
            // so we need to individually move each element.
            this->assign(std::__make_move_if_noexcept_iterator(__x.begin()),
                         std::__make_move_if_noexcept_iterator(__x.end()));
            __x.clear();
          }
      }

      template<typename _Up>
        _Up*
        _M_data_ptr(_Up* __ptr) const _GLIBCXX_NOEXCEPT
        { return __ptr; }

      template<typename _Ptr>
        typename std::pointer_traits<_Ptr>::element_type*
        _M_data_ptr(_Ptr __ptr) const
        { return empty() ? nullptr : std::__to_address(__ptr); }
    };

#if __cpp_deduction_guides >= 201606
  template<typename _InputIterator, typename _ValT
             = typename iterator_traits<_InputIterator>::value_type,
           typename _Allocator = allocator<_ValT>,
           typename = _RequireInputIter<_InputIterator>,
           typename = _RequireAllocator<_Allocator>>
    null_terminated_vector(_InputIterator, _InputIterator, _Allocator = _Allocator())
      -> null_terminated_vector<_ValT, _Allocator>;
#endif

  /**
   *  @brief  Vector equality comparison.
   *  @param  __x  A %null_terminated_vector.
   *  @param  __y  A %null_terminated_vector of the same type as @a __x.
   *  @return  True iff the size and elements of the vectors are equal.
   *
   *  This is an equivalence relation.  It is linear in the size of the
   *  vectors.  Vectors are considered equivalent if their sizes are equal,
   *  and if corresponding elements compare equal.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const null_terminated_vector<_Tp, _Alloc>& __x,
               const null_terminated_vector<_Tp, _Alloc>& __y)
    { return (__x.size() == __y.size()
              && std::equal(__x.begin(), __x.end(), __y.begin())); }

  /**
   *  @brief  Vector ordering relation.
   *  @param  __x  A %null_terminated_vector.
   *  @param  __y  A %null_terminated_vector of the same type as @a __x.
   *  @return  True iff @a __x is lexicographically less than @a __y.
   *
   *  This is a total ordering relation.  It is linear in the size of the
   *  vectors.  The elements must be comparable with @c <.
   *
   *  See std::lexicographical_compare() for how the determination is made.
  */
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const null_terminated_vector<_Tp, _Alloc>& __x, const null_terminated_vector<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
                                          __y.begin(), __y.end()); }

  /// Based on operator==
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const null_terminated_vector<_Tp, _Alloc>& __x, const null_terminated_vector<_Tp, _Alloc>& __y)
    { return !(__x == __y); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const null_terminated_vector<_Tp, _Alloc>& __x, const null_terminated_vector<_Tp, _Alloc>& __y)
    { return __y < __x; }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const null_terminated_vector<_Tp, _Alloc>& __x, const null_terminated_vector<_Tp, _Alloc>& __y)
    { return !(__y < __x); }

  /// Based on operator<
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const null_terminated_vector<_Tp, _Alloc>& __x, const null_terminated_vector<_Tp, _Alloc>& __y)
    { return !(__x < __y); }

  /// See std::null_terminated_vector::swap().
  template<typename _Tp, typename _Alloc>
    inline void
    swap(null_terminated_vector<_Tp, _Alloc>& __x, null_terminated_vector<_Tp, _Alloc>& __y)
    _GLIBCXX_NOEXCEPT_IF(noexcept(__x.swap(__y)))
    { __x.swap(__y); }

#if __cplusplus >= 201703L
  namespace __detail::__variant
  {
    template<typename> struct _Never_valueless_alt; // see <variant>

    // Provide the strong exception-safety guarantee when emplacing a
    // null_terminated_vector into a variant, but only if move assignment
    // cannot throw.
    template<typename _Tp, typename _Alloc>
      struct _Never_valueless_alt<_GLIBCXX_STD_C::null_terminated_vector<_Tp, _Alloc>>
      : std::is_nothrow_move_assignable<_GLIBCXX_STD_C::null_terminated_vector<_Tp, _Alloc>>
      { };
  }  // namespace __detail::__variant
#endif // C++17

} // namespace i1

#endif /* __NULL_TERMINATED_VECTOR_HPP__ */
