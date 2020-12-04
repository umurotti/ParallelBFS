#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "util.h"

int* BFS(int numVertices, int numEdges, int *offsets, int *edges, int source);

struct entry {
    int data;
    TAILQ_ENTRY(entry) entries; /* Tail queue. */
};
TAILQ_HEAD(tailhead, entry);

int main(int argc, char** argv) {
    char *input_file_name = "./sample_data.txt";
    if (argv[1] != NULL) {
        input_file_name = argv[1];
    }
    
    int source = 0;
    if(argv[2] != NULL) {
        source = atoi(argv[2]);
    }
    
    char *output_file_name = "./output_sample_data.txt";
    if (argv[3] != NULL) {
        output_file_name = argv[3];
    }
    
    int numVertices = 0;
    int numEdges = 0;
    int *offsets = NULL;
    int *edges = NULL;
    
    read_file(input_file_name, &numVertices, &numEdges, &offsets, &edges);

    int *distance = BFS(numVertices, numEdges, offsets, edges, source);
    
    FILE *resultPtr = fopen(output_file_name, "w+");
    for(int i = 0; i < numVertices; i++) {
        fprintf(resultPtr, "%d\n", distance[i]);
    }
    fclose(resultPtr);
    
    free(distance);
    return (EXIT_SUCCESS);
}

int* BFS(int numVertices, int numEdges, int *offsets, int *edges, int source) {
    // initialize queue
    struct tailhead head;
    TAILQ_INIT(&head);

    // insert source element as the first element to queue
    struct entry *source_vertice = malloc(sizeof (struct entry));
    source_vertice->data = source;
    TAILQ_INSERT_TAIL(&head, source_vertice, entries);
    int queue_counter = 1;
    
    // allocate array for storing distance values
    int *distance = malloc(sizeof (int) * numVertices);
    // initialize distance array values as +Inf
    for (int i = 0; i < numVertices; i++)
        distance[i] = -1;
    // distance of source to itself
    distance[source] = 0;
    // initial level
    int level = 1;
    
    // declaration of next element to be processed
    struct entry *next = NULL;
    // while queue is not empty
    while (TAILQ_FIRST(&head) != NULL) {
        // declaration of no. of added elements in this iteration as 0
        int no_of_added_elements = 0;
        // for each element in queue already before starting search
        while(queue_counter > 0)
        {
            // next = DEQUEUE(Q)
            next = TAILQ_FIRST(&head);
            TAILQ_REMOVE(&head, next, entries);
            queue_counter--;
            
            // number of neighbors to reach for the current vertex
            int num_of_neighbors = offsets[next->data + 1] - offsets[next->data];
            // for each neighbor of current vertex
            for (int i = 0; i < num_of_neighbors; i++) {
                int neighbor = edges[offsets[next->data] + i];
                if (distance[neighbor] == -1) {
                    distance[neighbor] = level;
                    struct entry *vertice = malloc(sizeof(struct entry));
                    vertice->data = neighbor;
                    TAILQ_INSERT_TAIL(&head, vertice, entries);
                    no_of_added_elements++;
                }
            }
            free(next);
        }
        // set size of queue as no. of added new elements
        queue_counter = no_of_added_elements;
        // increase level
        level++;
    }

    return distance;
}