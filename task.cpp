//
// Created by Patryk Knapik on 07.03.2018.
//

#include "task.h"

std::ostream &operator<<(std::ostream &stream, const task &Task) {
    stream << "Task ID: " << Task.getID() << "\n";
    stream << "Times: " << Task.getM1() << "M1, " << Task.getM2() << "M2, " << Task.getM3() << "M3";
    return stream;
}

void task::setM2(unsigned newM2) {
    M2time = newM2;
    sumTime = calculateSumTime();
    virtM1time = M1time + M2time;
    virtM2time = M2time + M3time;
}

void task::setM3(unsigned newM3) {
    M3time = newM3;
    sumTime = calculateSumTime();
    virtM2time = M2time + M3time;
}

void task::setM1(unsigned newM1) {
    M1time = newM1;
    sumTime = calculateSumTime();
    virtM1time = M1time + M2time;
}

task::task(unsigned newID, unsigned newM1time, unsigned newM2time, unsigned newM3time) : ID(newID), M1time(newM1time),
                                                                                         M2time(newM2time),
                                                                                         M3time(newM3time) {
    virtM1time = newM1time + newM2time;
    virtM2time = newM2time + newM3time;
    if (M1time <= M2time) {
        minTime = M1time;
    } else {
        minTime = M2time;
    }

    if (virtM1time <= virtM2time) {
        minVirtTime = virtM1time;
    } else {
        minVirtTime = virtM2time;
    }
}
