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
SRC = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/src/dll.c

# Source object file
O_SRC = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/objects/dll.o

# Header file
HEADER = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/include/dll.h

# Path to header
PATH_TO_HEADER = -I/home/tal/Documents/Infinity/work/tal.aharon/C/ds/include/

# Main file
MAIN = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/test/dll/dll_test.c

# Main file
O_MAIN = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/objects/dll_test.o

# The build target executable
TARGET = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/executables/dll

# Static Lib names
S_LIB = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/static_libs/libdll.a

# Shared Lib names
SO_NAME = /home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/shared_libs/libdll.so

# Shared lib path
PATH_TO_SO = -L/home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/shared_libs

# Static lib path
PATH_TO_S = -L/home/tal/Documents/Infinity/work/tal.aharon/C/ds/bin/static_libs

# Files of the project
C_FILES = $(MAIN) $(SRC)

# Files of the project
O_FILES = $(O_MAIN) $(O_SRC)

.PHONY : run leak release debug lib.a lib.so link_shared link_static clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADER)
	$(CC) $(CFLAGS) $(O_FILES) -o $(TARGET)


#******************************************************************************

$(O_MAIN) : $(MAIN) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(MAIN) -o $(O_MAIN)

$(O_SRC) : $(SRC) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)

#******************************************************************************

run : $(TARGET)
	$(TARGET)

#******************************************************************************

leak : $(TARGET)
	$(VALGRIND) $(TARGET)

#******************************************************************************

link_static : lib.a $(O_FILES)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(MAIN) $(PATH_TO_S) -ldll -o $(TARGET)

#******************************************************************************

lib.a : $(O_FILES)
	$(AR) $(S_LIB) $(O_SRC)
	ranlib $(S_LIB)

#******************************************************************************

link_shared : lib.so
	$(CC) $(PATH_TO_HEADER) $(PATH_TO_SO) -Wl,-rpath=$(dir $(SO_NAME)) -Wall $(MAIN) -ldll -o $(TARGET)

#******************************************************************************

lib.so : CFLAGS += -fPIC -c
lib.so : 
	$(RM) $(TARGET) $(O_SRC)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)
	$(CC) -shared -o $(SO_NAME) $(O_SRC)

#******************************************************************************

debug : CFLAGS += -DDEBUG_ON -g
debug : $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)
	$(DEBUG) $(TARGET)

#******************************************************************************

release : CFLAGS += -DNDEBUG -O3
release : $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)

#******************************************************************************

clean :
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(S_LIB)

#******************************************************************************
