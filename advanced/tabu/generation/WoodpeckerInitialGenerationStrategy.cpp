//
// Created by wojtek on 07/12/2019.
//

#include <queue>
#include <iostream>
#include <algorithm>
#include "WoodpeckerInitialGenerationStrategy.h"

class Solution WoodpeckerInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {

    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.ready < rhs.ready || (lhs.ready == rhs.ready && lhs.due < rhs.due);
    });

    auto machines = std::priority_queue<Machine, std::vector<Machine>, std::greater<> >();

    for(unsigned long i=0; i<BaseInitialGenerationStrategy::machines_number; i++) {
        machines.emplace(Machine());
    }

    while (!instance.empty()) {
        Machine m = machines.top();
        machines.pop();
        size_t current_index = 0;
        long current_criteria = instance[0].woodpecker_criteria(m.when_ready);
//        std::cout<<instance[0].id<<"\t"<<current_criteria<<std::endl;
        for (size_t i = 1; i<instance.size(); i++) {
            long temp_criteria = instance[i].woodpecker_criteria(m.when_ready);
//            std::cout<<instance[i].id<<"\t"<<temp_criteria<<std::endl;
            if(temp_criteria < current_criteria && instance[i].ready <= m.when_ready) {
                current_criteria = temp_criteria;
                current_index = i;
            }
        }
//        std::cout<<m.when_ready<<"\t"<<instance[current_index].id<<"\t"<<current_criteria<<std::endl;
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
