#pragma once

#include <assert.h>
#include <memory>
#include <type_traits>

template <typename T, std::size_t LEN = 0, std::size_t CAPACITY = 0>
class CustomVector
{
public:
  using Iterator = T*;

  CustomVector(std::size_t capacity)
      : m_memory(capacity > 0 ? new char[sizeof(T) * capacity] : nullptr)
      , m_capacity{capacity}
      , m_len{0}
  {}

  CustomVector()
      : m_memory(CAPACITY > 0 ? new char[sizeof(T) * CAPACITY] : nullptr)
      , m_capacity{CAPACITY}
      , m_len{0}
  {}

  CustomVector(const CustomVector& customVector)
      : m_capacity{customVector.m_capacity}
      , m_len{customVector.m_len}
  {
    std::copy(customVector.begin(), customVector.end(), m_memory);
  }

  CustomVector(CustomVector&& customVector)
      : m_capacity{customVector.m_capacity}
      , m_len{customVector.m_len}
  {
    // Steal the memory allocated for original vector
    m_memory              = customVector.m_memory;
    customVector.m_memory = nullptr;
  }

  CustomVector& operator=(const CustomVector& customVector)
  {
    m_capacity = customVector.m_capacity;
    m_len      = customVector.m_len;
    std::copy(customVector.begin(), customVector.end(), m_memory);
    return *this;
  }

  CustomVector& operator=(CustomVector&& customVector)
  {
    m_capacity = customVector.m_capacity;
    m_len      = customVector.m_len;
    // Steal the memory allocated for original vector
    m_memory              = customVector.m_memory;
    customVector.m_memory = nullptr;

    return *this;
  }

  const Iterator begin()
  {
    if (m_len == 0)
      return nullptr;

    return reinterpret_cast<T*>(m_memory);
  }

  const Iterator end()
  {
    if (m_len == 0)
      return nullptr;

    return reinterpret_cast<T*>(m_memory + m_len * sizeof(T));
  }

  T& at(size_t index)
  {
    // assert(index > m_len);
    return *reinterpret_cast<T*>(m_memory + index * sizeof(T));
  }

  const T& pushBack(const T& value)
  {
    if (m_capacity == 0)
      assert(false);   //, "CustomVector capacity 0");
    if (m_len + 1 > m_capacity)
      assert(false);   //, "CustomVector capacity exceeding, resizing not supported");

    T& valueStoredAt = *reinterpret_cast<T*>(m_memory + m_len * sizeof(T));
    valueStoredAt    = value;
    ++m_len;

    return valueStoredAt;
  }

  const T& emplaceBack(T&& value)
  {
    if (m_capacity == 0)
      assert(m_capacity == 0);       //, "CustomVector capacity 0");
    if (m_len >= m_capacity)
      assert(m_len >= m_capacity);   //, "CustomVector capacity exceeding, resizing not supported");

    T& valueStoredAt = *reinterpret_cast<T*>(m_memory + m_len * sizeof(T));
    valueStoredAt == std::move(value);
    ++m_len;
    return valueStoredAt;
  }

  ~CustomVector()
  {
    if (m_memory != nullptr)
      free(m_memory);
  }

  char*  m_memory;
  size_t m_len;
  size_t m_capacity;
};