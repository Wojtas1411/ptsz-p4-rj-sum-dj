//
// Created by wojtek on 08/12/2019.
//

#include <iostream>
#include "FirstNeighbourhoodGenerationStrategy.h"
#include "../Operation.h"
#include "../TabooSolver.h"

Solution FirstNeighbourhoodGenerationStrategy::swapCandidateStrategy(Solution current_solution,
                                                                     std::unordered_map<std::string, Operation> *tabooList,
                                                                     Solution current_best, size_t aspiration_plus_size,
                                                                     size_t machine_index) {
    return current_solution;
}

Solution FirstNeighbourhoodGenerationStrategy::lowCandidateStrategy(Solution current_solution,
                                                                    std::unordered_map<std::string, Operation> *tabooList,
                                                                    Solution current_best, size_t aspiration_plus_size,
                                                                    size_t tardy_machine_index) {

    unsigned long aspiration_value = current_best.tardinessValue();
    unsigned long current_best_value = current_solution.tardinessValue()*10000;
    Solution result = current_solution;//.makeCopy();
    Operation bestop = Operation();
    Operation bestrop = Operation();

    for(size_t current_tardy_index = 0; current_tardy_index < current_solution.machines[tardy_machine_index].tasks.size(); current_tardy_index++) {
        Solution partial = current_solution;//.makeCopy();
        partial.eraseTask(tardy_machine_index, current_tardy_index);

        for(size_t i = 0; i<partial.machines.size(); i++) {
            if(i == current_tardy_index) {
                continue;
            }
            for(size_t j=0; j<=partial.machines[i].tasks.size(); j++) {

                if(i == tardy_machine_index && j == current_tardy_index) {
                    continue;
                }
                /**
                 * skip some options where ready times are lower
                 */
//                if(j < partial.machines[i].tasks.size()/2 && partial.machines[i].tasks[j].ready < current_solution.machines[tardy_machine_index].tasks[current_tardy_index].ready) {
//                    continue;
//                }

                Solution checked = partial;//.makeCopy();
                checked.insertTask(i,j,current_solution.machines[tardy_machine_index].tasks[current_tardy_index]);

                long tardy_task_id = (long)current_solution.machines[tardy_machine_index].tasks[current_tardy_index].id;
                long early_task_id = (long)partial.machines[i].tasks[j].id;

                Operation op = Operation(InsertOperation, tardy_machine_index, tardy_task_id, i, early_task_id, this->operation_tenure);
                Operation rop = Operation(InsertOperation, i, early_task_id, tardy_machine_index, tardy_task_id, this->operation_tenure);

                if(checked.tardinessValue() < current_best_value && tabooList->count(op.getKey()) == 0) {

                    current_best_value = checked.tardinessValue();
                    result = checked;//.makeCopy();
                    bestop = op;
                    bestrop = rop;

                }
                else if (checked.tardinessValue() < aspiration_value && tabooList->count(op.getKey()) != 0) {
                    /**
                    * aspiration -> operation in taboo list but better than global best
                    */
                    std::cout<<"Aspiration"<<std::endl;
                    current_best_value = checked.tardinessValue();
                    result = checked;//.makeCopy();
                }

            }
        }
    }

    tabooList->insert({bestop.getKey(), bestop});
    tabooList->insert({bestrop.getKey(), bestrop});
    return result;
}

Solution FirstNeighbourhoodGenerationStrategy::highCandidateStrategy(Solution current_solution,
                                                                     std::unordered_map<std::string, Operation> *tabooList,
                                                                     Solution current_best, size_t aspiration_plus_size,
                                                                     size_t tardy_machine_index,
                                                                     size_t early_machine_index) {
    unsigned long aspiration_value = current_best.tardinessValue();
    unsigned long current_best_value = current_solution.tardinessValue()*10000;
    Solution result = current_solution;//.makeCopy();
    Operation bestop = Operation();
    Operation bestrop = Operation();

    for(size_t tardy_index = 0; tardy_index < current_solution.machines[tardy_machine_index].tasks.size(); tardy_index++) {
        Solution partial = current_solution;//.makeCopy();
        partial.eraseTask(tardy_machine_index, tardy_index);

        for(size_t early_index=0; early_index <= partial.machines[early_machine_index].tasks.size(); early_index++) {
            Solution checked = partial;//.makeCopy();
            checked.insertTask(early_machine_index, early_index, current_solution.machines[tardy_machine_index].tasks[tardy_index]);

            long tardy_task_id = (long)current_solution.machines[tardy_machine_index].tasks[tardy_index].id;
            long early_task_id = (long)partial.machines[early_machine_index].tasks[early_index].id;

            Operation op = Operation(InsertOperation, tardy_machine_index, tardy_task_id, early_index, early_task_id, this->operation_tenure);
            Operation rop = Operation(InsertOperation, early_index, early_task_id, tardy_machine_index, tardy_task_id, this->operation_tenure);

            if(checked.tardinessValue() < current_best_value && tabooList->count(op.getKey()) == 0) {

                current_best_value = checked.tardinessValue();
                result = checked;//.makeCopy();
                bestop = op;
                bestrop = rop;
            }
            else if (checked.tardinessValue() < aspiration_value && tabooList->count(op.getKey()) != 0) {
                /**
                * aspiration -> operation in taboo list but better than global best
                */
                std::cout<<"Aspiration"<<std::endl;
                current_best_value = checked.tardinessValue();
                result = checked;//.makeCopy();
            }
        }
    }

    tabooList->insert({bestop.getKey(), bestop});
    tabooList->insert({bestrop.getKey(), bestrop});
    return result;
}

Solution FirstNeighbourhoodGenerationStrategy::findBestNeighbour(Solution current_solution, std::unordered_map<std::string, Operation> * tabooList, Solution current_best, size_t aspiration_plus_size) {

    unsigned long max_tardiness = 0;
    size_t t_index = 0;
    unsigned long max_earliness = 0;
    size_t e_index = 0;

    for(size_t i=0; i < current_solution.machines.size(); i++){
        unsigned long current_earliness = current_solution.machines[i].earliness;
        unsigned long current_tardiness = current_solution.machines[i].tardiness;
        if (current_earliness > max_earliness) {
            max_earliness = current_earliness;
            e_index = i;
        }
        if (current_tardiness > max_tardiness) {
            max_tardiness = current_tardiness;
            t_index = i;
        }
    }

    Solution result = Solution();

    if(t_index == e_index) {
        result = lowCandidateStrategy(current_solution, tabooList, current_best, aspiration_plus_size, t_index);
    } else {
        result = highCandidateStrategy(current_solution, tabooList, current_best, aspiration_plus_size, t_index, e_index);
        if(result.tardinessValue() == current_solution.tardinessValue()) {
            result = lowCandidateStrategy(current_solution, tabooList, current_best, aspiration_plus_size, t_index);
        }
    }


//    std::cout<<t_index<<"\t"<<e_index<<"\t"<<result.tardinessValue()<<std::endl;
//    result.print();

    return result;
}
