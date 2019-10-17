#The following macros should be defined.
TARGET1=wiring
OBJECT1=asyn-inputs.o
OBJECT2=
CC=gcc
CXX=g++
LD=g++
LD_FLAGS += -lwiringPi
#LD_FLAGS += -lncurses -pthread
#C_FLAGS= -g -O0
C_FLAGS=
# end of user configuration
#
ALL : $(TARGET1)
$(TARGET1) : $(OBJECT1) $(OBJECT2)
$(LD) $^ $(LD_FLAGS) -o $@
%.o : %.c
$(CC) $(C_FLAGS) -c $<
%.o : %.cpp
$(CXX) $(C_FLAGS) -c $<
.PHONY: clean
clean :
-rm -f $(OBJECT1) $(OBJECT2)