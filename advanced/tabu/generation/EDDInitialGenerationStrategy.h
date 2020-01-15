//
// Created by wojtek on 07/12/2019.
//

#ifndef ADVANCED_EDDINITIALGENERATIONSTRATEGY_H
#define ADVANCED_EDDINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class EDDInitialGenerationStrategy: public BaseInitialGenerationStrategy {

    Solution generateSolution(std::vector<Task> instance) override;

};


#endif //ADVANCED_EDDINITIALGENERATIONSTRATEGY_H
