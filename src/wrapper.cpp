

#include "raynald.chung/include/cmd_line.h"
#include "raynald.chung/include/simple_sparse_vec_hash.h"
#include "raynald.chung/include/optimize.h"

#include "convert.hpp"

#include <Rcpp.h>
using namespace Rcpp;




// TODO: some kind of train object instead of just a weight?


// calculate all the p_i
void initializeP (std::vector<double> &p, 	
	std::vector<simple_sparse_vector> Dataset,
	std::vector<int> Labels,
	double lambda,
	bool verbose = false)
{
	p.clear();
	double sumup = 0;
	double average = 0;
	double variance = 0;
	uint num_examples = Labels.size();
	
	// for adaptive sampling
	// NOTE: the original code has here an index error. not sure, if this now is correct.
	p.push_back(1);
	for (uint i = 1; i <= num_examples; ++i) {
		p.push_back(sqrt(Dataset[i-1].snorm()) + sqrt(lambda));
		sumup += p[i];
	}
	
	average = sumup / num_examples;
	for (uint i = 0; i < num_examples; ++i) {
		variance += (average - p[i]) * (average - p[i]);
	}
	variance = variance / num_examples;
	
	if (verbose == true) {
		std::cout << "Norm average = " << average << std::endl;
		std::cout << "Norm variance = " << variance << std::endl;
	}
	
	for (uint i = 1; i <= num_examples; ++i) {
		p[i] /= sumup;
	}
}



// [[Rcpp::export]]
List AdaOptTrain (std::string method,
	NumericMatrix X, 
	NumericVector Y,
	double lambda = 0.0001, 
	uint epochs = 30,
	bool verbose = false) 
{
	// check method first before converting Dataset
	if ((method != "AdaSVRG") && (method != "AdaSGD") && (method != "AdaSDCA") && 
		(method != "AdaSDCAPlus") && 	(method != "NonUnifSGD") && 	(method != "NonUnifSDCA") && 
		(method != "AdaGrad")) {
		Rf_error ("Unknown method");
	}
	
	if (verbose == true) {
		Rcout << "AdaOpt: Loading data\n";
	}

	// convert R to internal format
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	uint dimension = 0;
	convertData (X, Y, Dataset, Labels, dimension);

	if (verbose == true) {
		Rcout << "Feature dimension is " << dimension << "\n";
	}
	
	// but somehow we work with one dimension more
	dimension = dimension + 1;
/*	
	for (int i = 0; i < Dataset.size(); i++) {
		Rcout << Y(i) << " ";
		Dataset[i].print(Rcout);
	}
*/
	
	// init probablity 
	std::vector<double> p;
	initializeP (p, Dataset, Labels, lambda, verbose);
	
	if (verbose == true) {
		std::cout << "Num examples = " << Labels.size() << std::endl;
		std::cout << "Num epochs = " << epochs << std::endl;
		std::cout << "Lambda = " << lambda << std::endl;
	}
	
	
	// do training
	// NOTE: in all examples (see main.cc in original code) eta_rule_type is zero with SGDLearn
	// it just replaces W with a transformed W while computing loss and error.
	Model mod;
	ResultStruct *resultStr;
	if (method == "AdaSVRG") {
		resultStr = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, VarianceReduction, 0, epochs, 1);
	} else if (method == "AdaSGD") {
		resultStr = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Adaptive, 0, epochs, 1);
	} else if (method == "AdaSDCA") {
		resultStr = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, Adaptive2, epochs, 1);
	} else if (method == "AdaSDCAPlus") {
		resultStr = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, AdaSDCAp, epochs, 1);
	} else if (method == "NonUnifSGD") {
		resultStr = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Plain, 0, epochs, 1);
	} else if (method == "NonUnifSDCA") {
		resultStr = mod.SDCALearn (Dataset, Labels, dimension, lambda, p, Plain, epochs, 1);
	} else if (method == "AdaGrad") {
		resultStr = mod.SGDLearn (Dataset, Labels, dimension, lambda, p, AdaGrad, 0, epochs, 1);
	} else {
		stop ("Unknown method");
	}
	
	// return found weight vector
	NumericVector W;
	convertWeightVector (resultStr -> W, W);
	List z = List::create(Rcpp::Named("W", W));
	return z ;
}



// [[Rcpp::export]]
List AdaOptTest(NumericVector W,
				NumericMatrix X, 
				NumericVector Y,
				bool verbose = false
   			) {
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
	TestResultStruct *res = mod.SGDTest (intW, Dataset, Labels, verbose);
	
	// convert back
	convertWeightVector (intW, W);
	
	// return weight
	List z = List::create(Rcpp::Named("W", W));
	
	// clean up
	delete res;
	return z ;
}

