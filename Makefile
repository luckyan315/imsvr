APP_PATH= .
INC_PATH= 	$(APP_PATH) \
			#/mb/libs/gtest-1.6.0/include
			#$(HOME)/dfs/ThirdLibs/gtest1.6/include

LIB_PATH= 	\
			#/mb/libs/gtest-1.6.0/lib/.libs
			#$(HOME)/dfs/ThirdLibs/gtest1.6/lib/.libs
			#$(APP_PATH)/lib/ 

DYNAMIC_LIBS= rt dl
STATIC_LIBS= 

SRC_NAME = $(patsubst %.cpp, %, $(wildcard *.cpp))   $(patsubst %.c, %, $(wildcard *.c)) 

TARGET= main

CC=g++

DEBUG_FLAGS= -g -Werror #-Wwrite-strings -Werror

CFLAGS= $(addprefix -I, $(INC_PATH)) $(DEBUG_FLAGS)
#LFLAGS= $(DEBUG_FLAGS) $(addprefix -L, $(LIB_PATH)) -Wl,-Bstatic $(addprefix -l, $(STATIC_LIBS)) -Wl,-Bdynamic $(addprefix -l, $(DYNAMIC_LIBS))
LFLAGS= $(DEBUG_FLAGS)
OBJS=$(addsuffix .o, $(SRC_NAME))

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS) 

%.o:%.c
	$(CC) $(CFLAGS) -c $<

%.o:%.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(TARGET) $(OBJS) *.o 


