#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#define AEREO_TORRE_PATH "/tmp/AEREO_TORRE_PATH"
struct tdati{
    int cod; 
    int nome_aereo; 
    char s[64];
};
void hangar();
void aereo(int nome_aereo);
void torredicontrollo();

