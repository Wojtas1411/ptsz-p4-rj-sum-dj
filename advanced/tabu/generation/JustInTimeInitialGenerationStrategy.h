//
// Created by wojtek on 08/12/2019.
//

#ifndef ADVANCED_JUSTINTIMEINITIALGENERATIONSTRATEGY_H
#define ADVANCED_JUSTINTIMEINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class JustInTimeInitialGenerationStrategy : public BaseInitialGenerationStrategy{
    Solution generateSolution(std::vector<Task> instance) override;
};


#endif //ADVANCED_JUSTINTIMEINITIALGENERATIONSTRATEGY_H
