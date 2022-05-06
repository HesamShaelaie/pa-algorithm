
BITS = 64

# Output directory
ODIR  = obj64
tmp  := $(shell mkdir -p $(ODIR))

# Basic compiler configuration and flags
CXX      = g++

d ?= 1
ifeq ($(d), 1)
    CXXFLAGS = -MMD -ggdb -O0 -std=gnu++14 -m$(BITS) -lemon
else
	CXXFLAGS = -MMD -s -DNDEBUG -O3 -std=gnu++14 -m$(BITS) -lemon
endif

# flag -g
# -03 some optimization, dose eliminate some of the codes

LDFLAGS	 = -m$(BITS) -lpthread -lemon


# The basenames of the c++ files that this program uses
CXXFILES = variables mathmatics generating_data config_t tests exitence index_creator config_d config_r reading inputesting pa_algorithm dijkstra printout Qlearning main 

# The executable we will build
TARGET = $(ODIR)/Project

# Create the .o names from the CXXFILES
OFILES = $(patsubst %, $(ODIR)/%.o, $(CXXFILES))

# Create .d files to store dependency information, so that we don't need to
# clean every time before running make
DFILES = $(patsubst %.o, %.d, $(OFILES))

# Default rule builds the executable
all: print $(TARGET) 

print: 
	printf '\33c\n'
	@echo "================================================"
	@echo $(CXXFLAGS)
	@echo "================================================"
# clean up everything by clobbering the output folder
clean:
	@echo cleaning up files...
	@rm -rf $(ODIR)

cleanx:
	@echo cleaning instances...
	@rm -rf instances

# build an .o file from a .cc file
$(ODIR)/%.o: %.cc
	@echo [CXX] $< "-->" $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

# Link rule for building the target from .o files

$(TARGET): $(OFILES)
	
	@echo [LD] $^ "-->" $@
	@$(CXX) -o $@ $^ $(LDFLAGS)

# Remember that 'all' and 'clean' aren't real targets
.PHONY: all clean cleanx print

# https://hiltmon.com/blog/2015/08/01/simple-c-plus-plus-from-makefiles-to-xcode-builds/

info:
	@./$(ODIR)/Project -h

crt1:
	@./$(ODIR)/Project -m 1 -t 1

crt2:
	@./$(ODIR)/Project -m 2 -t 1 -d 1

crt3:
	@./$(ODIR)/Project -m 5 -t 1 -d 1

run:
	@./$(ODIR)/Project -m 3 -t 1 -d 1
runq:
	@./$(ODIR)/Project -m 6 -t 1 -d 1

test:
	@./$(ODIR)/Project -m 4 -t 1
# Pull in all dependencies
-include $(DFILES)

rebuild: clean all

