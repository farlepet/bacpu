MAINDIR = $(CURDIR)
SRC     = $(MAINDIR)/src
INC     = $(MAINDIR)/inc

CSRC    = $(wildcard $(SRC)/*.c)
CSRC   += $(wildcard $(SRC)/inst/*.c)
OBJ     = $(patsubst %.c,%.o,$(CSRC))
EXEC    = $(MAINDIR)/bacpu

CFLAGS  = -Wall -Wextra -Werror -std=c99 -I $(INC)

all: $(OBJ)
	@echo "  Creating CPU binary"
	@$(CC) $(OBJ) -o $(EXEC)

clean:
	@rm -f $(OBJ) $(EXEC)

%.o: %.c
	@echo " CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<
