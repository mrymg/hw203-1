#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *name;
    int length;
    int *arr;
}vectors;
typedef struct{
    char *name;
    int x;
    int y;
    int **arr;
} matrix;

int lineCount(const char *filename)
{
    int ch = 0;
    int count = 1;
    FILE *fileHandle;

    if ((fileHandle = fopen(filename, "r")) == NULL) {
        return -1;
    }

    do {
        ch = fgetc(fileHandle);
        if ( ch == '\n')
            count++;
    } while (ch != EOF);

    fclose(fileHandle);

    return count;
}



int size_of_line(char *filename){
    int size_of_line = 0;

    FILE *vectorFile ;
    vectorFile= fopen(filename, "r");

    char * line = NULL;


    size_t len = 1;
    getline(&line, &len, vectorFile);

    size_of_line = (strlen(line)+1)/2;
    return size_of_line;
}
vectors veczeros(char *name, int length, int index, vectors *varr){

    varr[index].name = name;
    varr[index].length=length;
    varr[index].arr = (int*)malloc(sizeof(int)*length);


    return varr[index];
}

matrix matzeros(char *name, int x, int y, int index, matrix *mat){

   mat[index].name=name;
   mat[index].x=x;
   mat[index].y=y;
   mat[index].arr= (int **)malloc(x * sizeof(int *));
   int i;
    for ( i = 0; i < x ; i++) {
        mat[index].arr[i]= (int *)malloc(y * sizeof(int));
    }


    return mat[index];
}

vectors vecread(char *filename, vectors *vec, int index){
    char *linem;
    FILE *vectorFile ;
    vectorFile= fopen(filename, "r");
    if(vectorFile == NULL){
        printf("Error while opening file.\n");
    }
    char * line = NULL;

    int i =0;
    size_t len = 1;
    getline(&line, &len, vectorFile);
    vec[index].name = strtok(filename, ".");
    vec[index].length = (strlen(line)+1)/2;
    vec[index].arr = (int*)malloc(sizeof(int)*vec[index].length);


    linem = strtok(line," ");

    while(linem != NULL){
        vec[index].arr[i]=atoi(linem);
        linem = strtok(NULL, " " );
        i++;
    }
   return vec[index];
}

matrix matread( char *filename, matrix *mat, int index){
    int i;
    FILE *matrixFile ;
    matrixFile= fopen(filename, "r");
    if(matrixFile == NULL){
        printf("Error while opening file.\n");
    }

    int lineNum = lineCount(filename);
    int lineSize = size_of_line(filename);
    mat[index].name=strtok(filename, ".");
    mat[index].x = lineNum;
    mat[index].y = lineSize;
    mat[index].arr= (int **)malloc(lineNum * sizeof(int *));
    for (i = 0; i < lineNum ; i++) {
        mat[index].arr[i]= (int *)malloc(lineSize * sizeof(int));
    }
    char * line = NULL;
    size_t len = lineNum;

    int j,k;
    while ((getline(&line, &len, matrixFile)) != -1) {
        for (j = 0; j < lineNum ; j++) {
            for (k = 0; k < lineSize; k++) {
                mat[index].arr[j][k] = atoi(strtok(line, " "));
            }
        }
    }
    return mat[index];
}

