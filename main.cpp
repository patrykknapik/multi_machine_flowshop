#include <iostream>
#include <vector>
#include <list>
#include <sys/time.h>
#include <unordered_set>
#include "twoMachines.h"
#include "threeMachines.h"

#define TASK_COUNT 5
#define MIN_TIME 1
#define MAX_TIME 20
#define SHOW_PERMUTATIONS true

unsigned long int factorial(unsigned long int i) {
    unsigned long int f = 1;
    while (i != 1) {
        f *= i;
        --i;
    }
    return f;
}



int main() {
    timeval time_stamp_start, time_stamp_stop;
    double elapsed_time;
    std::vector<task *> tasks;
    std::list<task *> johnsonsTasksFront, johnsonsTasksBack;
    unsigned long int tasksPermutations = 0;
    std::srand(std::time(nullptr));

    twoMachines twoMs, twoMsJohnson;
    threeMachines threeMs, threeMsJohnson;

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


    //johnson:
    std::cout << "\n\nJonson's algorithm:\n";
    gettimeofday(&time_stamp_start, nullptr);
    std::sort(tasks.begin(), tasks.end(), taskCompMinTimeNeg);
    for (auto iter = tasks.rbegin(); iter != tasks.rend(); ++iter) {
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


    johnsonsTasksFront.clear();
    johnsonsTasksBack.clear();
    gettimeofday(&time_stamp_start, nullptr);
    std::sort(tasks.begin(), tasks.end(), taskCompVirtMinTimeNeg);
    for (auto iter = tasks.rbegin(); iter != tasks.rend(); ++iter) {
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

    for (task *Task : tasks) {
        delete Task;
    }

    return 0;
}