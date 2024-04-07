all: programaTrab.o utils.o
	gcc -o programaTrab programaTrab.o utils.o 
	

utils.o: utils.c
	gcc -c utils.c 
	
programaTrab.o: programaTrab.c
	gcc -c programaTrab.c 

clean:
	rm -f programaTrab programaTrab.o utils.o
run:
	./programaTrab