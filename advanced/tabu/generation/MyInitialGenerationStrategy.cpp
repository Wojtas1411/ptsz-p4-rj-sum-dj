//
// Created by wojtek on 07/12/2019.
//

#include <algorithm>
#include "MyInitialGenerationStrategy.h"

Solution MyInitialGenerationStrategy::generateSolution(std::vector<Task> instance) {
    auto machines = new std::vector<Machine>();
    for(int i=0; i<MyInitialGenerationStrategy::machines_number; i++){
        machines->emplace_back(Machine());
    }

    auto sacrificed = std::vector<Task>();

    std::sort(instance.begin(), instance.end());

    for (Task t: instance){
        unsigned long machine_min_criteria = t.criteria_machine(machines->at(0).when_ready);
        unsigned long machine_index = 0;
        for(int i=1; i<MyInitialGenerationStrategy::machines_number; i++){
            unsigned long criteria = t.criteria_machine(machines->at(i).when_ready);
            if(machine_min_criteria > criteria) {
                machine_min_criteria = criteria;
                machine_index = i;
            }
        }

        // kryterium poświęcania
        // całe zadanie nie wykona się w czasie
        //if (machines->at(machine_index).when_ready >= t.due && t.processing > 20) {

        // parametryzowane po procencie długości zadania, które nie wykona się w czasie
        unsigned long when_ready = machines->at(machine_index).when_ready;
        long started = std::max(when_ready, t.ready);
        long late = std::max(0L, (long)started + (long)t.processing - (long)t.due);
        double ratio = double(late)/double(t.processing);

        if (ratio > 0.8 && t.processing > 20) {
            sacrificed.push_back(t);
            continue;
        }

        machines->at(machine_index).addTask(t);
    }

    sort(sacrificed.begin(), sacrificed.end(), [](const Task& lhs, const Task& rhs){
        return lhs.processing < rhs.processing || (lhs.processing == rhs.processing && lhs.due < rhs.due);
    });

    for (Task t: sacrificed){
        unsigned long machine_min_criteria = t.criteria_machine(machines->at(0).when_ready);
        unsigned long machine_index = 0;
        for(int i=1; i<MyInitialGenerationStrategy::machines_number; i++){
            unsigned long criteria = t.criteria_machine(machines->at(i).when_ready);
            if(machine_min_criteria > criteria) {
                machine_min_criteria = criteria;
                machine_index = i;
            }
        }

        machines->at(machine_index).addTask(t);
    }

    return Solution(*machines);
}