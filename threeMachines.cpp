//
// Created by Patryk Knapik on 15.03.2018.
//

#include "threeMachines.h"

void threeMachines::calculateMakeSpan(const std::vector<task *> &tasks) {
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        if (iter == tasks.begin()) {
            M2time = M1time = M3time = (*iter)->getM1();
            M2time += (*iter)->getM2();
            M3time += (*iter)->getM2() + (*iter)->getM3();
        } else {
            M1time += (*iter)->getM1();
            M2time = std::max(M2time, M1time) + (*iter)->getM2();
            M3time = std::max(M2time, M3time) + (*iter)->getM3();
        }

    }

    Cmax = std::max(M1time, M2time);
    Cmax = std::max(M3time, Cmax);

    if (Cmax < Cmin) {
        Cmin = Cmax;
        queuedTasks = tasks;
    }
}

void threeMachines::calculateMakeSpan(const std::list<task *> &tasks) {
    std::vector<task *> tmpTasks;
    for (task *Task : tasks) {
        tmpTasks.push_back(Task);
    }
    calculateMakeSpan(tmpTasks);
}