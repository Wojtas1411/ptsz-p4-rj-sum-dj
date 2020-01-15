//
// Created by wojtek on 07/12/2019.
//

#ifndef ADVANCED_MYINITIALGENERATIONSTRATEGY_H
#define ADVANCED_MYINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class MyInitialGenerationStrategy: public BaseInitialGenerationStrategy {

    Solution generateSolution(std::vector<Task> instance) override;

};


#endif //ADVANCED_MYINITIALGENERATIONSTRATEGY_H
