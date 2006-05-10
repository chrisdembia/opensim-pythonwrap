# Makefile for compiling rdUTWalking8

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
LIB1	=	-lrdSDFast -lrdSimulation -lrdOldMath
LIB2	=	-lrdGFX -lgl -lm -lftn
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
#CCFLG		=	-O -LANG:std -woff 3303 -DUNIX -DRDSDFAST_EXPORTS
FFFLG		=	-g -DUNIX
#FFFLG		=	-O -DUNIX
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJS10	=	rdUTWalking8.o rdUTWalkingIntegCallback.o
OBJS20	=	w23intl.o w23force.o w23xbound.o w23newynode.o
OBJS30	=	w23parameters.o w23sforce.o w23spring.o 23skgspec.o w23ref_intl.o
OBJS40	=	drawUTWalking.o 23drawGL.o 23inputs.o
OBJS50	=	utModel_dyn.o
OBJS60	=	musmodel.o str_funcs.o
OBJS100	=	$(OBJS10) $(OBJS20) $(OBJS30) $(OBJS40) $(OBJS50) $(OBJS60)

#=============================
# TARGETS
#=============================
S100	=	$(LibDev)/librdUTWalking8.so

#=============================
# RULES
#=============================
all : $(S100)

clean :
	rm *.o so_locations $(S100)


$(S100) : $(OBJS100)
	$(CC) $(CCFLG) -shared -o $(S100) $(OBJS100) $(LIB)


rdUTWalking8.o : rdUTWalking8.cpp rdUTWalking8.h
	$(CC) $(CCFLG) $(INC) -c -o rdUTWalking8.o rdUTWalking8.cpp

rdUTWalkingIntegCallback.o : rdUTWalkingIntegCallback.cpp rdUTWalkingIntegCallback.h
	$(CC) $(CCFLG) $(INC) -c -o rdUTWalkingIntegCallback.o rdUTWalkingIntegCallback.cpp

utModel_dyn.o : utModel_dyn.c
	$(cc) $(CCFLG) -woff 1116,1174 $(INC) -c -o utModel_dyn.o utModel_dyn.c

drawUTWalking.o : drawUTWalking.f
	$(FF) $(FFFLG) -c -o drawUTWalking.o drawUTWalking.f

23drawGL.o : 23drawGL.c 23drawGL.h
	$(cc) $(CCFLG) -woff1174,1164 $(INC) -c -o 23drawGL.o 23drawGL.c

23inputs.o : 23inputs.c 23inputs.h
	$(cc) $(CCFLG) $(INC) -c -o 23inputs.o 23inputs.c

w23parameters.o : w23parameters.f
	$(FF) $(FFFLG) -c -o w23parameters.o w23parameters.f

w23intl.o : w23intl.f
	$(FF) $(FFFLG) -c -o w23intl.o w23intl.f

w23sforce.o : w23sforce.f
	$(FF) $(FFFLG) -c -o w23sforce.o w23sforce.f

w23spring.o : w23spring.f
	$(FF) $(FFFLG) -c -o w23spring.o w23spring.f

w23force.o : w23force.f
	$(FF) $(FFFLG) -c -o w23force.o w23force.f

w23xbound.o : w23xbound.f
	$(FF) $(FFFLG) -c -o w23xbound.o w23xbound.f

w23newynode.o : w23newynode.f
	$(FF) $(FFFLG) -c -o w23newynode.o w23newynode.f

w23moddat.o : w23moddat.f
	$(FF) $(FFFLG) -woff2310 -c -o w23moddat.o w23moddat.f

23skgspec.o : 23skgspec.f
	$(FF) $(FFFLG) -c -o 23skgspec.o 23skgspec.f

w23ref_intl.o : w23ref_intl.f
	$(FF) $(FFFLG) -c -o w23ref_intl.o w23ref_intl.f

musmodel.o : musmodel.f
	$(FF) $(FFFLG) -c -o musmodel.o musmodel.f

str_funcs.o : str_funcs.f
	$(FF) $(FFFLG) -c -o str_funcs.o str_funcs.f
