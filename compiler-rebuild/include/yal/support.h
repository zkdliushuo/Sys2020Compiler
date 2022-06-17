#ifndef YAL_IR_SUPPORT_H
#define YAL_IR_SUPPORT_H

#include <iterator>
#include <vector>

namespace YAL {

template <typename T> using ArrayRef = std::vector<T>;

template <typename To, typename U> To *cast(const U *that) {
  return dynamic_cast<To *>(const_cast<U *>(that));
}

template <typename To, typename U> To *cast(U *that) {
  return dynamic_cast<To *>(that);
}

template <typename To, typename U> bool isa(const U *that) {
  return cast<To>(that) ? true : false;
}

template <typename To, typename U> bool isa(U *that) {
  return cast<To>(that) ? true : false;
}

template <typename IteratorT> class iterator_range {
  IteratorT begin_iterator, end_iterator;

public:
  template <typename Container>
  iterator_range(Container &&c)
      : begin_iterator(c.begin()), end_iterator(c.end()) {}
  iterator_range(IteratorT begin_iterator, IteratorT end_iterator)
      : begin_iterator(std::move(begin_iterator)),
        end_iterator(std::move(end_iterator)) {}

  IteratorT begin() const { return begin_iterator; }
  IteratorT end() const { return end_iterator; }
};

template <class T> iterator_range<T> make_range(T x, T y) {
  return iterator_range<T>(std::move(x), std::move(y));
}
} // namespace YAL
#endif