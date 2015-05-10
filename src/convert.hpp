

#include "raynald.chung/include/cmd_line.h"
#include "raynald.chung/include/simple_sparse_vec_hash.h"
#include "raynald.chung/include/optimize.h"

#include <sstream>

#include <Rcpp.h>
using namespace Rcpp;



void convertData (NumericMatrix X, NumericVector Y, 
		std::vector<simple_sparse_vector> &Dataset,
		std::vector<int> &Labels,
		uint &dimension)
{
	
	for (size_t i = 0; i < X.nrow(); i++) {
		// find non-null rows and create a string from it
		std::stringstream tmp;
		int n = 0;
		for (size_t j = 0; j < X.ncol(); j++) {
			if (X(i,j) != 0) {
				tmp << j << " " << X(i,j) << " ";
				n++;
			}
		}
		
		std::istringstream is (tmp.str());
		simple_sparse_vector instance(is, n);
		Dataset.push_back(instance);
	}
		
	// TODO: this can be done in one line, yes.
	for (size_t i = 0; i < Y.size(); i++) {
		Labels.push_back(Y[i]);
	}
	
	dimension = X.ncol();
}
			  
			  
			  
void convertWeightVector (WeightVector W, NumericVector intW) {
}



void convertWeightVector (NumericVector intW, WeightVector W) {
}


