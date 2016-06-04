# cross compile...
CROSS_COMPILE = 

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

ARFLAGS = cr
RM = -rm -rf
MAKE = make

CFLAGS = -Wall
debug = y

ifeq ($(debug), y)
CFLAGS += -g
else
CFLAGS += -O2 -s
endif

DEFS =  -g\
		-D_FILE_OFFSET_BITS=64\
		-Wextra\
		-Werror\
		-Wconversion\
		-Wno-unused-parameter\
		-Wold-style-cast\
		-Woverloaded-virtual\
		-Wpointer-arith\
		-Wshadow\
		-Wwrite-strings\
		-march=native

CFLAGS += $(DEFS)

LDFLAGS += -rdynamic

# source file(s), including c file(s) cpp file(s)
# you can also use $(wildcard *.c), etc.
SRC_C   := $(wildcard *.c)
SRC_CPP := $(wildcard *.cpp)

# object file(s)
OBJ_C   := $(patsubst %.c,%.o,$(SRC_C))
OBJ_CPP := $(patsubst %.cpp,%.o,$(SRC_CPP))


LIB = commonlib.a


$(LIB): $(OBJ_C) $(OBJ_CPP)
	@echo "Generating static library: " $(notdir $@)
	@$(AR) $(ARFLAGS)  $@ $^



# make all .c or .cpp
%.o: %.c
	@echo "Compling: " $(addsuffix .c, $(basename $(notdir $@)))
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@echo "Compling: " $(addsuffix .cpp, $(basename $(notdir $@)))
	@$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaning..."
	@$(RM) $(LIB)
	@$(RM) *.o *.back *~

.PHONY: all clean
