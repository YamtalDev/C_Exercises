# Path to files
PATH_TO_DIR = /home/tal/Documents/Infinity/work/tal.aharon/ds/sorting/linear_sort

# The compiler : gcc for C program :
CC = gcc

# Compiler flags :
CFLAGS = -ansi -pedantic-errors -Wall -Wextra

# Valgrind
VALGRIND = valgrind --leak-check=yes --track-origins=yes

#Remove
RM = rm -rf

# Static Lib names
LIB_NAME = liblinear_sort.a

# Archive
AR = ar rcs

# Shared Lib names
SO_NAME = liblinear_sort.so

# Debug
DEBUG = gdb -tui

# Lib flags
LIB_FLAGS = -L. -llinear_sort

# Files of the project
C_FILES = linear_sort.c linear_sort_test.c

# Files of the project
O_FILES = linear_sort.o linear_sort_test.o

#Header
HEADER = linear_sort.h

# The build target executable
TARGET = linear_sort.out

.PHONY : run leak release debug lib.a lib.so clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADER)
	clear
	$(CC) $(CFLAGS) $(C_FILES) -o $(TARGET)
	ls

#******************************************************************************

linear_sort.o : linear_sort.c linear_sort.h

linear_sort_test.o : linear_sort_test.c linear_sort.h

#******************************************************************************

run : $(TARGET)
	clear
	./$(TARGET)

#******************************************************************************

leak : CFLAGS += -DDEBUG_ON -g
leak : clean $(TARGET)
	$(VALGRIND) ./$(TARGET)

#******************************************************************************

lib.a : $(LIB_NAME) $(O_FILES)
	$(CC) $(CFLAGS) linear_sort_test.c $(LIB_FLAGS) -o $(TARGET)
	ls

#******************************************************************************

$(LIB_NAME) : $(O_FILES)
	clear
	$(AR) $(LIB_NAME) linear_sort.o
	ranlib $(LIB_NAME)

#******************************************************************************

lib.so : CFLAGS += -fPIC -c
lib.so :
	clear
	$(RM) $(TARGET) linear_sort.o
	$(CC) $(CFLAGS) linear_sort.c
	$(CC) -shared -o $(SO_NAME) linear_sort.o
	$(CC) -L$(PATH_TO_DIR) -Wl,-rpath=$(PATH_TO_DIR) -Wall -o $(TARGET) linear_sort_test.c -llinear_sort

#******************************************************************************

debug : CFLAGS += -DDEBUG_ON -g
debug : $(TARGET)
	clear
	$(CC) $(CFLAGS) $(C_FILES) -o $(TARGET)
	$(DEBUG) $(TARGET)

#******************************************************************************

release : CFLAGS += -DNDEBUG -O3
release : $(TARGET)
	clear
	$(CC) $(CFLAGS) $(C_FILES) -o $(TARGET)
	ls

#******************************************************************************

clean :
	clear
	$(RM) $(TARGET) *.a *.o *.so
	ls

#******************************************************************************

#External dependancies
#ex.o  : CFLAGS += -c
#ex.o  :  ../ex/ex.c ../ex/ex.h
#	$(CC) $(CFLAGS) ../ex/ex.c
