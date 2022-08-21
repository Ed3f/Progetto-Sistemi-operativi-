#include "defined.h"
int aereo_n; 
int attesa (int max, int min);
void scrittura_su_pipe(int n);
void lettura_pipe (); 
void comunicazione_decollo( int n );
int i= 0;
int j = 0; 
/*void handler1( int sign){
char s[256];
}
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
    //sigaddset(&sig2,SIGUSR2);
    sigset_t sig1,sig2; 
    int sign1, sign2;
    sigemptyset(&sig1);
    sigaddset(&sig1,SIGUSR1);
    sigemptyset(&sig2);
    sigprocmask(SIG_BLOCK, &sig1, NULL);
    int secondi_attesa;
    int secondi_attesa2;
    secondi_attesa = attesa (8, 3);
    printf("attesa %d\n ",secondi_attesa);
    sleep(secondi_attesa);
    scrittura_su_pipe(nome_aereo);  
    int val = sigwait(&sig1,&sign1);
    time (&timet);
    pTm = localtime(&timet);
    sprintf(s,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    printf("%s inizio decollo aereo %d\n", s, nome_aereo);
    //printf("val = %d\n",sign1);
    int secondi_attesa1 = attesa(15,5);
    printf("aereo %d secondi attesa %d\n",nome_aereo,secondi_attesa1);
    sleep(secondi_attesa1);
    //printf("aereo decollato %d\n", nome_aereo);
    //printf("\n");
    comunicazione_decollo(nome_aereo);
    printf("fine decollo\n");
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
    struct tdati stdati;
    char s[256];
    time_t timet;
    struct tm *pTm;
    //struct tdati stdati; 
    sem_t *sem = sem_open("/np1", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);
    int fd = open ( AEREO_TORRE_PATH,O_WRONLY|O_NONBLOCK);
    stdati.nome_aereo = n;
    //aereo_n = stdati.nome_aereo;
    stdati.cod= getpid();
    strcpy(stdati.s,"aereo pronto al decollo");
    if(write(fd, &stdati, sizeof(stdati)) == -1) {
        perror("Child: Errore in write");
    } 
    sem_post(sem);
    close(fd);

}
void comunicazione_decollo(int n){
    printf("\e[0;31mprocessi entrati \e[0m\n");
    struct tdati stdati;
    sem_t *sem1 = sem_open("/np2", O_CREAT, S_IRWXU|S_IRGRP|S_IWGRP, 1);
    int fs = open(AEREO_TORRE_PATH,O_WRONLY); 
    stdati.nome_aereo_decollo = getpid(); 
    printf("pid %d\n", stdati.nome_aereo_decollo);
    stdati.n_a = n;
    strcpy(stdati.s2, "aereo decollato");
    //printf("cosa ho scritto %s", stdati.s2);
    if(write(fs, &stdati, sizeof(stdati)) == -1 ){
        printf("errore\n");
    }
    //printf("cosa ho scritto %s", stdati.s2);
    sem_post(sem1);
    close (fs);
}