//
// Created by wojtek on 07/12/2019.
//

#ifndef ADVANCED_ERTINITIALGENERATIONSTRATEGY_H
#define ADVANCED_ERTINITIALGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class ERTInitialGenerationStrategy: public BaseInitialGenerationStrategy {

    Solution generateSolution(std::vector<Task> instance) override;

};


#endif //ADVANCED_ERTINITIALGENERATIONSTRATEGY_H
