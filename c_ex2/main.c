
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include "queue.h"
#include "queue.c"

#define FILE_EXISTS 1
#define FILE_DOESNT_EXIST 0
#define  FILE_IS_NOT_EMPTY 1
#define  NUMBER_OF_ARGUMENTS_VALID 1
#define  MAX_CHARS_IN_LINE 1024
#define INPUT_DELIMS " \t\r\n"


//-done-  : define a data structure by typedef for a node and for the whole tree

/**
 *  this structure defines a node in our graph. it has a key,
 *  a queue of son's keys and another queue of sons nodes
 */
typedef struct
{
    // each node should have a key and sonsKeys, so:
    int key;
    Queue *sonsKeys;
    Queue *sonsNodes;


} Node;

/**
 * this structure defines a digraph, specifically a tree, (although initially we dont
 * know its a tree). it has a root, and some data members for the required information
 * on that tree
 */
typedef struct
{

    Node *root;
    int vertices;
    int edges;
    int maxDepth;
    int minDepth;
    int diatmeter;

} Graph;


/* ############### tree analyzer ############### */

/* im trying to perfect the way im approaching exercises.
 * it seems that for the longer exercises, just running towards them is not really the right approach.
 * the new way, at least for the sake of experiment, will be to first go over all of the exercise, and translate
 * it to actual TODOs, then to program to an interface, and only then finalizing the implementation.
 */


// before starting the exercise:

// // TODO: - catch up on basic graph theory
// //       - learn DFS algorithm
// //       - learn BFS algorithm
// //       - best explanation video is : https://www.youtube.com/watch?v=zaBhtODEL0w

//



// receiving arguments through the command line:
// // -done-: check if number of arguments is valid if not:
// // -done- - print the following message:
// // -done-  - with stderr
// // -done- - "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n"
// // -done-  - exit program with EXIT_FAILURE code

/**
 * this function checks if the number of arguments we got from the command line
 * is valid or not and handles it accordingly
 * @param argc the number of arguments we received
 * @return 1 if successful, nothing if if not
 */
int handleArgValidity(int argc)
{
    if ( argc != 3 )
    {
        fprintf(stderr, "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n");
        exit(EXIT_FAILURE);
    } else{
        return NUMBER_OF_ARGUMENTS_VALID;
    }
}


// // handle txt file address
// // // -done-: check if txt file exists (by relative path)
// // // -done- - if not, print: "Invalid input\n" with stderr
// // // -done- - exit program with EXIT_FAILURE code

/**
 * this function checks if the address we got for the txt file leads to an existing
 * file
 * @param filename the adress of the file we are validating
 * @return 1 if exists, exits the program if not
 */
