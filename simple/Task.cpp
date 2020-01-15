//
// Created by wojtek on 10/18/19.
//

#include <algorithm>
#include "Task.h"

Task::Task(unsigned long id, unsigned long ready, unsigned long processing, unsigned long due) {
    this->id = id;
    this->ready = ready;
    this->processing = processing;
    this->due = due;
    this->scheduled = 0;
    this->finished = 0;
    this->started = 0;
    this->early = 0;
    this->delayed = 0;
}

unsigned long Task::start(unsigned long ti) {
    this->scheduled = ti;
    this->early = due - processing - std::max(ti, ready);
    this->finished = std::max(ti, ready) + processing;
    this->started = std::max(ti, ready);

    this->delayed = std::max(0L, (long)this->started + (long)this->processing - (long)this->due);

    return this->finished;
}

long Task::criteria(unsigned long it) {
    // base for result is due time
    long result = 0;
    result += (long)this->due - (long)it;
    // due time is decreased with processing time
    // so late task should have criteria value below 0
    // for tasks we would have to wait till they are ready criteria will be bigger than 0
    result -= (long)this->processing;

    // optional penalty for waiting
    result += std::max(0L, (long)this->ready - (long)it);

    return result;
}

long Task::criteria_machine(unsigned long it) {
    long result = 0;

    // test 5
    result += (long)it;

    // optional penalty for waiting
    result += std::max(0L, (long)this->ready - (long)it)*2;

    return result;
}

bool operator < (const Task& lhs, const Task& rhs){
    return lhs.due < rhs.due;
}

bool operator > (const Task& lhs, const Task& rhs){
    return lhs.due > rhs.due;
}

bool operator == (const Task& lhs, const Task& rhs){
    return lhs.due == rhs.due;
}

