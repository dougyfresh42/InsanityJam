// 
// File: demographic.cpp 
// 
// 
// 
// @author ddm9373: Douglas Moyer
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include "demographic.h"
#include <string>
#include <sstream>
#include <stdlib.h>

demographic::demographic() {
    stance_ = new float[1];
}

demographic::~demographic() {if (stance_) delete[] stance_; stance_ = NULL;}

demographic::demographic(const demographic& that) {
    stance_ = new float[that.num_issues_];
    num_issues_ = that.num_issues_;
    name_ = that.name_;
    for(int i = 0; i < num_issues_; i++)
        stance_[i] = that.stance_[i];
}

demographic& demographic::operator=(const demographic& that) {
    if(this != &that) {
        delete[] stance_;
        stance_ = new float[that.num_issues_];
        num_issues_ = that.num_issues_;
        name_ = that.name_;
        for(int i = 0; i < num_issues_; i++)
            stance_[i] = that.stance_[i];
    }
    return *this;
}

void demographic::set_demographic(int num_issues, string line) {
    num_issues_ = num_issues;
    delete[] stance_;
    stance_ = new float[num_issues];
    stringstream ss(line);
    ss >> name_;
    string buff;
    for(int i = 0; i < num_issues; i++) {
        ss >> buff;
        stance_[i] = atof(buff.c_str());
    }

}

float demographic::stance(int index) { return stance_[index]; }

string demographic::name() { return name_; }


// // // // // // // // // // // // // // // // // // // // // // // // 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
