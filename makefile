OS := $(shell uname -s)

ifeq ($(OS), Linux)
	INCLUDES = -lcurses
else
	INCLUDES =
endif

all: forceVector.o unit.o main.o clear_term.o convert.o
	@echo linking executable
	@g++ $^ -o vector.exe $(INCLUDES)

forceVector.o: forceVector.cpp forceVector.h convert.o
	@echo compiling forceVector
	@g++ -c forceVector.cpp $(INCLUDES)

unit.o: unit.cpp unit.h convert.o
	@echo compiling unit
	@g++ -c unit.cpp $(INCLUDES)

clear_term.o: clear_term.h clear_term.cpp
	@echo compiling clear_term
	@g++ -c clear_term.cpp $(INCLUDES)

convert.o: convert.h convert.cpp
	@echo compiling convert
	@g++ -c convert.cpp $(INCLUDES)

main.o: main.cpp convert.o
	@echo compiling main
	@g++ -c main.cpp $(INCLUDES)

clean:
	@echo 'cleaning binary files'
	rm -f *.o  *.aux *.log 
	rm -f vector.exe

doc.pdf: doc.tex
	@echo 'compilling pdf'
	@pdflatex doc.tex

zip: clean all doc.pdf
	@echo 'building zip'
	zip everetc1 *.cpp *.h makefile doc.pdf
