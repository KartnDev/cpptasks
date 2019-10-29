#include <stdio.h>
#include <omp.h>
#include <time.h>

#define PLINE "========================================\n"
#define LINE printf("========================================\n\n");
#define noparal
#define paral
#define iters_double 30000
#define iters_triple 1000



#ifdef paral
    #include "ParallelIntegral.h"
#endif 
#ifdef noparal
    #include "NoParallelIntegral.h"
#endif


double func_double(double x, double y)
{
    return 2*x + y;
}

double func_triple(double x, double y, double z)
{
    return 2*x + y + z;
}


int main(int argc, char** argv)
{
    LINE
    double summ = 0;

    time_t start, end;
    double elapsed;

    #ifdef paral       
        time(&start);
        #pragma omp parallel
        {
            summ += r_double_integral_parallel(&func_double, 2, 0, 3, 2, iters_double, iters_double);
        }
        time(&end);
        elapsed = difftime(end, start);
        printf("double integral: %.9f\n", summ);
        printf("parallel takes: %.9f sec\n\n", elapsed);    
        LINE
    #endif
    
    


    #ifdef noparal
        summ = 0;
        time(&start);
        summ += r_double_integral(&func_double, 2, 0, 3, 2, iters_double, iters_double);
        time(&end);
        elapsed = difftime(end, start);
        printf("double integral: %.9f\n", summ);
        printf("no parallel takes: %.9f sec\n\n", elapsed);
        LINE
    #endif
    


    printf("\nTriple integrals section\n\n\n");

    LINE




    #ifdef paral     
        summ = 0;  
        time(&start);
        #pragma omp parallel
        {
            summ += r_triple_integral_parallel(&func_triple, 3, 1, 3, 1, 3, 1, iters_triple, iters_triple, iters_triple);
        }
        time(&end);
        elapsed = difftime(end, start);
        printf("triple integral: %.9f\n", summ);
        printf("parallel takes: %.9f sec\n\n", elapsed);    
        LINE
    #endif




    #ifdef noparal
        summ = 0;
        time(&start);
        summ += r_triple_integral(&func_triple, 3, 1, 3, 1, 3, 1, iters_triple, iters_triple, iters_triple);
        time(&end);
        elapsed = difftime(end, start);
        printf("triple integral: %.9f\n", summ);
        printf("no parallel takes: %.9f sec\n\n", elapsed);
        LINE
    #endif


    
    return 0;
}