//
// Created by wojtek on 27/11/2019.
//

#include <algorithm>
#include "Task.h"

Task::Task(unsigned long id, unsigned long ready, unsigned long processing, unsigned long due) {
    this->id = id;
    this->ready = ready;
    this->processing = processing;
    this->due = due;
}

/**
 * Return finish time of task started at ti
 * @param ti start time
 * @return finish time
 */
unsigned long Task::start(unsigned long ti) {
    return std::max(ti, ready) + this->processing;
}

long Task::criteria(unsigned long ti) {
    // base for result is due time
    long result = 0;
    result += (long)this->due - (long)ti;
    // due time is decreased with processing time
    // so late task should have criteria value below 0
    // for tasks we would have to wait till they are ready criteria will be bigger than 0
    result -= (long)this->processing;

    // optional penalty for waiting
    result += std::max(0L, (long)this->ready - (long)ti);

    return result;
}

long Task::criteria_machine(unsigned long it) {
    long result = 0;

    result += (long)it;

    // optional penalty for waiting
    result += std::max(0L, (long)this->ready - (long)it)*2;

    return result;
}

long Task::woodpecker_criteria(unsigned long ti) {
    long result = 0;

    result += (long)processing;
    result += std::max(0L, (long)this->due - (long)ti);
    result += std::max(0L, (long)this->due - (long)this->processing - (long)std::max(ti, this->ready));

    return result;
}

long Task::calculate_tardiness(unsigned long now) {
//    long started = std::max(this->ready, now);
    long started = (long)now;
    return std::max(0L, started + (long)this->processing - (long)this->due);
}

long Task::calculate_earliness(unsigned long now) {
//    long started = std::max(this->ready, now);
    long started = (long)now;
    return std::max(0L, (long)this->due - (long)this->processing - started);
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
