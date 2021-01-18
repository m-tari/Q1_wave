# Makefile for Wave

# use gcc compiler
CC   = gcc

############################
###      DIRECTORIES     ###
############################

# SDIR: directory containing the source files (.c)
SDIR   = src

# ODIR: directory containing the object files (.o)
ODIR   = obj

# HDIR: directory containing the header files (.h)
HDIR   = head

BINDIR = bin


L_GENERAL    = -lpthread -lm -ldl -Wall
LIBS_WAVE  = $(L_GENERAL)

I_HEAD       = -I$(HDIR)

EXE          = $(BINDIR)/wave

# list of flags to pass to the compilation command:
CFLAGS_WAVE  = -I$(HDIR)
CFLAGS_DEBUG = -g -I$(HDIR)

TARGETS      =  $(EXE)

############################
###        FILES         ###
############################

# functions library
SRC     = $(wildcard $(SDIR)/*.c)
HEAD    = $(wildcard $(HDIR)/*.h)
OBJ     = $(subst $(SDIR),$(ODIR),$(patsubst %.c,%.o,$(SRC))) 


############################
###   RULES DEFINITION   ###
############################

# Target to make
# Call "make wave" or "make" to use
.PHONY: wave
wave: CFLAGS = $(CFLAGS_WAVE)
wave: LIBS   = $(LIBS_WAVE)
wave: $(TARGETS)

# Call "make debug" to use
.PHONY: debug
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: LIBS   = $(LIBS_WAVE)
debug: $(TARGETS)

# compilation
$(ODIR)/%.o: $(SDIR)/%.c  $(HEAD)
	$(CC) $(CFLAGS) $(I_HEAD) -c -o $@ $<

# make obj dir if it does not exist
$(OBJ): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

# object files are prerequisites
$(EXE): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)
	@echo "Compiled executable"


clean:
	rm -f $(ODIR)/*.o $(BINDIR)/wave	
