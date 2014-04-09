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


//Different OS, different slash
#ifdef _WIN64
    const string prefix = "config\\";
#elif _WIN32
    const string prefix = "config\\";
#else
    const string prefix = "config/";
#endif

//commented
game::game(){
    //init srand to actually be random (pseudo)
    srand(time(NULL));
    //begin the game
    running_ = true;
    //opens all of the available controversial issues (ironically I don't think I ever use them)
    open_issues();
    //opens all of the available demographics, and how they feel about issues
    open_demographics();
    //reads in all of the available messages and severities for different issues
    init_messages();
    //initializes "major" issues and factors affecting them
    init_nation();
    //adds the first faction
    add_faction();
    state_ = INTERNAL;
}

//commented
game::~game(){
    //cleans up (hopefully) everything I created dynamically
    delete[] issues_;
    delete[] categories_;
    for(int i = 0; i < num_categories_; i++) 
        delete[] population_[i];
    delete[] population_;
    delete[] demo_per_cat_;
    for(int i = 0; i < num_issues_; i++){
        delete[] messages_[i];
        delete[] severities_[i];
    }
    delete[] messages_;
    delete[] severities_;
    delete[] num_messages_;

    delete[] nat_issues_;
    for(int i = 0 ; i < num_nat_issues_; i++) {
        delete[] nat_issue_demo_[i];
        delete[] nat_messages_[i];
    }
    delete[] nat_issue_demo_;
    delete[] nat_messages_;
    delete[] nat_issue_scores_;
    delete[] num_nat_messages_;
}

//commented
void game::open_issues() {
    //creates a new input stream from the issues file
    ifstream issue_f;
    string path = prefix;
    path.append("issues.txt");
    issue_f.open(path.c_str());
    if(issue_f.is_open()) {
        string getln;
        getline(issue_f, getln);
        //the first line is the number of issues
        num_issues_ = atoi(getln.c_str());
        issues_ = new string[num_issues_];
        for(int i = 0; i < num_issues_; i++)
            getline(issue_f, issues_[i]);
    }
    //if it don't work, don't start the game
    else running_ = false;
    issue_f.close();
}

