//
// Created by Dedefer on 08.09.2017.
//

#ifndef SEQUENCE_SEQUENCE_H
#define SEQUENCE_SEQUENCE_H

#include <cstddef>

using std::size_t;

template <class T>
class Sequence {
public:
    virtual size_t getLength() const noexcept = 0;

    virtual bool isEmpty() const noexcept  = 0;


    virtual T get(size_t) const = 0;

    virtual T operator[](size_t) const = 0;

    virtual T getFirst() const = 0;

    virtual T getLast() const = 0;


    virtual void append(const T&) = 0;

    virtual void prepend(const T&) = 0;

    virtual void insertAt(size_t, const T&) = 0;

    virtual void remove(const T&) noexcept = 0;

    virtual void clear() noexcept = 0;

    virtual ~Sequence() = default;
};


#endif //SEQUENCE_SEQUENCE_H
