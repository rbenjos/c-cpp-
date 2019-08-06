
#include <stdio.h>
#include <stdlib.h> // Imported for "EXIT_FAILURE" and "EXIT_SUCCESS"
#include <string.h> // Imported for "strtok"
#include <math.h>

/**
 * @brief Defines the maximum line length.
 */
#define LINE_MAX_SIZE 1024

/**
 * @brief The delimiters used to separate the input
 */
#define INPUT_DELIMS " \t\r\n"


int double_is_valid(char *str_number) {
    int counter = 0;
    int del_counter = 0;
    while (str_number[counter] != '\0') {
        char current_char = str_number[counter];
        int digit = current_char - '0';
        if (0 <= digit && digit <= 9) {
            counter++;
        } else {
            if (current_char == '.') {
                del_counter++;
                counter++;
            } else {
                fprintf(stderr,"ERROR\n");
                exit(EXIT_FAILURE);
                //todo: ERROR!
            }
        }
    }
    if (del_counter <= 1 && counter <= 9) {
        return 0;
    } else {
        fprintf(stderr,"ERROR\n");
        exit(EXIT_FAILURE);
        //todo: ERROR!
    }
}


int int_is_valid(char *str_number) {
    int counter = 0;
    int del_counter = 0;
    while (str_number[counter] != '\0') {
        char current_char = str_number[counter];
        int digit = current_char - '0';
        if (0 <= digit && digit <= 9) {
            counter++;
        } else
            {
                fprintf(stderr,"ERROR\n");
                exit(EXIT_FAILURE);
                //todo: ERROR!
            }
    }
}


double max_of_array(double conv_array[], int length) {
    double max = 0;
    int i;
    double current = 0;
    for (i = 0; i < length; i++) {
        current = round((conv_array[i] * 1000)) / 1000;
//        current = conv_array[i];
        if (current > max) {
            max = current;
        }
    }
    return max;
}

int output_histogram(double *conv_array, int length) {
    double max = max_of_array(conv_array, length);
    double current;
    int num_of_stars;
    int i;
    for (i = 0; i < length; i++) {
        current = round((conv_array[i] * 1000)) / 1000;
        double num_of_stars = floor((current * 20.0) / max);
        printf("\n%.3f: ", current);
        for (; num_of_stars--;) {
            printf("*");
        }
    }
    return 0;
}

int phi(int length, int t) {
    int phi = floor((length / 2)) + t;
    return phi;

}

/**
 * this function shortens the amplification array to match the samples array
 * @param array the pointer of the array we want to shorten
 * @param length the length to which we want to shorten
 * @return 0 if was successful, 1 if not
 */
int shorten_array(double *array, int length) {
    int counter = length;
    for (; counter < 100; counter++) {
        *(array + counter) = 0;
    }
    return 0;
}


void print_array(double *array, int length) {
    int i = 0;
    for (; i < length; i++) {
        if ((array[i]) > 0.0000000000000000001) {
            printf("%f,", (array[i]));
        } else { printf("_"); }
    }
    printf("\n");
}

/**
 * this function takes an array (either the samples or the amplifications) and centers its values as requested
 * in the exercise description
 * @param array the array we are centering
 * @param length the length of the array (the actual data in it, all arrays are length 100 here)
 * @return the pointer of the new and centered array
 */
