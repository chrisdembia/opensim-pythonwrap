
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
LIB	=	-L$(LibDev) -L$(LibRel) -lrdSDFast -lrdSimulation -lrdTools


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
CCFLG		=	-g -LANG:std -DUNIX -DRDSDFAST_EXPORTS
FFFLG		=	-g
ARFLG		=	-rsv

#=============================
# OBJECTS
#=============================
OBJS10	=	rdBlock.o block_dyn.o
OBJS100	=	$(OBJS10) $(OBJS20)

#=============================
# TARGETS
#=============================
S100	=	$(LibDev)/librdBlock.so

#=============================
# RULES
#=============================
all : $(S100)

clean :
	rm *.o so_locations $(S100)


$(S100) : $(OBJS100)
	$(CC) $(CCFLG) -shared -o $(S100) $(OBJS100) $(LIB)


rdBlock.o : rdBlock.cpp rdBlock.h
	$(CC) $(CCFLG) $(INC) -c -o rdBlock.o rdBlock.cpp

block_dyn.o : block_dyn.c
	$(cc) $(CCFLG) $(INC) -c -o block_dyn.o block_dyn.c

