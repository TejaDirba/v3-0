#include "Vector.h"
#include <utility>  // std::move

template<typename T>
Vector<T>::Vector(): _data(nullptr), _size(0), _cap(0) {}

template<typename T>
Vector<T>::Vector(size_type cnt)
  : _data(static_cast<T*>(::operator new(cnt*sizeof(T)))), _size(cnt), _cap(cnt)
{
    for (size_type i = 0; i < cnt; ++i)
        new(&_data[i]) T();
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init)
  : Vector(init.size())
{
    size_type i=0;
    for (auto& v: init) _data[i++] = v;
}

template<typename T>
Vector<T>::Vector(const Vector& o)
  : Vector(o._size)
{
    for (size_type i = 0; i < _size; ++i)
        _data[i] = o._data[i];
}

template<typename T>
Vector<T>::Vector(Vector&& o) noexcept
  : _data(o._data), _size(o._size), _cap(o._cap)
{
    o._data = nullptr; o._size = o._cap = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& o) {
    if (this != &o) {
        clear();
        reserve(o._size);
        for (size_type i = 0; i < o._size; ++i)
            new(&_data[i]) T(o._data[i]);
        _size = o._size;
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& o) noexcept {
    if (this != &o) {
        clear();
        ::operator delete(_data);
        _data = o._data; _size = o._size; _cap = o._cap;
        o._data = nullptr; o._size = o._cap = 0;
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    clear();
    ::operator delete(_data);
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type i) {
    return _data[i];
}
template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type i) const {
    return _data[i];
}
template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type i) {
    if (i >= _size) throw std::out_of_range("Vector::at");
    return _data[i];
}
template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type i) const {
    if (i >= _size) throw std::out_of_range("Vector::at");
    return _data[i];
}

template<typename T>
void Vector<T>::push_back(const T& v) {
    if (_size == _cap) reallocate(_cap ? _cap*2 : 1);
    new(&_data[_size++]) T(v);
}
template<typename T>
void Vector<T>::push_back(T&& v) {
    if (_size == _cap) reallocate(_cap ? _cap*2 : 1);
    new(&_data[_size++]) T(std::move(v));
}
template<typename T>
void Vector<T>::pop_back() {
    if (_size) { --_size; _data[_size].~T(); }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept { return _data; }
template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return _data; }
template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept { return _data + _size; }
template<typename T>
typename Vector<T>::const_iterator Vector<T>::end()   const noexcept { return _data + _size; }

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
    return _data[0];
}
template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return _data[0];
}
template<typename T>
typename Vector<T>::reference Vector<T>::back() {
    return _data[_size-1];
}
template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return _data[_size-1];
}

template<typename T>
bool Vector<T>::empty() const noexcept { return _size == 0; }
template<typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept { return _size; }
template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept { return _cap; }

template<typename T>
void Vector<T>::reserve(size_type n) {
    if (n > _cap) reallocate(n);
}

template<typename T>
void Vector<T>::clear() noexcept {
    for (size_type i = 0; i < _size; ++i)
        _data[i].~T();
    _size = 0;
}

template<typename T>
void Vector<T>::reallocate(size_type newCap) {
    T* newBlock = static_cast<T*>(::operator new(newCap*sizeof(T)));
    for (size_type i = 0; i < _size; ++i)
        new(&newBlock[i]) T(std::move(_data[i]));
    for (size_type i = 0; i < _size; ++i)
        _data[i].~T();
    ::operator delete(_data);
    _data = newBlock;
    _cap = newCap;
}
