# cross compile...
CROSS_COMPILE = 

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

ARFLAGS = cr
RM = -rm -rf
MAKE = make

debug = y


CFLAGS = -D_FILE_OFFSET_BITS=64\
		 -Wall\
		 -Wextra\
		 -Werror\
		 -Wconversion\
		 -Wno-unused-parameter\
		 -Wpointer-arith\
		 -Wshadow\
		 -Wwrite-strings\
		 -march=native

CPPFLAGS = -Wold-style-cast\
		   -Woverloaded-virtual

ifeq ($(debug), y)
	CFLAGS += -g
else
	CFLAGS += -O2 -s
endif

DLDFLAGS += -rdynamic

INCLUDE = ../common/


# source file(s), including c file(s) cpp file(s)
# you can also use $(wildcard *.c), etc.
SRC_C   := $(wildcard *.c)
SRC_CPP := $(wildcard *.cpp)

# object file(s)
OBJ_C   := $(patsubst %.c,%.o,$(SRC_C))
OBJ_CPP := $(patsubst %.cpp,%.o,$(SRC_CPP))


LIB = libnet.a


$(LIB): $(OBJ_C) $(OBJ_CPP)
	@echo "Generating static library: " $(notdir $@)
	@$(AR) $(ARFLAGS)  $@ $^
	make --no-print-directory post-build
#	make clean



# make all .c or .cpp
%.o: %.c
	@echo "Compling: " $(addsuffix .c, $(basename $(notdir $@)))
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

%.o: %.cpp
	@echo "Compling: " $(addsuffix .cpp, $(basename $(notdir $@)))
	@$(CXX) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@echo "cleaning..."
	@$(RM) $(LIB)
	@$(RM) *.o *.back *~

post-build:
	cp $(LIB) ../

.PHONY: all clean
.SECONDARY:post-build
