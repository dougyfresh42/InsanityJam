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
#include <sstream>
#include "game.h"

using namespace std;

string int2string(int a) {
    ostringstream ss;
    ss << a;
    return ss.str();
}

string float2string(float a) {
    ostringstream ss;
    ss.precision(3);
    ss << a;
    return ss.str();
}

int main( int argc, const char* argv[] ) {
    game run_game;
    vector<faction>* factions = run_game.factions();
    //int num_issues = run_game.num_issues();
    //string* issues = run_game.issues();
    int num_categories = run_game.num_categories();
    string* categories = run_game.categories();
    int num_national_issues = run_game.num_nat_issues();
    string* national_issues = run_game.nat_issues();
    float* nat_issues_score = run_game.nat_issue_scores();
    int total_categories = (num_categories > num_national_issues ? num_categories : num_national_issues);
    while(run_game.running()) {
        int x = 1;
        char input;
/*        cout << "National Issues:\n";
        for(int i = 0; i < num_national_issues; i++)
            cout << national_issues[i] << ": " << nat_issues_score[i] << "\n";
        for(vector<faction>::iterator it = factions->begin(); it != factions->end(); it++) {
            cout << "Faction " << x++ << ": Happiness: " << it->happiness() << "\n";
            for(int i = 0; i < num_categories; i++) {
                cout << setw(10) << left << categories[i] << "\t";
                cout << it->demo(i).name() << "\t";
                cout << "\n";
            }
        }
        cout << "\n";*/
        
        string display[factions->size() + 1][total_categories + 2];
        display[0][0] = "Major Issues";
        for(int i = 1; i <= total_categories; i++)
            display[0][i] = (i <= num_national_issues ? national_issues[i-1] + ": " + float2string(nat_issues_score[i-1]) : "");
        display[0][total_categories] = "Population: ";
        display[0][total_categories+1] = "Happiness: ";
        for(int i = 1; i <= factions->size(); i++) {
            display[i][0] = "Faction: ";
            display[i][0].append(int2string(i));
            for(int j = 1; j <= total_categories; j++)
                display[i][j] = (j <= num_categories ? (*factions)[i-1].demo(j-1).name() : "");
            display[i][total_categories] = int2string((*factions)[i-1].population_size());
            display[i][total_categories+1] = float2string((*factions)[i-1].happiness()); 
        }
        for(int i = 0; i < total_categories + 2; i++) {
            for(int j = 0; j < factions->size() + 1; j++)
                cout << setw(18) << left << display[j][i];
            cout << "\n";
        }
        string message[3];
        run_game.get_message(message);
        cout << message[0] << "\n(1) " << message[1] << "\t(2) " << message[2] << "\t or [Q]uit\n";
        bool correct_input = true;
        do {
            if(!correct_input) cout <<"Wrong input, please try again\n";
            correct_input = true;
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
