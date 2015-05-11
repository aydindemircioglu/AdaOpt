#!/usr/bin/Rscript  --vanilla 

#
# SVMBridge 
#
#		(C) 2015, by Aydin Demircioglu
# 
# SVMBridge is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SVMBridge is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# Please do not use this software to destroy or spy on people, environment or things.
# All negative use is prohibited.
#

#library (SVMBridge)
	library(methods)
	library(devtools)
	load_all (".")
#	build_vignettes(".")
#	document(".")
	# devtools::build_win()	
	# is done by document/loadall anyway?
	#library(Rcpp)
	#compileAttributes()

	# run tests
#	devtools::test()
#	devtools::check()
# R CMD check ./SVMBridge_1.0.tar.gz

	verbose = FALSE
	
	X = as.matrix(iris[,1:4])
	Y = as.matrix(as.numeric(iris[,5]))
	Y[Y==2]=-1
	Y[Y==3]=-1

	cat ("Training AdaSVRG\n")
	r = AdaOptTrain (method = "AdaSVRG", X, Y, verbose = verbose)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)
	
	cat ("Training AdaSDCA\n")
	r = AdaOptTrain (method = "AdaSDCA", X, Y, verbose = verbose)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)

	cat ("Training AdaSDCAPlus\n")
	r = AdaOptTrain (method = "AdaSDCAPlus", X, Y)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)

	cat ("Training AdaGrad\n")
	r = AdaOptTrain (method = "AdaGrad", X, Y)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)

	cat ("Training AdaSGD\n")
	r = AdaOptTrain (method = "AdaSGD", X, Y)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)
	
	cat ("Training NonUnifSDCA\n")
	r = AdaOptTrain (method = "NonUnifSDCA", X, Y)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)
	
	cat ("Training NonUnifSGD\n")
	r = AdaOptTrain (method = "NonUnifSGD", X, Y)
	cat ("Testing\n")
	t = AdaOptTest (r$W, X, Y, verbose = verbose)
	
	cat("\n?OK, Computer.\n")

	
	