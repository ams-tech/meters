INC_DIR = inc
SRC_DIR = src
OBJ_DIR = objs
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INC_FILES = $(shell find $(INC_DIR) -name '*.h')
CC = $(CROSS_COMPILE)gcc
CFLAGS = -I$(INC_DIR)

.PHONY: all
all:	meter_test

.PHONY: src_files
src_files:
	echo $(SRC_FILES)

.PHONY: obj_files
obj_files:
	echo $(OBJ_FILES)	

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#$< is the first item in the dependencies list
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES) $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

libmeter: $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf objs
	rm -f meter_test