int find_vector_index(char *name, vectors *vArr, int vSize){
    int i;
    for (i = 0; i <vSize ; i++) {
        if(strcmp(vArr[i].name, name)==0){
            return i;
        }
    }
    return 0;
}
matrix vecstack(char *vector1, char *vector2, char *direction, char *name, int index, matrix *mat,vectors *v, int vSize){
    if(strcmp(direction, "row") == 0 && v[find_vector_index(vector1, v, vSize)].length == v[find_vector_index(vector2, v, vSize)].length){
        mat[index].name=name;
        mat[index].x = 2;
        mat[index].y = v[find_vector_index(vector1, v, vSize)].length;
        mat[index].arr = (int **)malloc(2 * sizeof(int *));
        int i;
        for ( i = 0; i < 2 ; i++) {
            mat[index].arr[i]= (int *)malloc(mat[index].y * sizeof(int));
        }
        int y;
        for ( y = 0; y < mat[index].y ; y++) {
                mat[index].arr[0][y] = v[find_vector_index(vector1, v, vSize)].arr[y];
        }
        for ( y = 0; y < mat[index].y ; y++) {
                mat[index].arr[1][y] = v[find_vector_index(vector2, v, vSize)].arr[y];
        }



    }else if(strcmp(direction, "column") == 0 && v[find_vector_index(vector1, v, vSize)].length == v[find_vector_index(vector2, v, vSize)].length){
        mat[index].name=name;
        mat[index].x=  v[find_vector_index(vector1, v, vSize)].length;
        mat[index].y=2;
        mat[index].arr = (int **)malloc(mat[index].x * sizeof(int *));
        int i;
        for (i = 0; i < 2 ; i++) {
            mat[index].arr[i]= (int *)malloc(2 * sizeof(int));
        }

        for ( i = 0; i < mat[index].x; ++i) {
            mat[index].arr[i][0] = v[find_vector_index(vector1, v, vSize)].arr[i];
        }
        for ( i = 0; i < mat[index].x; ++i) {
            mat[index].arr[i][1] = v[find_vector_index(vector2, v, vSize)].arr[i];
        }

    }else{
        printf("error");
    }
    return mat[index];

}

