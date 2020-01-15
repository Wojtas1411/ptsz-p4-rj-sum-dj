//
// Created by wojtek on 27/11/2019.
//

#include <iostream>
#include <utility>
#include "Solution.h"

Solution::Solution(std::vector<Machine> machines) {
    this->machines = std::move(machines);

    if(this->machines.size() != P){
        std::cout<<"Well, fuck"<<std::endl;
    }

    for(int i=0; i<Solution::P; i++) {
        this->dirty.push_back(true);
    }

    for(std::size_t i = 0; i < this->machines.size(); i++){
        this->machines[i].calculateAll();
        this->dirty[i] = false;
    }
}

unsigned long Solution::tardinessValue() {
    unsigned long result = 0;
    for(int i = 0; i<Solution::P; i++){
        if(dirty[i]){
            machines[i].calculateAll();
            dirty[i] = false;
        }
        result += machines[i].tardiness;
    }
    return result;
}

Solution Solution::makeCopy() {

    Solution s = Solution();
    s.machines = this->machines;
    s.dirty = this->dirty;

    return s;

//    std::vector<Machine> copyp = std::vector<Machine>();
//    for(std::size_t i=0; i<this->machines.size(); i++) {
//        std::vector<Task> c = machines[i].getCopy();
//        copyp.emplace_back(Machine(c));
//    }
//
//    return Solution(copyp);
}

std::vector<Machine>& Solution::result() {
    return this->machines;
}

void Solution::eraseTask(size_t machine_index, size_t position) {
    this->machines[machine_index].tasks.erase(this->machines[machine_index].tasks.begin() + position);
    this->machines[machine_index].calculateAll();
}

void Solution::insertTask(size_t machine_index, size_t position, Task task) {
    if(position < this->machines[machine_index].tasks.size() ) {
        this->machines[machine_index].tasks.insert(this->machines[machine_index].tasks.begin() + position, task);
    } else {
        this->machines[machine_index].tasks.push_back(task);
    }
    this->machines[machine_index].calculateAll();
}

void Solution::print() {
    std::cout<<this->tardinessValue()<<std::endl;
    for(auto & m: this->machines) {
//        m.save(std::cout);
        std::cout<<m.tardiness<<"\t"<<m.earliness<<"\t"<<m.waiting<<std::endl;
    }
}
