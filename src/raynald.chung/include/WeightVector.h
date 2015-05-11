// Distributed under GNU General Public License (see license.txt for details).
//
//  Copyright (c) 2007 Shai Shalev-Shwartz.
//  All Rights Reserved.
//==============================================================================
// File Name: WeightVector.h
// Written by: Shai Shalev-Shwartz (28.01.07)
// efficiently implements a weight vector for sparse data
//==============================================================================

#ifndef _SHAI_WeightVector_H
#define _SHAI_WeightVector_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>

#include "simple_sparse_vec_hash.h"


class WeightVector {

    public:

		// empty constructor
		//
		WeightVector() : d (0), my_a (0.0), my_snorm (0.0), my_v (NULL)  { 
		};


		
        // Construct a Weight vector with dimension d
		//
        WeightVector (uint dd) : d (dd), my_a (1.0), my_snorm (0.0), my_v (NULL)  {
            my_v = new double[d];
            for (uint i = 0; i < d; ++i) {
				my_v[i] = 0.0;
			}
        }

        
        
        // Construct a Weight vector with dimension d from a file
        //
        WeightVector (uint dd, std::ifstream &model_file) : d (dd), my_a (1.0), my_snorm (0.0), my_v (NULL) {
            my_v = new double[d];

            for (uint i = 0; i < d; ++i) {
				my_v[i] = 0.0;
			}

            unsigned int ind = 0;
            model_file >> ind;

            while (model_file.good()) {
                char c;
                model_file >> c;
                double val;
                model_file >> val;
                my_v[ind] = val;
                my_snorm += val * val;
                model_file >> ind;
            }
        }

        
        WeightVector (std::vector<double> tmpV) {
			d = tmpV.size();
			my_a = 0.0;
			my_v = new double [d];
			for (uint i = 0; i < d; ++i) {
				my_v[i] = tmpV[i];
				my_snorm += my_v[i] * my_v[i];
				std::cout << (my_v[i]) << "..\n";
			}
		}

        // destructor
        ~WeightVector() { 
			delete[] my_v;  
		}

        
        // copy constructor
        //
        WeightVector (const WeightVector& rhs): my_v(0) {
			*this = rhs;
		}
		
		
		
		// copy other
		WeightVector &operator= (const WeightVector& rhs) {
			if (this != &rhs) {
				delete[] my_v;
				d = rhs.dimension();
				my_v = new double[d];
				
				for (size_t i = 0; i < d; i++) {
					my_v[i] = rhs.my_v[i];
				}
				
				my_a = rhs.my_a;
				my_snorm = rhs.my_snorm;
			}
			
			return *this;
		}
		
        
        void resize (uint dd) {
			d = dd;
			my_a = 1.0;
			my_snorm = 0.0;
			delete[] my_v;
			my_v = new double[d];
			
			for (uint i = 0; i < d; ++i)
				my_v[i] = 0.0;
		}
		
        
        // this *= s
        void scale (double s) {
            my_snorm *= (s * s);

            if (s != 0.0) {
                my_a *= s;
            } else {
                my_a = 1.0;

                for (uint i = 0; i < d; ++i) my_v[i] = 0.0;
            }
        }



        // this += s*x
        void add (simple_sparse_vector& x, double s) {
            double pred = 0.0, norm_x = 0.0;

            for (simple_sparse_vector_iterator it = x.my_vec.begin(); it != x.my_vec.end(); it++) {
                double val = (*it).second * s;
                norm_x += val * val;
                pred += 2.0 * my_v[ (*it).first] * val;
                my_v[ (*it).first] += (val / my_a);
            }

            my_snorm += norm_x + my_a * pred;
        }



        // this += s*x
        void add (WeightVector& x, double s) {
            x.flush_a();
            my_snorm = 0.0;

            for (uint i = 0; i < d; ++i) {
                my_v[i] *= my_a;
                my_v[i] += (x[i] * s);
                my_snorm += my_v[i] * my_v[i];
            }

            my_a = 1.0;
        }



        // Added for AdaGrad
        void sqr_add (WeightVector& x) {
            x.flush_a();

            my_snorm = 0.0;

            for (uint i = 0; i < d; ++i) {
                my_v[i] *= my_a;
                my_v[i] += (x[i] * x[i]);
                my_snorm += my_v[i] * my_v[i];
            }

            my_a = 1.0;
        }



        // Added for AdaGrad
        void pair_mul (WeightVector& x) {
            x.flush_a();

            for (uint i = 0; i < d; ++i) {
                if (my_v[i] != 0)
                    my_v[i] /= sqrt (x[i]);
            }
        }


        void print (std::ostream& os) {
            for (uint i = 0; i < d; ++i) {
                if (my_v[i] != 0.0)
                    os << i << ":" << (my_v[i]*my_a) << " ";
            }

            os << std::endl;
        }



        double operator[] (uint i) {
            if (i < d) return (my_v[i] * my_a);

            return 0.0;
        }

        
        
        uint dimension() const {
			return d;
		}

		
		
        double onenorm() {
            double ans = 0;

            for (uint i = 0; i < d; ++i) {
                ans += my_v[i] * my_a;
            }

            return ans;
        }

        // ||this||^2
        double snorm() {
            return my_snorm;
        }



        // make_my_a_one
        // use it for forcing my_a to be 1.0
        void flush_a() {
            if (my_a == 1.0)
                return;

            for (uint i = 0; i < d; ++i) {
                my_v[i] *= my_a;
            }

            my_a = 1.0;
        }


    private:
        // The internal representation of w is as w = a*v where:
        uint d;
        double my_a;
        double my_snorm;
        double* my_v;
};


//-----------------------------------------------------------------------------
/** Operator * for vector-vector multiplication
    @param u A reference to a simple_sparse_vector
    @param v A reference to a WeightVector
    @return The product (double)
*/
double operator* (simple_sparse_vector& u, WeightVector& v);



//-----------------------------------------------------------------------------
/** Operator * for vector-vector multiplication
    @param v A reference to a WeightVector
    @param u A reference to a simple_sparse_vector
    @return The product (double)
*/
double operator* (WeightVector& v, simple_sparse_vector& u);




#endif
