# Makefile for compiling a program for testing rdUTWalking.

#=============================
# DIRECTORIES
#=============================


#=============================
# INCLUDE SEARCH PATHS
#=============================
INC	= -I$(IncDev) -I$(IncRel)

#=============================
# LIBRARIES
#=============================
LIB1	=	-lrdUTWalking8 -lrdModelTestSuite -lrdSimulation
LIB	=	-L$(LibDev) -L$(LibRel) $(LIB1)

#=============================
# COMPILERS
#=============================
PURIFY = 
cc	=	$(PURIFY) cc
CC =	$(PURIFY) CC
FF	=	$(PURIFY) f77
AR	=	ar

#=============================
# FLAGS
#=============================
CCFLG		=	-g -DUNIX
FFFLG		=	-g
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJS100	=	rdTestUT.o w23moddat.o

#=============================
# TARGETS
#=============================
E100	=	$(Bin)/rdTestUT

#=============================
# RULES
#=============================
all : $(E100)

clean :
	rm *.o $(E100)


$(E100) : $(OBJS100)
	$(CC) $(CCFLG) -o $(E100) $(OBJS100) $(LIB)


rdTestUT.o : rdTestUT.cpp
	$(CC) $(CCFLG) $(INC) -c -o rdTestUT.o rdTestUT.cpp

w23moddat.o : w23moddat.f
	$(FF) $(FFFLG) -woff2310 -c -o w23moddat.o w23moddat.f

