//
// Created by Patryk Knapik on 15.03.2018.
//

#ifndef MULTI_MACHINE_FLOWSHOP_THREEMACHINES_H
#define MULTI_MACHINE_FLOWSHOP_THREEMACHINES_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "task.h"

class threeMachines {
private:
    unsigned int M1time = 0, M2time = 0, M3time = 0, Cmax = 0, Cmin = std::numeric_limits<unsigned int>::max();
    std::vector<task *> queuedTasks;
public:
    void calculateMakeSpan(const std::vector<task *> &tasks);

    void calculateMakeSpan(const std::list<task *> &tasks);

    unsigned int getMinMakeSpan() {
        return Cmin;
    }

    std::vector<task *> getOptimalTaskSet() {
        return queuedTasks;
    }

    unsigned int getCurrentMakeSpan() {
        return Cmax;
    }

    void generatePlot(std::string &fileName);
};


#endif //MULTI_MACHINE_FLOWSHOP_THREEMACHINES_H
