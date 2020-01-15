//
// Created by wojtek on 08/12/2019.
//

#include "JustInTimeInitialGenerationStrategy.h"

#include <queue>
#include <iostream>

Solution JustInTimeInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {
    auto machines = std::priority_queue<Machine, std::vector<Machine>, std::greater<> >();

    for(unsigned long i=0; i<BaseInitialGenerationStrategy::machines_number; i++) {
        machines.emplace(Machine());
    }

    while (!instance.empty()) {
        Machine m = machines.top();
        machines.pop();
        size_t current_index = 0;
        long current_criteria = instance[0].calculate_tardiness(m.when_ready) + instance[0].calculate_earliness(m.when_ready);
        for (size_t i = 1; i<instance.size(); i++) {
            long temp_criteria = instance[i].calculate_tardiness(m.when_ready) + instance[i].calculate_earliness(m.when_ready);
            if(temp_criteria < current_criteria) {
                current_criteria = temp_criteria;
                current_index = i;
            }
        }
//        std::cout<<instance[current_index].id<<"\t"<<current_criteria<<"\t"<<m.when_ready<<std::endl;
        m.addTask(instance[current_index]);
        instance.erase(instance.begin() + current_index);
        machines.push(m);
    }

    std::vector<Machine> result = std::vector<Machine>();

    while (!machines.empty()) {
        result.push_back(machines.top());
        machines.pop();
    }

    return Solution(result);
}
