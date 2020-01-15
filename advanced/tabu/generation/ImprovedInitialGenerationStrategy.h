//
// Created by wojtek on 08/12/2019.
//

#ifndef ADVANCED_IMPROVEDINITIALGENERATIONSTRATEGY_H
#define ADVANCED_IMPROVEDINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class ImprovedInitialGenerationStrategy : public BaseInitialGenerationStrategy{
    Solution generateSolution(std::vector<Task> instance) override;
};


#endif //ADVANCED_IMPROVEDINITIALGENERATIONSTRATEGY_H