//commented
//honestly the parsing isn't terribly advanced so I didn't comment too much
//can elaborate if asked
void game::open_demographics() {
    ifstream demo_f;
    string path = prefix;
    path.append("demographics.txt");
    demo_f.open(path.c_str());
    if(demo_f.is_open()) {
        string getln;
        getline(demo_f, getln);
        //how many different demographic categories there are
        num_categories_ = atoi(getln.c_str());
        
        population_ = new demographic*[num_categories_];
        //need to know how many demographics are in each category
        demo_per_cat_ = new int[num_categories_];
        //what the categories are
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
    else running_ = false;
    demo_f.close();
}

//commented
//same thing, its just a bunch of getlines and arrays
void game::init_messages() {
    messages_ = new string*[num_issues_];
    severities_ = new int*[num_issues_];
    num_messages_ = new int[num_issues_];
    for(int i = 0; i < num_issues_; i++) {
        ifstream temp;
        string path = prefix;
        #ifdef WINDOWS
        path.append("issues\\");
        #else
        path.append("issues/");
        #endif
        path.append(issues_[i]);
        path.append(".txt");
        temp.open(path.c_str());
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
}

//more parsing
void game::init_nation() {
    ifstream national_f;
    string path = prefix;
    path.append("international.txt");
    national_f.open(path.c_str());
    if(national_f.is_open()) {
        string getln;
        getline(national_f, getln);
        num_nat_issues_ = atoi(getln.c_str());

        nat_issues_ = new string[num_nat_issues_];
        nat_issue_demo_ = new int*[num_nat_issues_];
        nat_issue_scores_ = new float[num_nat_issues_];
        for(int i = 0; i < num_nat_issues_; i++) {
            getline(national_f, getln);
            string piece;
            stringstream ss(getln);
            ss >> piece;
            nat_issues_[i] = piece;
            nat_issue_scores_[i] = 5;
            nat_issue_demo_[i] = new int[num_issues_];
            for(int j = 0; j < num_issues_; j++) {
                ss >> piece;
                nat_issue_demo_[i][j] = atoi(piece.c_str());
            }
        }
    }
    national_f.close();
    nat_messages_ = new string*[num_nat_issues_];
    num_nat_messages_ = new int[num_nat_issues_];
    for(int i = 0; i < num_nat_issues_; i++) {
        path = prefix;
	#ifdef WINDOWS
	path.append("international\\");
	#else
        path.append("international/");
	#endif
        path.append(nat_issues_[i]);
        path.append(".txt");
        national_f.open(path.c_str());
        if(national_f.is_open()) {
            string getln;
            getline(national_f, getln);
            num_nat_messages_[i] = atoi(getln.c_str());
            nat_messages_[i] = new string[num_nat_messages_[i]];
            for(int j = 0; j < num_nat_messages_[i]; j++) {
                getline(national_f, getln);
                nat_messages_[i][j] = getln;
            }
        }
        national_f.close();
    }
}

//GETTERS
vector<faction>* game::factions() { return &factions_; }

int game::num_issues() { return num_issues_; }

int game::num_nat_issues() { return num_nat_issues_; }

string* game::nat_issues(){ return nat_issues_;}

float* game::nat_issue_scores() { return nat_issue_scores_; }

string* game::issues() { return issues_; }

int game::num_categories() { return num_categories_; }

string* game::categories() { return categories_; }
//END GETTERS

//commented
void game::get_message(string *return_value) {
    bool cont = true;
    //if the game was lost
    if(check_lost(return_value)) cont = false;
    if(cont && nat_issue(return_value)) cont = false;
    if(cont) {
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
}

bool game::check_lost(string* return_value) {
    bool lost = true;
    for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++) {
        if(it->population_size() > 0) lost =false;
        if(it->happiness() < 30) {
            return_value[1] = "Return";
            return_value[2] = "Exit";
            return_value[0] = "A faction has revolted, Game Over";
            state_ = LOST;
            running_ = false;
        }
    }
    if(lost) {
        return_value[1] = "Return";
        return_value[2] = "Exit";
        return_value[0] = "Sorry, ya lost.";
        state_ = LOST;
        running_ = false;
    }
    return lost;
}

bool game::nat_issue(string *return_value) {
    for(int i = 0; i < num_nat_issues_; i++) {
        for(int j = 0; j < num_nat_messages_[i]; j++) {
            stringstream ss(nat_messages_[i][j]);
            string min, max;
            ss >> min; ss >> max;
            if(nat_issue_scores_[i] < atoi(min.c_str()) || nat_issue_scores_[i] > atoi(max.c_str())) {
                if(rand() % 100 < (10 / num_nat_messages_[i])) {
                    float happiness, population;
                    string temp;
                    ss >> temp;
                    happiness = atof(temp.c_str());
                    ss >> temp;
                    population = atof(temp.c_str());
                    int factionn;
                    ss >> temp;
                    factionn = atoi(temp.c_str());
                    if(factionn == 0);
                    else if(factionn < 0) factions_.pop_back();
                    else add_faction();
                    for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++){
                        it->add_happiness(happiness);
                        it->mul_population(population);
                    }
                    ss >> temp;
                    return_value[0] = temp;
                    while (ss >> temp) return_value[0] += " " + temp;
                    return_value[1] = "Accept";
                    return_value[2] = "OK";
                    state_ = INTERNATIONAL;
                    return true;
                }
            }
        }
    }
    return false;
}

void game::response(int a) {
    if(a == 1) {
        if(state_ == INTERNAL) {
            for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++)
                it->update_happiness(current_issue_, current_severity_, true);
            for(int i = 0; i < num_nat_issues_; i++) {
                int cur = nat_issue_scores_[i];
                nat_issue_scores_[i] += nat_issue_demo_[i][current_issue_] /
                    (-400.0 / (cur * (cur - 10)) - 15);
            }
        } else if (state_ == LOST) running_ = false;
        else state_ = INTERNAL;
    }
    if(a == 2) {
        if(state_ == INTERNAL) {
            for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++)
                it->update_happiness(current_issue_, current_severity_, false);
            for(int i = 0; i < num_nat_issues_; i++) {
                int cur = nat_issue_scores_[i];
                nat_issue_scores_[i] -= nat_issue_demo_[i][current_issue_] /
                    (-400.0 / (cur * (cur - 10)) - 15);
            }
        } else if (state_ == LOST) running_ = false;
        else state_ = INTERNAL;
    }
    if(a == 13) running_ = false; 
    float total_happiness = 0;
    for(vector<faction>::iterator it = factions_.begin(); it != factions_.end(); it++)
        total_happiness += it->happiness();
    if(total_happiness/factions_.size() > 70) add_faction();
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
