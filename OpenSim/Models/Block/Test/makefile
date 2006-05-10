# Makefile for compiling library rdTestBlock

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
LIB1	=	-lsuAnalyses  -lrdBlock -lrdSDFast -lrdSimulation 
LIB2	=	-lrdTools -lrdSQP -lxerces-c1_7_0
LIB	=	-L$(LibDev) -L$(LibRel) $(LIB1) $(LIB2)


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
CCFLG		=	-g -woff 3303,1116 -DUNIX -DRDSDFAST_EXPORTS
FFFLG		=	-g -DUNIX
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJ10	=	rdTestBlock.o

#=============================
# TARGETS
#=============================
E100	=	$(Bin)/testBlock


#=============================
# RULES
#=============================
all : $(E100)

clean :
	rm *.o so_locations $(E100)


$(E100) : $(OBJ10)
	$(CC) $(CCFLG) -o $(E100) $(OBJ10) $(LIB)


rdTestBlock.o : rdTestBlock.cpp
	$(CC) $(CCFLG) $(INC) -c -o rdTestBlock.o rdTestBlock.cpp
