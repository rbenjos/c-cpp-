#include <stdio.h>
#include <stdlib.h> // Imported for "EXIT_FAILURE" and "EXIT_SUCCESS"
#include <string.h> // Imported for "strtok"

/**
 * @brief Defines the maximum line length.
 */
#define LINE_MAX_SIZE 1024

/**
 * @brief The delimiters used to separate the input
 */
#define INPUT_DELIMS " \t\r\n"

/**
 * @brief The main function that runs the program.
 * @param argc Non-negative value representing the number of arguments passed
 * to the program from the environment in which the program is run.
 * @param argv Pointer to the first element of an array of pointers to null-terminated
 * multibyte strings that represent the arguments passed to the program from the execution
 * environment. The value of argv[argc] is guaranteed to be a null pointer.
 * @return 0, to tell the system the execution ended without errors, or 1, to
 * tell the system that the code has execution errors.
 */

/**
 * this function shortens the amplification array to match the samples array
 * @param array the pointer of the array we want to shorten
 * @param length the length to which we want to shorten
 * @return 0 if was successful, 1 if not
 */
int shorten_array (double* array, int length){
    int counter = length;
    for (;counter<100;counter++){
        *(array+counter)=0;
    }
    return 0;
}

/**
 * this function takes an array (either the samples or the amplifications) and centers its values as requested
 * in the exercise description
 * @param array the array we are centering
 * @param length the length of the array (the actual data in it, all arrays are length 100 here)
 * @return the pointer of the new and centered array
 */
double* center_array (double* array, int length) {
    double *centered_array = (double *) (malloc(100 * sizeof(double)));
    int counter = 0;
    int margin1 = (length / 2) - 1;
    int margin2 = (length / 2) - 1;
    for (; margin1--;) {
        *(centered_array + counter) = 0;
        counter++;
    }
    int i=0;
    for (; i<length;i++) {
        *(centered_array + counter) = *(array+i);
        counter++;
    }


    for (; margin2--;) {
        *(centered_array + counter) = 0;
        counter++;
    }
    return centered_array;
}

/**
 * this function normalizes an array with the L1 normalization. basically sums up the array, and then divides each
 * of its members by the sum.
 * @param array a pointer referring to the array we are normalizing.
 * @return 0 if was successful and 1 if not.
 */
int normalize_array(double* array){
    double sum = 0.0;
    int i=0;
    for (;i<100;i++){
        sum+= *(array+i);
    }
    int j=0;
    for (;j<100;j++){
        *(array+j) /= sum;
    }
}

/**
 * this function receives a string and parses it into a double with no more than 8 significant digits
 * @param string a pointer to the string representing a single number
 * @return a double of the parsed string
 */
double str_to_trunc_double(char* string)
{


    int delimeter_counter=0;
    int counter = 0;
    int dotposition=0;
    double number = 0;
    while (counter<9 && *(string+counter) != '\0' ){
        char current_char = *(string+counter);
        if (current_char == '.'){dotposition = counter;}
        else {
            int current_int = current_char - '0';
            number = number*10 +current_int;
            //printf("%c_",current_char);
            // check validity with
            //printf("current number is %f \n ",number);
        }
        counter++;
    }
    if (dotposition) {
        dotposition = counter - dotposition-1;
        for (; dotposition--;) {
            number /= 10;
            // check validity with
            //printf("current cut number is %f \n ",number);
        }
    }
    //printf("final number is %f \n ",number);
    return number;

    }


/**
 * this function finds the end of the data in a given array, defined as the location of the first zero after which
 * all remaining members are zeros.
 * @param arr a pointer referring to the array we are measuring
 * @return 0 if was successful and 1 if not
 */
int find_end_of_array (double* arr){
    int has_zero = 0;
    int cur_zero_location = 0;
    int counter= 0;

    while (counter<100)
    {
        if (!*(arr+counter)){
            if (!has_zero){
                cur_zero_location = counter;
                has_zero = 1;
            }
        } else {
            has_zero =0;
        }
        counter++;
    }
    return  cur_zero_location;
}

/**
 * this function creates an array of either samples (from the drum) or amplification function values.
 * it takes in a single line of chars from the user, if the input is valid, it breaks it up into double typed numbers
 * (not more than a 100 of those), each has 9 digits (including the delimeter), and puts them into an array
 * @return the pointer of the array
 */
double* make_array()
{
    /* Initializing the variables that'll contain the line information */
    char line[LINE_MAX_SIZE];
    char *value = NULL;

    /* Reads the line from the stdin */
    if (fgets(line, LINE_MAX_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "No input\n");
        return EXIT_FAILURE;
    }

    /* Now "line" contains the contents of the entire line, including the suffix "\n", and "strlen(line)" contains the line length.
     Lets read the first value. If there's no input, we'll get "NULL" */
    value = strtok(line, INPUT_DELIMS);

    /* Handle every value and read the next value */
    double* arr = (double*)(malloc(100 * sizeof(double)));
    int counter = 0;
    while (value != NULL)
    {
        /* Read the value and print it */
        size_t length = strlen(value);
        double new_val = str_to_trunc_double(value);
        //printf("Input String: %f \n", new_val);
        arr[counter] = new_val;

        /* Using the same approach as we've done in Java,
         * we can iterate over the string characters using standard
         * array script operations.
         * For example:
           <code>
            for (int i = 0; i < length; ++i) {
                // str[i] is the i'th character in the string.
                printf("%c", str[i]);
            }
           </code>
         */

        /* Read the next value */
        value = strtok(NULL, INPUT_DELIMS);
        counter++;
    }
    while(counter<100){
        arr[counter]=0;
        counter++;
    }

    for (;counter--;){
        //printf("%f_",arr[99-counter]);
    }
    double* pointer_to_arr = &arr[0];
    printf("%p",pointer_to_arr);
    return pointer_to_arr;
}


int main(int argc, const char* argv[])
{
    // first we will get our samples array
    double* pointer_to_samples = make_array();

    // then our amplification array
    double* pointer_to_amp = make_array();


    int length_of_samples = find_end_of_array(pointer_to_samples);
    int length_of_amps = find_end_of_array(pointer_to_samples);
}