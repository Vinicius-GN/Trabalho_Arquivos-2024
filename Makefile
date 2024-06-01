all: programaTrab.o manipulacao_dados.o funcionalidades_intr.o vetorIndex.o funcionalidades_trab1.o abordagem_dinamica.o getset_dados.o lista_trabintr.o
	gcc -o programaTrab programaTrab.o manipulacao_dados.o funcionalidades_intr.o funcionalidades_trab1.o vetorIndex.o abordagem_dinamica.o getset_dados.o lista_trabintr.o
	
manipulacao_dados.o: manipulacao_dados.c
	gcc -c manipulacao_dados.c 
	
programaTrab.o: programaTrab.c
	gcc -c programaTrab.c 

funcionalidades_intr.o: funcionalidades_intr.c
	gcc -c funcionalidades_intr.c

index.o: funcionalidades_trab1.c
	gcc -c funcionalidades_trab1.c

vetorIndex.o: vetorIndex.c 
	gcc -c vetorIndex.c;

abordagem_dinamica.o: abordagem_dinamica.c
	gcc -c abordagem_dinamica.c

getset_dados.o: getset_dados.c
	gcc -c getset_dados.c

lista_trabintr.o: lista_trabintr.c
	gcc -c lista_trabintr.c

copy:
	rm -f b1.bin indice.bin
	cp "/home/vinicius/Desktop/arquivos/Entrada/binario10.bin" "/home/vinicius/Desktop/trabalho_arquivos/b1.bin"

clean:
	rm -f programaTrab programaTrab.o manipulacao_dados.o funcionalidades_intr.o funcionalidades_trab1.o vetorIndex.o abordagem_dinamica.o getset_dados.o lista_trabintr.o

run:
	./programaTrab