#include "defined.h"
typedef enum { true, false } pista; 
/*
cuore pulsante del progetto legge i messaggi inviati da hangar ed aerei decide il 
decollo degli aerei 
*/
void torredicontrollo(){
    pista p1 = true; 
    pista p2 = true; 
    int richieste_aerei[10];
    int i = 0;  
    printf("avvio torre\n");
    int wstatus, fd, iReadCount = 1;
    struct tdati stdati;
    fd = open(AEREO_TORRE_PATH, O_RDONLY);                
    //if ((iReadCount = read(fd, &stdati, sizeof(stdati))) > 0 ){
    stdati.s[0] = '\0';
    //printf("1\n");
    while (strcmp(stdati.s, "aerei terminati")) {
        if (iReadCount= read(fd, &stdati, sizeof(stdati)) > 0 ){
        //printf("%d",iReadCount);
        //printf("id %d\n",stdati.nome_aereo);
        if (strcmp(stdati.s, "aereo pronto al decollo") == 0 ){
                    printf("aereo %d %s\n", stdati.nome_aereo, stdati.s);
                    //sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);
                    while (i < 10){
                        printf ("1\n");
                        printf("id %d\n", stdati.nome_aereo);
                        //sem_wait(sem);
                        richieste_aerei [i] = stdati.nome_aereo;
                        //printf("id %d\n",richieste_aerei[i]);
                        if (p1 == true) {
                            // torre di controllo autorizza il decollo 
                            p1 = false; 
                            printf("2\n");
                            printf("aereo:%d\n",stdati.nome_aereo);
                            int ft= open (TORRE_AEREO_PATH,O_WRONLY);
                                strcpy(stdati.s2,"decollo autorizzato pista 1");
                                if(write(ft, &stdati, sizeof(stdati)) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                 else {
                                        printf("%s\n",stdati.s2);
                                        printf("messaggio inviato correttamente\n"); 
                                    }
                                    close(ft);
                                    printf("3\n");
                                    break; 
                        }
                        else if ( p2 ==  true) {
                            // torre di controllo autorizza decollo alla p2
                            p2 = false; 
                            printf("4\n");
                            int ndati;
                            printf("aereo:%d\n",stdati.nome_aereo);
                            int ft = open (TORRE_AEREO_PATH,O_WRONLY);
                            printf("89\n "); 
                             strcpy(stdati.s2,"decollo autorizzato pista numero 2");
                             printf("%s\n",stdati.s2);
                             printf("PORCO DIOOOOOOOOOOOOOOOO\n");
                              if((ndati = write(ft, &stdati, sizeof(stdati))) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                 else {
                                    printf("69\n");
                                    printf("%d\n ", ndati);
                                    printf("%s\n",stdati.s2);
                                    printf("messaggio inviato correttamente torre\n"); 
                                    }
                                    close(ft);
                                    printf("5\n");
                                break; 
                        }
                        i++; 
                    }
                    //kill(stdati.cod,SIGRTMIN + 1);
                }
                else{
                    printf("%s\n",stdati.s);
                }
            }
        }
        close (fd);
       // sem_post(sem);
        //printf("2\n");
    }
//}