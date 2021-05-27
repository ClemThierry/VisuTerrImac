# $(BIN) est le nom du binaire généré
BIN = visu
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./
# INCLUDES
LIBS = -lglut -lGLU -lGL -lm
# INCLUDES
LIBDIR =
# Compilateur
GCC = gcc
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS = gldrawing.o visu.o create_object.o

default: $(BIN)

all: $(OBJECT)

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

visu.o: visu.c visu.h
	@echo "**** td1_maze.c ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

gl_drawing.o: gl_drawing.c gl_drawing.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

create_object.o: create_object.c create_object.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;
