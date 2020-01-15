//
// Created by wojtek on 07/12/2019.
//

#include "EDDInitialGenerationStrategy.h"
#include <algorithm>
#include <queue>

Solution EDDInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {
    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.due < rhs.due || (lhs.due == rhs.due && lhs.ready < rhs.ready);
    });

    auto machines = std::priority_queue<Machine,std::vector<Machine>, std::greater<> >();

    for(unsigned long i=0; i<BaseInitialGenerationStrategy::machines_number; i++) {
        machines.emplace(Machine());
    }

    for(const auto element: instance) {
        Machine m = machines.top();
        machines.pop();
        m.addTask(element);
        machines.push(m);
    }

    std::vector<Machine> result = std::vector<Machine>();

    while (!machines.empty()) {
        result.push_back(machines.top());
        machines.pop();
    }

    return Solution(result);
}
