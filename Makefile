#Setup compiler and key flags
CC = gcc
CPPFLAGS = -O0 -Wall -Wextra -Werror -mavx2 -g -fopenmp
LIB_PATHS = -lm
TARGET = acacgs

#Define the build directory
BUILD_DIR = ./build

#Define critical C files
CC_LIST =main.c generate_matrix.c conjugateGradient.c sparsemv.c waxpby.c ddot.c compute_residual.c mytimer.c

#If you are using Silo, append the writer file to the compilation list, and add required flags
ifdef SILO
SILO_DIR = /modules/cs257/silo-4.11
CC_LIST += silo_writer.c
CPPFLAGS += -DUSING_SILO -I$(SILO_DIR)/include
LIB_PATHS += -L$(SILO_DIR)/lib -lsilo
endif

#If you want it to print out stuff, add the USING_VERBOSE flag
ifdef VERBOSE
CPPFLAGS += -DUSING_VERBOSE
endif

#Generate the object names and paths, now that the list is complete

CC_OBJ_LIST := $(CC_LIST:%.c=$(BUILD_DIR)/%.o)

#----- TARGETS -----
#Default behaviour for the Makefile is to clean, then compile each CXX file into an object file, then link it all together
all: $(CC_OBJ_LIST) $(TARGET)

#Compile the final program
$(TARGET):
	$(CC) $(CC_OBJ_LIST) $(CPPFLAGS) $(LIB_PATHS) -o $(TARGET)

#Compile each raw code file into an object file, in the correct build directory
$(CC_OBJ_LIST): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CPPFLAGS) $< -o $@

#Cleanup anything that might be left over...
.PHONY: clean
clean:
	@rm -f *.o $(TARGET)
	@rm -rf $(BUILD_DIR)
