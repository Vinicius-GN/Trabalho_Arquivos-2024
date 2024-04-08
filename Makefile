all: programaTrab.o utils.o funcionalidades.o
	gcc -o programaTrab programaTrab.o utils.o funcionalidades.o
	

utils.o: utils.c
	gcc -c utils.c 
	
programaTrab.o: programaTrab.c
	gcc -c programaTrab.c 

funcionalidades.o: funcionalidades.c
	gcc -c funcionalidades.c

clean:
	rm -f programaTrab programaTrab.o utils.o funcionalidades.o
run:
	./programaTrab