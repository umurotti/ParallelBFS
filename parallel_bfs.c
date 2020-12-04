#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "util.h"
#include "stack.h"
#include <math.h>

// function declarations
int find_owner(int vertex, int* displs, int size);
int** alloc_2d_int(int rows, int cols);
int get_no_of_neigbors(int vertex, int *local_offsets, int *displs, int rank);
int find_neighbor(int vertex, int *local_offsets, int local_offset_size, int index, int *local_edges, int *displs, int rank);
int are_all_empty(struct Stack* FS, int size);
int already_exists(int **buffer, int col, int buffer_size, int toSearch);

// main function
int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int root = 0;
    // global
    int *offsets;
    int *edges;
    int *displs_vertices;
    int *displs_edges;
    int *vertice_arr_sizes;
    int *edges_arr_sizes;
    int numVertices;
    int source;
    int level;
    int ops;
    char *output_file_name;
    // local
    int *local_offsets;
    int local_offset_size;
    int *local_edges;
    int local_edge_size;
    int *distance;
    int *result;

    // master
    if (rank == root) {
        // take arguments
        char *input_file_name = "./sample_data.txt";
        if (argv[1] != NULL) {
            input_file_name = argv[1];
        }

        source = 0;
        if (argv[2] != NULL) {
            source = atoi(argv[2]);
        }

        output_file_name = "./output_data.txt";
        if (argv[4] != NULL) {
            output_file_name = argv[4];
        }

        numVertices = 0;
        int numEdges = 0;
        offsets = NULL;
        edges = NULL;
        // read input file
        read_file(input_file_name, &numVertices, &numEdges, &offsets, &edges);
        
        // init array vertices
        vertice_arr_sizes = malloc(sizeof (int) * size);
        for (int i = 0; i < size; i++) {
            vertice_arr_sizes[i] = numVertices / size;
            if (i < numVertices % size)
                vertice_arr_sizes[i]++;
        }
        
        // init displs array for scattering
        displs_vertices = malloc(sizeof (int) * size);
        displs_vertices[0] = 0;
        for (int i = 1; i < size; i++) {
            displs_vertices[i] = displs_vertices[i - 1] + vertice_arr_sizes[i - 1];
        }
        
        // init array edges
        edges_arr_sizes = malloc(sizeof (int) * size);
        for (int i = 0; i < size - 1; i++) {
            edges_arr_sizes[i] = offsets[displs_vertices[i + 1]] - offsets[displs_vertices[i]];
        }
        edges_arr_sizes[size - 1] = numEdges - offsets[displs_vertices[size - 1]];
        
        // init displs array for scattering
        displs_edges = malloc(sizeof (int) * size);
        displs_edges[0] = 0;
        for (int i = 1; i < size; i++) {
            displs_edges[i] = displs_edges[i - 1] + edges_arr_sizes[i - 1];
        }
    }
    
    // debug mode boolean argument
    int isDebug = 1;
    if (argv[3] != NULL) {
        isDebug = atoi(argv[3]);
    }
    // if debug is 1, disable printf
    if (!isDebug)
        fclose(stdout);
    
    // brodacast source vertice
    MPI_Bcast(&source, 1, MPI_INT, root, MPI_COMM_WORLD);
    // broadcast total number of vertices
    MPI_Bcast(&numVertices, 1, MPI_INT, root, MPI_COMM_WORLD);
    
    // root
    if (rank != root) {
        // allocate mem for displs arrays
        displs_vertices = malloc(sizeof (int) * size);
        displs_edges = malloc(sizeof (int) * numVertices);
    }
    // broadcast displs arrays for vertices and edges
    MPI_Bcast(displs_vertices, size, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(displs_edges, numVertices, MPI_INT, root, MPI_COMM_WORLD);
    
    // scatter array sizes to each node
    MPI_Scatter(vertice_arr_sizes, 1, MPI_INT, &local_offset_size, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(edges_arr_sizes, 1, MPI_INT, &local_edge_size, 1, MPI_INT, root, MPI_COMM_WORLD);
    
    // allocate memory for storing vertices and edges for each node
    local_offsets = malloc(sizeof (int) * local_offset_size + 1);
    local_edges = malloc(sizeof (int) * local_edge_size);
    
    // Scatter vertices and edges
    MPI_Scatterv(offsets, vertice_arr_sizes, displs_vertices, MPI_INT, local_offsets, local_offset_size, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatterv(edges, edges_arr_sizes, displs_edges, MPI_INT, local_edges, local_edge_size, MPI_INT, root, MPI_COMM_WORLD);
    local_offsets[local_offset_size] = local_offsets[0] + local_edge_size;
    
    // debug printing
    //**//
    printf("P%d: local_number_of_vertices=%d\n", rank, local_offset_size);
    for(int i = 0; i < local_offset_size; i++)
        printf("P%d: vertices[%d]=%d, normalized_vertices[%d]=%d\n", rank, i, local_offsets[i], i, local_offsets[i] - local_offsets[0]);
    printf("P%d: local_number_of_edges=%d\n", rank, local_edge_size);
    for(int i = 0; i < local_edge_size; i++)
        printf("P%d: edges[%d]=%d\n", rank, i, local_edges[i]);
    //**//
    
    // free memory
    free(displs_edges);
    // root
    if (rank == root)
        free(vertice_arr_sizes);
    free(edges_arr_sizes);
    
    // allocate mem for distance memory
    distance = malloc(sizeof (int) * numVertices);
    
    // init distance array with value -1
    for (int i = 0; i < numVertices; i++)
        distance[i] = -1;
    distance[source] = 0;
    
    // init level
    level = 1;
    
    // buffer size calculation: ceiling integer division; max_ possible no. of elements for a single node
    int buff_size = (numVertices + size - 1) / size;
    // init Frontier Stack
    struct Stack* FS = createStack(buff_size);
    
    // ops := owner of the source vertice
    ops = find_owner(source, displs_vertices, size);
    
    // no. of elements in stack := 0
    int queue_counter = 0;
    
    // owner of source vertice
    if (rank == ops) {
        // push source vertice to Frontier Stack
        push(FS, source);
        queue_counter = 1;
        // distance of source vertice is 0
        distance[source] = 0;
    }
    
    // 2D contagious array allocation as buffers
    int **send_buff = alloc_2d_int(buff_size, size);
    int **recv_buff = alloc_2d_int(buff_size, size);
    // buffer sizes, each element indicates no. of elements to i/o in buffer
    int *send_buff_sizes = malloc(sizeof (int) * size);
    int *recv_buff_sizes = malloc(sizeof (int) * size);
    // init with 0
    for (int i = 0; i < size; i++) {
        send_buff_sizes[i] = 0;
        recv_buff_sizes[i] = 0;
    }
    // init with -1
    for (int i = 0; i < buff_size; i++) {
        for (int j = 0; j < size; j++) {
            send_buff[i][j] = -1;
            recv_buff[i][j] = -1;
        }
    }
    
    // WHILE ALL Frontier Stacks are NOT empty
    while (!are_all_empty(FS, size)) {
        // WHILE current F.S. is NOT empty
        while (!isEmpty(FS)) {
            // FOR each element in F.S.
            while (queue_counter > 0) {
                // pop from stack as current element
                int cur = pop(FS);
                queue_counter--;
                // find number of neighbors for current vertice
                int no_of_neighbors = get_no_of_neigbors(cur, local_offsets, displs_vertices, rank);
                // loop for each neighbor
                for (int i = 0; i < no_of_neighbors; i++) {
                    // find i. neighbor of current vertice
                    int neighbor = find_neighbor(cur, local_offsets, local_offset_size, i, local_edges, displs_vertices, rank);
                    // owner node of i. neighbor
                    int pv = find_owner(neighbor, displs_vertices, size);
                    // if i. neighbor is not already put into buffer
                    if (!already_exists(send_buff, pv, send_buff_sizes[pv], neighbor)) {
                        // send buffer's pv. column and final row set to neighbor
                        send_buff[send_buff_sizes[pv]][pv] = neighbor;
                        // increment read size for buffer of the owner node
                        send_buff_sizes[pv]++;
                    }
                }

            }

        }
        
        // allToAll communication to realize sending buffers in each processor in receive buffer
        for (int i = 0; i < buff_size; i++)
            MPI_Alltoall(&(send_buff[i][0]), 1, MPI_INT, &(recv_buff[i][0]), 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Alltoall(send_buff_sizes, 1, MPI_INT, recv_buff_sizes, 1, MPI_INT, MPI_COMM_WORLD);
        
        // for all received vertices coming from j. node
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < recv_buff_sizes[j]; i++) {
                // if vertice has not already been visited
                if (distance[recv_buff[i][j]] == -1) {
                    // set distance value as level
                    distance[recv_buff[i][j]] = level;
                    // push vertice to Frontier Stack
                    push(FS, recv_buff[i][j]);
                    queue_counter++;
                }
            }
        }
        // increment level
        level++;
        
        //reset buff sizes to 0
        for (int i = 0; i < size; i++) {
            send_buff_sizes[i] = 0;
            recv_buff_sizes[i] = 0;
        }
        
    }
    
    // free
    free(&(send_buff[0][0]));
    free(&(recv_buff[0][0]));
    free(send_buff);
    free(recv_buff);
    free(send_buff_sizes);
    free(recv_buff_sizes);
    free(displs_vertices);
    free(local_offsets);
    free(local_edges);
    
    // root
    if (rank == root) {
        // allocate memory for resulting array
        result = malloc(sizeof (int) * numVertices);
    }
    
    // allToOne reduce; taking max of each node's distance value elements; producing result
    MPI_Reduce(distance, result, numVertices, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);
    
    // free
    free(distance);

    // root
    if (rank == root) {
        // write to file
        FILE *resultPtr = fopen(output_file_name, "w+");
        for (int i = 0; i < numVertices; i++) {
            fprintf(resultPtr, "%d\n", result[i]);
        }
        fclose(resultPtr);
        // free resulting memory
        free(result);
    }

    MPI_Finalize();
    return (EXIT_SUCCESS);
}

int find_owner(int vertex, int* displs, int size) {
    int i = 0;
    while (displs[i] <= vertex && i < size)
        i++;
    return i - 1;
}

int** alloc_2d_int(int rows, int cols) {
    int *data = (int *) malloc(rows * cols * sizeof (int));
    int **array = (int **) malloc(rows * sizeof (int*));
    for (int i = 0; i < rows; i++)
        array[i] = &(data[cols * i]);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            array[i][j] = 0;
    return array;
}

int get_no_of_neigbors(int vertex, int *local_offsets, int *displs, int rank) {
    int index;
    if (rank == 0) {
        index = vertex;
    } else {
        index = vertex % displs[rank];
    }
    return local_offsets[index + 1] - local_offsets[index];
}

int find_neighbor(int vertex, int *local_offsets, int local_offset_size, int index, int *local_edges, int *displs, int rank) {
    int norm_index;
    if (rank == 0) {
        norm_index = vertex;
    } else {
        norm_index = vertex % displs[rank];
    }
    return local_edges[local_offsets[norm_index] - local_offsets[0] + index];
}

int are_all_empty(struct Stack* FS, int size) {
    int is_empty = isEmpty(FS);
    MPI_Allreduce(&is_empty, &is_empty, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return is_empty == size;
}

int already_exists(int **buffer, int col, int buffer_size, int toSearch) {
    for (int i = 0; i < buffer_size; i++)
        if (buffer[i][col] == toSearch)
            return 1;
    return 0;
}