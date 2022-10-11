# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3 -std=c99

# pliki naglowkowe
INC = -Ipomiar_czasu

# biblioteki
LIB = -Lpomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 

my_clone.o: my_clone.c pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) my_clone.c $(INC)

my_clone: my_clone.o
	$(LOADER) $(OPT) my_clone.o -o my_clone $(LIB)

clean:
	rm -f *.o fork clone
