#include "defined.h"
int attesa (int max, int min);
void scrittura_su_pipe(int n);
void lettura_pipe (); 
void scrittura_su_pipe2(int n);
/*
Funzione aereo la quale attende un periodo tra gli 8-3 sec per la preparazioe 
comunica alla torre la volontà di prendere il volo ed infine attende dai 5-15 sec 
per il decollo effettivo  
*/
void  aereo(int nome_aereo){
    char s[256];
    time_t timet;
    time (&timet);
    struct tm *pTm;
    struct tdati stdati; 
    int secondi_attesa;
    secondi_attesa = attesa (8, 3);
    printf("attesa %d\n ",secondi_attesa);
    sleep(secondi_attesa);
    /*time (&timet);
    pTm = localtime(&timet);
    sprintf(s,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    printf("[ %s ] aereo pronto al decollo %d\n", s, nome_aereo);*/
    scrittura_su_pipe(nome_aereo);
    lettura_pipe(); 
    int secondi_attesa2  = attesa(15,5);
    printf("aereo %d ",nome_aereo);
    printf("seconda pausa = %d\n", secondi_attesa2);
    sleep(secondi_attesa2);
    printf("aereo %d\n",stdati.nome_aereo);
    scrittura_su_pipe2(nome_aereo);
}
// funzione che randomicamente mi determina il tempo di attesa
int attesa (int max, int min){
    time_t timet;
    time (&timet);
    struct tm *pTm = localtime(&timet);
    srand(pTm->tm_sec);
    int valore = (rand () % max);
    return ((valore < min ? min+1 : valore));
}
// comunicazione aereo - torre tramite pipe 
void scrittura_su_pipe(int n ){
    /* sigset_t sigset;
    int signum;
    sigemptyset(&sigset);
	sigaddset(&sigset, SIGRTMIN + 1);
	sigprocmask(SIG_BLOCK, &sigset, NULL);*/ 
    //printf("%d",n);
    //sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);
    struct tdati stdati;
    int fd = open ( AEREO_TORRE_PATH,O_WRONLY);
    //sem_wait (sem);
    stdati.nome_aereo = n;
    printf("aereo che scrive %d\n", stdati.nome_aereo);
    stdati.cod = getpid();
    strcpy(stdati.s,"aereo pronto al decollo");
    if(write(fd, &stdati, sizeof(stdati)) == -1) {
        perror("Child: Errore in write");
    }
    close(fd);
    //sem_post(sem);
}
void lettura_pipe(){
    char si[256];
    time_t timet;
    struct tm *pTm;
    struct tdati stdati;
    int ft,dati_letti = 1; 
    ft= open(TORRE_AEREO_PATH,O_RDONLY);
    stdati.s2[0] = '\0';
    dati_letti = read(ft,&stdati,sizeof(stdati));
    if (dati_letti > 0){
    if(strcmp(stdati.s2, "decollo autorizzato pista 1") == 0){
        time (&timet);
        pTm = localtime(&timet);
        sprintf(si,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
        printf("%s ", si);
        printf("aereo %d %s\n",stdati.nome_aereo, stdati.s2); 
        close(ft);
    }
    if(strcmp(stdati.s2, "decollo autorizzato pista numero 2") == 0 ){
        time (&timet);
        pTm = localtime(&timet);
        sprintf(si,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
        printf("%s ", si);
        printf("aereo %d %s\n",stdati.nome_aereo, stdati.s2); 
        close(ft);
        }
    }
}
void scrittura_su_pipe2(int n ){
    struct tdati stdati;
    int fs = open ( DECOLLO_AEREO_PATH,O_WRONLY);
    stdati.nome_aereo = n;
    printf("aereo che scrive %d\n", stdati.nome_aereo);
    //stdati.cod = getpid();
    strcpy(stdati.s3,"aereo decollato");
    if(write(fs, &stdati, sizeof(stdati)) == -1) {
        perror("Child: Errore in write");
    }
    else {
    printf("messaggio inviato correttamente aereo %d\n", stdati.nome_aereo); 
    }
    close(fs);
}