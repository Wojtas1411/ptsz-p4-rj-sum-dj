//
// Created by wojtek on 27/11/2019.
//

#include "Machine.h"
#include <iostream>
#include <utility>
Machine::Machine() {
    this->tasks = std::vector<Task>();
    this->tardy_tasks = std::vector<size_t >();
    this->early_tasks = std::vector<size_t >();
    this->waiting_tasks = std::vector<size_t >();
}

Machine::Machine(std::vector<Task> tasks): Machine() {
    this->when_ready = 0;
    this->tasks = std::move(tasks);
    this->tardy_tasks = std::vector<size_t >();
    this->early_tasks = std::vector<size_t >();
    this->waiting_tasks = std::vector<size_t >();
    this->calculateAll();
}

/**
 * Update machine with given task
 * @param task
 */
void Machine::addTask(Task task) {
    this->when_ready = task.start(this->when_ready);
    this->tasks.push_back(task);
}

unsigned long Machine::calculateTardiness() {
    unsigned long result = 0;
    this->when_ready = 0;
    for(unsigned long i=0; i<this->tasks.size(); i++){
        long started = std::max(this->when_ready, tasks[i].ready);
        result += std::max(0L, (long)(started + tasks[i].processing) - (long)tasks[i].due);
        this->when_ready = tasks[i].start(this->when_ready);
    }
    return result;
}

unsigned long Machine::calculateEarliness() {
    unsigned long result = 0;
    this->when_ready = 0;
    for(unsigned long i=0; i<this->tasks.size(); i++){
        long started = std::max(this->when_ready, tasks[i].ready);
        result += std::max(0L, (long)tasks[i].due - (long)(started + tasks[i].processing) );
        this->when_ready = tasks[i].start(this->when_ready);
    }
    return result;
}

unsigned long Machine::calculateWaiting() {
    unsigned long result = 0;
    this->when_ready = 0;
    for(unsigned long i=0; i<this->tasks.size(); i++){
        result += std::max(0L, (long)tasks[i].ready - (long)this->when_ready);
        this->when_ready = tasks[i].start(this->when_ready);
    }
    return result;
}

void Machine::calculateAll() {
    // clear
    this->tardiness = 0;
    this->earliness = 0;
    this->waiting = 0;
    this->when_ready = 0;
    this->tardy_tasks.clear();
    this->early_tasks.clear();
    this->waiting_tasks.clear();
    // for each task
    for(size_t i=0; i<this->tasks.size(); i++){
        long started = std::max(this->when_ready, tasks[i].ready);
        // calculate values
        tasks[i].tardiness = std::max(0L, (long)(started + tasks[i].processing) - (long)tasks[i].due);
        tasks[i].earliness = std::max(0L, (long)tasks[i].due - (long)(started + tasks[i].processing) );
        //tasks[i].waiting = std::max(0L, (long)tasks[i].ready - (long)this->when_ready);
        // increase machine values
        this->tardiness += tasks[i].tardiness;
        this->earliness += tasks[i].earliness;
        //this->waiting += tasks[i].waiting;
        // add to tasks indexes vector
        //if(tasks[i].tardiness > 0) tardy_tasks.push_back(i);
        //if(tasks[i].earliness > 0) early_tasks.push_back(i);
        //if(tasks[i].waiting > 0) waiting_tasks.push_back(i);
        // update when ready
        this->when_ready = tasks[i].start(this->when_ready);
    }
}

/**
 * Save machine in given format on output stream
 * @param out
 */
void Machine::save(std::ostream &out) {
    if(!this->tasks.empty()){
        for(unsigned long i=0; i<this->tasks.size() - 1; i++){
            out << this->tasks.at(i).id << " ";
        }
        out << this->tasks.at(this->tasks.size() - 1).id << std::endl;
    }
}


/*
 * ----- Operator override -----
 */

bool operator < (const Machine& lhs, const Machine& rhs){
    return lhs.when_ready < rhs.when_ready;
}

bool operator > (const Machine& lhs, const Machine& rhs){
    return lhs.when_ready > rhs.when_ready;
}

std::vector<Task> Machine::getCopy() {
    return this->tasks;
}
