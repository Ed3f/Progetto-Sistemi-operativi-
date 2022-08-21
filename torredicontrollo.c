#include "defined.h"
typedef enum { true, false } pista; 
/*
cuore pulsante del progetto legge i messaggi inviati da hangar ed aerei decide il 
decollo degli aerei 
*/
void torredicontrollo(){
    char si[256];
    time_t timet;
    pista p1 = true; 
    pista p2 = true; 
    int richieste_aerei[10];
    int aereo_pista_1 ;
    int pista; 
    int aereo_pista_2 ; 
    printf("avvio torre\n");
    int wstatus, fd, iReadCount = 1;
    struct tdati stdati;
    fd = open(AEREO_TORRE_PATH, O_RDONLY|O_NONBLOCK);  
    sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);  
    sem_t *sem1 = sem_open("/np2", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);            
    stdati.s[0] = '\0';
    int i = 0;
    int j = 0; 
    int u = 0;
    int ripetizione = 0;  
    while (strcmp(stdati.s, "aerei terminati")){ 
        ripetizione++;
        printf("ripetizione = %d\n", ripetizione);
        sem_wait(sem);

        if (iReadCount = read(fd, &stdati, sizeof(stdati)) > 0 ){
            if (strcmp(stdati.s, "aereo pronto al decollo") == 0 ){
                printf("89\n");
                if ( i < 10 ){
                    time (&timet);
                    struct tm *pTm = localtime(&timet);
                    sprintf(si,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
                    printf("%s aereo %d %s\n",si, stdati.nome_aereo, stdati.s);
                    richieste_aerei [i] = stdati.cod;
                    printf("codici %d, cicli = %d\n ",  richieste_aerei [i], i);
                    i++;  
                }
                //sem_post(sem);
               if (j < 10 ){
                    printf("quante volte entra nel ciclo %d\n",j);
                    if (p1 == true ){
                        p1 = false; 
                        int cod1 = richieste_aerei[j];
                         printf("\e[0;31m richieste aerei = %d\e[0m\n\n", richieste_aerei[j]);
                        aereo_pista_1 = cod1;
                        pista = 1; 
                        printf("\e[0;31m codice %d \e[0m\n\n", cod1);
                        j++;
                        kill(cod1 ,SIGUSR1);
                        p1 = true; 
                    }
                    else if (p2 == true ){
                        p2 = false; 
                        int cod2 = richieste_aerei[j];
                        printf("\e[0;31m richieste aerei = %d\e[0m\n\n", richieste_aerei[j]);
                        aereo_pista_2 = cod2;
                        pista = 2;
                        printf("\e[0;31m codice %d \e[0m\n\n", cod2);
                        j++;
                        kill(cod2,SIGUSR1);
                        p2 = true; 
                    }
                    if (p1 == false || p2 == false){ 
                        u++;
                        printf("entrate %d\n",u);
                       int readcontenuto = 1; 
                        int pippo;
                        int fs = open (AEREO_TORRE_PATH, O_RDONLY|O_NONBLOCK);
                       while (readcontenuto = read (fs, &stdati, sizeof(stdati))){
                        pippo =  (strcmp(stdati.s2, "aereo decollato"));
                        printf("%s aereo = %d\n",stdati.s2, stdati.n_a);
                        if (pista == 1){
                                p1 = true;
                                break; 
                        }
                        else if (pista == 2){
                                p2 = true; 
                                break;
                        }
                       }
                                //close(fs);
                        /*int fs,readcontenuto = 1 ;
                        stdati.s2[0] = '\0';
                        fs = open (AEREO_TORRE_PATH, O_RDONLY|O_NONBLOCK);
                        if (readcontenuto = read (fs, &stdati, sizeof(stdati))){
                            printf("cosa c'è scritto %s\n", stdati.s2);
                            if (strcmp(stdati.s2, "aereo decollato") == 0){
                                printf("\e[0;31m djnojonvso \e[0m\n");
                                printf("%s aereo = %d\n",stdati.s2, stdati.n_a);
                                //printf("%d == %d\n", aereo_pista_1,stdati.nome_aereo_decollo);
                                //if (aereo_pista_1 ==  stdati.nome_aereo_decollo){
                                    printf("fine decollo\n");
                                        printf("5\n");
                                        p1 = true;
                                        p2 = true;
                                        //sem_post(sem);
                                //} 
                               /* printf("%d == %d\n", aereo_pista_1,stdati.nome_aereo_decollo);
                                if (aereo_pista_2 == stdati.nome_aereo_decollo){
                                printf("\e[0;31m djnojonvso \e[0m\n");
                                printf("fine decollo\n");
                                        printf("6\n");
                                        p2 = true;
                                        sem_post(sem);*/
                            /* else {
                                    printf("errore in lettura\n");
                                }   
                            }
                    
                            if (readcontenuto == -1 ){
                                perror("Torre: errore in lettura");
                            }
                        printf("byte letti %d\n", readcontenuto);*/
                        }
                    }
            }
        }
        if (strcmp(stdati.s, "aerei terminati") == 0) {
            printf("%s\n",stdati.s);
            close(fd);
        }
    }
}