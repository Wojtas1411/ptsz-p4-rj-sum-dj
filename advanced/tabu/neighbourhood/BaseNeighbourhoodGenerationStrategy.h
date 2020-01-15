//
// Created by wojtek on 07/12/2019.
//

#ifndef ADVANCED_BASENEIGHBOURHOODGENERATIONSTRATEGY_H
#define ADVANCED_BASENEIGHBOURHOODGENERATIONSTRATEGY_H


#include <unordered_map>
#include "../Operation.h"
#include "../Solution.h"

//enum OperationEnum {
//    InsertOperation,
//    SwapOperation
//};

class BaseNeighbourhoodGenerationStrategy {

public:
    static std::string operationToString(OperationEnum type, size_t pos1, long id1, size_t pos2, long id2) {
        return std::to_string(type) + "-" + std::to_string(pos1) + ":" + std::to_string(id1) + "-" + std::to_string(pos2) + ":" + std::to_string(id2);
    }

    long operation_tenure = 0;

    virtual Solution findBestNeighbour(Solution current_solution, //seed for neighbours generation
            std::unordered_map<std::string, Operation> * tabooList,          // taboo list
            Solution current_best,                      // aspiration criteria
            size_t aspiration_plus_size) = 0;           // aspiration + generated neighbours
};

#endif //ADVANCED_BASENEIGHBOURHOODGENERATIONSTRATEGY_H