double *center_array(double *array, int length) {

    double *centered_array = (double *) (malloc(100 * sizeof(double)));
    int counter = 0;
    int margin1 = ((100 - length) / 2);
    int margin2 = ((100 - length) / 2);
    for (; margin1--;) {
        *(centered_array + counter) = 0;
        counter++;
    }
    int i = 0;
    for (; i < length; i++) {
        *(centered_array + counter) = *(array + i);
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
int normalize_array(double *array) {
    double sum = 0.0;
    int i = 0;
    for (; i < 100; i++) {
        sum += *(array + i);
    }
    int j = 0;
    for (; j < 100; j++) {
        *(array + j) /= sum;
    }
}

/**
 * this function receives a string and parses it into a double with no more than 8 significant digits
 * @param string a pointer to the string representing a single number
 * @return a double of the parsed string
 */
double str_to_trunc_double(char *string) {


    int delimeter_counter = 0;
    int counter = 0;
    int dotposition = 0;
    double number = 0;

    if (double_is_valid(string)==0) {

        while (*(string + counter) != '\0') {
            char current_char = *(string + counter);
            if (current_char == '.') { dotposition = counter; }
            else {
                int current_int = current_char - '0';
                number = number * 10 + current_int;
                //printf("%c_",current_char);
                // check validity with
                //printf("current number is %f \n ",number);
            }
            counter++;
        }
        if (dotposition) {
            dotposition = counter - dotposition - 1;
            for (; dotposition--;) {
                number /= 10;
                // check validity with
                //printf("current cut number is %f \n ",number);
            }
        }
    } else {
        fprintf(stderr,"ERROR\n");
        exit(EXIT_FAILURE);
        //todo: ERROR!!
    }

    return number;

}

/**
* this function receives a string and parses it into a double with no more than 8 significant digits
* @param string a pointer to the string representing a single number
* @return a double of the parsed string
*/
int str_to_int(char *string) {


    int counter = 0;
    int number = 0;

    if (int_is_valid(string) == 0) {

        while (*(string + counter) != '\0') {
            char current_char = *(string + counter);
            int current_int = current_char - '0';
            number = number * 10 + current_int;
            //printf("current digit is: %d \n and the whole integer is: %d",current_int, number);
            // check validity with
            //printf("current number is %f \n ",number);
            counter++;
        }

        //printf("final number is %f \n ",number);
        return number;
    } else
        {
            fprintf(stderr,"ERROR\n");
            exit(EXIT_FAILURE);
            // todo: ERROR!
        }
}



/**
 * this function finds the end of the data in a given array, defined as the location of the first zero after which
 * all remaining members are zeros.
 * @param arr a pointer referring to the array we are measuring
 * @return 0 if was successful and 1 if not
 */
int find_end_of_array(double *arr) {
    int has_zero = 0;
    int cur_zero_location = 0;
    int counter = 0;

    while (counter < 100) {
        if (!*(arr + counter)) {
            if (!has_zero) {
                cur_zero_location = counter;
                has_zero = 1;
            }
        } else {
            has_zero = 0;
        }
        counter++;
    }
    return cur_zero_location;
}

/**
 * this function creates an array of either samples (from the drum) or amplification function values.
 * it takes in a single line of chars from the user, if the input is valid, it breaks it up into double typed numbers
 * (not more than a 100 of those), each has 9 digits (including the delimeter), and puts them into an array
 * @return the pointer of the array
 */
double *make_array() {
    /* Initializing the variables that'll contain the line information */
    char line[LINE_MAX_SIZE];
    char *value = NULL;

    /* Reads the line from the stdin */
    if (fgets(line, LINE_MAX_SIZE, stdin) == NULL) {
        fprintf(stderr, "No input\n");
//        return EXIT_FAILURE;
    }

    /* Now "line" contains the contents of the entire line, including the suffix "\n", and "strlen(line)" contains the line length.
     Lets read the first value. If there's no input, we'll get "NULL" */
    value = strtok(line, INPUT_DELIMS);

    /* Handle every value and read the next value */
    double *arr = (double *) (malloc(100 * sizeof(double)));
    int counter = 0;
    while (value != NULL) {
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
        if (counter>100){
            fprintf(stderr,"ERROR\n");
            exit(EXIT_FAILURE);
            //todo: ERROR!
        }
    }
    while (counter < 100) {
        arr[counter] = 0;
        counter++;
    }

    for (; counter--;) {
        //printf("%f_",arr[99-counter]);
    }
    double *pointer_to_arr = &arr[0];
    return pointer_to_arr;
}


double *convolve(double f[], int length_of_samples, double g[], int length_of_amps) {


    int N = length_of_samples;
    int M = length_of_amps;

    int t_start = -ceil((N / 2)) - 1;
    int t_end = floor((N / 2)) - 1;
    int t = t_start;

    int m;
    int m_start;
    int m_end;
    double conv_sum;
    double *convoluted_array = (double *) (malloc(M * sizeof(double)));

    for (; t < t_end; t++) {

//        printf("t is : %d \n",t);
        conv_sum = 0;

        if (0 <= phi(N, t) && phi(N, t) <= N) {

            int m_start = -M / 2;
            int m_end = M / 2;
            int m = m_start;
            for (; m <= m_end; m++) {
                if (0 <= phi(M, t - m) && phi(M, m) <= M) {
//                    printf(" %.2f*%.2f+" ,f[phi(M, t - m)],g[phi(M, m)]);
                    conv_sum += ((f[phi(M, t - m)]) * ((g[phi(M, m)])));
                }
            }
            *(convoluted_array + phi(M, t) + 1) = conv_sum;
        }
    }
    return convoluted_array;

}

int main(int argc, const char *argv[]) {
    // first we will get our samples array
    printf("please enter the drum beats array: \n");
    double *pointer_to_samples = make_array();

    // then our amplification array
    printf("please enter the amplification values array: \n");
    double *pointer_to_amp = make_array();

    int length_of_samples = find_end_of_array(pointer_to_samples);
    int length_of_amps = find_end_of_array(pointer_to_amp);


    // if the length of samples is bigger than length of amps, we need to shorten the amount of samples:
    if (length_of_samples < length_of_amps) {
        fprintf(stderr,"ERROR\n");
        exit(EXIT_FAILURE);
        //todo: ERROR!
    }

    // and then we will get n
    printf("please enter n, then number of convolutions with the amplification function: \n");

    char raw_n[LINE_MAX_SIZE];
    fgets(raw_n, LINE_MAX_SIZE, stdin);
    char *parsed_n = strtok(raw_n, INPUT_DELIMS);

    int n = str_to_int(parsed_n);

//    printf("printing received arrays: \n\n");
//
//    print_array(pointer_to_samples, 100);
//    print_array(pointer_to_amp, 100);
//
//    // then we will get our array's data's lengths
//
//    printf("\nfinding length of arrays\n");
//
//
//    printf("length of samples is: %d \n", length_of_samples);
//    printf("length of amps is: %d \n", length_of_amps);
//
//
    // then we will center them as requested

    printf("\ncentering arrays \n");
    pointer_to_samples = center_array(pointer_to_samples, length_of_samples);
    pointer_to_amp = center_array(pointer_to_amp, length_of_amps);
//
//    printf("\nprinting centered arrays: \n");
//
//    print_array(pointer_to_samples, 100);
//    print_array(pointer_to_amp, 100);
//
//
//    // then we will normalize the samples
//
//    printf("\nnormalizing samples\n");
//
    normalize_array(pointer_to_samples);
//
//    printf("\nprinting normalized arrays: \n");
//
//    print_array(pointer_to_samples, 100);
//    print_array(pointer_to_amp, 100);

//    double a[] = {0.000, 0.000, 0.130, 0.174, 0.217, 0.261, 0.217, 0.000, 0.000, 0.000};
//
//    double b[] = {0.000, 0.000, 0.000, 0.200, 0.400, 0.400, 0.000, 0.000, 0.000, 0.000};
//
//    double* a1 = &a[0];
//    double* b1 = &b[0];

    double *convolved_function = pointer_to_samples;

    printf("\n");

    // now its time to convolve as many times as given
    int j;
    for (j = 0; j < n; j++) {
        convolved_function = convolve(convolved_function, 100, pointer_to_amp, 100);
        normalize_array(convolved_function);
//        printf("\n");
//        print_array(convolved_function, 100);
    }

    // and print out the histogram

    output_histogram(convolved_function, 100);
}
