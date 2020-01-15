//
// Created by wojtek on 18/12/2019.
//

#include "BestOfTwoGenerationStrategy.h"

class Solution BestOfTwoGenerationStrategy::generateSolution(std::vector<Task> instance) {

    Solution solution1 = this->s1->generateSolution(instance);
    Solution solution2 = this->s2->generateSolution(instance);
    if(solution1.tardinessValue() < solution2.tardinessValue()) {
        return solution1;
    }
    return solution2;
}

BestOfTwoGenerationStrategy::BestOfTwoGenerationStrategy(BaseInitialGenerationStrategy *s1,
                                                         BaseInitialGenerationStrategy *s2) {
    this->s1 = s1;
    this->s2 = s2;
}
