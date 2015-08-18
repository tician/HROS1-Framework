ifeq (,$(filter _%,$(notdir $(CURDIR))))
include target.mk
else

VPATH = $(SRCDIR)

#~~~~~~~~~~~~~~~~~~~~ Output File Name ~~~~~~~~~~~~~~~~~~~~
PROJECT_NAME = hros1

#~~~~~~~~~~~~~~~~~~~~ Source Files ~~~~~~~~~~~~~~~~~~~~
SRCS = \
        framework/src/CM730.cpp         \
        framework/src/math/Matrix.cpp   \
        framework/src/math/Plane.cpp    \
        framework/src/math/Point.cpp    \
        framework/src/math/Vector.cpp   \
        framework/src/math/QuadraticStateTransform.cpp   \
        framework/src/math/MotionState.cpp   \
        framework/src/motion/JointData.cpp      \
        framework/src/motion/Kinematics.cpp     \
        framework/src/motion/MotionManager.cpp  \
        framework/src/motion/MotionStatus.cpp   \
        framework/src/motion/AngleEstimator.cpp \
        framework/src/motion/modules/Action.cpp \
        framework/src/motion/modules/Head.cpp   \
        framework/src/motion/modules/Walking.cpp\
        framework/src/vision/BallFollower.cpp   \
        framework/src/vision/PS3BallFollower.cpp   \
        framework/src/vision/LineFollower.cpp   \
        framework/src/vision/RobotFollower.cpp   \
        framework/src/vision/ConnectRegions.cpp   \
        framework/src/vision/RadonTransform.cpp   \
        framework/src/vision/BallTracker.cpp    \
        framework/src/vision/ColorFinder.cpp    \
        framework/src/vision/Image.cpp          \
        framework/src/vision/ImgProcess.cpp     \
        framework/src/controller/PS3Controller.cpp \
        framework/src/commander/SerialInputCommander.cpp    \
        framework/src/minIni/minIni.c \
        linux/src/LinuxActionScript.cpp   \
        linux/src/LinuxCamera.cpp   \
        linux/src/LinuxCM730.cpp    \
        linux/src/LinuxMotionTimer.cpp    \
        linux/src/LinuxNetwork.cpp

#~~~~~~~~~~~~~~~~~~~~ Object Files ~~~~~~~~~~~~~~~~~~~~
#BINDIR = bin
OBJDIR = obj

TARGET := $(PROJECT_NAME).a

CSRCS = $(filter %.c,$(SRCS))
CXXSRCS = $(filter %.cpp,$(SRCS))
OBJS = $(CSRCS:.c=.c.o) $(CXXSRCS:.cpp=.cpp.o)
#OBJS = $(notdir $(RAWOBJS))

#RAWOBJS = $(CSRCS:.c=.c.o) $(CXXSRCS:.cpp=.cpp.o)
#OBJS = $(addprefix $(OBJDIR)/,$(RAWOBJS))

#COBJS = $(addprefix $(OBJDIR)/, $(CSRCS:.c=.c.o) )
#CXXOBJS = $(addprefix $(OBJDIR)/, $(CXXSRCS:.cpp=.cpp.o) )
#COBJS = $(CSRCS:.c=.c.o)
#CXXOBJS = $(CXXSRCS:.cpp=.cpp.o)
#COBJS = $(addprefix $(OBJDIR)/, $(CSRCS:.c=.o) )
#CXXOBJS = $(addprefix $(OBJDIR)/, $(CXXSRCS:.cpp=.o) )


#~~~~~~~~~~~~~~~~~~~~ Include Directories ~~~~~~~~~~~~~~~~~~~~
INCLUDE_DIRS = -I. -I$(VPATH)/framework/include -I$(VPATH)/linux/include
# -I$(VPATH)/framework/src/minIni

#~~~~~~~~~~~~~~~~~~~~ Library Directories ~~~~~~~~~~~~~~~~~~~~
LIBRARY_DIRS = -L.
LIBS = 

#~~~~~~~~~~~~~~~~~~~~ Compiler Options ~~~~~~~~~~~~~~~~~~~~
COMPILE_OPTS = -g -O2 -fno-common -std=gnu++0x
COMPILE_OPTS += -Wall -Wextra -Wmain -pedantic -pedantic-errors -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default
COMPILE_OPTS += -fPIC -shared -DLINUX -D_GNU_SOURCE -Wall -g 

#~~~~~~~~~~~~~~~~~~~~ Linker Options ~~~~~~~~~~~~~~~~~~~~
LINKER_OPTS = -s -ldl -lrt
LINKER_OPTS += -g -lpthread -ldl -lbluetooth -lncurses -lusb


# Compiler flags to generate dependency files. 
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d

#~~~~~~~~~~~~~~~~~~~~ Toolchain Prefix ~~~~~~~~~~~~~~~~~~~~
TCHAIN_PREFIX=

CC = $(TCHAIN_PREFIX)gcc
CFLAGS = $(GENDEPFLAGS) $(INCLUDE_DIRS) $(COMPILE_OPTS)

CXX = $(TCHAIN_PREFIX)g++
CXXFLAGS = $(GENDEPFLAGS) $(INCLUDE_DIRS) $(COMPILE_OPTS)

AS = $(TCHAIN_PREFIX)gcc
ASFLAGS = $(GENDEPFLAGS) $(COMPILE_OPTS) -c

