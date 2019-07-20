all: exec

run: exec
	./exec
	
exec: SegmentaImagem.o main.o
	gcc -o exec SegmentaImagem.o main.o

main.o: main.c
	gcc -c main.c

SegmentaImagem.o: SegmentaImagem.c
	gcc -c SegmentaImagem.c