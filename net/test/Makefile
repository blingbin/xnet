# cross compile...
CROSS_COMPILE = 

CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

ARFLAGS = cr
RM = -rm -rf
MAKE = make

CFLAGS += -Wall\
		  -Wextra\
		  -Werror\
		  -Wconversion\
		  -Wno-unused-parameter\
		  -Wno-unused-local-typedefs\
		  -Wold-style-cast\
		  -Woverloaded-virtual\
		  -Wpointer-arith\
		  -Wshadow\
		  -Wwrite-strings\
		  -march=native

debug = y

ifeq ($(debug), y)
	CFLAGS += -g
else
	CFLAGS += -O2 -s
endif



LDFLAGS = -rdynamic -lnet -lcommon  -lpthread -L../../

INCDIRS = -I../  -I../../common/

CFLAGS += $(INCDIRS)



DES = Reactor_test01\
	  Reactor_test02

all:$(DES)


Reactor_test01:Reactor_test01.cpp
	@echo "Compling: " $(addsuffix .c, $(basename $(notdir $@)))
	@$(CXX) $(CFLAGS) $^ -o $@  $(LDFLAGS)

Reactor_test02:Reactor_test02.cpp
	@echo "Compling: " $(addsuffix .c, $(basename $(notdir $@)))
	@$(CXX) $(CFLAGS) $^ -o $@  $(LDFLAGS)




clean:
	@echo "cleaning..."
	@$(RM) $(DES)
	@$(RM) *.o *.back *~

.PHONY: all clean
