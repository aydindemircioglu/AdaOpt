

#include "raynald.chung/include/cmd_line.h"
#include "raynald.chung/include/simple_sparse_vec_hash.h"
#include "raynald.chung/include/optimize.h"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
List AdaSVRG() {

	double lambda = 0.0001;
	uint epoch = 30;
	uint num_rounds = 10;
	
	std::vector<simple_sparse_vector> Dataset;
	std::vector<int> Labels;
	uint dimension = 0;
	
	std::vector<simple_sparse_vector> testDataset;
	std::vector<int> testLabels;

	std::vector<double> p;

	Model mod;
	//mod.ReadData(data_filename, Dataset, Labels, dimension, readingTime);
	
	
	// global?? , VarianceReduction
	
	Rcout << "AdaSVRG:\n";
	mod.SGDLearn(Dataset, Labels, dimension, testDataset, testLabels,
				 lambda, p, VarianceReduction, 0, num_rounds, epoch, 1);
	
	List z            = List::create() ;
	return z ;
}

