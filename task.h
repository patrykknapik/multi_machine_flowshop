//
// Created by Patryk Knapik on 07.03.2018.
//

#ifndef MULTI_MACHINE_FLOWSHOP_TASK_H
#define MULTI_MACHINE_FLOWSHOP_TASK_H

#include <iostream>
#include <vector>

class task {
private:
    unsigned int ID, M1time, M2time, M3time, virtM1time, virtM2time, minTime, minVirtTime;

public:
    task(unsigned newID, unsigned newM1time, unsigned newM2time, unsigned newM3time) : ID(newID), M1time(newM1time),
                                                                                       M2time(newM2time),
                                                                                       M3time(newM3time) {
        virtM1time = newM1time + newM2time;
        virtM2time = newM2time + newM3time;
        if (M1time < M2time) {
            minTime = M1time;
        } else {
            minTime = M2time;
        }

        if (virtM1time < virtM2time) {
            minVirtTime = virtM1time;
        } else {
            minVirtTime = virtM2time;
        }
    }

    unsigned getID() const {
        return ID;
    }

    void setID(unsigned newID) {
        ID = newID;
    }

    unsigned getM1() const {
        return M1time;
    }

    void setM1(unsigned newM1) {
        M1time = newM1;
        virtM1time = M1time + M2time;
    }

    unsigned getM2() const {
        return M2time;
    }

    void setM2(unsigned newM2) {
        M2time = newM2;
        virtM1time = M1time + M2time;
        virtM2time = M2time + M3time;
    }

    unsigned getM3() const {
        return M3time;
    }

    void setM3(unsigned newM3) {
        M3time = newM3;
        virtM2time = M2time + M3time;
    }

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

#endif //MULTI_MACHINE_FLOWSHOP_TASK_H
