//
// Created by Patryk Knapik on 07.03.2018.
//

#ifndef MULTI_MACHINE_FLOWSHOP_TASK_H
#define MULTI_MACHINE_FLOWSHOP_TASK_H

#include <iostream>

class task {
private:
    unsigned int ID, M1time, M2time, M3time;

public:
    task(unsigned newID, unsigned newM1time, unsigned newM2time, unsigned newM3time) : ID(newID), M1time(newM1time),
                                                                                       M2time(newM2time),
                                                                                       M3time(newM3time) {}

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
    }

    unsigned getM2() const {
        return M2time;
    }

    void setM2(unsigned newM2) {
        M2time = newM2;
    }

    unsigned getM3() const {
        return M3time;
    }

    void setM3(unsigned newM3) {
        M3time = newM3;
    }

    bool operator<(const task &task1) const {
        return ID < task1.getID();
    }

};

std::ostream &operator<<(std::ostream &stream, const task &Task);


#endif //MULTI_MACHINE_FLOWSHOP_TASK_H
