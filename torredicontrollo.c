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
    printf("avvio torre\n");
    int wstatus, fd, iReadCount = 1;
    struct tdati stdati;
    fd = open(AEREO_TORRE_PATH, O_RDONLY | O_NONBLOCK);                
    //if ((iReadCount = read(fd, &stdati, sizeof(stdati))) > 0 ){
    stdati.s[0] = '\0';
      int i = 0; 
    while (strcmp(stdati.s, "aerei terminati")) {
        if (iReadCount= read(fd, &stdati, sizeof(stdati)) > 0 ){
        //printf("%d",iReadCount);
        //printf("id %d\n",stdati.nome_aereo);
        if (strcmp(stdati.s, "aereo pronto al decollo") == 0 ){
                    printf("aereo %d %s\n", stdati.nome_aereo, stdati.s);
                        //sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 2);
                        printf ("1\n");
                        printf("richiesta presa in carico attendere i decolli\n");
                        printf("id = %d\n",i);
                        richieste_aerei [i] = stdati.nome_aereo;     
                        i++;  
                    //kill(stdati.cod,SIGRTMIN + 1);
                }
                if (p1 == true) {
                            // torre di controllo autorizza il decollo 
                            p1 = false; 
                            stdati.p =1;
                            printf("2\n");
                            int ft = open (TORRE_AEREO_PATH,O_WRONLY|O_NONBLOCK);
                                strcpy(stdati.s2,"decollo autorizzato pista 1");
                                if(write(ft, &stdati, sizeof(stdati)) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                 /*else {
                                        //printf("%s\n",stdati.s2);
                                        printf("messaggio inviato correttamente\n"); 
                                    }*/
                                    close(ft);
                                    }
                        else if ( p2 ==  true) {
                            // torre di controllo autorizza decollo alla p2
                            p2 = false; 
                            stdati.p =2;
                            printf("4\n");
                            int ndati;
                            //printf("aereo:%d\n",stdati.nome_aereo);
                            int ft = open (TORRE_AEREO_PATH,O_WRONLY |O_NONBLOCK);
                             strcpy(stdati.s2,"decollo autorizzato pista numero 2");
                              if((ndati = write(ft, &stdati, sizeof(stdati))) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                 /*else {
                                    //printf("%d\n ", ndati);
                                    //printf("%s\n",stdati.s2);
                                    printf("messaggio inviato correttamente torre\n"); 
                                    }*/
                                    close(ft);   
                                }
                                else if (p1 == false || p2 == false ){
                                    int fs= open(DECOLLO_AEREO_PATH,O_RDONLY|O_NONBLOCK);
                                    int readstring = 1; 
                                     stdati.s3[0] = '\0';
                                     printf("17\n");
                                     if (readstring = read(fs, &stdati, sizeof(stdati)) > 0 ){
                                     if ( strcmp(stdati.s3, "aereo decollato da pista 1") == 0  ){
                                        printf("18\n");
                                        printf("%s %d\n",stdati.s3,stdati.nome_aereo);
                                        p1 = true; 
                                        }   
                                     }
                                        else {
                                            printf("errore\n ");
                                        }
                                    if (iReadCount= read(fs, &stdati, sizeof(stdati)) > 0 && strcmp(stdati.s3, "aereo decollato da pista  2") == 0 ){
                                        printf("19\n");
                                        printf("%s %d\n",stdati.s3,stdati.nome_aereo);
                                        p2 = true;
                                    }
                                         close(fs);
                                }
                                else if (strcmp(stdati.s, "aerei terminati") == 0){
                                        printf("%s\n",stdati.s);
                                        }
                                    }
                            }
                             close (fd);
}
       // sem_post(sem);
        //printf("2\n");