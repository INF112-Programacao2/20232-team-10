#ifndef V_DICE
#define V_DICE

#include <random>

class Dice{
    public:
        static int single_die(int range); 
        static int dice(int range, int quant=1, char mode='+');
        static std::random_device rng;
};
#endif