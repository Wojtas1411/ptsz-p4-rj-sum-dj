//
// Created by wojtek on 23/10/2019.
//

#ifndef SIMPLE_MACHINE_H
#define SIMPLE_MACHINE_H


#include <vector>
#include <fstream>
#include "Task.h"

class Machine {

public:

    unsigned long when_ready = 0;

    std::vector<Task>* tasks;

    Machine();

    void addTask(Task task);

    unsigned long calculateTotalDelay();

    void save(std::ostream& out);

};

bool operator < (const Machine& lhs, const Machine& rhs);

bool operator > (const Machine& lhs, const Machine& rhs);


#endif //SIMPLE_MACHINE_H
