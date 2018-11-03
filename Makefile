CFLAGS=-std=c99 -Wall -pedantic
FICHEIROS=flight_analysis.c flight_analysis.h menus_options.c menus_options.h config_model.txt tf_prog2018_19_intermedio.pdf Makefile 
EXECUTAVEL=flight_analysis
COMMANDS = zip gcc

$(EXECUTAVEL): flight_analysis.o menus_options.o Makefile
	gcc -o $(EXECUTAVEL) flight_analysis.o menus_options.o

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
menus_options.o: menus_options.c flight_analysis.h menus_options.h