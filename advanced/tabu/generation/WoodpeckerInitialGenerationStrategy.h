//
// Created by wojtek on 07/12/2019.
//

#ifndef ADVANCED_WOODPECKERINITIALGENERATIONSTRATEGY_H
#define ADVANCED_WOODPECKERINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class WoodpeckerInitialGenerationStrategy: public BaseInitialGenerationStrategy {

    Solution generateSolution(std::vector<Task> instance) override;

};


#endif //ADVANCED_WOODPECKERINITIALGENERATIONSTRATEGY_H
