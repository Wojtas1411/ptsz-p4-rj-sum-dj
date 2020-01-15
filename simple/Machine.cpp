//
// Created by wojtek on 23/10/2019.
//

#include "Machine.h"
#include <iostream>
Machine::Machine() {
    this->tasks = new std::vector<Task>();
}

void Machine::addTask(Task task) {
    this->when_ready = task.start(this->when_ready);
    this->tasks->push_back(task);
}

unsigned long Machine::calculateTotalDelay() {
    unsigned long result = 0;
    for(unsigned long i=0; i<this->tasks->size(); i++){
        result += tasks->at(i).delayed;
    }
    return result;
}

void Machine::save(std::ostream &out) {
    if(!this->tasks->empty()){
        for(unsigned long i=0; i<this->tasks->size() - 1; i++){
            out << this->tasks->at(i).id << " ";
        }
        out << this->tasks->at(this->tasks->size() - 1).id << std::endl;
    }
}

bool operator < (const Machine& lhs, const Machine& rhs){
    return lhs.when_ready < rhs.when_ready;
}

bool operator > (const Machine& lhs, const Machine& rhs){
    return lhs.when_ready > rhs.when_ready;
}

