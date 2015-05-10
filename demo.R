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

	
	X = as.matrix(iris[,1:4])
	Y = as.matrix(as.numeric(iris[,5]))
	Y[Y==2]=-1
	Y[Y==3]=-1

	AdaOpt(method = "AdaSVRG", X, Y)
	AdaOpt(method = "AdaSDCA", X, Y)
	AdaOpt(method = "AdaSDCAPlus", X, Y)
	AdaOpt(method = "AdaGrad", X, Y)
	AdaOpt(method = "AdaSGD", X, Y)
	AdaOpt(method = "NonUnifSDCA", X, Y)
	AdaOpt(method = "NonUnifSGD", X, Y)
	
	print("OK, Computer")
	AdaOpt(method = "Unknown", X, Y)

	
	