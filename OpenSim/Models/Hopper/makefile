
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
OBJS10	=	suHopper.o hopper_dyn.o
OBJS100	=	$(OBJS10) $(OBJS20)

#=============================
# TARGETS
#=============================
S100	=	$(LibDev)/libsuHopper.so

#=============================
# RULES
#=============================
all : $(S100)

clean :
	rm *.o so_locations $(S100)


$(S100) : $(OBJS100)
	$(CC) $(CCFLG) -shared -o $(S100) $(OBJS100) $(LIB)


suHopper.o : suHopper.cpp suHopper.h
	$(CC) $(CCFLG) $(INC) -c -o suHopper.o suHopper.cpp

hopper_dyn.o : hopper_dyn.c
	$(cc) $(CCFLG) $(INC) -c -o hopper_dyn.o hopper_dyn.c

