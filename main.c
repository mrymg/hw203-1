#include <stdio.h>
#include <malloc.h>
#define    SATIR   18
#define    SUTUN   18

int main() {

    FILE *p = NULL;
    int matDizi[SATIR][SUTUN];
    char *dosyaAdi = "mapmatrix1.txt";
    int i, j;
    printf("Map Matrix\n");
    if((p = fopen("mapmatrix1.txt", "r")) != NULL){

        for(i = 0; i < SATIR; i++){

            for(j = 0; j < SUTUN; j++){

                fscanf(p, "%d", &matDizi[i][j]);
                printf("%d ", matDizi[i][j]);

            }
            printf("\n");
        }
    }else{

        printf("*** %s dosyasi bulunamadi!", dosyaAdi);
    }
    fclose(p);

    printf("\nKey Matrix \n ")

    FILE *km = NULL;
    int kMat[3][3];
    int x,y;

    if((km = fopen("keymatrix1.txt", "r")) != NULL){

        for(x = 0; x < 3; x++){

            for(y = 0; y < 3; y++){

                fscanf(p, "%d", &kMat[x][y]);
                printf("%d ", kMat[x][y]);

            }
            printf("\n");
        }
    return 0;


}
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

    int N = count/2+1;


  // fclose(fp);

/*matrix*/
    float **map=malloc(N*sizeof(float));
    for(i=0;i<N;++i)
        map[i]=malloc(4*sizeof(float));



}