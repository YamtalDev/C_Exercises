# The compiler : gcc for C program :
CC = gcc

# Compiler flags :
CFLAGS =

# Valgrind
VALGRIND = valgrind --leak-check=yes --track-origins=yes

# Debug
DEBUG = gdb -tui

#Remove
RM = rm -rf

# Archive
AR = ar -rcs

# Source file
SRC = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/src/memory_mapping_full.c

# Source object file
O_SRC = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/objects/memory_mapping_full.o

# Header file
HEADER = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/include/memory_mapping_full.h

# Path to header
PATH_TO_HEADER = -I/home/tal/Documents/Infinity/work/tal.aharon/system_programing/include/

# Main file
MAIN = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/test/memory_mapping_full/memory_mapping_full_test.c

# Main file
O_MAIN = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/objects/memory_mapping_full_test.o

# The build target executable
TARGET = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/executables/memory_mapping_full

# Static Lib names
S_LIB = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/static_libs/libmemory_mapping_full.a

# Shared Lib names
SO_NAME = /home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/shared_libs/libmemory_mapping_full.so

# Shared lib path
PATH_TO_SO = -L/home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/shared_libs

# Static lib path
PATH_TO_S = -L/home/tal/Documents/Infinity/work/tal.aharon/system_programing/bin/static_libs

# Files of the project
C_FILES = $(MAIN) $(SRC)

# Files of the project
O_FILES = $(O_MAIN) $(O_SRC)

.PHONY : run leak release debug lib.a lib.so link_shared link_static clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADER)
	$(CC) $(CFLAGS) $(O_FILES) -o $(TARGET)
	clear

#******************************************************************************

$(O_MAIN) : $(SRC) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(MAIN) -o $(O_MAIN)
	clear

$(O_SRC) : $(MAIN) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)
	clear

#******************************************************************************

run : $(TARGET)
	clear
	$(TARGET)

#******************************************************************************

leak : $(TARGET)
	$(VALGRIND) $(TARGET)
	clear

#******************************************************************************

link_static : lib.a $(O_FILES)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(MAIN) $(PATH_TO_S) -lmemory_mapping_full -o $(TARGET)_lstatic
	clear

#******************************************************************************

lib.a : $(O_FILES)
	$(AR) $(S_LIB) $(O_SRC)
	ranlib $(S_LIB)
	clear

#******************************************************************************

link_shared : lib.so
	$(CC) $(PATH_TO_HEADER) $(PATH_TO_SO) -Wl,-rpath=$(PATH_TO_SO) -Wall $(MAIN) -lmemory_mapping_full -o $(TARGET)_lshared
	clear

#******************************************************************************

lib.so : CFLAGS += -fPIC -c
lib.so : 
	$(RM) $(TARGET) $(O_SRC)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)
	$(CC) -shared -o $(SO_NAME) $(O_SRC)
	clear

#******************************************************************************

debug : CFLAGS += -DDEBUG_ON -g
debug : $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)
	$(DEBUG) $(TARGET)
	clear

#******************************************************************************

release : CFLAGS += -DNDEBUG -O3
release : $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)
	clear

#******************************************************************************

clean :
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(S_LIB)
	clear

#******************************************************************************

#External dependancies
#ex.o  : CFLAGS += -c
#ex.o  :  ../ex/ex.c ../ex/ex.h
#	$(CC) $(CFLAGS) ../ex/ex.c
