#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/**
Copyright 2020 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


int read_file(char *file_name, int *numVertices, int *numEdges, int **offsets, int **edges) {
    FILE *inputFile = fopen(file_name, "r");
    if(inputFile){
        int success;
        success = fscanf(inputFile, "%d", &*numVertices);
        if(!success){
           printf("Bad File format!\n");
           return 0;
        }
        success = fscanf(inputFile, "%d", &*numEdges);
        if(!success){
           printf("Bad File format!\n");
           return 0;
        }
        *offsets = (int*) malloc( ((*numVertices)+1) *sizeof(int) );
        *edges = (int*) malloc( (*numEdges) * sizeof(int) );

        for(int i = 0; i < *numVertices;i++){
            success = fscanf(inputFile, "%d",&((*offsets)[i]) );
            if(!success){
               printf("Bad File format!\n");
               return 0;
            }
        }
        (*offsets)[*numVertices] = *numEdges;
        for(int i = 0; i < *numEdges;i++){
            success = fscanf(inputFile, "%d",&((*edges)[i]) );
            if(!success){
               printf("Bad File format!\n");
               return 0;
            }
        }
        fclose(inputFile);
        return 1;
    }
    return 0;
}
