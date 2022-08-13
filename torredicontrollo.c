#include "defined.h"
typedef enum { true, false } pista; 
/*
cuore pulsante del progetto legge i messaggi inviati da hangar ed aerei decide il 
decollo degli aerei 
*/
void torredicontrollo(){
    pista p1 = true; 
    pista p2 = true; 
    printf("avvio torre\n");
    int wstatus, fd, iReadCount = 1;
    struct tdati stdati;
    fd = open(AEREO_TORRE_PATH, O_RDONLY);
    if ((iReadCount = read(fd, &stdati, sizeof(stdati))) > 0 ){
    stdati.s[0] = '\0';
    //printf("1\n");
    while (strcmp(stdati.s, "aerei terminati")) {
        if (iReadCount = read(fd, &stdati, sizeof(stdati)) > 0 ){
        //printf("%d",iReadCount);
        if (strcmp(stdati.s, "aereo pronto al decollo") == 0 ){
                    printf("aereo %d %s\n", stdati.nome_aereo, stdati.s);
                }
                else{
                    printf("%s\n",stdati.s);
                }
            }
        }
        //printf("2\n");
    }
}