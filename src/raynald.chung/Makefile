##########################################################################
# Makefile for sparse pegasos
##########################################################################

HDR = include/simple_sparse_vec_hash.h include/WeightVector.h include/optimize.h
SRC = simple_sparse_vec_hash.cc  WeightVector.cc optimize.cc cmd_line.cc

CC = g++ 

CFLAGS  = -Wall -O3  -std=c++11 -fPIC
#CFLAGS  = -g 
LFLAGS  = -lm

OBJS = $(SRC:.cc=.o)

OUTPUTFILE = ./libraynald.a

%.o: %.cc $(HDR)
	$(CC) -std=c++11 $(CFLAGS) -c $<

        
all: $(OUTPUTFILE)


$(OUTPUTFILE): $(OBJS)
	ar ru $@ $^
	ranlib $@

    
.PHONY: install
install:\
    mkdir -p $(INSTALLDIR)\
    cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean 
clean:\
    for file in $(CLEANEXTS); do rm -f *.$$file; done


