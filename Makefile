CFLAGS=-std=c99 -Wall -pedantic
FICHEIROS=flight_analysis.c flight_analysis.h menus_options.c menus_options.h calculo.c calculo.h config_model.txt Makefile 
EXECUTAVEL=flight_analysis
COMMANDS = zip gcc

$(EXECUTAVEL): flight_analysis.o menus_options.o calculo.o Makefile
	gcc -o $(EXECUTAVEL) flight_analysis.o menus_options.o calculo.o -lm -lSDL2 -lSDL2_image

install:
	sudo apt install $(COMMANDS)

doc:
	doxygen -g
	doxygen

zip: $(FICHEIROS)
	zip -9 flight_analysis.zip $(FICHEIROS)

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

flight_analysis.o: flight_analysis.c flight_analysis.h menus_options.h
menus_options.o: menus_options.c flight_analysis.h menus_options.h calculo.h calculo.o
calculo.o: calculo.c calculo.h