//
// Created by Dedefer on 09.09.2017.
//

#ifndef SEQUENCE_ARRAYSEQUENCE_H
#define SEQUENCE_ARRAYSEQUENCE_H

#include "Sequence.h"
#include <stdexcept>
#include <initializer_list>


template <class T>
class ArraySequence : public Sequence<T> {

public:

    ArraySequence() noexcept : _len{0}, _arrPtr{nullptr} {}

    ArraySequence(std::initializer_list<T> objList)
            : _len{0}, _arrPtr{nullptr} {
        if (objList.size()) {
            _arrPtr = new T[objList.size()];
            _len = objList.size();
            size_t i = 0;
            for (const T& item : objList) {_arrPtr[i++] = item;}
        }
    }

    ArraySequence<T>& operator = (std::initializer_list<T> objList) {
        clear();
        if (objList.size()) {
            _arrPtr = new T[objList.size()];
            _len = objList.size();
            size_t i = 0;
            for (const T& item : objList) {_arrPtr[i++] = item;}
        }
        return *this;
    }

    ArraySequence(const ArraySequence<T>& obj) : _len{0}, _arrPtr{nullptr} {
        if (obj._len) {
            _arrPtr = new T[obj._len];
            _len = obj._len;
            for (auto i = 0; i < _len; ++i) {_arrPtr[i] = obj._arrPtr[i];}
        }
    }

    ArraySequence<T>& operator = (const ArraySequence<T>& rhs) {
        if (this != &rhs) {
            clear();
            if (rhs._len) {
                _arrPtr = new T[rhs._len];
                _len = rhs._len;
                for (auto i = 0; i < _len; ++i) {_arrPtr[i] = rhs._arrPtr[i];}
            }
        }
        return *this;
    }

    ArraySequence(ArraySequence<T>&& obj) noexcept
            : _len{obj._len}, _arrPtr{obj._arrPtr} {
        obj._len = 0;
        obj._arrPtr = nullptr;
    }

    ArraySequence<T>& operator = (ArraySequence<T>&& rhs) noexcept {
        if (this != &rhs) {
            clear();
            _len = rhs._len;
            _arrPtr = rhs._arrPtr;

            rhs._len = 0;
            rhs._arrPtr = nullptr;
        }
        return *this;
    }

    ~ArraySequence() override {clear();}

    size_t getLength() const noexcept override {return _len;}

    bool isEmpty() const noexcept override {return !_len;}

    T get(size_t index) const override {
        if (index >= 0 && index < _len) {return _arrPtr[index];}
        throw std::out_of_range("index is out of range");
    }

    T operator[](size_t index) const override {return get(index);}

    T getFirst() const override {
        if (_len > 0) {return *_arrPtr;}
        throw std::out_of_range("sequence is empty");
    }

    T getLast() const override {
        if (_len > 0) {return _arrPtr[_len - 1];}
        throw std::out_of_range("sequence is empty");
    }

    ArraySequence<T> getSubsequence(size_t startIndex, size_t endIndex) const {
        if (startIndex >= 0 && endIndex < _len && startIndex <= endIndex) {
            ArraySequence<T> tempObj;
            tempObj._len = endIndex - startIndex + 1;
            tempObj._arrPtr = new T[tempObj._len];
            for (auto i = startIndex; i <= endIndex; ++i) {tempObj._arrPtr[i - startIndex] = _arrPtr[i];}
            return std::move(tempObj);
        }
        throw std::out_of_range("indices are out of range");
    }

    void append(const T& obj) override {
        T* tempArr = new T[_len + 1];
        for (auto i = 0; i < _len; ++i) {tempArr[i] = std::move(_arrPtr[i]);}
        tempArr[_len++] = obj;
        auto arrToDelete = _arrPtr;
        _arrPtr = tempArr;
        delete [] arrToDelete;
    }

    void prepend(const T& obj) override {insertAt(0, obj);}

    void insertAt(size_t targetIndex, const T& obj) override {
        if (targetIndex >= 0 && targetIndex <= _len) {
            if (targetIndex == _len) {
                append(obj);
                return;
            }
            T* tempArr = new T[_len + 1];
            for (auto i = 0, difference = 0; i < _len; ++i) {
                if (i == targetIndex) {
                    tempArr[i] = obj;
                    ++difference;
                }
                tempArr[i + difference] = std::move(_arrPtr[i]);
            }
            ++_len;
            auto arrToDelete = _arrPtr;
            _arrPtr = tempArr;
            delete [] arrToDelete;
        } else {throw std::out_of_range("index is out of range");}
    }

    void remove(const T& value) noexcept override {
        if (_len) {
            T* tempArr = new T[_len - 1];
            int difference = 0;
            for (auto i = 0; i < _len; ++i) {
                if (difference || !(_arrPtr[i] == value)) {tempArr[i + difference] = std::move(_arrPtr[i]);}
                else {--difference;}
            }
            _len += difference;
            auto arrToDelete = _arrPtr;
            _arrPtr = tempArr;
            delete [] arrToDelete;
        }
    }

    void clear() noexcept override {
        delete [] _arrPtr;
        _arrPtr = nullptr;
        _len = 0;
    }


private:

    size_t _len;

    T* _arrPtr;

};


#endif //SEQUENCE_ARRAYSEQUENCE_H
