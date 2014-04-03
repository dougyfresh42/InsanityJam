// 
// File: faction.cpp 
// 
// 
// 
// @author ddm9373: Douglas Moyer
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <math.h>
#include "faction.h"
#include "demographic.h"

faction::faction(demographic *demos, int num_demo){
    pop_demo_ = demos;
    num_demo_ = num_demo;
    happiness_ = 50;
}

//faction::~faction() { delete[] pop_demo_; }
faction::~faction() {
    //for(int i = 0; i < num_demo_; i++) {
        //demographic newd;
        //pop_demo_[i] = newd;
    //}
    delete[] pop_demo_;
}

faction::faction(const faction& that) {
    pop_demo_ = new demographic[that.num_demo_];
    num_demo_ = that.num_demo_;
    for(int i = 0; i < num_demo_; i++)
        pop_demo_[i] = that.pop_demo_[i];
    happiness_ = that.happiness_;
    population_size_ = that.population_size_;
    loyalty_ = that.loyalty_;
}

faction& faction::operator=(const faction& that) {
    if(this != &that) {
        delete[] pop_demo_;
        pop_demo_ = new demographic[that.num_demo_];
        num_demo_ = that.num_demo_;
        for(int i = 0; i < num_demo_; i++)
            pop_demo_[i] = that.pop_demo_[i];
        happiness_ = that.happiness_;
        population_size_ = that.population_size_;
        loyalty_ = that.loyalty_;
    }
    return *this;
}

demographic faction::demo(int index) { return pop_demo_[index]; }

float faction::happiness() { return happiness_; }

float faction::loyalty() { return loyalty_; }

int faction::population_size() { return population_size_; }

void faction::update_happiness(int issue, int severity, bool positive) {
    for(int i = 0; i < num_demo_; i++) 
        happiness_ += (positive ? (1) : (-1)) * (pop_demo_[i].stance(issue) - .5)*pow(2, severity);
}

// // // // // // // // // // // // // // // // // // // // // // // // 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
