#include <iostream>
#include <vector>
#include <algorithm>

#include <queue>

#include "Task.h"
#include "Machine.h"

/*
 * Test 10
 * Poświęcanie od 80%
 * Długie zadania od 20 jednostek
 * Kara * 2 za wyprzedenie
 */

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

std::vector<Machine>& algorithm2(std::vector<Task> instance) {
    auto machines = new std::vector<Machine>();
    for(int i=0; i<P; i++){
        machines->emplace_back(Machine());
    }

    auto sacrificed = std::vector<Task>();

    std::sort(instance.begin(), instance.end());

    for (Task t: instance){
        unsigned long machine_min_criteria = t.criteria_machine(machines->at(0).when_ready);
        unsigned long machine_index = 0;
        for(int i=1; i<P; i++){
            unsigned long criteria = t.criteria_machine(machines->at(i).when_ready);
            if(machine_min_criteria > criteria) {
                machine_min_criteria = criteria;
                machine_index = i;
            }
        }

        // kryterium poświęcania
        // całe zadanie nie wykona się w czasie
        //if (machines->at(machine_index).when_ready >= t.due && t.processing > 20) {

        // parametryzowane po procencie długości zadania, które nie wykona się w czasie
        unsigned long when_ready = machines->at(machine_index).when_ready;
        long started = std::max(when_ready, t.ready);
        long late = std::max(0L, (long)started + (long)t.processing - (long)t.due);
        double ratio = double(late)/double(t.processing);

        if (ratio > 0.8 && t.processing > 20) {
            sacrificed.push_back(t);
            continue;
        }

        machines->at(machine_index).addTask(t);
    }

    for (Task t: sacrificed){
        unsigned long machine_min_criteria = t.criteria_machine(machines->at(0).when_ready);
        unsigned long machine_index = 0;
        for(int i=1; i<P; i++){
            unsigned long criteria = t.criteria_machine(machines->at(i).when_ready);
            if(machine_min_criteria > criteria) {
                machine_min_criteria = criteria;
                machine_index = i;
            }
        }

        machines->at(machine_index).addTask(t);
    }

    return *machines;
}

std::vector<Machine>& algorithm(std::vector<Task> instance){
    auto machines = new std::priority_queue<Machine, std::vector<Machine>, std::greater<Machine> >();
    for(int i=0; i<P; i++){
        machines->emplace(Machine());
    }

    // finalne szeregowanie po spóźnieniu
    while(!instance.empty()){
        Machine current = machines->top();
        machines->pop();

        unsigned long min_criteria = instance[0].criteria(current.when_ready);
        unsigned long min_criteria_index = 0;

        for(unsigned long i=1; i<instance.size(); i++){
            //long criteria_value = instance[i].criteria(current.when_ready);
            long criteria_value = (long)instance[i].due + (long)instance[i].processing/2;
            if(min_criteria > criteria_value){
                min_criteria = criteria_value;
                min_criteria_index = i;
            }
        }

        current.addTask(instance[min_criteria_index]);
        instance.erase(instance.begin() + min_criteria_index);

        machines->push(current);
    }


    //rewrite priority queue to vector
    auto result_vec = new std::vector<Machine>();

    while(!machines->empty()){
        result_vec->push_back(machines->top());
        machines->pop();
    }

    return *result_vec;
}

void saveResult(std::vector<Machine>& result, char* filepath){
    unsigned long total_delay = 0;
    unsigned long instance_size = 0;
    for(auto & i : result){
        total_delay += i.calculateTotalDelay();
        instance_size += i.tasks->size();
    }

    //std::string output_path = "./output/wt/l"+std::to_string(instance_size)+".txt";

    std::ofstream out;
//    out.open(output_path.c_str());
    out.open(filepath);
    out<<total_delay<<std::endl;

    for(auto & i : result){
        i.save(out);
    }

    out.close();
}

int main(int argc, char **argv) {

    if(argc < 3){
        std::cout<<"No arguments given"<<std::endl;
        std::cout<<"Provide filenames"<<std::endl;
        return 0;
    }


    char* input_filepath = argv[1];
    char* output_filepath = argv[2];

    std::vector<Task> instance = readInstance(input_filepath);
    //std::vector<Machine> result = algorithm(instance);
    std::vector<Machine> result = algorithm2(instance);
    saveResult(result, output_filepath);

    return 0;
}