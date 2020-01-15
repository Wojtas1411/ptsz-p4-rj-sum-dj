//
// Created by wojtek on 10/18/19.
//

#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H


class Task {

public:
    unsigned long id;
    unsigned long ready;
    unsigned long processing;
    unsigned long due;

    unsigned long scheduled;

    unsigned long early; // LUZ
    unsigned long finished;
    unsigned long started;

    unsigned long delayed;

    Task(unsigned long id, unsigned long ready, unsigned long processing, unsigned long due);

    unsigned long start(unsigned long ti);

    long criteria(unsigned long it);

    long criteria_machine(unsigned long ti);

};

bool operator < (const Task& lhs, const Task& rhs);

bool operator > (const Task& lhs, const Task& rhs);

bool operator == (const Task& lhs, const Task& rhs);


#endif //SIMPLE_TASK_H
