#include <iostream>
#include <vector>
#include <list>
#include <sys/time.h>
#include "twoMachines.h"
#include "threeMachines.h"

#define TASK_COUNT 12
#define MIN_TIME 1
#define MAX_TIME 20
#define TABOO_TIME 20
#define SHOW_PERMUTATIONS false
#define GENERATE_PLOT false
#define GENERATE_TEST_DATA true

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i;
        --i;
    }
    return f;
}

bool isTimeElapsed(timeval startTime, timeval currentTime, double period) {
    double tmp = currentTime.tv_sec - startTime.tv_sec;
    return tmp > period;

}

std::vector<std::vector<task *> > generateNeigbouhood(std::vector<task *> tasks, unsigned int iter) {
    std::vector<std::vector<task *> > tmpList;
    task *tmptask = tasks.at(iter);
    tasks.erase(tasks.begin() + iter);
    std::vector<task *> backup = tasks;
    for (auto i = 0; i < tasks.size(); ++i) {
        if (i == iter)
            continue;
        tasks.insert(tasks.begin() + i, tmptask);
        tmpList.push_back(tasks);
        tasks = backup;

    }

    return tmpList;
}

unsigned int getMakeSpanThreeMs(const std::vector<task *> &tasks) {
    unsigned int M1time = 0, M2time = 0, M3time = 0, Cmax = 0;
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

    return Cmax;
}


