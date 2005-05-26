# MAKEFILE FOR SAMPLE CODE USING CFSQP

#=============================
# DIRECTORIES
#=============================


#=============================
# INCLUDE SEARCH PATHS
#=============================
INC	= 	-I$(IncDev) -I$(IncRel)

#=============================
# LIBRARIES
#=============================
LIB	= 	-L$(LibDev) -L$(LibRel) -lcfsqp -lm

#=============================
# COMPILERS
#=============================
CC = CC
cc = cc
AR = ar

#=============================
# FLAGS
#=============================
CCFLG	=	-g -DUNIX -DSUCFSQP_EXPORTS
ccFLG	=	-g -DUNIX
ARFLG	=	-rsv

#=============================
# OBJECTS
#=============================
OBJS1	=	cfsqp.o qld.o
OBJS2	=	sampl1CC.o
OBJS3	=	samplePerfOnly.o

#=============================
# TARGETS
#=============================
S1	=	$(LibDev)/libcfsqp.so
E2 = /home/fca/Bin/sampl1CC
E3 = /home/fca/BinsamplePerfOnly


#=============================
# RULES
#=============================
all : $(S1)

clean :
	rm *.o so_locations

$(S1) : $(OBJS1)
	$(CC) $(CCFLG) -shared -o $(S1) $(OBJS1)

$(E2) : $(OBJS2)
	CC $(CCFLG) -o $(E2) $(OBJS2) $(LIB)

$(E3) : $(OBJS3)
	CC $(CCFLG) -o $(E3) $(OBJS3) $(LIB)

samplePerfOnly.o : samplePerfOnly.cpp
	$(CC) $(ccFLG) $(INC) -c -o samplePerfOnly.o samplePerfOnly.cpp

sampl1CC.o : sampl1CC.cpp
	$(CC) $(ccFLG) $(INC) -c -o sampl1CC.o sampl1CC.cpp

cfsqp.o : cfsqp.c
	$(cc) $(ccFLG) $(INC) -c -o cfsqp.o cfsqp.c

qld.o : qld.c
	$(cc) $(ccFLG) $(INC) -c -o qld.o qld.c


