#pragma once
#include <random>
class Randor {
    std::random_device rd;
    std::mt19937 gen;
    int max_val;
public:
    Randor() : gen(rd()), max_val(0) {}
    void setX(int x) { 
        max_val = x; 
    }
    
    int getRandom() { 
        std::uniform_int_distribution<> distrib(0, max_val);
        return distrib(gen);
    }
};
