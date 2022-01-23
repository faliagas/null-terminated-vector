# Null-Terminated Vector Class

Although `std::vector` is a good, all-purpose vector class, its use can be very disadvantageous under certain circumstances. The pitfalls of carelessly using it can have a devastating effect on performance and memory use.

- The most noticeable downside of `std::vector` is the space it takes up. Three times that of a pointer is not a negligible amount of memory, especially for programs containing a large number of small vectors.
- The way `std::vector`s expand as one pushes more items to them is another catch. If, for example, we have a 16 element vector, and we need to add just one more element, we will end up having wasted the space of an additional 15-element space. Sure, we can fix it by shrinking the vector, but this does not come without performance and coding costs.
- The use of immutable or almost immutable vectors is not unusual. The `std::array` class is a potential candidate for the former case, but the number of elements is not always a known value at compile time. When a program uses a lot of immutable or almost immutable vectors, `std::vector` is not the right choice.

We'd like to have a vector class that takes up as much space as a pointer without sacrificing performance, at least not in some of the cases described above.

## Requirements

- Programming interface similar to `std::vector`'s
- No performance degradation
- Memory consumption that of a pointer's

## Details

Elements of `null_terminated_vector` instances support the following two methods:

```c++
  static T null_terminator();
  bool is_null() const noexcept;
```

The first returns the element to be considered the *null terminator*, and the second returns true if *this* is a null terminator. Null terminators should not be inserted into the null terminated vector.

Helper classes eliminating the need for explicit definition of `null_terminated_vector` classes for simple types and pointers, are provided.

## Performance considerations

Push or pop operations on `null_terminated_vector`s are more time-consuming than on `std::vectors` as each involves a memory relocation. With almost immutable or with small vectors, this does not incur any sensible performance penalties. In all other cases, we can fix this issue in one of two ways.

1. Collect push or pop operations in a `std::vector,` then insert it into the original Null Terminated Vector.

2. Convert the original `null_terminated_vector` into a `std::vector,` do the push/pop operations, and finally convert it back into a `null_terminated_vector.`

Here is an example of the second method.

```c++
  null_terminated_vector<T> a{1, 2, 3, 4};
  vector<T> b;
  a.convert_to(b);
  b.push(5);
  b.push(6);
  a = b;
```
