//
// Created by wojtek on 08/12/2019.
//

#ifndef ADVANCED_FIRSTNEIGHBOURHOODGENERATIONSTRATEGY_H
#define ADVANCED_FIRSTNEIGHBOURHOODGENERATIONSTRATEGY_H


#include "BaseNeighbourhoodGenerationStrategy.h"

class FirstNeighbourhoodGenerationStrategy : public BaseNeighbourhoodGenerationStrategy {
protected:
    Solution swapCandidateStrategy(Solution current_solution, std::unordered_map<std::string , Operation> *tabooList, Solution current_best, size_t aspiration_plus_size, size_t machine_index);
    Solution highCandidateStrategy(Solution current_solution, std::unordered_map<std::string , Operation> *tabooList, Solution current_best, size_t aspiration_plus_size, size_t tardy_machine_index,size_t early_machine_index);
    Solution lowCandidateStrategy(Solution current_solution, std::unordered_map<std::string , Operation> *tabooList, Solution current_best, size_t aspiration_plus_size, size_t tardy_machine_index);

public:
    Solution findBestNeighbour(Solution current_solution, std::unordered_map<std::string , Operation> *tabooList, Solution current_best, size_t aspiration_plus_size) override;
};


#endif //ADVANCED_FIRSTNEIGHBOURHOODGENERATIONSTRATEGY_H