int checkFileExists(const char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if ( file )
    {
        fclose(file);
        return FILE_EXISTS;
    }
    else
    {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
}



// // handle first vertex
// // // -done-: check if vertex is a valid natural number
// // // -done- - if not, print: "Invalid input\n" with stderr
// // //  -done- - exit program with EXIT_FAILURE code

// // handle second vertex

// // // -done-: check if vertex is valid natural number
// // // -done-  - if not, print: "Invalid input\n" with stderr
// // // -done-  - exit program with EXIT_FAILURE code


/**
 * this function receives a string, checks if it represents a valid
 * integer, returns it if its valid, and handles the error if not
 * @param string the string representing the integer
 * @return the integer represented if its valid. nothing if not
 */
int returnIntIfValid(const char *string)
{
    int counter = 0;
    int number = 0;
    while ( string[counter] != '\0' )
    {
        char currentChar = string[counter];
        int digit = currentChar - '0';
        if ( 0 <= digit && digit <= 9 )
        {
            number = number * 10 + digit;
        }
        else
        {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
    }
    return number;
}
// parsing the txt file:

// // check validity:

// // // -done-:- check if file is empty, if it is. print: "Invalid input\n" with stderr
// // //   -done-   - exit program with EXIT_FAILURE code

/**
 * this function checks if the file (after we validated its existence) is empty
 * @param filename the file we are checking
 * @return 1 if its not empty, nothing if it is empty.
 */
int checkFileNotEmpty(const char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    // if the file is empty the end of it will be 0
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if ( 0 != size )
    {
        fclose(file);
        return FILE_IS_NOT_EMPTY;
    }
    else
    {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
}


// // handiling first line

// // // -done-: read first number and mark as n = num of vertexes
// // // -done-: check if its a valid natural number > 0


// // handling the lines after that
// // TODO: read every line number as a vertex (key(line) = line - 2)

// // TODO: read every line's numbers as the sonsKeys of that vertex

/*  TODO: save in a special data structure (data members: key, sonsKeys) and
    TODO: and if "-" in the line instead of numbers, leave sonsKeys empty*/

// // TODO: notice finishing not with \n, but with \0 (or any other end of the file literal)

// // after finishing reading all the lines

// // TODO: - check if n actually represents the number of line
// //       - check if the vertexes given in the cli exist

/**
 * this function receives a node, and a string representing all of its children.
 * if the input is valid, it sets up children for the given node
 * @param node the node for which we are making children/branches
 * @param currentLine the line of text representing its children
 * @return 1 if successful, nothing if not
 */
int giveChildren(Node *node, const char *currentLine)
{

    /* first we will make a queue for the sons's keys (because we dont necessarily have
    all of their nodes yet */

    char *currentNum = NULL;
    node->sonsKeys = allocQueue();

    // then we will read each individual string (hopefully its an integer
    currentNum = strtok(currentLine, INPUT_DELIMS);
    while ( currentNum != NULL)
    {
        int currentInt = returnIntIfValid(currentNum);
        enqueue(node->sonsKeys, currentInt);
    }
    return 0;
}

/**
 * this function reads the text file, and builds the base for the graph, meaning
 * a data structure to host all the information about the vertices and connections
 * @param filename the file we are reading
 * @return 1 if successful, 0 if not
 */
int readTreeFile(const char *filename)
{
    // opening the file

    FILE *file;
    file = fopen(filename, "r");
    int numberOfLine = 0;

    char *currentLine = NULL;
    // first handling n

    fgets(currentLine, MAX_CHARS_IN_LINE, file);
    numberOfLine ++;
    int n = returnIntIfValid(currentLine);

    // now reading the rest of them iteratively

    while ( fgets(currentLine, MAX_CHARS_IN_LINE, file))
    {
        numberOfLine ++;
        Node *node = malloc(sizeof(Node));
        node->key = numberOfLine;
        giveChildren(node, currentLine);

        /* parse each line individually, save each as a node by the line number
           and save the content of the line as the children */
    }
}


// data structure validation
// TODO: check that the data structure you made is actually a tree:
//       - find the most efficient algorithm to ensure that this is a tree
//       - probably has no loops, and is connected
//       - if it is not a tree, print the following message through stderr
//       - "The given graph is not a tree\n"

// TODO: - find maximal depth
//          - find minimal depth
//          - find diameter
//          - find pathlength between 2 vertices given

/**
 * this function takes in a tree (after we have verified its a tree) and gives
 * back its maximal depth
 * @param graph our tree
 * @return its maximal depth
 */
int getMaximalDepth(Graph graph)
{
    int maximalDepth = 0;
    Node *root = graph.root;
    return maximalDepth;
}

/**
 * this function takes in a tree (after we have verified its a tree) and gives
 * back its minimal depth
 * @param graph our tree
 * @return its minimal depth
 */
int getMinimalDepth(Graph graph)
{
    int minimalDepth;
    return minimalDepth;
}

/**
* this function takes in a tree (after we have verified its a tree) and gives
 * back its diameter. meaning the largest path available withing that tree.
 * @param graph our tree
 * @return the diameter of this tree
 */
int getDiameter(Graph graph)
{
    int diameter = 0;
    return diameter;

}

/**
 * this function takes in a tree, and 2 vertices (who are verified to be in that tree)
 * calculates and gives back the shortest path between those 2 vertices
 * @param graph our tree
 * @param u the first vertex (order matters here)
 * @param v the second vertex
 * @return a queue representing the shortest path between those 2 vertices
 */
Queue getPath(Graph graph, Node u, Node v)
{
    Queue path;
    return path;

}

// output:

// // TODO: print the following by their order:
// //       - the key of the root
// //       - the number of vertexes
// //       - number of edges
// //       - minimal depth
// //       - maximal depth
// //       - maximal path's length
// //       - the sequence of vertexes from u to v, by order, with spaces between
// //

/**
 * this function takes in a tree, and prints the required information about
 * that tree
 * @param graph the tree we are analyzing
 * @param u the first vertex (order matters here)
 * @param v the second vertex
 * @return 1 if successful, nothing if not
 */
int output(Graph graph, Node u, Node v)
{
    printf("%d\n", graph.root->key);
    printf("%d\n", graph.vertices);
    printf("%d\n", graph.edges);
    printf("%d\n", graph.minDepth);
    printf("%d\n", graph.maxDepth);
    printf("%d\n", graph.root->key);

    Queue path = getPath(graph, u, v);


}

// after finishing the exercise:

// // TODO: - compare with school solution for at least 25 data structures
// //       - README file
// //       - run on school computers
// //       - assure runtime efficiency limitations
