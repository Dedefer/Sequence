//
// Created by Dedefer on 08.09.2017.
//

#ifndef SEQUENCE_LISTSEQUENCE_H
#define SEQUENCE_LISTSEQUENCE_H

#include <stdexcept>
#include <initializer_list>
#include "Sequence.h"

template <class T>
class ListSequence : public Sequence<T> {
public:
    ListSequence() noexcept : _len{0}, _leftEnd{nullptr}, _rightEnd{nullptr} {}

    ListSequence(std::initializer_list<T> objList)
            : _len{0}, _leftEnd{nullptr}, _rightEnd{nullptr} {
        for (const T& item : objList) {append(item);}
    }

    ListSequence<T>& operator = (std::initializer_list<T> objList) {
        clear();
        for (const T& item : objList) {append(item);}
        return *this;
    }

    ListSequence(const ListSequence<T>& obj)
            : _len{0}, _leftEnd{nullptr}, _rightEnd{nullptr} {
        for (auto nodePtr = obj._leftEnd; nodePtr; nodePtr = nodePtr -> rightNode) {
            append(nodePtr -> value);
        }
    }

    ListSequence<T>& operator = (const ListSequence<T>& rhs) {
        if (this != &rhs) {
            clear();
            for (auto nodePtr = rhs._leftEnd; nodePtr; nodePtr = nodePtr -> rightNode) {
                append(nodePtr -> value);
            }
        }
        return *this;
    }

    ListSequence(ListSequence<T>&& obj) noexcept
            : _len{obj._len}, _leftEnd{obj._leftEnd}, _rightEnd{obj._rightEnd} {
        obj._len = 0;
        obj._rightEnd = obj._leftEnd = nullptr;
    }

    ListSequence<T>& operator = (ListSequence<T>&& rhs) noexcept {
        if (this != &rhs) {
            clear();
            _len = rhs._len;
            _leftEnd = rhs._leftEnd;
            _rightEnd = rhs._rightEnd;

            rhs._len = 0;
            rhs._leftEnd = rhs._rightEnd = nullptr;
        }
        return *this;
    }

    ~ListSequence() override {clear();}



    size_t getLength() const noexcept override {return _len;}

    bool isEmpty() const noexcept override {return !_len;}

    T get(size_t index) const override {
        if (index >= 0 && index < _len) {
            auto nodePtr = _leftEnd;
            for (auto i = 0; i < index; ++i) {
                nodePtr = nodePtr -> rightNode;
            }
            return nodePtr -> value;
        }
        throw std::out_of_range("index is out of range");
    }

    T operator[](size_t index) const override {return get(index);}

    T getFirst() const override {
        if (_len > 0) {return _leftEnd -> value;}
        throw std::out_of_range("sequence is empty");
    }

    T getLast() const override {
        if (_len > 0) {return _rightEnd -> value;}
        throw std::out_of_range("sequence is empty");
    }

    ListSequence<T> getSubsequence(size_t startIndex, size_t endIndex) const {
        if (startIndex >= 0 && endIndex < _len && startIndex <= endIndex) {
            auto nodePtr = _leftEnd;
            for (auto i = 0; i < startIndex; ++i) {
                nodePtr = nodePtr -> rightNode;
            }
            ListSequence<T> tempObj;
            for (auto i = startIndex; i < (endIndex + 1); ++i) {
                tempObj.append(nodePtr -> value);
                nodePtr = nodePtr -> rightNode;
            }
            return std::move(tempObj);
        }
        throw std::out_of_range("indices are out of range");
    }

    void append(const T& obj) override {
        auto tempNode = new TNode(obj, _rightEnd);
        if (_rightEnd) {
            _rightEnd -> rightNode = tempNode;
        } else {_leftEnd = tempNode;}
        _rightEnd = tempNode;
        ++_len;
    }

    void prepend(const T& obj) override {
        auto tempNode = new TNode(obj, nullptr, _leftEnd);
        if (_leftEnd) {
            _leftEnd -> leftNode = tempNode;
        } else {_rightEnd = tempNode;}
        _leftEnd = tempNode;
        ++_len;
    }

    void insertAt(size_t index, const T& obj) override {
        if (index >= 0 && index <= _len) {
            if (index == 0) {
                prepend(obj);
                return;
            }
            if (index == _len) {
                append(obj);
                return;
            }
            auto nodePtr = _leftEnd;
            for (auto i = 0; i < index; ++i) {nodePtr = nodePtr -> rightNode;}
            TNode* tempNode = new TNode(obj, nodePtr -> leftNode, nodePtr);
            nodePtr -> leftNode = tempNode;
            if (nodePtr == _rightEnd) {_rightEnd = tempNode;}
            tempNode -> leftNode -> rightNode = tempNode;
            ++_len;
            return;
        }
        throw std::out_of_range("index is out of range");
    }

    void remove(const T& value) override {
        for (auto nodePtr = _leftEnd; nodePtr; nodePtr = nodePtr -> rightNode) {
            if (value == nodePtr -> value) {
                if (nodePtr -> leftNode) {
                    nodePtr -> leftNode -> rightNode = nodePtr -> rightNode;
                } else {_leftEnd = nodePtr -> rightNode;}
                if (nodePtr -> rightNode) {
                    nodePtr -> rightNode -> leftNode = nodePtr -> leftNode;
                } else {_rightEnd = nodePtr -> leftNode;}
                delete nodePtr;
                --_len;
                return;
            }
        }
    }

    void clear() noexcept override {
        auto nodePtr = _leftEnd;
        while (nodePtr) {
            auto nodeToDelete = nodePtr;
            nodePtr = nodePtr -> rightNode;
            delete nodeToDelete;
        }
        _rightEnd = _leftEnd = nullptr;
        _len = 0;
    }

private:

    struct TNode {

        TNode *leftNode, *rightNode;

        T value;

        TNode(const T& value, TNode *leftNode = nullptr, TNode *rightNode = nullptr) noexcept
                : value{value}, leftNode{leftNode}, rightNode{rightNode} {}
    };

    TNode *_leftEnd, *_rightEnd;

    size_t _len;

};


#endif //SEQUENCE_LISTSEQUENCE_H
