//
// Created by wojtek on 27/11/2019.
//

#ifndef ADVANCED_TASK_H
#define ADVANCED_TASK_H


class Task {

public:
    unsigned long id;
    unsigned long ready;
    unsigned long processing;
    unsigned long due;

    unsigned long tardiness;
    unsigned long earliness;
    unsigned long waiting;

    Task(unsigned long id, unsigned long ready, unsigned long processing, unsigned long due);

    unsigned long start(unsigned long ti);

    long criteria(unsigned long ti);
    long criteria_machine(unsigned long ti);
    long woodpecker_criteria(unsigned long ti);

    long calculate_tardiness(unsigned long now);
    long calculate_earliness(unsigned long now);

};

bool operator < (const Task& lhs, const Task& rhs);

bool operator > (const Task& lhs, const Task& rhs);

bool operator == (const Task& lhs, const Task& rhs);


#endif //ADVANCED_TASK_H
