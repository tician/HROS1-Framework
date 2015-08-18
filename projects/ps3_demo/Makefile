###############################################################
#
# Purpose: Makefile for "demo"
# Author.: robotis
# Version: 0.1
# License: GPL
#
###############################################################

TARGET = demo

INCLUDE_DIRS = -I../../include/hros1_framework -I../../include/hros1_linux

CXX = g++
CXXFLAGS += -g -O2 -DLINUX -Wall -std=gnu++0x $(INCLUDE_DIRS)
#CXXFLAGS += -O2 -DDEBUG -DLINUX -Wall $(INCLUDE_DIRS)
LFLAGS += -g -lpthread -ljpeg -lrt -lbluetooth

OBJECTS = StatusCheck.o main.o

all: $(TARGET)

clean:
	rm -f *.a *.o $(TARGET) core *~ *.so *.lo

#libclean:
#	make -C ../../src/hros1 clean

#distclean: clean libclean

hros1.a:
	@[ -f '../../lib/hros1.a' ] || ( make -C ../../src/hros1 && make -C ../../src/hros1 install )

$(TARGET): $(OBJECTS) hros1.a
	$(CXX) $(CFLAGS) $(OBJECTS) ../../lib/hros1.a -o $(TARGET) $(LFLAGS)
	chmod 755 $(TARGET)

# useful to make a backup "make tgz"
tgz: clean
	mkdir -p backups
	tar czvf ./backups/DARwIn_demo_`date +"%Y_%m_%d_%H.%M.%S"`.tgz --exclude backups *
