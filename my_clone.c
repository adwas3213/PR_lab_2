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


    zmienna_lokalna= *((int *)argument);
    for(int i=0;i<100000;i++)
    {
      zmienna_lokalna =zmienna_lokalna+1;
    }

    /* int wynik; */
    /* wynik=execv("./program",NULL); */
    /* if(wynik==-1) */
    /*   printf("Proces potomny nie wykonal programu\n"); */

    printf("Zmienna przekazana do funkcji za zmienna lokalna %d\n",zmienna_lokalna);
    return 0;
}

int funkcja_watku_wykorzystujaca_argument( void* argument )
{

    /* int wynik; */
    /* wynik=execv("./program",NULL); */
    /* if(wynik==-1) */
    /*   printf("Proces potomny nie wykonal programu\n"); */
    printf("Wykonana funkcja wykorzystujaca argument");
    drukuj_czas();

    return 0;
}

main()
{

    void *stos,*stos2;
    pid_t pid,pid2;
    int i;

    stos = malloc( ROZMIAR_STOSU );
    stos2 = malloc( ROZMIAR_STOSU );
    if (stos == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit( 1 );
    }

    int przekazywany=0;
    void* wsk=&przekazywany;
    pid=clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,
               CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, wsk );
    pid2=clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU,
                CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, wsk);
    waitpid(pid, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);
//    drukuj_czas();
    printf("Przekazywana wartosc to : %d",przekazywany);

    free( stos );
    free(stos2);
}