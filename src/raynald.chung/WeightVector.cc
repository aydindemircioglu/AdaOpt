//=============================================================================
// File Name: WeightVector.cc
// implements the methods of the WeightVector class
//=============================================================================

#include "include/WeightVector.h"


//--------------------------------------------------------------------------
double operator* (simple_sparse_vector& u, WeightVector& v) {
    double outcome = 0.0;
    for( simple_sparse_vector_iterator it = u.my_vec.begin(); 
            it != u.my_vec.end(); it++) {
        outcome += ((*it).second * v[(*it).first]);
    }
    return outcome;
}

//-----------------------------------------------------------------------------
double operator* (WeightVector& v, simple_sparse_vector& u) {
    return (u*v);
}


