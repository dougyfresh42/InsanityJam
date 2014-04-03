// 
// File: main.cpp 
// 
// 
// 
// @author ddm9373: Douglas Moyer
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <iostream>
#include <iomanip>
#include "game.h"

using namespace std;

int main( int argc, const char* argv[] ) {
    game run_game;
    vector<faction>* factions = run_game.factions();
    //int num_issues = run_game.num_issues();
    //string* issues = run_game.issues();
    int num_categories = run_game.num_categories();
    string* categories = run_game.categories();
    while(run_game.running()) {
        int x = 1;
        char input;
        for(vector<faction>::iterator it = factions->begin(); it != factions->end(); it++) {
            cout << "Faction " << x++ << ": Happiness: " << it->happiness() << "\n";
            for(int i = 0; i < num_categories; i++) {
                cout << setw(10) << left << categories[i] << "\t";
                cout << it->demo(i).name() << "\t";
                cout << "\n";
            }
        }
        cout << "\n";
        string message[3];
        run_game.get_message(message);
        cout << message[0] << "\n(1) " << message[1] << "\t(2) " << message[2] << "\t or [Q]uit\n";
        bool correct_input = true;
        do {
            if(!correct_input) cout <<"Wrong input, please try again\n";
            string buff;
            cin >> buff;
            input = buff[0];
            switch(input) {
                case '1':
                    run_game.response(1);
                    break;
                case '2':
                    run_game.response(2);
                    break;
                case 'q':
                    run_game.response(13);
                    break;
                default:
                    correct_input = false;
                    break;
            }
        } while(!correct_input);
    }
    return 0;
}

// // // // // // // // // // // // // // // // // // // // // // // // 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
