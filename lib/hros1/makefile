
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
        framework/src/controller/JoystickController.cpp \
        framework/src/commander/SerialInputCommander.cpp    \
        framework/src/minIni/minIni.cpp \
        linux/src/LinuxActionScript.cpp   \
        linux/src/LinuxCamera.cpp   \
        linux/src/LinuxCM730.cpp    \
        linux/src/LinuxMotionTimer.cpp    \
        linux/src/LinuxNetwork.cpp

#~~~~~~~~~~~~~~~~~~~~ Object Files ~~~~~~~~~~~~~~~~~~~~
BINDIR = bin
OBJDIR = obj

TARGET = $(BINDIR)/$(PROJECT_NAME)

CSRCS = $(filter %.c,$(SRCS))
CPPSRCS = $(filter %.cpp,$(SRCS))
RAWOBJS = $(CSRCS:.c=.c.o) $(CPPSRCS:.cpp=.cpp.o)
OBJS = $(addprefix $(OBJDIR)/,$(RAWOBJS))

#~~~~~~~~~~~~~~~~~~~~ Include Directories ~~~~~~~~~~~~~~~~~~~~
INCLUDE_DIRS = -I. -I./framework/include -I./linux/include

#~~~~~~~~~~~~~~~~~~~~ Library Directories ~~~~~~~~~~~~~~~~~~~~
LIBRARY_DIRS = -L.
LIBS = 

#~~~~~~~~~~~~~~~~~~~~ Compiler Options ~~~~~~~~~~~~~~~~~~~~
COMPILE_OPTS = -g -O3 -fno-common
COMPILE_OPTS += -Wall -Wextra -Wmain -pedantic -pedantic-errors -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default

#~~~~~~~~~~~~~~~~~~~~ Linker Options ~~~~~~~~~~~~~~~~~~~~
LINKER_OPTS = -s -ldl -lrt

#~~~~~~~~~~~~~~~~~~~~ Toolchain Prefix ~~~~~~~~~~~~~~~~~~~~
TCHAIN_PREFIX=

CC = $(TCHAIN_PREFIX)gcc
CFLAGS = $(INCLUDE_DIRS) $(COMPILE_OPTS)

CXX = $(TCHAIN_PREFIX)g++
CXXFLAGS = $(INCLUDE_DIRS) $(COMPILE_OPTS)

AS = $(TCHAIN_PREFIX)gcc
ASFLAGS = $(COMPILE_OPTS) -c

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
MSG_COMPILING_CPP = Compiling C++:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_CREATING_LIBRARY = Creating library:

#~~~~~~~~~~~~~~~~~~~~ all ~~~~~~~~~~~~~~~~~~~~
all: begin gccversion spotcheck sizebefore build sizeafter end

#~~~~~~~~~~~~~~~~~~~~ build ~~~~~~~~~~~~~~~~~~~~
spotcheck:
	@echo $(MSG_BUILD_DIRS)
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@echo

build: $(TARGET)

$(TARGET): $(OBJS)
#	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS) 

%.c.o: $(CSRCS)
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: $(CPPSRCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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
	echo $(MSG_SIZE_AFTER);				\
	$(SIZE) $(TARGET);						\
	2>/dev/null; echo; fi

gccversion : 
	@$(CC) --version

#~~~~~~~~~~~~~~~~~~~~ clean ~~~~~~~~~~~~~~~~~~~~
clean: begin clean_list end

clean_list:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

#~~~~~~~~~~~~~~~~~~~~ backup ~~~~~~~~~~~~~~~~~~~~
backup: clean
	tar cJvf ../$(PROJECT_NAME)_`date +"%Y-%m-%d_%H%M"`.tar.xz *

#~~~~~~~~~~~~~~~~~~~~ phony ~~~~~~~~~~~~~~~~~~~~
.PHONY: all

