# Makefile for compiling library rdSDFast

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
LIB1	=	-lrdSDFast -lrdSimulation -lrdTools
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
CCFLG		=	-g -woff 3303,1116 -DUNIX -DRDSDFAST_EXPORTS
FFFLG		=	-g -DUNIX
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJS10	=	cgmalWalking01.o cgmalWalking01_dyn.o
OBJS100	=	$(OBJS10) $(OBJS20)

#=============================
# TARGETS
#=============================
S100	=	$(LibDev)/libcgmalWalking01.so

#=============================
# RULES
#=============================
all : $(S100)

clean :
	rm *.o so_locations $(S100)


$(S100) : $(OBJS100)
	$(CC) $(CCFLG) -shared -o $(S100) $(OBJS100) $(LIB)


cgmalWalking01.o : cgmalWalking01.cpp cgmalWalking01.h
	$(CC) $(CCFLG) $(INC) -c -o cgmalWalking01.o cgmalWalking01.cpp

cgmalWalking01_dyn.o : cgmalWalking01_dyn.c
	$(cc) $(CCFLG) $(INC) -c -o cgmalWalking01_dyn.o cgmalWalking01_dyn.c
