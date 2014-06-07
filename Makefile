MAINDIR = $(CURDIR)
SRC     = $(MAINDIR)/src
INC     = $(MAINDIR)/inc

CSRC    = $(wildcard $(SRC)/*.c)
CSRC   += $(wildcard $(SRC)/inst/*.c)
OBJ     = $(patsubst %.c,%.o,$(CSRC))
EXEC    = $(MAINDIR)/bacpu

DEFS   += -D_POSIX_C_SOURCE=199309L
LIBS   += -pthread
INCS   += -I $(INC)
CFLAGS += -Wall -Wextra -Werror -std=c99 $(DEFS) $(LIBS) $(INCS)
# CFLAGS += -g

all: $(OBJ)
	@echo "  Creating CPU binary"
	@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean:
	@rm -f $(OBJ) $(EXEC)

%.o: %.c
	@echo " CC $<"
	@$(CC) $(CFLAGS) -c -o $@ $<