int find_matrix_index(char *name, matrix *mArr,int mSize){
    int i;
    for (i = 0; i <mSize ; i++) {
        if(strcmp(mArr[i].name, name)==0){
            return i;
        }
    }
    return 0;

}
matrix matstack(char *mat1, char *mat2, char *where, matrix *m, int mSize ){
    int i1,i2;
    i1 = find_matrix_index(mat1, m, mSize);
    i2 = find_matrix_index(mat2, m, mSize);
    int old_size_m1x = m[find_matrix_index(mat1, m, mSize)].x;
    int old_size_m1y = m[find_matrix_index(mat1, m, mSize)].y;
    int old_Size_m2x = m[find_matrix_index(mat2, m, mSize)].x;
    int old_Size_m2y = m[find_matrix_index(mat2, m, mSize)].y;
    if(strcmp(where,"d")== 0 && m[i1].y == m[i2].y){
        int new_size_x= old_size_m1x + old_Size_m2x;
        int new_size_y= old_size_m1y;
        m[i1].x = new_size_x;
        m[i1].arr = (int **)  realloc(m[i1].arr, sizeof(int *) * m[i1].x);
        int i;
        for (i = 0; i < old_size_m1x ; i++) {
            m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * new_size_y);
        }
        for (i = old_size_m1x; i < new_size_x ; i++) {
            m[i1].arr[i]= (int *) malloc( sizeof(int) * new_size_y);
        }


        int k,l;


        for ( k = 0; k < old_Size_m2x ; k++) {
            for (l = 0; l < new_size_y ; l++) {
                m[i1].arr[new_size_x-old_size_m1x+k][l] = m[i2].arr[k][l];
            }
        }
        return m[i1];


    }
    else if(strcmp(where,"r")==0 && m[i1].x == m[i2].x){
        int new_size_x= old_size_m1x;
        int new_size_y= old_size_m1y + old_Size_m2y;
        m[i1].y = new_size_y;
        m[i1].arr = (int **)  realloc(m[i1].arr, sizeof(int *) * m[i1].x);
        int i;
        for (i = 0; i < old_size_m1y ; i++) {
            m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * new_size_y);
        }
        for (i = old_size_m1y; i < new_size_y ; i++) {
            m[i1].arr[i]= (int *) malloc( sizeof(int) * new_size_y);
        }
        int k,l;
        for ( k = 0; k < new_size_x ; k++) {
            for (l = 0; l < new_size_y ; l++) {
                m[i1].arr[k][l + new_size_y-old_size_m1y] = m[i2].arr[k][l];
            }
        }
        return m[i1];
    }
    else{ return m[i1];}




}
matrix mvstack(char *mat1, char *vec1, char *where, matrix *m, vectors *v, int mSize, int vSize ){
    int i1,i2;
    i1 = find_matrix_index(mat1, m, mSize);
    i2 = find_vector_index(vec1, v, mSize);
    int old_size_m1x = m[find_matrix_index(mat1, m, mSize)].x;
    int old_size_m1y = m[find_matrix_index(mat1, m, mSize)].y;
    int vectorSize = v[find_vector_index(vec1, v, vSize)].length;
    if(strcmp(where,"d")==0 && m[i1].y == vectorSize) {
        int new_size_x = old_size_m1x + 1;
        int new_size_y = old_size_m1y;
        m[i1].x = new_size_x;
        m[i1].arr = (int **)  realloc(m[i1].arr, sizeof(int *) * m[i1].x);
        int i;
        for (i = 0; i < old_size_m1x ; i++) {
            m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * new_size_y);
        }
        for (i = old_size_m1x; i < new_size_x ; i++) {
            m[i1].arr[i]= (int *) malloc( sizeof(int) * new_size_y);
        }
        int l;



        for (l = 0; l < new_size_y ; l++) {
            m[i1].arr[new_size_x-old_size_m1x][l] = v[i2].arr[l];
        }

        return m[i1];


    }
    else if(strcmp(where,"r")==0 && m[i1].x == m[i2].x){

        int new_size_y= old_size_m1y + 1;
        m[i1].y = new_size_y;
        m[i1].arr = (int **)  realloc(m[i1].arr, sizeof(int *) * m[i1].x);
        int i;
        for (i = 0; i < old_size_m1y ; i++) {
            m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * new_size_y);
        }
        for (i = old_size_m1y; i < new_size_y ; i++) {
            m[i1].arr[i]= (int *) malloc( sizeof(int) * new_size_y);
        }
        int l;
        for (l = 0; l < new_size_y ; l++) {
            m[i1].arr[l][new_size_y-old_size_m1y] = v[i2].arr[l];
        }
        return m[i1];
    }
    else{printf("error");
        return m[i1];}



}
int findMaxRow(matrix p,matrix *m, int x, int y ){
    int i;
    int maximum;
    maximum = p.arr[x][0];
    for (i = 0; i < p.y ; i++) {
        if(p.arr[x][i] > maximum){
            maximum = p.arr[x][i];
        }
    }
    return  maximum;
};
int findMaxCol(matrix p,matrix *m, int x, int y){
    int i;
    int maximum;
    maximum = p.arr[0][y];
    for (i = 0; i < p.x ; i++) {
        if(p.arr[i][y] < maximum){
            maximum = p.arr[i][y];
        }
    }
    return  maximum;
};
int findMinRow(matrix p,matrix *m, int x, int y ){
    int i;
    int minimum;
    minimum = p.arr[x][0];
    for (i = 0; i < p.y ; i++) {
        if(p.arr[x][i] < minimum){
            minimum = p.arr[x][i];
        }
    }
    return  minimum;
};
int findMinCol(matrix p,matrix *m, int x, int y){
    int i;
    int minimum;
    minimum = p.arr[0][y];
    for (i = 0; i < p.x ; i++) {
        if(p.arr[i][y] < minimum){
            minimum = p.arr[i][y];
        }
    }
    return  minimum;
};
matrix pad(char *mat, int x, int y, char *mode, matrix *m, int mSize){
    int i1;
    i1= find_matrix_index(mat, m, mSize);
    int oldx = m[i1].x;
    int oldy =m[i1].y;
    matrix p = m[i1];
    if(strcmp(mode,"maximum") == 0){

            m[i1].x = oldx + x;
            m[i1].y  = oldy + y ;
            m[i1].arr = (int **) realloc(m[i1].arr, sizeof(int *) * m[i1].x);
            int i;

            for (i = 0; i < oldx ; i++) {
                m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * m[i1].y);
            }
            for (i = oldx; i < m[i1].x ; i++) {
                m[i1].arr[i]= (int *) malloc( sizeof(int) * m[i1].y);
            }


            int r,c;
            for ( r = 0; r < oldx; r++) {
                for ( c = oldy; c < m[i1].y; c++) {
                    m[i1].arr[r][c] = findMaxRow(p, m, r, c);

                }
            }
            for ( r = oldx; r < m[i1].x; r++) {
                for ( c = 0; c < m[i1].y; c++) {

                    m[i1].arr[r][c] = findMaxCol(p, m, r, c);


                }

            } return m[i1];
           }else if(strcmp(mode,"minimum") == 0) {
        m[i1].x = oldx + x;
        m[i1].y = oldy + y;
        m[i1].arr = (int **) realloc(m[i1].arr, sizeof(int *) * m[i1].x);
        int i;
        for (i = 0; i < oldx; i++) {
            m[i1].arr[i] = (int *) realloc(m[i1].arr[i], sizeof(int) * m[i1].y);
        }
        for (i = oldx; i < m[i1].x; i++) {
            m[i1].arr[i] = (int *) malloc(sizeof(int) * m[i1].y);
        }
        int r, c;
        for (r = 0; r < oldx; r++) {
            for (c = oldy; c < m[i1].y; c++) {
                m[i1].arr[r][c] = findMinRow(p, m, r, c);
            }
        }
        for (r = 0; oldx < m[i1].x; r++) {

            for (c = 0; c < m[i1].y; c++) {
                m[i1].arr[r][c] = findMinCol(p, m, r, c);

            }
        }


        return m[i1];
    }else{
        return m[i1];
    }

};
matrix padval(char *mat, int x, int y, int val, matrix *m, int mSize){
    int i1;
    i1= find_matrix_index(mat, m, mSize);
    int oldx = m[i1].x;
    int oldy =m[i1].y;
    m[i1].x = oldx + x;
    m[i1].y  = oldy + y ;
    m[i1].arr = (int **) realloc(m[i1].arr, sizeof(int *) * m[i1].x);
    int i;

    for (i = 0; i < oldx ; i++) {
        m[i1].arr[i]= (int *) realloc(m[i1].arr[i], sizeof(int) * m[i1].y);
    }
    for (i = oldx; i < m[i1].x ; i++) {
        m[i1].arr[i]= (int *) malloc( sizeof(int) * m[i1].y);
    }


    int r,c;
    for ( r = 0; r < oldx; r++) {
        for ( c = oldy; c < m[i1].y; c++) {
            m[i1].arr[r][c] = val;

        }
    }
    for ( r = oldx; r < m[i1].x; r++) {
        for ( c = 0; c < m[i1].y; c++) {

            m[i1].arr[r][c] = val;


        }

    } return m[i1];


};



