//
// Created by wojtek on 27/11/2019.
//

#ifndef ADVANCED_TABOOSOLVER_H
#define ADVANCED_TABOOSOLVER_H


#include "generation/BaseInitialGenerationStrategy.h"
#include "neighbourhood/BaseNeighbourhoodGenerationStrategy.h"

class TabooSolver {
public:

    static const long time_constant_ms = 10;

    BaseInitialGenerationStrategy *generationStrategy = nullptr;
    BaseNeighbourhoodGenerationStrategy *neighbourhoodGenerationStrategy = nullptr;

    TabooSolver();

    TabooSolver * setGenerationStrategy(BaseInitialGenerationStrategy *gs);
    TabooSolver * setNeighbourhoodGenerationStrategy(BaseNeighbourhoodGenerationStrategy * ngs);

    Solution solve(const std::vector<Task>& instance);


};


#endif //ADVANCED_TABOOSOLVER_H

