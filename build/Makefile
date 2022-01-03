# Set project directory one level above of Makefile directory. $(CURDIR) is a GNU make variable containing the path to the current working directory
PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/src
BUILDDIR := $(PROJDIR)/build
BINARYDIR := $(PROJDIR)/bin
# Name of the final executable
TARGET = $(BINARYDIR)/trainer

# Decide whether the commands will be shown or not
VERBOSE = FALSE 

# Create the list of directories
DIRS = server solution
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

# Generate the GCC includes parameters by adding -I before each source folder
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))
LIB_INCLUDE = -I$(SOURCEDIR)/include

# Library path
LIBPATH := $(SOURCEDIR)/lib
LIBRARY_NAME = tbcli clialloc tbcliin common mio datatype tbmsg tbstr clientcommon env_client
LIBRARIES = $(foreach lib, $(LIBRARY_NAME), $(addprefix -l, $(lib)))

# Add this list to VPATH, the place make will look for the source files
VPATH = $(SOURCEDIRS)

# Create a list of *.cc sources in DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cc))

# Define objects for all sources
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.cc=.o))

# Define dependencies files for all objects
DEPS = $(OBJS:.o=.d)

# Name the compiler
CC = g++

# Debug option
DEBUG_OPT=${ETF_COMPILE_OPT}

# Commands
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SEP=/

# Remove space after separator
PSEP = $(strip $(SEP))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =  
else
    HIDE = @
endif

# Define the function that will generate each rule
define generateRules
$(1): $(subst $(BUILDDIR), $(SOURCEDIR), $(patsubst %.o, %.cc, $(1)))
	$(HIDE)$(CC) -c $$(INCLUDES) $$(LIB_INCLUDE) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) $(DEBUG_OPT) -MMD
endef

.PHONY: all clean directories 

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(HIDE)$(CC) $(OBJS) $(DEBUG_OPT) -pthread -o $(TARGET) -L$(LIBPATH) $(LIBRARIES)

# Include dependencies
-include $(DEPS)

# Generate rules
$(foreach obj, $(OBJS), $(eval $(call generateRules, $(obj)))) 

directories: 
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Remove all objects, dependencies and executable files generated during the build
clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
