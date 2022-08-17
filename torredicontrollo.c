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
    int aereo_pista_1 ;
    int aereo_pista_2 ; 
    printf("avvio torre\n");
    int wstatus, fd, iReadCount = 1;
    struct tdati stdati;
    stdati.p =0; 
    fd = open(AEREO_TORRE_PATH, O_RDONLY);                
    //if ((iReadCount = read(fd, &stdati, sizeof(stdati))) > 0 ){
    stdati.s[0] = '\0';
      int i = 0; 
    while (strcmp(stdati.s, "aerei terminati")) {
        if (iReadCount= read(fd, &stdati, sizeof(stdati)) > 0 ){
        //printf("%d",iReadCount);
        //printf("id %d\n",stdati.nome_aereo);
        if (strcmp(stdati.s, "aereo pronto al decollo") == 0 ){
                    char si[256];
                    time_t timet;
                    time (&timet);
                    struct tm *pTm = localtime(&timet);
                    sprintf(si,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
                    printf("%s ", si); 
                    printf("aereo %d %s\n", stdati.nome_aereo, stdati.s);
                        //sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 2);
                        printf("richiesta presa in carico attendere i decolli\n");
                        printf("id = %d\n",i);
                        richieste_aerei [i] = stdati.nome_aereo;     
                        i++;  
                    //kill(stdati.cod,SIGRTMIN + 1);
                }
                if (p1 == true) {
                            // torre di controllo autorizza il decollo 
                            p1 = false;
                            aereo_pista_1 = stdati.nome_aereo;
                            int ft = open (TORRE_AEREO_PATH,O_WRONLY);
                                strcpy(stdati.s2,"decollo autorizzato pista 1");
                                if(write(ft, &stdati, sizeof(stdati)) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                    close(ft);
                                    }
                        else if ( p2 ==  true) {
                            // torre di controllo autorizza decollo alla p2
                            p2 = false; 
                            aereo_pista_2 = stdati.nome_aereo;
                            int ndati;
                            int ft = open (TORRE_AEREO_PATH,O_WRONLY );
                             strcpy(stdati.s2,"decollo autorizzato pista numero 2");
                              if((ndati = write(ft, &stdati, sizeof(stdati))) == -1) {
                                        perror("Torre: Errore in scrittura\n");
                                         }
                                 close(ft);   
                                }
                                else if (p1 == false || p2 == false ){
                                    int fs= open(DECOLLO_AEREO_PATH,O_RDONLY);
                                    int readstring = 1; 
                                    stdati.s3[0] = '\0';
                                    if (readstring = read(fs, &stdati, sizeof(stdati)) > 0 ){
                                     if ( strcmp(stdati.s3, "aereo decollato") == 0  ){
                                        char si[256];
                                        time_t timet;
                                        time (&timet);
                                        struct tm *pTm = localtime(&timet);
                                        sprintf(si,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
                                        printf("%s ", si); 
                                        printf("aereo %d %s\n",stdati.s3,stdati.nome_aereo);
                                        if (stdati.nome_aereo == aereo_pista_1){
                                        p1 = true;
                                        }   
                                        else if (stdati.nome_aereo == aereo_pista_2)
                                        {
                                        p2 = true; 
                                        }
                                     }
                                        else {
                                            printf("errore\n ");
                                        }
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