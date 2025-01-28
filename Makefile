SRC_DIR = src
OBJ_DIR = obj
LIST_C = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(LIST_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OPTIONS = gcc -g -Wall -pthread -I include
EXECUTE = duplicados
EXECUTE_DIR = output
MD5LIB = mode/md5-lib/libmd5.a
# Mostrar variables
# show-vars:
#     $(info OBJ=$(OBJ))

all: prepare $(EXECUTE_DIR)/$(EXECUTE)

prepare:
	mkdir -p $(OBJ_DIR) $(EXECUTE_DIR)

$(EXECUTE_DIR)/$(EXECUTE): $(OBJ)
	$(OPTIONS) -o $@ $^ $(MD5LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(OPTIONS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(EXECUTE_DIR)