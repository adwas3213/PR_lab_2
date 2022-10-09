//
// Created by Adam on 09.10.2022.
//

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include "pomiar_czasu/pomiar_czasu.h"
int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
    for(int i=0;i<100000;i++)
    zmienna_globalna++;

    /* int wynik; */
    /* wynik=execv("./program",NULL); */
    /* if(wynik==-1) */
    /*   printf("Proces potomny nie wykonal programu\n"); */
    drukuj_czas();
    printf("Wykonana funkcja wykorzystujaca zmienna globalna");
    return 0;
}

int funkcja_watku_wykorzystujaca_argument( void* argument )
{
    for(int i=0;i<100000;i++)
        (*argument)+=1;

    /* int wynik; */
    /* wynik=execv("./program",NULL); */
    /* if(wynik==-1) */
    /*   printf("Proces potomny nie wykonal programu\n"); */
    drukuj_czas();
    printf("Wykonana funkcja wykorzystujaca argument");
    return 0;
}

main()
{

    void *stos;
    pid_t pid,pid2;
    int i;

    stos = malloc( ROZMIAR_STOSU );
    if (stos == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit( 1 );
    }

    int przekazywany=0;
    inicjuj_czas();
    pid=clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,
               CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
    pid2=clone( &funkcja_watku_wykorzystujaca_argument, (void *) stos+ROZMIAR_STOSU,
                CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &przekazywany );
//    drukuj_czas();

    free( stos );
}