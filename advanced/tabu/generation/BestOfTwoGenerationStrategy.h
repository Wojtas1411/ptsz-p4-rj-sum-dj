//
// Created by wojtek on 18/12/2019.
//

#ifndef ADVANCED_BESTOFTWOGENERATIONSTRATEGY_H
#define ADVANCED_BESTOFTWOGENERATIONSTRATEGY_H


#include "BaseInitialGenerationStrategy.h"

class BestOfTwoGenerationStrategy : public BaseInitialGenerationStrategy {
protected:
    BaseInitialGenerationStrategy * s1;
    BaseInitialGenerationStrategy * s2;

public:
    Solution generateSolution(std::vector<Task> instance) override;

    BestOfTwoGenerationStrategy(BaseInitialGenerationStrategy * s1, BaseInitialGenerationStrategy * s2);
};


#endif //ADVANCED_BESTOFTWOGENERATIONSTRATEGY_H
