#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<typename T>
class Vector {
public:
    using value_type      = T;
    using size_type       = size_t;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = T*;
    using const_iterator  = const T*;

    Vector();
    explicit Vector(size_type count);
    Vector(std::initializer_list<T> init);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    ~Vector();

    reference       operator[](size_type i);
    const_reference operator[](size_type i) const;
    reference       at(size_type i);
    const_reference at(size_type i) const;

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();

    iterator       begin()       noexcept;
    const_iterator begin() const noexcept;
    iterator       end()         noexcept;
    const_iterator end()   const noexcept;

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back()  const;

    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type capacity() const noexcept;
    void      reserve(size_type newCap);
    void      clear()    noexcept;

private:
    T*         _data;
    size_type  _size;
    size_type  _cap;

    void reallocate(size_type newCap);
};

#include "Vector.tpp"
#endif
