#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>
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

// double meanSquaredErrorCM()
// {
//     long int difference, differenceSquared;
//     double sumOfSquaredDifferences = 0;
// #pragma omp parallel for reduction(+ \
//                                    : sumOfSquaredDifferences) private(difference, differenceSquared)
//     for (int j = 0; j < MATRIX_DIM; j++)
//     {
//         for (int i = 0; i < MATRIX_DIM; i++)
//         {
//             difference = mA[i * MATRIX_DIM + j] - mB[i * MATRIX_DIM + j];
//             differenceSquared = pow(difference, 2);
//             sumOfSquaredDifferences += differenceSquared;
//         }
//     }

//     double result = sumOfSquaredDifferences / pow(MATRIX_DIM, 2);

//     return result;
// }

double meanSquaredErrorCH()
{
    long int difference, differenceSquared;
    double sumOfSquaredDifferences = 0;
#pragma omp parallel for reduction(+ \
                                   : sumOfSquaredDifferences) private(difference, differenceSquared)
    for (int i = 0; i < MATRIX_DIM; i++)
    {
        for (int j = 0; j < MATRIX_DIM; j++)
        {
            difference = mA[i * MATRIX_DIM + j] - mB[i * MATRIX_DIM + j];
            differenceSquared = pow(difference, 2);
            sumOfSquaredDifferences += differenceSquared;
        }
    }

    double result = sumOfSquaredDifferences / pow(MATRIX_DIM, 2);

    return result;
}

int main(int argc, char *argv[])
{
    double start, end, startexecCM, endCM, startexecCH, endCH;
    double execution_time, calculation_timeCM, calculation_timeCH;
    start = omp_get_wtime();
    if (load_matrices(argv) == -1)
    {
        return -1;
    }

    startexecCH = omp_get_wtime();
    double mseCH = meanSquaredErrorCH();
    endCH = omp_get_wtime();

    startexecCM = omp_get_wtime();
    // double mseCM = meanSquaredErrorCM();
    endCM = omp_get_wtime();
    end = omp_get_wtime();

    calculation_timeCM = endCM - startexecCM;
    calculation_timeCH = endCH - startexecCH;
    execution_time = endCM - start;

    printf("Mean squared error(CH): %.2lf\nCalculation time(CH): %lf\nExecution time:%lf",
           mseCH, calculation_timeCH, execution_time);
}