LD = $(TCHAIN_PREFIX)gcc
LDFLAGS = $(INCLUDE_DIRS) $(LIBRARY_DIRS) $(LIBS) $(LINKER_OPTS)

OBJCP = $(TCHAIN_PREFIX)objcopy
OBJCPFLAGS_HEX = -O ihex
OBJCPFLAGS_BIN = -O binary

OBJDUMP = $(TCHAIN_PREFIX)objdump
OBJDUMPFLAGS = -h -S -C -D

SIZE = $(TCHAIN_PREFIX)size

AR = $(TCHAIN_PREFIX)ar
ARFLAGS = cr


#~~~~~~~~~~~~~~~~~~~~ messages ~~~~~~~~~~~~~~~~~~~~
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_BUILD_DIRS = Checking build directories exist:
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_COMPILING_CXX = Compiling C++:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:

#~~~~~~~~~~~~~~~~~~~~ all ~~~~~~~~~~~~~~~~~~~~
_hros1_blobs: all
all: begin gccversion spotcheck sizebefore filenames build sizeafter end

#~~~~~~~~~~~~~~~~~~~~ build ~~~~~~~~~~~~~~~~~~~~
spotcheck:
	@echo $(MSG_BUILD_DIRS)
#	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@echo

filenames:
	@echo $(VPATH)
	@echo $(CSRCS)
	@echo $(CXXSRCS)
	@echo $(OBJS)
#	@echo $(COBJS)
#	@echo $(CXXOBJS)
	@echo 

build: $(TARGET) 

$(TARGET): $(OBJS)
#$(TARGET): $(COBJS) $(CXXOBJS)
#$(TARGET): $(CSRCS) $(CXXSRCS)
#	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
#	$(AR) $(ARFLAGS) $@ $(OBJDIR)/$(OBJS)
	$(AR) $(ARFLAGS) $@ $(addprefix $(OBJDIR)/,$(notdir $(OBJS)))
#	$(AR) $(ARFLAGS) $@ $(OBJDIR)/$(COBJS) $(OBJDIR)/$(CXXOBJS) 
#	$(AR) $(ARFLAGS) $@ $(COBJS) $(CXXOBJS)

#PS3Controller: JoystickController.cpp.o
#	make -C framework/src/controller
#	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)
#	$(CXX) JoystickController.cpp.o $(LDFLAGS) -o $@


#JoystickController.cpp.o: 
#	make -C framework/src/controller


%.c.o: %.c
#%.c.o: $(CSRCS)
#$(COBJS): %.c.o: %.c
#$(filter %.c.o,$(OBJS)): %.c.o: %.c
#$(COBJS): $(subst obj/,,$(CSRCS))
#$(filter %.c.o,$(OBJS)): %.c.o: $(subst obj/,,%.c)
#%.c.o: $(subst obj/,,%.c)
#$(filter .c.o,$(OBJS)): $(OBJDIR)/%.c.o: %.c
#$(COBJS): $(OBJDIR)/%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@
#	$(CC) -o $@ -c $< $(CFLAGS)
#	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

%.cpp.o: %.cpp
#%.cpp.o: $(CXXSRCS)
#$(CXXOBJS): %.cpp.o: %.cpp
#$(filter %.cpp.o,$(OBJS)): %.cpp.o: %.cpp
#$(CXXOBJS): $(CXXSRCS)
#$(filter %.cpp.o,$(OBJS)): %.cpp.o: $(subst obj/,,%.cpp)
#%.cpp.o: $(subst obj/,,%.cpp)
#$(filter .cpp.o,$(OBJS)): $(OBJDIR)/%.cpp.o: %.cpp
#$(CXXOBJS): $(OBJDIR)/%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@
#	$(CXX) -o $@ -c $< $(CXXFLAGS)
#	$(CXX) $(CXXFLAGS) -c $< -o $@
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)




#~~~~~~~~~~~~~~~~~~~~ Eye candy ~~~~~~~~~~~~~~~~~~~~
begin:
	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
	@echo

sizebefore:
	@if test -f $(TARGET); then echo;		\
	echo $(MSG_SIZE_BEFORE);				\
	$(SIZE) $(TARGET);						\
	2>/dev/null; echo; fi

sizeafter:
	@if test -f $(TARGET); then echo;		\
	echo $(MSG_SIZE_AFTER);					\
	$(SIZE) $(TARGET);						\
	2>/dev/null; echo; fi

gccversion : 
	@$(CC) --version

#~~~~~~~~~~~~~~~~~~~~ clean ~~~~~~~~~~~~~~~~~~~~
clean: begin clean_list end

clean_list:
#	rm -f $(OBJS)
#	rm -f $(TARGET)
	rm -rf $(OBJDIR)
#	rm -rf $(BINDIR)
	rm -rf .dep

install: really_install clean

really_install:
#	mv $(TARGET) ../$(TARGET)
	cp $(TARGET) ../../../lib/$(TARGET)
	ln -s $(VPATH)/framework/include ../../../include/hros1_framework
	ln -s $(VPATH)/linux/include ../../../include/hros1_linux

#~~~~~~~~~~~~~~~~~~~~ backup ~~~~~~~~~~~~~~~~~~~~
backup: clean
	tar cJvf ../$(PROJECT_NAME)_`date +"%Y-%m-%d_%H%M"`.tar.xz *

#~~~~~~~~~~~~~~~~~~~~ phony ~~~~~~~~~~~~~~~~~~~~
.PHONY: all

# Include the dependency files. 
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


endif