matrix add(char *m1, char *m2,  matrix *m,int  mSize){
    int i1,i2;
    i1 = find_matrix_index(m1, m, mSize);
    i2 = find_matrix_index(m2, m, mSize);
    int i,j;
    if(m[i1].x == m[i2].x && m[i1].y ==m[i2].y){
        for (i = 0; i < m[i1].x ; i++) {
            for ( j = 0; j < m[i1].y; j++) {
                m[i1].arr[i][j] = m[i1].arr[i][j] + m[i2].arr[i][j];
            }
        }
        return m[i1];
    }else{

        return m[i1];
    }

}
matrix multiply(char *m1, char *m2,  matrix *m,int  mSize){
    int i1,i2;
    i1 = find_matrix_index(m1, m, mSize);
    i2 = find_matrix_index(m2, m, mSize);
    int i,j;
    if(m[i1].x == m[i2].y){
        for (i = 0; i < m[i1].x ; i++) {
            for ( j = 0; j < m[i1].y; j++) {
                m[i1].arr[i][j] = m[i1].arr[i][j] * m[i2].arr[i][j];
            }
        }
        return m[i1];
    }else{
       ;
        return m[i1];
    }

}
matrix subtract(char *m1, char *m2,  matrix *m,int  mSize){
    int i1,i2;
    i1 = find_matrix_index(m1, m, mSize);
    i2 = find_matrix_index(m2, m, mSize);
    int i,j;
    if(m[i1].x == m[i2].x && m[i1].y ==m[i2].y){
        for (i = 0; i < m[i1].x ; i++) {
            for ( j = 0; j < m[i1].y; j++) {
                m[i1].arr[i][j] = m[i1].arr[i][j] - m[i2].arr[i][j];
            }
        }
        return m[i1];
    }else{
        return m[i1];
    }

}

