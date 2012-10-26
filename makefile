CC=g++
CFLAGS=-I. -Wall -O3 -c
OBJDIR=lib
OBJ=$(OBJDIR)/main.o $(OBJDIR)/email.o
EXE=Email

.PHONY: all clean

all: $(EXE)

Email: $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@
	
$(OBJDIR):
	mkdir -p $@
	
clean:
	rm -rf $(OBJDIR) $(EXE) 
