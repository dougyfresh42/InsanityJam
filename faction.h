// File: faction.h 
// 
// Version: 
//     $Id$ 
// 
// faction.h TODO_DOCS_
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef FACTION_H
#define FACTION_H

// add include files only if needed for these declarations.
#include "demographic.h"

/// @author ddm9373: ddm9373 Douglas Moyer 
///
class faction {
    public:
        faction(demographic *demos, int num_demo);
        ~faction();
        faction(const faction& that);
        faction& operator=(const faction& that);
        demographic demo(int index);
        void update_happiness(int issue, int severity, bool positive); 
        float happiness();
        float loyalty();
        int population_size();
    private:
        demographic *pop_demo_;
        int num_demo_;
        int population_size_;
        float happiness_;
        float loyalty_;
};

#endif // FACTION_H

// // // // // // // // // // // // // // // // // // // // // // // // 
// 
// Revisions: 
//     $Log$ 
// 
