//
// Created by wojtek on 27/11/2019.
//

#include "TabooSolver.h"
#include "Operation.h"

#include <chrono>
#include <iostream>
#include <unordered_map>

TabooSolver * TabooSolver::setGenerationStrategy(BaseInitialGenerationStrategy *gs) {
    this->generationStrategy = gs;
    return this;
}

TabooSolver * TabooSolver::setNeighbourhoodGenerationStrategy(BaseNeighbourhoodGenerationStrategy * ngs) {
    this->neighbourhoodGenerationStrategy = ngs;
    return this;
}

TabooSolver::TabooSolver() = default;

class Solution TabooSolver::solve(const std::vector<Task>& instance) {

    this->neighbourhoodGenerationStrategy->operation_tenure = (long)instance.size()/2;

    auto start_time_point = std::chrono::system_clock::now();
    unsigned long max_duration_ms = instance.size()*TabooSolver::time_constant_ms;

    Solution temp = this->generationStrategy->generateSolution(instance);
    Solution best = temp.makeCopy();

    std::cout<<"Initial tardiness\t"<<best.tardinessValue()<<std::endl;

    auto tabooMap = new std::unordered_map<std::string, Operation>();

    unsigned long iteration = 0;
    unsigned long iterations_without_improvement = 0;

    while (best.tardinessValue() > 0) {

        /**
         * Find next solution
         */
        unsigned long ptemp = temp.tardinessValue();
        temp = this->neighbourhoodGenerationStrategy->findBestNeighbour(temp, tabooMap, best, instance.size());
        if (temp.tardinessValue() < best.tardinessValue()) {
            best = temp.makeCopy();

//            std::cout<<"New best value\t"<<best.tardinessValue()<<std::endl;
        }
        /**
         * check if solution is better
         */
        if(ptemp <= temp.tardinessValue()) {
            iterations_without_improvement += 1;
        } else {
            iterations_without_improvement = 0;
        }

        /**
         * Timeout check
         */
        auto checkpoint_time_point = std::chrono::system_clock::now();
        unsigned long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(checkpoint_time_point-start_time_point).count();
        if(duration_ms > max_duration_ms) {
            std::cout<<"Terminated due timeout at iteration:\t"<<iteration<<std::endl;
            break;
        }

        /**
         * Deal with taboo map
         */
        std::vector<std::string> to_remove = std::vector<std::string>();
        for(const auto & pair: *tabooMap) {
            Operation o = pair.second;
            o.remainingTime--;
            if(o.remainingTime > 0) tabooMap->at(pair.first) = o;
            else to_remove.push_back(pair.first);
        }
        for(const auto & r: to_remove){
            tabooMap->erase(r);
        }

        /**
         * Handle restart
         */
//        if (iterations_without_improvement >= TabooSolver::max_iterations_without_improvement) {
//            std::cout<<"Restarting"<<std::endl;
//            temp = generationStrategy->generateSolution(instance);
//            iterations_without_improvement = 0;
//            if(temp.tardinessValue() < best.tardinessValue()) {
//                best = temp.makeCopy();
//            }
//        }

        iteration++;
    }
    std::cout<<"Final result\t"<<best.tardinessValue()<<std::endl;
    return best;
}