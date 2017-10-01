//
// Created by Dedefer on 09.09.2017.
//

#ifndef SEQUENCE_UNITTESTFORSEQUENCE_H
#define SEQUENCE_UNITTESTFORSEQUENCE_H

#include "Sequence.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

template <class SequenceType>
class UnitTestForSequence {
public:

    void fullTest() {

        log.clear();

        std::unique_ptr<Sequence<int>> sample = std::make_unique<SequenceType>();

        check(true, "_________INITIALIZING________");

        check(sample -> getLength() == 0, "Length is equal 0 after init");

        check(sample -> isEmpty() == true, "isEmpty() is equal true after init");

        sample -> append(23);

        check(true, "_________APPENDING 23________");

        check(sample -> isEmpty() == false, "isEmpty() is equal false after append 23");

        check(sample -> getLength() == 1, "Length is equal 1 after append 23");

        check(sample -> getFirst() == 23, "First element is equal 23");

        check(sample -> getLast() == 23, "Last element is equal 23");

        check(sample -> get(0) == 23, "get(0) is equal 23");

        try {sample -> get(-1);} catch (std::exception&) {
            check(true, "get(-1) throws exception");
        }

        try {sample -> get(1);} catch (std::exception&) {
            check(true, "get(1) throws exception");
        }

        sample -> append(43);

        check(true, "_________APPENDING 43________");

        check(sample -> getLength() == 2, "Length is equal 2 after append 43");

        check(sample -> getFirst() == 23, "First element is equal 23");

        check(sample -> getLast() == 43, "Last element is equal 43");

        check(sample -> get(0) == 23, "get(0) is equal 23");

        check(sample -> get(1) == 43, "get(1) is equal 43");

        try {sample -> get(-1);} catch (std::exception&) {
            check(true, "get(-1) throws exception");
        }

        try {sample -> get(2);} catch (std::exception&) {
            check(true, "get(2) throws exception");
        }

        sample -> prepend(53);

        check(true, "_________PREPENDING 53________");

        check(sample -> getLength() == 3, "Length is equal 3 after prepend 53");

        check(sample -> getFirst() == 53, "First element is equal 53");

        check(sample -> getLast() == 43, "Last element is equal 43");

        check(sample -> get(0) == 53, "get(0) is equal 53");

        check(sample -> get(1) == 23, "get(1) is equal 23");

        check(sample -> get(2) == 43, "get(2) is equal 43");

        try {sample -> get(-1);} catch (std::exception&) {
            check(true, "get(-1) throws exception");
        }

        try {sample -> get(3);} catch (std::exception&) {
            check(true, "get(3) throws exception");
        }

        std::unique_ptr<Sequence<int>> sampleCpy{sample -> copy()};

        check(true, "_________CREATING COPY SEQUENCE________");

        check(sampleCpy -> getLength() == 3, "Length of sample copy is equal 3");

        check(sampleCpy -> getFirst() == 53, "First element of sample copy is equal 53");

        check(sampleCpy -> getLast() == 43, "Last element of sample copy is equal 43");

        check(sampleCpy -> get(0) == 53, "get(0) of sample copy is equal 53");

        check(sampleCpy -> get(1) == 23, "get(1) of sample copy is equal 23");

        check(sampleCpy -> get(2) == 43, "get(2) of sample is equal 43");

        check(sample -> getLength() == 3, "Length of sample is equal 3");

        check(sample -> getFirst() == 53, "First element of sample is equal 53");

        check(sample -> getLast() == 43, "Last element of sample is equal 43");

        check(sample -> get(0) == 53, "get(0) of sample is equal 53");

        check(sample -> get(1) == 23, "get(1) of sample is equal 23");

        check(sample -> get(2) == 43, "get(2) of sample is equal 43");


        std::unique_ptr<Sequence<int>> sampleMoveDest = std::make_unique<SequenceType>(std::move(*dynamic_cast<SequenceType*>(sampleCpy.get())));

        check(true, "_________MOVING COPY TO DEST SEQUENCE________");

        check(sampleCpy -> getLength() == 0, "Length of copy is equal 0");

        check(sampleMoveDest -> getLength() == 3, "Length of dest is equal 3");


        std::unique_ptr<Sequence<int>> subSeqOfSample{sample -> getSubsequence(1,1)};

        check(true, "_________CREATING SUBSEQUENCE________");

        check(subSeqOfSample -> getFirst() == 23, "First element of Subsequence(1,1) is equal 23");

        check(subSeqOfSample -> getLast() == 23, "Last element of Subsequence(1,1) is equal 23");

        try {sample -> getSubsequence(2,1);} catch (std::exception&) {
            check(true, "Subsequence(2,1) throws exception");
        }

        sample -> clear();

        check(true, "_________CLEARING SEQUENCE________");

        check(sample -> getLength() == 0, "Length is equal 0 after clear");

        sample.reset(new SequenceType({}));

        check(true, "_________CREATING SEQUENCE FROM EMPTY INIT LIST________");

        check(sample -> getLength() == 0, "Length is equal 0 after init");

        sample.reset(new SequenceType{1,2,3});

        check(true, "_________CREATING SEQUENCE FROM INIT LIST {1,2,3}________");

        check(sample -> getLength() == 3, "Length is equal 3 after init");

        check(sample -> getFirst() == 1, "First element is equal 1");

        check(sample -> getLast() == 3, "Last element is equal 3");

        check(sample -> get(0) == 1, "get(0) is equal 1");

        check(sample -> get(1) == 2, "get(1) is equal 2");

        check(sample -> get(2) == 3, "get(2) is equal 3");

        try {sample -> get(-1);} catch (std::exception&) {
            check(true, "get(-1) throws exception");
        }

        try {sample -> get(3);} catch (std::exception&) {
            check(true, "get(3) throws exception");
        }

        sample -> insertAt(1, 4);

        check(true, "_________INSERTING 4 TO INDEX 1________");

        check(sample -> getLength() == 4, "Length is equal 4 after insert");

        check(sample -> get(0) == 1, "get(0) is equal 1 after insert");

        check(sample -> get(1) == 4, "get(1) is equal 4 after insert");

        check(sample -> get(2) == 2, "get(2) is equal 2 after insert");

        check(sample -> get(3) == 3, "get(3) is equal 3 after insert");

        try {sample -> insertAt(5, 10);} catch (std::exception&) {
            check(true, "insertAt(5, 10) throws exception");
        }

        try {sample -> insertAt(-1, 10);} catch (std::exception&) {
            check(true, "insertAt(-1, 10) throws exception");
        }

        sample -> remove(4);

        check(true, "_________REMOVING 4________");

        check(sample -> getLength() == 3, "Length is equal 3 after remove");

        check(sample -> getFirst() == 1, "First element is equal 1 after remove");

        check(sample -> getLast() == 3, "Last element is equal 3 after remove");

        check(sample -> get(0) == 1, "get(0) is equal 1 after remove");

        check(sample -> get(1) == 2, "get(1) is equal 2 after remove");

        check(sample -> get(2) == 3, "get(2) is equal 3 after remove");

        sample -> remove(1);

        check(true, "_________REMOVING 1________");

        check(sample -> getLength() == 2, "Length is equal 2 after remove");

        check(sample -> getFirst() == 2, "First element is equal 2 after remove");

        check(sample -> getLast() == 3, "Last element is equal 3 after remove");

        check(sample -> get(0) == 2, "get(0) is equal 2 after remove");

        check(sample -> get(1) == 3, "get(1) is equal 3 after remove");

        sample -> remove(4);

        check(true, "_________REMOVING 4(DOES NOT EXIST)________");

        check(sample -> getLength() == 2, "Length is equal 2 after remove");

        check(sample -> get(0) == 2, "get(0) is equal 2 after remove");

        check(sample -> get(1) == 3, "get(1) is equal 3 after remove");


    }

    void printLog(std::ostream& stream) noexcept {

        stream << "---------------------------------------------\n";
        std::time_t currentTime = std::time(nullptr);
        stream << typeid(SequenceType).name() << std::endl;
        stream << std::asctime(std::localtime(&currentTime)) << std::endl << std::endl;
        for (const auto& logString : log) {
            stream << logString << std::endl << std::endl;
        }
        stream << typeid(SequenceType).name() << " passed " << passed << "/" << checked
               << "\n---------------------------------------------\n";

    }


private:

    std::vector<std::string> log;

    int checked{0}, passed{0};

    void check(bool result, std::string procedure) {
        ++checked;
        if (result) {++passed;}
        procedure += (result ? " : OK" : " : FAILURE");
        std::cerr << procedure << std::endl << std::endl;
        log.push_back(std::move(procedure));

    }
};


#endif //SEQUENCE_UNITTESTFORSEQUENCE_H
