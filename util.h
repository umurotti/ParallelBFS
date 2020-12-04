/*
*		reads a a graph file in CSR format, each integer number separated by line,
*       first line numRows, second line numColumns, next numrows lines define offsets
*       array, and very next numColumns lines define edges array.
*
*       @params:
*		file_name: name of the file
*		numRows: number of rows(vertices) in the file
*		numColumns: number of columns (edges) in the file
*       offsets: offsets(vertices) array
*       edges: edge(columns) array
*
*       Returns 0 if there is a file format or a reading problem, 1 if successful
*
*       Usage Example:
*       int numVertices,numEdges,*offsets,*edges;
*       int success = read_file(argv[1],&numVertices,&numEdges,&offsets,&edges);
*       if(success){
*           //Do the computation
*       }
**/
int read_file(char *file_name, int *numRows, int *numColumns, int **offsets, int **edges);
