//
// Created by wojtek on 08/12/2019.
//

#include "ImprovedInitialGenerationStrategy.h"

#include <algorithm>
#include <iostream>
#include <queue>

Solution ImprovedInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {
    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.ready < rhs.ready || (lhs.ready == rhs.ready && lhs.due < rhs.due);
    });

    auto machines = new std::vector<Machine>();
    for(int i=0; i<ImprovedInitialGenerationStrategy::machines_number; i++){
        machines->emplace_back(Machine());

        while (true) {
            long min_index = -1;
            long min_value = 1000000;

            unsigned long now = machines->at(i).when_ready;
            for(unsigned long j=0; j<instance.size(); j++) {
                long criteria = instance[j].criteria(now);
                if(criteria >= 0 && criteria < min_value) {
                    min_value = criteria;
                    min_index = (long)j;
                }
            }

            if(min_index == -1) {
                break;
            }

//            std::cout<<i<<"\t"<<instance[min_index].id<<std::endl;

            machines->at(i).addTask(instance[min_index]);
            instance.erase(instance.begin() + min_index);
        }

    }

    if(!instance.empty()){
        std::cout<<"Something left\t"<<instance.size()<<std::endl;
    }

    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.processing < rhs.processing;
    });

    auto machines2 = new std::priority_queue<Machine,std::vector<Machine>, std::greater<> >();

    for(const auto& m: *machines){
        machines2->emplace(m);
    }

    machines->clear();
    machines->shrink_to_fit();

    for(auto t: instance) {
        Machine m = machines2->top();
        machines2->pop();
        m.addTask(t);
        machines2->push(m);
    }

    auto result = std::vector<Machine>();

    while(!machines2->empty()){
        result.push_back(machines2->top());
        machines2->pop();
    }

    return Solution(result);
}
