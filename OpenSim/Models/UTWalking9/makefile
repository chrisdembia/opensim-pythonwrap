# Makefile for compiling rdUTWalking9

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
LIB1	=	-lrdSDFast -lrdSimulation
LIB2	=	-lm -lftn
#LIB3	=	-lsdDyn23 -lutMusMod -lrdUtil
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
CCFLG		=	-g -LANG:std -woff 3303 -DUNIX -DRDSDFAST_EXPORTS
#CCFLG	=	-O -woff 3303 -DUNIX -DRDSDFAST_EXPORTS
FFFLG		=	-g -DUNIX
#FFFLG	=	-O -DUNIX
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJS10	=	rdUTWalking9.o

OBJS100	=	$(OBJS10)

#=============================
# TARGETS
#=============================
S100	=	$(LibDev)/librdUTWalking9.so

#=============================
# RULES
#=============================
all : $(S100)

clean :
	rm *.o so_locations $(S100)


$(S100) : $(OBJS100)
	$(CC) $(CCFLG) -shared -o $(S100) $(OBJS100) $(LIB)


rdUTWalking9.o : rdUTWalking9.cpp rdUTWalking9.h
	$(CC) $(CCFLG) $(INC) -c -o rdUTWalking9.o rdUTWalking9.cpp

w23moddat.o : w23moddat.f
	$(FF) $(FFFLG) -woff2310 -c -o w23moddat.o w23moddat.f
