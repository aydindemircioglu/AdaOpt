

#include "raynald.chung/include/cmd_line.h"
#include "raynald.chung/include/simple_sparse_vec_hash.h"
#include "raynald.chung/include/optimize.h"

#include "convert.hpp"

#include <Rcpp.h>
using namespace Rcpp;


// TODO: some kind of train object instead of just a weight?



// [[Rcpp::export]]
List AdaOpt (std::string method,
	NumericMatrix X, 
	NumericVector Y,
	double lambda = 0.0001, 
	uint epochs = 30) 
{
	
	 // TODO: check method first before converting Dataset
	
	// convert R to internal format
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	uint dimension = 0;
	convertData (X, Y, Dataset, Labels, dimension);
	
	// do training
	std::vector<double> p;
	Model mod;
	WeightVector tmpW(dimension);
	if (method == "AdaSVRG") {
		tmpW = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, VarianceReduction, 0, epochs, 1);
	} else if (method == "AdaSGD") {
		tmpW = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Adaptive, 0, epochs, 1);
	} else if (method == "AdaSDCA") {
		tmpW = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, Adaptive2, epochs, 1);
	} else if (method == "AdaSDCAPlus") {
		tmpW = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, AdaSDCAp, epochs, 1);
	} else if (method == "NonUnifSGD") {
		tmpW = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Plain, 0, epochs, 1);
	} else if (method == "NonUnifSDCA") {
		tmpW = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, Plain, epochs, 1);
	} else if (method == "AdaGrad") {
		tmpW = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, AdaGrad, 0, epochs, 1);
	} else {
		Rf_error ("Unknown method");
	}
	
	NumericVector W;
	convertWeightVector (tmpW, W);
	List z = List::create(Rcpp::Named("W", W));
	return z ;
}


// [[Rcpp::export]]
List AdaSGDTest(NumericMatrix X, NumericVector Y, NumericVector W) {
	// convert R to internal format
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	uint dimension = 0;
	convertData (X, Y, Dataset, Labels, dimension);
	
	// convert weight vector
	WeightVector intW (dimension);
	convertWeightVector (W, intW);
	
	// do testing
	Model mod; 
	mod.SGDTest (intW, Dataset, Labels);
	
	// convert back
	convertWeightVector (intW, W);
	
	// return weight
	List z = List::create(Rcpp::Named("W", W));
	return z ;
}

