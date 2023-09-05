# The compiler : gcc for C program :
CC = gcc

# Compiler flags :
CFLAGS = -ansi -pedantic-errors -Wall -Wextra

# Valgrind
VALGRIND = valgrind --leak-check=yes --track-origins=yes

# Debug
DEBUG = gdb -tui

#Remove
RM = rm -rf

# Archive
AR = ar -rcs

# Source file
SRC = ../../src/vector.c

# Source object file
O_SRC = ../../bin/objects/vector.o

# Header file
HEADER = ../../include/vector.h

# Path to header
PATH_TO_HEADER = -I../../include/

# Main file
MAIN = ../../test/vector/vector_test.c

# Main file
O_MAIN = ../../bin/objects/vector_test.o

# The build target executable
TARGET = ../../bin/executables/vector

# Static Lib names
S_LIB = ../../bin/static_libs/libvector.a

# Shared Lib names
SO_NAME = ../../bin/shared_libs/libvector.so

# Shared lib path
PATH_TO_SO = -L../../bin/shared_libs

# Static lib path
PATH_TO_S = -L../../bin/static_libs

# Files of the project
C_FILES = $(MAIN) $(SRC)

# Files of the project
O_FILES = $(O_MAIN) $(O_SRC)

.PHONY : run leak release debug lib.a lib.so link_shared link_static clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADER)
	$(CC) $(CFLAGS) $(O_FILES) -o $(TARGET) -lm

#******************************************************************************

$(O_MAIN) : $(SRC) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(MAIN) -o $(O_MAIN)

$(O_SRC) : $(MAIN) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)

#******************************************************************************

run : $(TARGET)
	$(TARGET)

#******************************************************************************

leak : $(TARGET)
	$(VALGRIND) $(TARGET)

#******************************************************************************

link_static : lib.a $(O_FILES)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(MAIN) $(PATH_TO_S) -lvector -o $(TARGET)_lstatic
	clear

#******************************************************************************

lib.a : $(O_FILES)
	$(AR) $(S_LIB) $(O_SRC)
	ranlib $(S_LIB)
	clear

#******************************************************************************

link_shared : lib.so
	$(CC) $(PATH_TO_HEADER) $(PATH_TO_SO) -Wl,-rpath=$(PATH_TO_SO) -Wall $(MAIN) -lvector -o $(TARGET)_lshared
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
	clear
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(S_LIB)


#******************************************************************************

# When including: put the $(EXTERNAL_O_SRC) $(EXTERNAL_SRC) with the c files and o files.
# Put the variables in the top section of the make file and the rule in the objects rull section.
# In the header file remember to include the external header

# External dependency src
# EXTERNAL_SRC = ../../bin/objects/?.c

# External dependency object
# EXTERNAL_O_SRC = ../../src/?.o

#$(EXTERNAL_O_SRC) : $(EXTERNAL_SRC) $(EXTERNAL_HEADER)
#	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC) -o $(EXTERNAL_O_SRC)
#	clear
