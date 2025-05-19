#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char **argv){
    int n, *arr = NULL;
    printf("Enter size of array: ");
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    printf("Enter array elements: ");
    for(int i = 0; i<n; ++i)
        scanf("%d",  &arr[i]);
    clock_t startTime, endTime;
    double totalTime;
    startTime  = clock();

    double sum = 0.0, mean, variance = 0.0, deviation;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i<n; ++i){
        sum+=arr[i];
    } mean = sum/n;

    #pragma omp parallel for reduction(+:variance)
    for(int i = 0; i<n; ++i){
        variance += (arr[i] - mean) * (arr[i] - mean);
    } variance /= n;
    deviation = sqrt(variance);

    endTime = clock();
    totalTime = (double)(endTime - startTime) / 1e9;
    printf("Standard deviation: %.9f\nCalculation time: %.9f seconds\n", deviation, totalTime);

    free(arr);
}
