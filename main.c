#include <stdio.h>
#include <malloc.h>

int main() {

    readMap();

}

void readMap(){
    int i;
    int j;



    FILE *fp;
    fp=fopen("mapmatrix1.txt", "r");
    if (fp == NULL) {
        printf("File not found");
        exit(1);
    }
    int c, count;

    count = 0;
    for( ;; )
    {
        c = fgetc( fp );
        if( c == EOF || c == '\n' )
            break;
        ++count;
    }

    int n = count/2+1;


  // fclose(fp);

/*matrix*/
    float **map=malloc(n*sizeof(float));
    for(i=0;i<n;++i)
        map[i]=malloc(4*sizeof(float));



}