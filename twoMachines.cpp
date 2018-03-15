//
// Created by Patryk Knapik on 15.03.2018.
//

#include "twoMachines.h"

void twoMachines::calculateMakeSpan(const std::vector<task *> &tasks) {
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        std::cout << (*iter)->getID() << ' ';
        if (iter == tasks.begin()) {
            M2time = M1time = (*iter)->getM1();
            M2time += (*iter)->getM2();

        } else {
            M1time += (*iter)->getM1();
            M2time = std::max(M2time, M1time) + (*iter)->getM2();
        }
    }
    Cmax = std::max(M1time, M2time);

    if (Cmax < Cmin) {
        Cmin = Cmax;
        queuedTasks = tasks;
    }
}

void twoMachines::calculateMakeSpan(const std::list<task *> &tasks) {
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        std::cout << (*iter)->getID() << ' ';
        if (iter == tasks.begin()) {
            M2time = M1time = (*iter)->getM1();
            M2time += (*iter)->getM2();

        } else {
            M1time += (*iter)->getM1();
            M2time = std::max(M2time, M1time) + (*iter)->getM2();
        }
    }
    Cmax = std::max(M1time, M2time);

    if (Cmax < Cmin) {
        Cmin = Cmax;
        queuedTasks.clear();
        for (task *Task : tasks) {
            queuedTasks.push_back(Task);
        }
    }
}