int main() {
    timeval time_stamp_start, time_stamp_stop, time_stamp_taboo;
    double elapsed_time, twoMachinesBruteForceTime, twoMachinesJohnsonTime, threeMachinesBruteForceTime, threeMachinesJohnsonTime, threeMachinesNEHTime, threeMachinesTabuTime;
    std::vector<task *> tasks, tabuBestTasks, tabuBestTasksLocal, tabuBestTasksLocalTmp;
    std::vector<std::vector<task *> > tabuList, tabuNeighbourhood;
    std::list<task *> johnsonsTasksFront, johnsonsTasksBack;
    unsigned long int tasksPermutations = 0;
    std::srand(std::time(nullptr));

    twoMachines twoMs, twoMsJohnson;
    threeMachines threeMs, threeMsJohnson, threeMsNEH;

    for (unsigned i = 1; i <= TASK_COUNT; ++i) {
        tasks.push_back(new task(i, (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME,
                                 (std::rand() % (MAX_TIME - MIN_TIME)) + MIN_TIME));
    }


    std::cout << "Tasks parameters:\n";
    for (task *Task : tasks) {
        std::cout << *Task << "\n";
    }

    //brute force:
    std::cout << "\n\nBrute force algorithm:\n";

    if (SHOW_PERMUTATIONS) {
        tasksPermutations = factorial(tasks.size());
        std::cout << "\nPermutations(" << tasksPermutations << "):\n";

        for (; tasksPermutations != 0; --tasksPermutations) {
            std::next_permutation(tasks.begin(), tasks.end());

            for (task *Task : tasks) {
                std::cout << Task->getID() << ' ';
            }
            twoMs.calculateMakeSpan(tasks);
            threeMs.calculateMakeSpan(tasks);

            std::cout << "; 2M: C = " << twoMs.getCurrentMakeSpan();
            std::cout << "; 3M: C = " << threeMs.getCurrentMakeSpan() << '\n';

        }
    }

    gettimeofday(&time_stamp_start, nullptr);
    tasksPermutations = factorial(tasks.size());
    for (; tasksPermutations != 0; --tasksPermutations) {
        std::next_permutation(tasks.begin(), tasks.end());

        twoMs.calculateMakeSpan(tasks);
    }
    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "\n\nSugested tasks queue for two machines: ";
    for (auto Task : twoMs.getOptimalTaskSet()) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << twoMs.getMinMakeSpan() << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    twoMachinesBruteForceTime = elapsed_time;


    gettimeofday(&time_stamp_start, nullptr);
    tasksPermutations = factorial(tasks.size());
    for (; tasksPermutations != 0; --tasksPermutations) {
        std::next_permutation(tasks.begin(), tasks.end());

        threeMs.calculateMakeSpan(tasks);
    }
    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "Sugested tasks queue for three machines: ";
    for (task *Task : threeMs.getOptimalTaskSet()) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << threeMs.getMinMakeSpan() << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    threeMachinesBruteForceTime = elapsed_time;

    //johnson:
    std::cout << "\n\nJonson's algorithm:\n";
    gettimeofday(&time_stamp_start, nullptr);
    std::sort(tasks.begin(), tasks.end(), taskCompMinTime);
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        if ((*iter)->getMinTime() == (*iter)->getM1()) {
            johnsonsTasksFront.push_back(*iter);
        } else {
            johnsonsTasksBack.push_front(*iter);
        }
    }
    johnsonsTasksFront.splice(johnsonsTasksFront.end(), johnsonsTasksBack);
    twoMsJohnson.calculateMakeSpan(johnsonsTasksFront);
    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "\n\nSugested tasks queue for two machines: ";
    for (auto Task : johnsonsTasksFront) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << twoMsJohnson.getCurrentMakeSpan() << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    twoMachinesJohnsonTime = elapsed_time;

    johnsonsTasksFront.clear();
    johnsonsTasksBack.clear();

    gettimeofday(&time_stamp_start, nullptr);
    std::sort(tasks.begin(), tasks.end(), taskCompVirtMinTime);
    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter) {
        if ((*iter)->getMinVirtTime() == (*iter)->getVirtM1()) {
            johnsonsTasksFront.push_back(*iter);
        } else {
            johnsonsTasksBack.push_front(*iter);
        }
    }
    johnsonsTasksFront.splice(johnsonsTasksFront.end(), johnsonsTasksBack);
    threeMsJohnson.calculateMakeSpan(johnsonsTasksFront);
    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "Sugested tasks queue for three machines: ";
    for (task *Task : johnsonsTasksFront) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << threeMsJohnson.getCurrentMakeSpan() << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    threeMachinesJohnsonTime = elapsed_time;

    std::sort(tasks.begin(), tasks.end(), [](const task *a, const task *b) -> bool { return a->getID() < b->getID(); });
    std::cout << "Tasks order reset before neh: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }
    //neh
    std::cout << "\n\nNEH algorithm:\n";
    std::vector<task *> tmp, best, bestPrev;
    unsigned Cmin = std::numeric_limits<unsigned>::max(), tmpCmax;
    gettimeofday(&time_stamp_start, nullptr);
    std::sort(tasks.begin(), tasks.end(), taskCompSumTimeNeg);
    bestPrev.clear();
    for (task *Task : tasks) {
        tmp = bestPrev;
        for (unsigned i = 0; i <= tmp.size(); ++i) {
            tmp.insert(tmp.begin() + i, Task);
            if ((tmpCmax = threeMsNEH.calculateMakeSpan(tmp)) < Cmin) {
                Cmin = tmpCmax;
                best = tmp;
            }
            tmp = bestPrev;
        }
        tmp.push_back(Task);
        if ((tmpCmax = threeMsNEH.calculateMakeSpan(tmp)) < Cmin) {
            best = tmp;
        }
        Cmin = std::numeric_limits<unsigned>::max();
        bestPrev = best;
    }
    tasks = best;
    threeMsNEH.clear();
    threeMsNEH.calculateMakeSpan(tasks);

    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "Sugested tasks queue for three machines: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << threeMsNEH.getCurrentMakeSpan() << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    threeMachinesNEHTime = elapsed_time;


    std::sort(tasks.begin(), tasks.end(), [](const task *a, const task *b) -> bool { return a->getID() < b->getID(); });
    std::cout << "Tasks order reset before tabu: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }

    //tabu
    unsigned iter = 0, localCmaxTmp, localCmax = std::numeric_limits<unsigned>::max();
    bool tabuEnd = false, tabuListFlag = false;
    std::cout << "\n\nTabu algorithm:\n";
    gettimeofday(&time_stamp_start, nullptr);
    time_stamp_taboo = time_stamp_start;
    tabuBestTasksLocal = tabuBestTasks = tasks;
    while (!tabuEnd) {

        tabuNeighbourhood = generateNeigbouhood(tabuBestTasksLocal, iter);
        if (tabuNeighbourhood.size() == 0) {
            iter = 0;
            for (std::vector<task *> tmpTasks : tabuList) {
                localCmaxTmp = getMakeSpanThreeMs(tmpTasks);
                if (localCmaxTmp < localCmax) {
                    localCmax = localCmaxTmp;
                    tasks = tmpTasks;
                }
            }
            localCmax = std::numeric_limits<unsigned>::max();
            gettimeofday(&time_stamp_taboo, nullptr);
            if (isTimeElapsed(time_stamp_start, time_stamp_taboo, TABOO_TIME)) {
                tabuEnd = true;
            }
            continue;
        }
        for (std::vector<task *> tmpTasks : tabuNeighbourhood) {

            if (std::find(tabuList.begin(), tabuList.end(), tmpTasks) != tabuList.end()) {
                continue;
            }
            localCmaxTmp = getMakeSpanThreeMs(tmpTasks);
            if (localCmaxTmp < localCmax) {
                localCmax = localCmaxTmp;
                tabuBestTasksLocalTmp = tmpTasks;
            }
        }
        localCmax = std::numeric_limits<unsigned>::max();
        //time elapsed
        gettimeofday(&time_stamp_taboo, nullptr);
        if (isTimeElapsed(time_stamp_start, time_stamp_taboo, TABOO_TIME)) {
            tabuEnd = true;
            continue;
        }
        if (getMakeSpanThreeMs(tabuBestTasksLocalTmp) < getMakeSpanThreeMs(tabuBestTasksLocal)) {
            tabuBestTasksLocal = tabuBestTasksLocalTmp;
            tabuList.push_back(tabuBestTasksLocal);
            iter = 0;
        } else {
            ++iter;
        }

        if (iter >= tasks.size()) {
            iter = 0;
            for (std::vector<task *> tmpTasks : tabuList) {
                localCmaxTmp = getMakeSpanThreeMs(tmpTasks);
                if (localCmaxTmp < localCmax) {
                    localCmax = localCmaxTmp;
                    tasks = tmpTasks;
                }
            }
            localCmax = std::numeric_limits<unsigned>::max();
        }
    }
    gettimeofday(&time_stamp_stop, nullptr);

    std::cout << "Sugested tasks queue for three machines: ";
    for (task *Task : tasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << getMakeSpanThreeMs(tasks) << '\n';
    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";

    threeMachinesTabuTime = elapsed_time;

    if (GENERATE_PLOT) {
        std::string nazwa("bfplot2.svg");

        twoMs.generatePlot(nazwa);
        nazwa = "bfplot3.svg";
        threeMs.generatePlot(nazwa);
        nazwa = "jplot2.svg";
        twoMsJohnson.generatePlot(nazwa);
        nazwa = "jplot3.svg";
        threeMsJohnson.generatePlot(nazwa);

    }

    if (GENERATE_TEST_DATA) {
        std::ofstream file;
        file.open("test_data_two_machines.log", std::ofstream::app);
        file << "|" << TASK_COUNT << "|" << twoMachinesJohnsonTime << " ms|" << twoMsJohnson.getMinMakeSpan();
        file << "|" << twoMachinesBruteForceTime << " ms|" << twoMs.getMinMakeSpan() << "|\n";
        file.close();
        file.open("test_data_three_machines.log", std::ofstream::app);
        file << "|" << TASK_COUNT << "|" << threeMachinesJohnsonTime << " ms|" << threeMsJohnson.getMinMakeSpan();
        file << "|" << threeMachinesBruteForceTime << " ms|" << threeMs.getMinMakeSpan();
        file << "|" << threeMachinesNEHTime << " ms|" << threeMsNEH.getMinMakeSpan();
        file << "|" << threeMachinesTabuTime << " ms|" << getMakeSpanThreeMs(tasks) << "|\n";
        file.close();

    }


    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
}