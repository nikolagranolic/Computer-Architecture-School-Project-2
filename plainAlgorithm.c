#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define MATRIX_DIM 4096
#define MATRIX_SIZE (MATRIX_DIM * MATRIX_DIM)
int mA[MATRIX_SIZE] = {0};
int mB[MATRIX_SIZE] = {0};
int mC[MATRIX_SIZE] = {0};

int load_matrices(char *argv[])
{
    FILE *fpA;
    FILE *fpB;

    fpA = fopen(argv[1], "r");
    fpB = fopen(argv[2], "r");

    if ((fpA == NULL) || (fpB == NULL))
    {
        printf("Error opening necessary files.");
        return -1;
    }

    int successA = 0;
    int successB = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        successA = fscanf(fpA, "%d", &mA[i]);
        successB = fscanf(fpB, "%d", &mB[i]);
    }

    fclose(fpA);
    fclose(fpB);

    return 0;
}

double meanSquaredErrorCM()
{
    long int difference, differenceSquared;
    double sumOfSquaredDifferences = 0;
    for (int j = 0; j < MATRIX_DIM; j++)
    {
        for (int i = 0; i < MATRIX_DIM; i++)
        {
            difference = mA[i * MATRIX_DIM + j] - mB[i * MATRIX_DIM + j];
            differenceSquared = pow(difference, 2);
            sumOfSquaredDifferences += differenceSquared;
        }
    }

    double result = sumOfSquaredDifferences / pow(MATRIX_DIM, 2);

    return result;
}

// double meanSquaredErrorCH()
// {
//     long int difference, differenceSquared;
//     double sumOfSquaredDifferences = 0;
//     for (int i = 0; i < MATRIX_DIM; i++)
//     {
//         for (int j = 0; j < MATRIX_DIM; j++)
//         {
//             difference = mA[i * MATRIX_DIM + j] - mB[i * MATRIX_DIM + j];
//             differenceSquared = pow(difference, 2);
//             sumOfSquaredDifferences += differenceSquared;
//         }
//     }

//     double result = sumOfSquaredDifferences / pow(MATRIX_DIM, 2);

//     return result;
// }


int main(int argc, char *argv[])
{
    clock_t start, end, startexecCM, endCM, startexecCH, endCH;
    double execution_time, calculation_timeCM, calculation_timeCH;
    start = clock();
    if (load_matrices(argv) == -1)
    {
        return -1;
    }
    
    // startexecCH = clock();
    // double mseCH = meanSquaredErrorCH();
    // endCH = clock();
    startexecCM = clock();
    double mseCM = meanSquaredErrorCM();
    endCM = clock();

    end = clock();

    calculation_timeCM = ((double)(endCM - startexecCM)) / CLOCKS_PER_SEC;
    // calculation_timeCH = ((double)(endCH - startexecCH)) / CLOCKS_PER_SEC;
    execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Mean squared error(CM): %.2lf \nCalculation time(CM): %lf\nExecution time: %lf",
    mseCM, calculation_timeCM, execution_time);
    
    return 0;
}