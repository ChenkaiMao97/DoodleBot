# define the C++ compiler to use 
CXX = g++

# define any compiler-time flags
CFLAGS = -Wall -pthread

# define some directories:
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

# define any include directories containing header files other than /use/inlcude
INCLUDES = -I$(INCLUDE_DIR)

# define library paths in addition to /use/lib
LFLAGS = -L$(LIB_DIR)

# define any libraries to link to executable:
LIBS = -lpigpio

# define C++ source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# define the C object files
OBJS = $(SRCS:.c=.o)

# define the executable file:
MAIN = goto_test


.PHONY: depend clean

all: $(MAIN)
	@echo compiler for $(MAIN) has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
