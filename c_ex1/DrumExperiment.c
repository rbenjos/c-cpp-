
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
#define MAX_STARS 20.0
#define EPSILON 0.00000001
#define MAX_ARRAY_LENGTH 100
#define MAX_CHARS_PER_DOUBLE 9

/**
 * this function checks whther a given string who is supposed to be converted to a double is indeed
 * a valid double
 * @param strNumber the string of the number we want to convert
 * @return 0 is valid, exits the program if not
 */
int doubleIsValid(char *strNumber)
{
    int counter = 0;
    int delCounter = 0;
    while (strNumber[counter] != '\0')
    {
        char currentChar = strNumber[counter];
        int digit = currentChar - '0';
        if (0 <= digit && digit <= MAX_CHARS_PER_DOUBLE)
        {
            counter ++;
        }
        else
        {
            if (currentChar == '.')
            {
                delCounter ++;
                counter ++;
            }
            else
            {
                fprintf(stderr, "ERROR\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (delCounter <= 1 && counter <= MAX_CHARS_PER_DOUBLE)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * this function checks if a string that is supposed to be converted to an integer
 * is indeed a valid integer
 * @param strNumber the string we want to convert to an integer
 * @return 0 if valid, exits the program if not
 */
int intIsValid(char *strNumber)
{
    int counter = 0;
    int delCounter = 0;
    while (strNumber[counter] != '\n' && strNumber[counter] != '\0')
    {
        char currentChar = strNumber[counter];
        int digit = currentChar - '0';
        if (0 <= digit && digit <= 9)
        {
            counter ++;
        }
        else
        {
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

/**
 * this function takes in an array of a certain length and finds the maximum member of that array
 * @param convArray the array we are looking in
 * @param length the length of that array
 * @return the maximum number in that array
 */
double maxOfArray(double *convArray, int length)
{
    double max = 0;
    int i;
    double current = 0;
    for (i = 0; i < length; i ++)
    {
        current = round(convArray[i] * 1000) / 1000;
        if (current > max)
        {
            max = current;
        }
    }
    return max;
}

/**
 * this function outputs a histogram of the array who is a result of all of the convolutions
 * @param convArray the array we are making the histogram from
 * @param length the length of that array
 * @return 0 if successful
 */
int outputHistogram(double *convArray, int length)
{
    double max = maxOfArray(convArray, length);

    if (max < EPSILON)
    {
        return 0;
    }

    double current;
    int numOfStars;
    int i;
    for (i = 0; i < length; i ++)
    {
        current = round((convArray[i] * 1000)) / 1000;
        double numOfStars = floor((current * MAX_STARS) / max);
        printf("\n%.3f: ", current);
        for (; numOfStars --;)
        {
            printf("*");
        }
    }
    return 0;
}

/**
 * this function helps us with adjusting the convolution indices to our arrays
 * @param length the length of the array (M or N)
 * @param t the point in which we are calculating the convolution
 * @return the adjusted value
 */
int phi(int length, int t)
{
    int phi = floor((length / 2)) + t;
    return phi;
}

/**
 * this function shortens the amplification array to match the samples array
 * @param array the pointer of the array we want to shorten
 * @param length the length to which we want to shorten
 * @return 0 if was successful, 1 if not
 */
int shortenArray(double *array, int length)
{
    int counter = length;
    for (; counter < MAX_ARRAY_LENGTH; counter ++)
    {
        *(array + counter) = 0;
    }
    return 0;
}

/**
 * this function is a helper function, conviniently prints arrays
 * @param array the array we are printing
 * @param length its length
 */
void printArray(double *array, int length)
{
    int i = 0;
    for (; i < length; i ++)
    {
        if ((array[i]) > 0.0000000000000000001)
        {
            printf("%.3f,", (array[i]));
        }
        else
        {
            printf("_");
        }
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
double *centerArray(double *array, int length, double *centeredArray)
{

//    centeredArray = (double *) (malloc(MAX_ARRAY_LENGTH * sizeof(double)));
    int counter = 0;
    int margin1 = ((MAX_ARRAY_LENGTH - length) / 2);
    int margin2 = ((MAX_ARRAY_LENGTH - length) / 2);
    for (; margin1 --;)
    {
        *(centeredArray + counter) = 0;
        counter ++;
    }
    int i = 0;
    for (; i < length; i ++)
    {
        *(centeredArray + counter) = *(array + i);
        counter ++;
    }


    for (; margin2 --;)
    {
        *(centeredArray + counter) = 0;
        counter ++;
    }
    return centeredArray;
}

/**
 * this function normalizes an array with the L1 normalization. basically sums up the array, and then divides each
 * of its members by the sum.
 * @param array a pointer referring to the array we are normalizing.
 * @return 0 if was successful and 1 if not.
 */
int normalizeArray(double *array)
{
    double sum = 0.0;
    int i = 0;
    for (; i < MAX_ARRAY_LENGTH; i ++)
    {
        sum += *(array + i);
    }
    int j = 0;
    for (; j < MAX_ARRAY_LENGTH; j ++)
    {
        *(array + j) /= sum;
    }
}

/**
 * this function receives a string and parses it into a double with no more than 8 significant digits
 * @param string a pointer to the string representing a single number
 * @return a double of the parsed string
 */
double strToDouble(char *string)
{
    int delimeterCounter = 0;
    int counter = 0;
    int dotposition = 0;
    double number = 0;

    if (doubleIsValid(string) == 0)
    {

        while (*(string + counter) != '\0')
        {
            char currentChar = *(string + counter);
            if (currentChar == '.')
            {
                dotposition = counter;
            }
            else
            {
                int current_int = currentChar - '0';
                number = number * 10 + current_int;
            }
            counter ++;
        }
        if (dotposition)
        {
            dotposition = counter - dotposition - 1;
            for (; dotposition --;)
            {
                number /= 10;
            }
        }
    }
    else
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
    return number;
}

/**
* this function receives a string and parses it into a double with no more than 8 significant digits
* @param string a pointer to the string representing a single number
* @return a double of the parsed string
*/
int strToInt(char *string)
{
    int counter = 0;
    int number = 0;

    if (intIsValid(string) == 0)
    {

        while ((string[counter]) != '\0' && (string[counter]) != '\n')
        {
            char currentChar = *(string + counter);
            int currentInt = currentChar - '0';
            number = number * 10 + currentInt;
            counter ++;
        }
        return number;
    }
    else
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * this function finds the end of the data in a given array, defined as the location of the first zero after which
 * all remaining members are zeros.
 * @param arr a pointer referring to the array we are measuring
 * @return 0 if was successful and 1 if not
 */
int findEndOfArray(double *arr)
{
    int hasZero = 0;
    int curZeroLocation = 0;
    int counter = 0;

    while (counter < MAX_ARRAY_LENGTH)
    {
        if (! *(arr + counter))
        {
            if (! hasZero)
            {
                curZeroLocation = counter;
                hasZero = 1;
            }
        }
        else
        {
            hasZero = 0;
        }
        counter ++;
    }
    return curZeroLocation;
}

/**
 * this function creates an array of either samples (from the drum) or amplification function values.
 * it takes in a single line of chars from the user, if the input is valid, it breaks it up into double typed numbers
 * (not more than a 100 of those), each has 9 digits (including the delimeter), and puts them into an array
 * @return the pointer of the array
 */
double *makeArray(double *arr)
{
    /* Initializing the variables that'll contain the line information */
    char line[LINE_MAX_SIZE];
    char *value = NULL;

    /* Reads the line from the stdin */
    if (fgets(line, LINE_MAX_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }

    /* Now "line" contains the contents of the entire line, including the suffix "\n", and "strlen(line)" contains the line length.
     Lets read the first value. If there's no input, we'll get "NULL" */
    value = strtok(line, INPUT_DELIMS);

    /* Handle every value and read the next value */
    int counter = 0;
    while (value != NULL)
    {
        /* Read the value and print it */
        size_t length = strlen(value);
        double newVal = strToDouble(value);
        //printf("Input String: %f \n", newVal);
        arr[counter] = newVal;

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
        counter ++;
        if (counter > 100)
        {
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);

        }
    }
    arr[100] = counter;
    while (counter < MAX_ARRAY_LENGTH)
    {
        arr[counter] = 0;
        counter ++;
    }

    for (; counter --;)
    {
    }
    double *pointerToArr = &arr[0];
    return pointerToArr;
}

/**
 * this function does the convolution itself, it takes in 2 arrays and outputs
 * an array (size 100) as the results
 * @param f our first array containing the sound samples
 * @param length_of_samples length of that array
 * @param g our second array containing the amplification values
 * @param length_of_amps length of the second array
 * @return an array (size 100) representing the value of the discrete convolution of the 2 arrays
 * given above
 */


int copyArray(double *firstArray, double *secondArray, int length)
{
    int i = 0;
    for (; i < length; i ++)
    {
        secondArray[i] = firstArray[i];
    }
}

double *convolve(double f[], int lengthOfSamples, double g[], int lengthOfAmps, double *new)
{


    int N = lengthOfSamples;
    int M = lengthOfAmps;

    int t_start = - ceil((N / 2)) - 1;
    int tEnd = floor((N / 2)) - 1;
    int t = t_start;

    int m;
    int m_start;
    int m_end;
    double convSum;
//    double *convoluted_array = (double *) (malloc(100 * sizeof(double)));

    for (; t < tEnd; t ++)
    {
        convSum = 0;

        if (0 <= phi(N, t) && phi(N, t) <= N)
        {
            int mStart = - M / 2;
            int mEnd = M / 2;
            int m = mStart;
            for (; m <= mEnd; m ++)
            {
                if (0 <= phi(M, t - m) && phi(M, m) <= M)
                {
                    printf("t is: %d and m is: %d\n",t,m);
                    convSum += ((f[phi(M, t - m)]) * ((g[phi(M, m)])));
                }
            }
            *(new + phi(M, t) + 1) = convSum;
        }
    }
    return new;

}

int main(int argc, const char *argv[])
{
    // first we will get our samples array
    double samples[101];
    double *pointerToSamples = &samples;
    pointerToSamples = makeArray(pointerToSamples);

    // then our amplification array
    double amps[101];
    double *pointerToAmp = &amps;
    pointerToAmp = makeArray(pointerToAmp);

    int lengthOfSamples = pointerToSamples[100];
    int lengthOfAmps = pointerToAmp[100];


    // if the length of samples is bigger than length of amps, we need to shorten the amount of samples:
    if (lengthOfSamples < lengthOfAmps && lengthOfSamples != 0)
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);

    }

    // and then we will get n

    char rawN[LINE_MAX_SIZE];
    if (fgets(rawN, LINE_MAX_SIZE, stdin) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }


    printf("printing arrays:\n");
    printf("array 1:\n");
    printArray(pointerToSamples,100);
    printf("array 2:\n");
    printArray(pointerToAmp,100);
    printf("\n");


    int n = strToInt(rawN);

    // then we will center them as requested

    double centeredSamples[MAX_ARRAY_LENGTH] = {0};
    double centeredAmps[MAX_ARRAY_LENGTH] = {0};

    pointerToSamples = centerArray(pointerToSamples, lengthOfSamples, centeredSamples);
    pointerToAmp = centerArray(pointerToAmp, lengthOfAmps, centeredAmps);

    printf("printing centered arrays:\n");
    printf("array 1:\n");
    printArray(pointerToSamples,100);
    printf("array 2:\n");
    printArray(pointerToAmp,100);
    printf("\n");

    // then we will normalize the samples

    normalizeArray(pointerToSamples);
    double *old = pointerToSamples;
    double extra[MAX_ARRAY_LENGTH];
    double *new = &extra[0];


    printf("printing normalized arrays:\n");
    printf("array 1:\n");
    printArray(pointerToSamples,100);
    printf("array 2:\n");
    printArray(pointerToAmp,100);
    printf("\n");

    // now its time to convolve as many times as given
    int j;
    for (j = 0; j < n; j ++)
    {
        new = convolve(old, MAX_ARRAY_LENGTH, pointerToAmp, MAX_ARRAY_LENGTH, new);

        printf("printing convolved array:\n");
        printf("convoled array:\n");
        printArray(new,100);

        normalizeArray(new);
        copyArray(new, old, MAX_ARRAY_LENGTH);

        printf("printing convolved normalized arrays:\n");
        printf("convolved aand normalized array:\n");
        printArray(new,100);

    }

    // and print out the histogram

    outputHistogram(new, MAX_ARRAY_LENGTH);
}
