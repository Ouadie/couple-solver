OS := $(shell uname -s)

ifeq ($(OS), Linux)
	INCLUDES = -lcurses
else
	INCLUDES =
endif

all: force_vector.o unit_num.o main.o clear_term.o convert.o point.o system.o
	@echo linking executable
	@g++ $^ -o vector.exe $(INCLUDES)

main.o: main.cpp convert.o
	@echo compiling main
	@g++ -c main.cpp $(INCLUDES)

test: force_vector.o unit_num.o test.o clear_term.o convert.o point.o system.o
	@echo linking executable
	@g++ $^ -o test $(INCLUDES)

test.o: test.cpp convert.o
	@echo compiling test
	@g++ -c test.cpp $(INCLUDES)

system.o: system.cpp system.h
	@echo compiling system
	@g++ -c system.cpp $(INCLUDES)
	
point.o: point.cpp point.h
	@echo compiling point
	@g++ -c point.cpp $(INCLUDES)

force_vector.o: force_vector.cpp force_vector.h convert.o
	@echo compiling force_vector
	@g++ -c force_vector.cpp $(INCLUDES)

unit_num.o: unit_num.cpp unit_num.h convert.o
	@echo compiling unit_num
	@g++ -c unit_num.cpp $(INCLUDES)

clear_term.o: clear_term.h clear_term.cpp
	@echo compiling clear_term
	@g++ -c clear_term.cpp $(INCLUDES)

convert.o: convert.h convert.cpp
	@echo compiling convert
	@g++ -c convert.cpp $(INCLUDES)


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
