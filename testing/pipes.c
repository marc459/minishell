#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(){

     int fd1[2], fd2[2];
     char buffer[30], buffer2[30];

     pid_t pid, pidNieto;

     pipe(fd1);
     pipe(fd2);

     pid = fork();

     switch(pid){

          case -1: // Error
                printf("Ha habido un error \n");
                exit(-1);
                break;
          case 0: // Hijo
                close(fd1[0]);
                printf("Escribe el padre: \n");
                write(fd1[1], "El padre dice hola", 20);

                //Creación de nieto
                pidNieto = fork();

                switch(pidNieto){
                     case -1: // Error
                          printf("Ha habido un error \n");
                          exit(-1);
                          break;
                     case 0:
                          close(fd2[0]);
                          printf("Escribe el nieto \n");
                          write(fd2[1], "Soy el nieto", 13);
                          break;
                     default:
                          close(fd2[1]);
                          wait(NULL);
                          printf("El padre lee \n");
                          read(fd2[0], buffer2, 13);
                          printf("Mensaje leído: %s", buffer2);
                          break;
                }
                break;
          default: // Padre
                close(fd1[1]);
                wait(NULL); // Espero que finalice el nieto
                printf("\nEl abuelo lee: \n");
                read(fd1[0], buffer, 20);
                printf("Mensaje leído: %s \n", buffer);
                break;
     }

}