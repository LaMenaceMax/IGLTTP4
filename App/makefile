# Parameters
CXX = g++ -std=c++11

# Actions
COMPILE = $(CXX) -c
LINK = $(CXX)

OBJECTS = fichierIm.o \
		  canal.o \
		  fonctions.o \
		  nrfourn.o \
		  image.o \
		  menu.o \

all: tp \
	clean

# Object files
%.o: %.cpp
	$(COMPILE) $+ -o $@

# Cleaning
clean:
	rm -Rf *.o
	@echo "--"
	@echo "Cleaned."

# Main target
tp: $(OBJECTS)
	$(LINK) -o tp2 $(OBJECTS) $(LIBS)
	@echo "--"
	@echo "Done."
