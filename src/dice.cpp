#include "../include/dice.h"

std::random_device Dice::rng;
std::mt19937 gen(Dice::rng());

int Dice::single_die(int range){
    std::uniform_int_distribution<std::mt19937::result_type> d(1, range);
    return d(rng);
}

int Dice::dice(int range, int quant, char mode){
    int result = 0;
    if (mode == '<'){
        result = INT32_MAX;
    }
    int d;
    for (int i = 0; i < quant; i++){
        d = single_die(range);
        if (mode == '+'){
            result += d;
        }
        else if (mode == '>'){
            if (result < d){
                result = d;
            }
        }
        else if (mode == '<'){
            if (result > d){
                result = d;
            }
        }
    }
    return result;
}
