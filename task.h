//
// Created by Patryk Knapik on 07.03.2018.
//

#ifndef MULTI_MACHINE_FLOWSHOP_TASK_H
#define MULTI_MACHINE_FLOWSHOP_TASK_H

#include <iostream>
#include <vector>

class task {
private:
    unsigned int ID, M1time, M2time, M3time, virtM1time, virtM2time, minTime, minVirtTime, sumTime;

    unsigned int calculateSumTime() {
        return (M1time + M2time + M3time);
    }

public:
    task(unsigned newID, unsigned newM1time, unsigned newM2time, unsigned newM3time);

    unsigned getID() const {
        return ID;
    }

    void setID(unsigned newID) {
        ID = newID;
    }

    unsigned getM1() const {
        return M1time;
    }

    void setM1(unsigned newM1);

    unsigned getM2() const {
        return M2time;
    }

    void setM2(unsigned newM2);

    unsigned getM3() const {
        return M3time;
    }

    void setM3(unsigned newM3);

    unsigned getVirtM2() const {
        return virtM2time;
    }

    unsigned getVirtM1() const {
        return virtM1time;
    }

    unsigned getMinTime() const {
        return minTime;
    }

    unsigned getMinVirtTime() const {
        return minVirtTime;
    }

    unsigned getSumTime() const {
        return sumTime;
    }

    bool operator<(const task &task1) const {
        return ID < task1.getID();
    }

};

std::ostream &operator<<(std::ostream &stream, const task &Task);

inline bool taskCompM1(const task *task1, const task *task2) {
    return ((task1->getM1()) < (task2->getM1()));
}

inline bool taskCompM2(const task *task1, const task *task2) {
    return ((task1->getM2()) < (task2->getM2()));
}

inline bool taskEqual(const task *task1, const task *task2) {
    if (((task1->getID()) == (task2->getID())))
        return true;
    return false;
}

inline bool taskCompMinTime(const task *task1, const task *task2) {
    return ((task1->getMinTime()) < (task2->getMinTime()));
}

inline bool taskCompVirtMinTime(const task *task1, const task *task2) {
    return ((task1->getMinVirtTime()) < (task2->getMinVirtTime()));
}

inline bool taskCompMinTimeNeg(const task *task1, const task *task2) {
    return ((task1->getMinTime()) > (task2->getMinTime()));
}

inline bool taskCompVirtMinTimeNeg(const task *task1, const task *task2) {
    return ((task1->getMinVirtTime()) > (task2->getMinVirtTime()));
}

inline bool taskCompSumTime(const task *task1, const task *task2) {
    return ((task1->getSumTime()) < (task2->getSumTime()));
}

inline bool taskCompSumTimeNeg(const task *task1, const task *task2) {
    return ((task1->getSumTime()) > (task2->getSumTime()));
}

#endif //MULTI_MACHINE_FLOWSHOP_TASK_H
