#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>
#define AEREO_TORRE_PATH "/tmp/AEREO_TORRE_PATH"
#define TORRE_AEREO_PATH "/tmp/TORRE_AEREO_PATH"
#define DECOLLO_AEREO_PATH "/tmp/DECOLLO_AEREO_PATH"
struct tdati{
    int cod; 
    int p ;
    int nome_aereo; 
    char s[64];
    char s2[64]; 
    char s3[64];
    };
void hangar();
void aereo(int nome_aereo);
void torredicontrollo();

