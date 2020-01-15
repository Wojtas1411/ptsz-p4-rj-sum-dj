//
// Created by wojtek on 07/12/2019.
//

#include <vector>
#include "../Solution.h"

#ifndef ADVANCED_BASEINITIALGENERATIONSTRATEGY_H
#define ADVANCED_BASEINITIALGENERATIONSTRATEGY_H


class BaseInitialGenerationStrategy {

public:
    static const unsigned long machines_number = 4;

    virtual Solution generateSolution(std::vector<Task> instance) = 0;

};


#endif //ADVANCED_BASEINITIALGENERATIONSTRATEGY_H
