//
// Created by Patryk Knapik on 15.03.2018.
//


#include "threeMachines.h"

unsigned threeMachines::calculateMakeSpan(const std::vector<task *> &tasks) {
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
    return Cmax;
}

unsigned threeMachines::calculateMakeSpan(const std::list<task *> &tasks) {
    std::vector<task *> tmpTasks;
    for (task *Task : tasks) {
        tmpTasks.push_back(Task);
    }
    return calculateMakeSpan(tmpTasks);
}

void threeMachines::generatePlot(std::string &fileName) {
    std::ofstream file;
    unsigned prevM1timeTmp, prevM2timeTmp, prevM3timeTmp, M1timeTmp, M2timeTmp, M3timeTmp;
    std::vector<std::string> colors;
    colors.push_back("0xFF0000");
    colors.push_back("0xFFE400");
    colors.push_back("0x71FF00");
    colors.push_back("0x00FFE1");
    colors.push_back("0x0096FF");
    colors.push_back("0x000FFF");
    colors.push_back("0xBB00FF");
    colors.push_back("0xFF00BC");
    colors.push_back("0xFFAC00");
    colors.push_back("0x000000");

    auto iter = colors.begin();

    file.open("tmp.gpl");
    file << "set terminal svg size 1000,750\n";
    file << "set output '"<< fileName << "'\n";
    file << "$DATA << EOD\n";

    prevM1timeTmp = 0;
    prevM2timeTmp = queuedTasks.at(0)->getM1();
    prevM3timeTmp = queuedTasks.at(0)->getM1() + queuedTasks.at(0)->getM2();

    for (auto Task : queuedTasks) {
        file << prevM1timeTmp << " -1 ";
        M1timeTmp = Task->getM1();
        prevM1timeTmp += M1timeTmp;
        file << M1timeTmp << " 0 " << (*iter) << ' ' << Task->getID() << '\n';

        prevM2timeTmp = std::max(prevM2timeTmp, prevM1timeTmp);
        file << prevM2timeTmp << " -2 ";
        M2timeTmp = Task->getM2();
        prevM2timeTmp += Task->getM2();
        file << M2timeTmp << " 0 " << (*iter) << ' ' << Task->getID() << '\n';

        prevM3timeTmp = std::max(prevM3timeTmp, prevM1timeTmp);
        prevM3timeTmp = std::max(prevM2timeTmp, prevM3timeTmp);
        file << prevM3timeTmp << " -3 ";
        M3timeTmp = Task->getM3();
        prevM3timeTmp += Task->getM3();
        file << M3timeTmp << " 0 " << (*iter) << ' ' << Task->getID() << '\n';

        if (++iter == colors.end())
            iter = colors.begin();
    }
    file << "EOD\n";
    file << "unset key\n";
    file << "set xlabel \"time (total makespan: " << Cmin << ")\"\n";
    file << "set yrange [-4:0]\n";
    file << "set ytics (\"\" 0,\"First Machine\" -1, \"Second Machine\" -2, \"Third Machine\" -3, \"\" -4)\n";
    file << "plot $DATA using 1:2:3:4:5 with vectors lw 3 lc rgb variable, $DATA using 1:2:6 with labels offset 1,1\n";
    file << "reset\n";
    file.close();
    system("gnuplot tmp.gpl");

}

void threeMachines::clear() {
    M1time = 0;
    M2time = 0;
    M3time = 0;
    Cmax = 0;
    Cmin = std::numeric_limits<unsigned int>::max();
    queuedTasks.clear();
}
