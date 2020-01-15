#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include <queue>

#include "Task.h"
#include "Machine.h"
#include "tabu/Solution.h"
#include "tabu/generation/BaseInitialGenerationStrategy.h"
#include "tabu/generation/EDDInitialGenerationStrategy.h"
#include "tabu/generation/ERTInitialGenerationStrategy.h"
#include "tabu/generation/MyInitialGenerationStrategy.h"
#include "tabu/generation/WoodpeckerInitialGenerationStrategy.h"
#include "tabu/generation/ImprovedInitialGenerationStrategy.h"
#include "tabu/generation/JustInTimeInitialGenerationStrategy.h"
#include "tabu/generation/BestOfTwoGenerationStrategy.h"
#include "tabu/neighbourhood/BaseNeighbourhoodGenerationStrategy.h"
#include "tabu/neighbourhood/FirstNeighbourhoodGenerationStrategy.h"
#include "tabu/TabooSolver.h"

//constants
const unsigned long P = 4;

std::vector<Task>& readInstance(const char* filepath){
    std::ifstream inStream;
    inStream.open(filepath);
    auto result = new std::vector<Task>();

    unsigned long N;
    inStream>>N;
    unsigned long p, r, d;
    for (unsigned long i=0; i<N; i++){
        inStream>>p>>r>>d;
        result->emplace_back(Task(i+1,r,p,d));
    }

    inStream.close();

    return *result;
}


/**
 * Initial algorithm - sort by earliest ready date, choose first free machine
 * @param instance
 * @return
 */
std::vector<Machine>& initial(std::vector<Task> instance) {
    sort(instance.begin(), instance.end(), [](const Task& lhs, const Task& rhs){
        return lhs.ready < rhs.ready || (lhs.ready == rhs.ready && lhs.due < rhs.due);
    });

    auto machines = new std::priority_queue<Machine,std::vector<Machine>, std::greater<> >();
    for(int i=0; i<P; i++){
        machines->emplace(Machine());
    }

    for(auto t: instance) {
        Machine m = machines->top();
        machines->pop();
        m.addTask(t);
        machines->push(m);
    }

    auto result =  new std::vector<Machine>();

    while(!machines->empty()){
        result->push_back(machines->top());
        machines->pop();
    }

    return *result;
}


void saveResult(std::vector<Machine>& result, char* filepath){
    unsigned long total_delay = 0;
    unsigned long instance_size = 0;
    for(auto & i : result){
        total_delay += i.calculateTardiness();
        instance_size += i.tasks.size();
    }

    std::ofstream out;
    out.open(filepath);
    out<<total_delay<<std::endl;

    for(auto & i : result){
        i.save(out);
    }

    out.close();
}

void resultValidator(const std::vector<Task>& instance, std::vector<Machine> & result) {

    int size = instance.size();

    bool * used = new bool[size];

    for(size_t i = 0; i < size; i++) {
        used[i] = false;
    }

    int machine_tasks = 0;
    for(const auto& m : result) {
        for(auto t: m.tasks) {
            machine_tasks++;
            if(t.id <= size && t.id > 0) {
                used[t.id-1] = true;
                if(instance[t.id-1].processing != t.processing || instance[t.id-1].ready != t.ready || instance[t.id-1].due != t.due) {
                    std::cout<<"Changed task params id "<<t.id<<std::endl;
                }
            }
            else {
                std::cout<<"Invalid task id "<<t.id<<std::endl;
            }
        }
    }

    if(machine_tasks != size) {
        std::cout<<"invalid number of tasks"<<std::endl;
    }

    for(size_t i=0; i< size; i++){
        if(!used[i]){
            std::cout<<"Task: "<<i+1<<" not used"<<std::endl;
        }
    }

    std::cout<<"Clearing"<<std::endl;
    delete[] used;
    std::cout<<"Done"<<std::endl;
}

int main(int argc, char **argv) {

    if(argc < 3){
        std::cout<<"No arguments given"<<std::endl;
        std::cout<<"Provide filenames"<<std::endl;
        return 1;
    }


    char* input_filepath = argv[1];
    char* output_filepath = argv[2];

    BaseInitialGenerationStrategy *generationStrategy = new BestOfTwoGenerationStrategy(new WoodpeckerInitialGenerationStrategy(), new JustInTimeInitialGenerationStrategy());
//    BaseInitialGenerationStrategy *generationStrategy = new WoodpeckerInitialGenerationStrategy();
    BaseNeighbourhoodGenerationStrategy *neighbourhoodStrategy = new FirstNeighbourhoodGenerationStrategy();

    TabooSolver tabooSolver = TabooSolver();
    tabooSolver.setGenerationStrategy(generationStrategy);
    tabooSolver.setNeighbourhoodGenerationStrategy(neighbourhoodStrategy);


    std::vector<Task> instance = readInstance(input_filepath);

//    std::vector<Machine> result = generationStrategy->generateSolution(instance).result();
    std::vector<Machine> result = tabooSolver.solve(instance).result();
    resultValidator(instance, result);
    saveResult(result, output_filepath);

    return 0;
}