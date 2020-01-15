//
// Created by wojtek on 27/11/2019.
//

#ifndef ADVANCED_MACHINE_H
#define ADVANCED_MACHINE_H


#include <vector>
#include <fstream>
#include "Task.h"

class Machine {

public:

    unsigned long when_ready = 0;
    unsigned long tardiness = 0;
    unsigned long earliness = 0;
    unsigned long waiting = 0;

    std::vector<Task> tasks;
    std::vector<size_t> tardy_tasks;
    std::vector<size_t> early_tasks;
    std::vector<size_t> waiting_tasks;

    Machine();
    explicit Machine(std::vector<Task> tasks);

    void addTask(Task task);

    unsigned long calculateTardiness();
    unsigned long calculateEarliness();
    unsigned long calculateWaiting();

    void calculateAll();

    void save(std::ostream& out);

    std::vector<Task> getCopy();

};

bool operator < (const Machine& lhs, const Machine& rhs);

bool operator > (const Machine& lhs, const Machine& rhs);


#endif //ADVANCED_MACHINE_H