int main( int argc, char *argv[] ){


    int vecCount = 0;
    int matCount = 0;


/*//    char *arrays = argv[1];
//    strcat(arrays,"/");
//    char *commands= argv[2];
// */
    char *cmd = "commands2.txt";

    FILE *output =NULL;
    char *out = "output.txt";

    output= fopen(out,"w");




    int i=0;
    int j=0;
    FILE *myFile = fopen(cmd, "r");
    int lineNum = lineCount(cmd);
    char **commandArray=NULL;
    commandArray =(char **)malloc(sizeof(char)*lineNum);
    for (i = 0; i< lineNum; i++) {
        commandArray[i] = (char *)malloc(50 * sizeof(char));
    }

    char * line = NULL;
    size_t len = lineNum;
    char *command;


    while ((getline(&line, &len, myFile)) != -1) {

        commandArray[j++] = strdup(line);

        command = strtok(line," ");
        if(strcmp(command, "matzeros") == 0 || strcmp(command, "matread") == 0 || strcmp(command, "matslice") == 0 || strcmp(command, "vecstack") == 0){
            matCount++;
        }else if(strcmp(command, "veczeros") == 0 || strcmp(command, "vecread") == 0 || strcmp(command, "vecslice") == 0 || strcmp(command, "matslicerow") == 0 || strcmp(command, "matslicecol") == 0){
            vecCount++;
        }


    }

    vectors *vectorArray = (vectors *)malloc(sizeof(vectors)*vecCount);
    matrix *matrixArray = (matrix*)malloc(sizeof(matrix)*matCount);

    int mIndex = 0; int vIndex =0;
    char *ch;
    int k;
    for (k= 0; k < lineNum; k++) {
        ch = strtok(commandArray[k], " ");
        if(strcmp(ch, "\n") == 0 || strcmp(ch,"\r\n") == 0){
            fprintf(output, "error\n");
        }
        else if(strcmp(ch,"veczeros") == 0){


            ch=strtok(NULL, " ");
            char *vname= ch;
            ch=strtok(NULL, " ");
            int vlen=atoi(ch);
            vectors v=veczeros(vname, vlen, vIndex,vectorArray);
            fprintf(output, "created vector %s %d\n", v.name, v.length);
            int iter;
            for (iter = 0; iter <v.length ; iter++) {
                v.arr[iter]=0;
                fprintf(output, "%d ", v.arr[iter]);
            }fprintf(output, "\n");


        vIndex++;

        }else if(strcmp(ch,"matzeros") == 0){
            ch=strtok(NULL, " ");
            char *name = ch;
            ch=strtok(NULL, " ");
            int row = atoi(ch);
            ch=strtok(NULL, " ");
            int col = atoi(ch);
            matrix m=matzeros(name, row, col, mIndex, matrixArray);
            fprintf(output, "created matrix %s %d %d\n", m.name,m.x,m.y);
            for(j=0; j<m.x; j++){
                for(k=0; k<m.y; k++){
                    m.arr[j][k] = 0;
                    fprintf(output, "%d ", m.arr[j][k]);
                }
                fprintf(output, "\n");
            }

        mIndex++;
        }else if(strcmp(ch,"vecread") == 0){

            ch=strtok(NULL, " ");
            char *readVectorName = strtok(ch,"\n");
            vectors v = vecread(readVectorName, vectorArray, vIndex);
            char *n =strtok(v.name,"/");
            n=strtok(NULL, "/");
            printf("read vector %s %d \n", n, v.length);
            int l;
            for ( l = 0; l < v.length-1; l++) {
                fprintf(output, "%d ", v.arr[l]);
            }fprintf(output, "\n");
        vIndex++;


        }else if(strcmp(ch,"matread") == 0){
            ch=strtok(NULL, " ");
            char *anam = ch;
            char *readMatrixName=strtok(ch, "\n") ;
            matrix m=  matread(readMatrixName, matrixArray, mIndex);
            char *n =strtok(m.name,"/");

            fprintf(output, "read matrix %s %d %d\n",ch,m.x,m.y);
            int t,y;
            for ( t = 0; t < m.x ; t++) {
                for ( y = 0; y < m.y ; y++) {
                    fprintf(output, "%d ",m.arr[t][y]);
                }fprintf(output, "\n");
            }
        mIndex++;

        }else if(strcmp(ch,"vecstack") == 0){
            ch=strtok(NULL, " ");
            char *v1 = ch;
            ch=strtok(NULL, " ");
            char *v2 = ch;
            ch=strtok(NULL, " ");
            char *direction = strtok(ch, "\n");
            ch=strtok(NULL, " ");
            char *name = ch;
            matrix m = vecstack(v1,v2,direction,name,mIndex,matrixArray,vectorArray,matCount);
            fprintf(output, "vectors concatenated %s %d %d\n",m.name,m.x,m.y );
            int a,b;
            for (a = 0; a < m.x ; a++) {
                for ( b = 0; b <m.y ; b++) {
                    fprintf(output, "%d ", m.arr[a][b]);
                }fprintf(output, "\n");
            }
        mIndex++;
        }else if(strcmp(ch,"matstack") == 0){
            ch=strtok(NULL, " ");
            char *m1 = ch;
            ch=strtok(NULL, " ");
            char *m2 =ch;
            ch=strtok(NULL, " ");
            char *direction = strtok(ch, "\n");
            matrix m = matstack(m1,m2,direction, matrixArray, matCount);
            fprintf(output, "matrices concatenated %s %d %d\n", m.name, m.x, m.y);
            int l,n;
            for ( l = 0; l < m.x; l++) {
                for ( n = 0; n < m.y ; n++) {
                    fprintf(output, "%d ", m.arr[l][n]);
                }fprintf(output, "\n");
            }


        }else if(strcmp(ch,"mvstack") == 0){
            ch=strtok(NULL, " ");
            char *m1 = ch;
            ch=strtok(NULL, " ");
            char *v1 =ch;
            ch=strtok(NULL, " ");
            char *direction = strtok(ch, "\n");
            matrix m = mvstack(m1,v1,direction,matrixArray,vectorArray,matCount,vecCount);
            fprintf(output, "matrix and vector concatenated %s %d %d\n", m.name, m.x, m.y);
            int l,n;
            for ( l = 0; l < m.x; l++) {
                for ( n = 0; n < m.y ; n++) {
                    fprintf(output, "%d ", m.arr[l][n]);
                }fprintf(output, "\n");
            }

        }else if(strcmp(ch,"pad") == 0){
            ch=strtok(NULL, " ");
            char *name = ch;
            ch=strtok(NULL, " ");
            int x= atoi(ch);
            ch=strtok(NULL, " ");
            int y = atoi(ch);
            ch=strtok(NULL, " ");
            char *maxmin = strtok(ch,"\n");


            matrix m= pad(name,x,y,maxmin,matrixArray,matCount);
            fprintf(output, "padded matrix %s %d %d \n", m.name, m.x,m.y);
            int r,c;
            for ( r = 0; r < m.x ; r++) {
                for ( c = 0; c <m.y ; c++) {
                    fprintf(output, "%d ", m.arr[r][c]);
                }fprintf(output, "\n");
            }


        }else if(strcmp(ch,"padval") == 0){
            ch=strtok(NULL, " ");
            char *name = ch;
            ch=strtok(NULL, " ");
            int x= atoi(ch);
            ch=strtok(NULL, " ");
            int y = atoi(ch);
            ch=strtok(NULL, " ");
            int value = atoi(ch);
            matrix m= padval(name,x,y,value,matrixArray,matCount);
            fprintf(output, "padded matrix %s %d %d \n", m.name, m.x,m.y);
            int r,c;
            for ( r = 0; r < m.x ; r++) {
                for ( c = 0; c <m.y ; c++) {
                    fprintf(output, "%d ", m.arr[r][c]);
                }fprintf(output, "\n");
            }


        }else if(strcmp(ch," ss ") == 0){
            ch=strtok(NULL, " ");
            printf("%s\n", ch);

        }else if(strcmp(ch,"ss") == 0){
            ch=strtok(NULL, " ");
            printf("%s\n", ch);

        }else if(strcmp(ch,"ss") == 0){
            ch=strtok(NULL, " ");
            printf("%s\n", ch);

        }else if(strcmp(ch,"ss") == 0){
            ch=strtok(NULL, " ");
            printf("%s\n", ch);

        }else if(strcmp(ch,"add") == 0){
            ch=strtok(NULL, " ");
            char *m1 = ch;
            ch=strtok(NULL, " ");
            char *m2 = ch;
            matrix m= add(m1,m1,matrixArray,matCount);
            fprintf(output, "add %s %s", m1, m2);
            int mx,my;
            for ( mx = 0; mx <m.x ; mx++) {
                for ( my = 0; my <m.y ; my++) {
                    fprintf(output, "%d ",m.arr[mx][my]);
                }fprintf(output, "\n");
            }


        }else if(strcmp(ch,"multiply") == 0){
            ch=strtok(NULL, " ");
            char *m1 = ch;
            ch=strtok(NULL, " ");
            char *m2 = ch;
            matrix m= multiply(m1,m1,matrixArray,matCount);
            fprintf(output, "multiply %s %s", m1, m2);
            int mx,my;
            for ( mx = 0; mx <m.x ; mx++) {
                for ( my = 0; my <m.y ; my++) {
                    fprintf(output, "%d ",m.arr[mx][my]);
                }fprintf(output, "\n");
            }

        }else if(strcmp(ch,"subtract") == 0){
            ch=strtok(NULL, " ");
            char *m1 = ch;
            ch=strtok(NULL, " ");
            char *m2 = ch;
            matrix m= subtract(m1,m1,matrixArray,matCount);
            fprintf(output, "subtract %s %s", m1, m2);
            int mx,my;
            for ( mx = 0; mx <m.x ; mx++) {
                for ( my = 0; my <m.y ; my++) {
                    fprintf(output, "%d ",m.arr[mx][my]);
                }fprintf(output, "\n");
            }

        }
        else{
            fprintf(output, "error\n");
        }


    }


    fclose(myFile);
    fclose(output);
/* //    free(commandArray);
//    int a;
//    for ( a = 0;a < matrixArray->x; a++) {
//        free(matrixArray->arr[a]);
//    }
//
//    for ( a = 0; a < matCount ; a++) {
//        free(matrixArray->arr);
//        free(matrixArray->name);
//    }
//    for ( a = 0; a < vecCount ; a++) {
//        free(vectorArray->arr);
//        free(vectorArray->name);
//    }
*/




}
