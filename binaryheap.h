#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <assert.h>

namespace can { namespace common {

// You can write your own compare function
template<typename T>
struct Compare
{
  bool operator() (const T& lhs, const T& rhs)
  {
    return (lhs > rhs);    // max heap
    //return (lhs < rhs);  //min heap
  }
}; // Compare

template<typename T, typename compare>
class BinaryHeap
{
public:

  BinaryHeap(size_t capacity);

  BinaryHeap(
    T*     src,
    size_t size,
    size_t capacity);

  ~BinaryHeap()
  {
    if(share_ == false)
    {
      delete [] array_;
      array_ = NULL;
    }
  }

  void Build()
  {
    int idx = size_ >> 1;
    for(; idx >= 0; --idx)
    {
      this->Heapify(idx);
    }
  }

  size_t size() const
  {
    return size_;
  }

  T& at(size_t index)
  {
    assert(index < size_);
    return array_[index];
  }

  T& Extreme()
  {
    return *array_;
  }

  bool Insert(const T& val);

  void Remove(size_t index);

  // 1, for max-heap, same to Increase key
  // 2, for min-heap, same to Decrease key
  void ReplaceToExtreme(size_t index, const T& val);

  void ReplaceFarFromExtreme(size_t index, const T& val);

private:

  size_t Parent(size_t index)
  {
    if (index != 0)
    {
      --index;
      index = index >> 1;
    }
    return index;
  }

  size_t Left(size_t index)
  {
    index = (index << 1) + 1;
    return index;
  }

  size_t Right(size_t index)
  {
    index = (index << 1) + 2;
    return index;
  }

  int Heapify(size_t index);

private:

  bool   share_;      // share array space with outside ?
  size_t size_;       // current used size of the heap
  size_t capacity_;   // max size of the heap
  T*     array_;

  compare cmp_;

};  // BinaryHeap

template<typename T, typename compare>
BinaryHeap<T, compare>::BinaryHeap(size_t capacity)
  : share_(false)
  , size_(0)
  , capacity_(capacity)
  , array_(NULL)
{
  assert(capacity > 0);
  array_ = new T[capacity_];
}

template<typename T, typename compare>
BinaryHeap<T, compare>::BinaryHeap(
  T*     src,
  size_t size,
  size_t capacity)
  : share_(true)
  , size_(size)
  , capacity_(capacity)
  , array_(src)
{
  assert(src && capacity > 0 && size >= capacity);
}

template<typename T, typename compare>
void BinaryHeap<T, compare>::
     ReplaceFarFromExtreme(size_t index, const T& val)
{
  if (index >= size_)
    return;
  array_[index] = val;
  this->Heapify(index);
}

template<typename T, typename compare>
int BinaryHeap<T, compare>::Heapify(size_t index)
{
  int    changed = 0;
  size_t idx     = index;
  do
  {
    index = idx;
    size_t left   = this->Left(idx);
    size_t right  = this->Right(idx);
    if (left < size_ && cmp_(array_[left], array_[idx]))
    {
      idx = left;
    }
    if (right < size_ && cmp_(array_[right], array_[idx]))
    {
      idx = right;
    }
    if (index == idx)
    {
      break; // property maked
    }
    // swap values
    T tmp = array_[index];
    array_[index] = array_[idx];
    array_[idx] = tmp;
    ++changed;
  } while (true);
  return changed;
}

template<typename T, typename compare>
bool BinaryHeap<T, compare>::Insert(const T& val)
{
  if(capacity_ <= size_)
    return false;

  size_t cursor = size_;
  array_[cursor] = val;
  ++size_;
  int changed = 0;
  do
  {
    cursor = this->Parent(cursor);
    changed = this->Heapify(cursor);
  } while(cursor > 0 && changed > 0);
  return true;
}

template<typename T, typename compare>
void BinaryHeap<T, compare>::Remove(size_t index)
{
  if(index >= size_)
    return ;
  --size_;
  if (size_ > 0)
  {
    // swap with the last one
    array_[index] = array_[size_];
    this->Heapify(index);
  }
}

// 1, for max-heap, same to Increase key
// 2, for min-heap, same to Decrease key
template<typename T, typename compare>
void BinaryHeap<T, compare>::
     ReplaceToExtreme(size_t index, const T& val)
{
  if(index >= size_)
    return;
  array_[index] = val;
  size_t parent = 0;
  size_t child  = index;
  do
  {
    parent = this->Parent(child);
    if (cmp_(array_[child], array_[parent]))
    {
      T tmp = array_[child];
      array_[child]  = array_[parent];
      array_[parent] = tmp;
      child = parent;
    }
    else
    {
      break;
    }
  } while(parent > 0);
}

}} // ::can::common

#endif // BINARY_HEAP_H_

