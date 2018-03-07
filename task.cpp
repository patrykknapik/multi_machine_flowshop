//
// Created by Patryk Knapik on 07.03.2018.
//

#include "task.h"

std::ostream &operator<<(std::ostream &stream, const task &Task) {
    stream << "Task ID: " << Task.getID() << "\n";
    stream << "Times: " << Task.getM1() << "M1, " << Task.getM2() << "M2, " << Task.getM3() << "M3";
    return stream;
}