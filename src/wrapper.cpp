

#include "raynald.chung/include/cmd_line.h"
#include "raynald.chung/include/simple_sparse_vec_hash.h"
#include "raynald.chung/include/optimize.h"

#include <Rcpp.h>
using namespace Rcpp;





// [[Rcpp::export]]
List AdaSGDOpt( NumericMatrix X, NumericVector Y,
			  double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Adaptive, 0, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}



// [[Rcpp::export]]
List AdaSDCAOpt( NumericMatrix X, NumericVector Y,
			 double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SDCALearn (Dataset, Labels, dimension, testDataset, testLabels, lambda, p, Adaptive2, num_rounds, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}

			 


// [[Rcpp::export]]
List AdaSDCAPlusOpt( NumericMatrix X, NumericVector Y,
			 double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SDCALearn (Dataset, Labels, dimension, testDataset, testLabels, lambda, p, AdaSDCAp, num_rounds, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}




// [[Rcpp::export]]
List NonUnifSGDOpt( NumericMatrix X, NumericVector Y,
			  double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SGDLearn (Dataset, Labels, dimension, lambda, p, Plain, 0, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}



// [[Rcpp::export]]
List NonUnifSDCAOpt( NumericMatrix X, NumericVector Y,
			  double lambda = 0.0001, uint epoch = 30) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SDCALearn (Dataset, Labels, dimension, testDataset, testLabels, lambda, p, Plain, 0, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}
			  


// [[Rcpp::export]]
List AdaGradOpt( NumericMatrix X, NumericVector Y,
			 double lambda = 0.0001, uint epoch = 30) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SGDLearn (Dataset, Labels, dimension, lambda, p, AdaGrad, 0, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}



// [[Rcpp::export]]
List AdaSGDTest( NumericMatrix X, NumericVector Y,
				 double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	uint dimension = Dataset.size();
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod; 
	WeightVector W(dimension);
	mod.SGDTest (W, Dataset, Labels);
	
	List z            = List::create() ;
	return z ;
				 }
				 
				 
				 



// [[Rcpp::export]]
List AdaSVRGOpt( NumericMatrix X, NumericVector Y,
			  double lambda = 0.0001, uint epoch = 30, uint num_rounds = 10) {
	
	// TODO: can this be done more efficient?
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	
	for (size_t i = 0; i < X.nrow(); i++) {
		// find non-null rows and create a string from it
		// 		std::istringstream is;
		// 		simple_sparse_vector instance(is, n);
		// 		Dataset.push_back(instance);
		// 		num_examples++;
	}
	
	// TODO: this can be done in one line, yes.
	for (size_t i = 0; i < Y.size(); i++) {
		Labels.push_back(Y[i]);
	}
	
	
	uint dimension = Dataset.size();
	
	
	
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;
	
	std::vector<double> p;
	
	// ??? global?? , VarianceReduction
	
	Model mod;
	mod.SGDLearn (Dataset, Labels, dimension, lambda, p, VarianceReduction, 0, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}
			  
			  
			  


