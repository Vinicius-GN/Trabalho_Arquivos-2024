all: programaTrab.o utils.o funcionalidades_intr.o vetorIndex.o index.o
	gcc -o programaTrab programaTrab.o utils.o funcionalidades_intr.o index.o vetorIndex.o
	
utils.o: utils.c
	gcc -c utils.c 
	
programaTrab.o: programaTrab.c
	gcc -c programaTrab.c 

funcionalidades_intr.o: funcionalidades_intr.c
	gcc -c funcionalidades_intr.c

index.o: index.c
	gcc -c index.c

vetorIndex.o: vetorIndex.c 
	gcc -c vetorIndex.c;

clean:
	rm -f programaTrab programaTrab.o utils.o funcionalidades_intr.o index.o vetorIndex.o

run:
	./programaTrab