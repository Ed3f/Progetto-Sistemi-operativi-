#include "defined.h"
int attesa (int max, int min);
void scrittura_su_pipe(int n);
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
    int secondi_attesa;
    secondi_attesa = attesa (8, 3);
    printf("Attesa = %d\n",secondi_attesa);
    sleep(secondi_attesa);
    /*time (&timet);
    pTm = localtime(&timet);
    sprintf(s,"%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    printf("[ %s ] aereo pronto al decollo %d\n", s, nome_aereo);*/
    scrittura_su_pipe(nome_aereo);
    /*lettura_da_pipe(); 
    secondi_attesa  = attesa(15,5); 
    printf("aereo %d decollato", nome_aereo);*/
}
// funzione che randomicamente mi determina il tempo di attesa
int attesa (int max, int min){
    time_t timet;
    time (&timet);
    struct tm *pTm = localtime(&timet);
    srand(pTm->tm_sec);
    int valore = (rand () % max);
    return ((valore < 3 ? min+1 : valore));
}
// comunicazione aereo - torre tramite pipe 
void scrittura_su_pipe(int n ){
    
    //printf("%d",n);
    struct tdati stdati;
    int fd = open ( AEREO_TORRE_PATH,O_WRONLY);
    stdati.nome_aereo = n;
    stdati.cod = getpid();
    strcpy(stdati.s,"aereo pronto al decollo");
    if(write(fd, &stdati, sizeof(stdati)) == -1) {
        perror("Child: Errore in write");
    }
    else {
    printf("messaggio inviato correttamente\n");
    signalwait(); 
    }
    close(fd);
}