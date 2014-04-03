// File: demographic.h 
// 
// Version: 
//     $Id$ 
// 
// demographic.h TODO_DOCS_
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef DEMOGRAPHIC_H
#define DEMOGRAPHIC_H

// add include files only if needed for these declarations.
#include <string>

using namespace std;
/// @author ddm9373: ddm9373 Douglas Moyer 
///
class demographic {
    public:
        demographic();
        ~demographic();
        demographic(const demographic& that);
        demographic& operator=(const demographic& that);
        float stance(int index);
        string name();
        void set_demographic(int num_issues, string line);
    private:
        string name_;
        float* stance_;
        int num_issues_;
};

#endif // DEMOGRAPHIC_H

// // // // // // // // // // // // // // // // // // // // // // // // 
// 
// Revisions: 
//     $Log$ 
// 
