// 
// File: game.cpp 
// 
// 
// 
// @author ddm9373: Douglas Moyer
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "game.h"

game::game(){
    srand(time(NULL));
    open_issues();
    open_demographics();
    init_messages();
    add_faction();
    running_ = true;
}

game::~game(){
    delete[] issues_;
    delete[] categories_;
    for(int i = 0; i < num_categories_; i++) 
        delete[] population_[i];
    delete[] population_;
    delete[] demo_per_cat_;
    //delete factions_;
    for(int i = 0; i < num_issues_; i++){
        delete[] messages_[i];
        delete[] severities_[i];
    }
    delete[] messages_;
    delete[] severities_;
    delete[] num_messages_;
}

void game::open_issues() {
    ifstream issue_f;
    issue_f.open("issues.txt");
    if(issue_f.is_open()) {
        string getln;
        getline(issue_f, getln);
        num_issues_ = atoi(getln.c_str());

        issues_ = new string[num_issues_];
        for(int i = 0; i < num_issues_; i++)
            getline(issue_f, issues_[i]);
    }
    issue_f.close();
}

void game::open_demographics() {
    ifstream demo_f;
    demo_f.open("demographics.txt");
    if(demo_f.is_open()) {
        string getln;
        getline(demo_f, getln);
        num_categories_ = atoi(getln.c_str());
        
        population_ = new demographic*[num_categories_];
        demo_per_cat_ = new int[num_categories_];
        categories_ = new string[num_categories_];
        
        string buff;
        for(int i = 0; i < num_categories_; i++) {
            getline(demo_f, getln);
            stringstream ss(getln);
            ss >> categories_[i];
            ss >> buff;
            demo_per_cat_[i] = atoi(buff.c_str());
            population_[i] = new demographic[demo_per_cat_[i]];
            for(int j = 0; j < demo_per_cat_[i]; j++) {
                getline(demo_f, getln);
                population_[i][j].set_demographic(num_issues_, getln);
            }
        }
    }
    demo_f.close();
}

void game::init_messages() {
    messages_ = new string*[num_issues_];
    severities_ = new int*[num_issues_];
    num_messages_ = new int[num_issues_];
    for(int i = 0; i < num_issues_; i++) {
        ifstream temp;
        temp.open((issues_[i] + ".txt").c_str());
        if(temp.is_open()) {
            string getln;
            getline(temp, getln);
            num_messages_[i] = atoi(getln.c_str());
            messages_[i] = new string[num_messages_[i]];
            severities_[i] = new int[num_messages_[i]];
            int curr_severity;
            for(int j = 0; j < num_messages_[i]; j++) {
                getline(temp, getln);
                if(atoi(getln.c_str()) != 0) {
                    curr_severity = atoi(getln.c_str());
                    getline(temp, getln);
                }
                messages_[i][j] = getln;
                severities_[i][j] = curr_severity;
            }
        }
    }
    //for(int i = 0; i < num_issues_; i++)
        //for(int j = 0; j < num_messages_[i]; j++)
            //cout << messages_[i][j] << "\n";
}

vector<faction>* game::factions() { return &factions_; }

int game::num_issues() { return num_issues_; }

string* game::issues() { return issues_; }

int game::num_categories() { return num_categories_; }

string* game::categories() { return categories_; }

void game::get_message(string *return_value) {
    current_issue_ = rand() % num_issues_;
    int message = rand() % num_messages_[current_issue_];
    current_severity_ = severities_[current_issue_][message];
    stringstream ss(messages_[current_issue_][message]);
    ss >> return_value[1];
    ss >> return_value[2];
    string ccat;
    ss >> return_value[0];
    while(ss >> ccat) return_value[0] += " " + ccat;
}

void game::response(int a) {
    if(a == 1) {
        //for(int i = 0; i < num_categories_; i++) {
            //demographic temp = factions_.front().demo(i);
            //cout << "As " << temp.name() << "s we " << ((temp.stance(current_issue_) >= .5) ? "Approve" : "Disapprove") << " of your decision.\n";
        //}
        for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++)
            it->update_happiness(current_issue_, current_severity_, true);
    }
    if(a == 2) {
        for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++)
            it->update_happiness(current_issue_, current_severity_, false);
    }
    if(a == 13) running_ = false; 
}

bool game::running() { return running_; }

void game::add_faction() {
    demographic* randomd = new demographic[num_categories_];
    for(int i = 0; i < num_categories_; i++) {
        randomd[i] = population_[i][rand() % (demo_per_cat_[i])];
    }
    //factions_ = new faction(randomd, num_categories_);
    factions_.push_back(faction(randomd, num_categories_));
}
// // // // // // // // // // // // // // // // // // // // // // // // 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
