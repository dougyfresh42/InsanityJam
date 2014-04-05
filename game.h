// File: game.h 
// 
// Version: 
//     $Id$ 
// 
// game.h TODO_DOCS_
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef GAME_H
#define GAME_H

// add include files only if needed for these declarations.
#include <string>
#include <vector>
#include "demographic.h"
#include "faction.h"

using namespace std;

/// @author ddm9373: ddm9373 Douglas Moyer 
///
enum state {
    INTERNAL,
    INTERNATIONAL,
    UPDATE_MESSAGE,
    LOST
};

class game {
    public:
        game();
        ~game();
        vector<faction> *factions();
        int num_issues();
        string* issues();
        int num_categories();
        string* categories();
        void get_message(string* return_value);
        void response(int a);
        bool running();
        int num_nat_issues();
        string* nat_issues();
        float* nat_issue_scores();
    private:
        enum state state_;

        bool running_;
        int current_issue_;
        int current_severity_;
        string *issues_;
        string *categories_;
        string **messages_;
        int *num_messages_;
        int **severities_;
        demographic **population_;
        vector<faction> factions_;
        //faction* factions_;
        //int num_demo_;
        int num_issues_;
        int num_categories_;
        int *demo_per_cat_;
        void open_issues();
        void open_demographics();
        void init_messages();
        void add_faction();
        void init_nation();

        int num_nat_issues_;
        string* nat_issues_;
        int** nat_issue_demo_;
        float* nat_issue_scores_;
        string** nat_messages_;
        int* num_nat_messages_;

        bool check_lost(string* return_value);
        bool nat_issue(string* return_value);
};

#endif // GAME_H

// // // // // // // // // // // // // // // // // // // // // // // // 
// 
// Revisions: 
//     $Log$ 
// 
