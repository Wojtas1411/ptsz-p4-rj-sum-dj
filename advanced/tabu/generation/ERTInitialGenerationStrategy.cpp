//
// Created by wojtek on 07/12/2019.
//

#include <queue>
#include <algorithm>
#include "ERTInitialGenerationStrategy.h"

Solution ERTInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {
    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.ready < rhs.ready || (lhs.ready == rhs.ready && lhs.due < rhs.due);
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