#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getTotalOcorrunces(int * vect){
    int len;
    int total = 0;
    for(len = 0; len < 26; len++){
        total += vect[len];
    }
    return total;
}

void writeBackFrequency(char * file, int * freq){
    int total = getTotalOcorrunces(freq);
    FILE * fp = fopen(file, "w");
    for(int i = 0; i < 26; i++){
        float value = (float)100 * freq[i] / total;
        fprintf(fp, "%f ", value);
    }
    fclose(fp);
}



int charCount(char letra, char * string){
    int i; 
    int counter = 0;
    printf("String:%s\n", string);
    for(i = 0; i < strlen(string); i++){
        if(string[i] == letra || string[i] == letra + 32){
            printf("Achou %c em %c\n", letra, string[i]);
            counter+=1;
        }
    }
    return counter;
}

void countAZ(char * string, char * file){
    char c;
    int vector[26];
    for(c = 'A'; c < 'Z'; c++){
        // fprintf(fp, "%d ",charCount(c, string));
        vector[c - 'A'] = charCount(c, string);
    }
    writeBackFrequency(file, vector);
}


void checkFileIsOk(char * file){
    FILE * fp = fopen(file, "r");
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    fclose(fp);
}

long fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

char * readFile(char * file){
    FILE * fp = fopen(file, "r");
    checkFileIsOk(file);
    long size = fsize(fp);
    char * fcontent = malloc(size);
    fread(fcontent, 1, size, fp);
    return fcontent;
}

void writeTable(char * out, char * in){
    checkFileIsOk(in);
    checkFileIsOk(out);
    fclose(fopen(out, "w"));
    countAZ(readFile(in), out);

}
 


int main(int argc, char const *argv[]){
    // printf("%s", readFile("texto.txt"));
    // writeTable("tabelaTexto.txt", "texto.txt");
    // printf("%c", 'a' - 32);
    writeTable("tabelaTexto.txt", "texto.txt");
    // printf("%d", getTotalOcorrunces("tabelaTexto.txt"));
    return 0;
}
