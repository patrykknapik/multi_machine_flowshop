#include <iostream>
#include <vector>
#include <sys/time.h>
#include "task.h"

#define TASK_COUNT 2
#define MIN_TIME 1
#define MAX_TIME 20

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i;
        --i;
    }
    return f;
}

struct twoMachines {
    unsigned int M1time = 0, M2time = 0, Cmax = 0, Cmin = std::numeric_limits<unsigned int>::max();
    std::vector<task *> queuedTasks;
};

struct threeMachines {
    unsigned int M1time = 0, M2time = 0, M3time = 0, Cmax = 0, Cmin = std::numeric_limits<unsigned int>::max();
    std::vector<task *> queuedTasks;
};

int main() {
    timeval time_stamp_start, time_stamp_stop;
    double elapsed_time;
    std::vector<task *> tasks;
    unsigned long int tasksPermutations = 0;
    std::srand(std::time(nullptr));

    twoMachines twoMs;
    threeMachines threeMs;

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
    gettimeofday(&time_stamp_start, NULL);
    tasksPermutations = factorial(tasks.size());
    std::cout << "\nPermutations(" << tasksPermutations << "):\n";

    for (; tasksPermutations != 0; --tasksPermutations) {
        std::next_permutation(tasks.begin(), tasks.end());

        for (auto iter = tasks.begin(); iter < tasks.end(); ++iter) {
            std::cout << (*iter)->getID() << ' ';
            if (iter == tasks.begin()) {
                twoMs.M2time = twoMs.M1time = (*iter)->getM1();
                twoMs.M2time += (*iter)->getM2();

            } else {
                twoMs.M1time += (*iter)->getM1();
                twoMs.M2time = std::max(twoMs.M2time, twoMs.M1time) + (*iter)->getM2();
            }

        }

        for (auto iter = tasks.begin(); iter < tasks.end(); ++iter) {
            if (iter == tasks.begin()) {
                threeMs.M2time = threeMs.M1time = threeMs.M3time = (*iter)->getM1();
                threeMs.M2time += (*iter)->getM2();
                threeMs.M3time += (*iter)->getM2() + (*iter)->getM3();
            } else {
                threeMs.M1time += (*iter)->getM1();
                threeMs.M2time = std::max(threeMs.M2time, threeMs.M1time) + (*iter)->getM2();
                threeMs.M3time = std::max(threeMs.M2time, threeMs.M3time) + (*iter)->getM3();
            }

        }

        threeMs.Cmax = std::max(threeMs.M1time, threeMs.M2time);
        threeMs.Cmax = std::max(threeMs.M3time, threeMs.Cmax);
        twoMs.Cmax = std::max(twoMs.M1time, twoMs.M2time);
        std::cout << "; 2M: C = " << twoMs.Cmax;
        std::cout << "; 3M: C = " << threeMs.Cmax << '\n';

        if (twoMs.Cmax < twoMs.Cmin) {
            twoMs.Cmin = twoMs.Cmax;
            twoMs.queuedTasks = tasks;
        }

        if (threeMs.Cmax < threeMs.Cmin) {
            threeMs.Cmin = threeMs.Cmax;
            threeMs.queuedTasks = tasks;
        }
    }
    gettimeofday(&time_stamp_stop, NULL);

    std::cout << "\n\nSugested tasks queue for two machines: ";
    for (task *Task : twoMs.queuedTasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << twoMs.Cmin << '\n';

    std::cout << "Sugested tasks queue for three machines: ";
    for (task *Task : threeMs.queuedTasks) {
        std::cout << Task->getID() << ' ';
    }
    std::cout << "; Cmin = " << threeMs.Cmin << '\n';

    elapsed_time = (time_stamp_stop.tv_sec - time_stamp_start.tv_sec) * 1000.0;      // sec to ms
    elapsed_time += (time_stamp_stop.tv_usec - time_stamp_start.tv_usec) / 1000.0;   // us to ms
    std::cout << "Computation time: " << elapsed_time << " ms.\n\n\n";


    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
}