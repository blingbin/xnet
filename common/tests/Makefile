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



LDFLAGS = -rdynamic  ../commonlib.a  -lpthread

INCDIRS = ../

CFLAGS += -I$(INCDIRS)



DES = Thread_unittest\
	  Timestamp_unittest\
	  Mutex_test\
	  CountDownLatch_test1\
	  CountDownLatch_test2\
	  BlockingQueue_test\
	  BlockingQueue_bench\
	  BoundedBlockingQueue_test\
	  ThreadPool_test\
	  Singleton_test\
	  ThreadLocal_test\
	  SingletonThreadLocal_test\
	  ThreadLocalSingleton_test

all:$(DES)


Atomic_unittest:Atomic_unittest.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

BlockingQueue_bench:BlockingQueue_bench.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

BlockingQueue_test:BlockingQueue_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)


BoundedBlockingQueue_test:BoundedBlockingQueue_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

CountDownLatch_test1:CountDownLatch_test1.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)


CountDownLatch_test2:CountDownLatch_test2.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)



Exception_test:Exception_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

Mutex_test:Mutex_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

Singleton_test:Singleton_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

SingletonThreadLocal_test:SingletonThreadLocal_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

ThreadLocalSingleton_test:ThreadLocalSingleton_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

ThreadLocal_test:ThreadLocal_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

ThreadPool_test:ThreadPool_test.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

Thread_unittest:Thread_unittest.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)

Timestamp_unittest:Timestamp_unittest.cpp
	g++ $(CFLAGS) $^ -o $@  $(LDFLAGS)


clean:
	@echo "cleaning..."
	@$(RM) $(DES)

	@$(RM) *.o *.back *~

.PHONY: all clean
