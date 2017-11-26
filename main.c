/*
 *
The reflected binary code, also known as Gray code after Frank Gray,
is a binary numeral system where two successive values differ in only
one bit (binary digit).

The code list for n bits can be generated recursively from the list
for nâˆ’1 bits by reflecting the list (i.e. listing the entries in
reverse order), concatenating the original list with the reversed
list, prefixing the entries in the original list with a binary 0, and
then prefixing the entries in the reflected list with a binary 1.

Example
-------

The two codes of length equal to 1 are made-up of one 0 and one 1:

  0
  1

To move from 1 to 2 bits, the list is firstly reflected (-- indicates
a mirror), and then 0s are added above and 1s below the reflection
point.

  0      0     00
  1      1     01
---    ---    ---
         1     11
         0     10

The process in then repeated to move from 2 to 3 bits (reflection and
then 0s and 1s addition):

 00     00    000
 01     01    001
 11     11    011
 10     10    010
---    ---    ---
        10    110
        11    111
        01    101
        00    100
        00    100

Write a recursive program that:
- Receives n as a parameter
- Generates all Gray code on n bits, and stores the code in a dynamic
  matrix with n rows and 2^n columns
- Prints out the resulting matrix
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char** malloc2d(int n);
void gray_setup(char*** m,int n);
void gray_r(char*** m,int level,int n);
char* rev(char* string);
void print(char** m,int n);
void free2d(char*** m,int n);

int main(int argc,char** argv) {
    //Variables declaration
    int n;
    char **matrix;

    //Checking and initializations
    if(argc!=2){
        fprintf(stderr,"Wrong number of CL arguments.\nRun as <%s n>,n integer number.\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    n=atoi(argv[1]);
    if(n<=0){
        fprintf(stderr,"n must be a positive, non-zero integer!\n");
        exit(EXIT_FAILURE);
    }
    matrix=malloc2d(n);

    //Core
    gray_setup(&matrix,n);
    print(matrix,n);

    //Freeing&exiting
    free2d(&matrix,n);
    return 0;
}

char** malloc2d(int n){
    char** res=malloc(n*sizeof(char*));
    int i;
    if(res==NULL){
        fprintf(stderr,"Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<n;i++){
        res[i]=malloc(((int)pow(2,n)+1)*sizeof(char));
        if(res[i]==NULL){
            fprintf(stderr,"Memory allocation error.\n");
        }
        strcpy(res[i],"");
    }
}

void gray_setup(char*** m,int n){
    //Base case
    sprintf(*m[0],"01");
    gray_r(m,1,n);
}

void gray_r(char*** m,int level,int n){
    //Local variables
    int bits=level+1,i,j;
    char *reverse=malloc(bits*sizeof(char));
    if(reverse==NULL){
        fprintf(stderr,"Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    //Recursion ends when the level is equal to n
    if(level==n)
        return;

    //Merge from previous level
    strcpy(*m[level],*m[level-1]);
    reverse=rev(*m[level]);
    //Add one and zeros
    for(i=0;i<bits;i++) *m[level][i]+=0;
    for(j=0;j<bits;j++) reverse[j]+=(int)pow(10,bits);
    //Concatenate
    strcat(*m[level],reverse);
    //Recur
    gray_r(m,level+1,n);
}
char* rev(char* string){
    size_t l=strlen(string);
    char *res=malloc(l*sizeof(char));
    if(res==NULL)
        exit(EXIT_FAILURE);
    for(int i=0;i<l;i++)
        res[i]=string[l-i-1];
    return res;
}

void print(char** m,int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < (int) pow(2, i); j++) {
            fprintf(stdout, "%c ", m[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

void free2d(char*** m,int n){
    int i;
    for(i=0;i<n;i++) free(*m[i]);
    free(*m);
}