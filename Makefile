all: programaTrab.o utils.o funcionalidades_intr.o vetorIndex.o funcionalidades_trab1.o utils_trab1.o
	gcc -o programaTrab programaTrab.o utils.o funcionalidades_intr.o funcionalidades_trab1.o vetorIndex.o utils_trab1.o
	
utils.o: utils.c
	gcc -c utils.c 
	
programaTrab.o: programaTrab.c
	gcc -c programaTrab.c 

funcionalidades_intr.o: funcionalidades_intr.c
	gcc -c funcionalidades_intr.c

index.o: funcionalidades_trab1.c
	gcc -c funcionalidades_trab1.c

vetorIndex.o: vetorIndex.c 
	gcc -c vetorIndex.c;

utils_trab1.o: utils_trab1.c
	gcc -c utils_trab1.c

copy:
	rm -f b1.bin indice.bin
	cp "C:\Users\gutoc\Documents\GitHub\trabalho_arquivos\b1.bin" "C:\Users\gutoc\Documents\GitHub\trabalho_arquivos\binario10.bin"
clean:
	rm -f programaTrab programaTrab.o utils.o funcionalidades_intr.o funcionalidades_trab1.o vetorIndex.o utils_trab1.o 

run:
	./programaTrab