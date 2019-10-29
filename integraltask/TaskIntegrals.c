#include <stdio.h>
#include <omp.h>
#include <time.h>

#define paral
#define noparal


#ifdef paral
    #include "ParallelIntegral.h"
#endif 
#ifdef noparal
    #include "NoParallelIntegral.h"
#endif


double func(double x, double y)
{
    return 2*x + y;
}




int main(int argc, char** argv)
{
    printf("=========================\n\n");
    double summ = 0;

    time_t start, end;
    double elapsed;

    #ifdef paral       
        time(&start);
        #pragma omp parallel
        {
            summ += r_double_integral_parallel(&func, 2, 0, 3, 2, 30000, 30000);
        }
        time(&end);
        elapsed = difftime(end, start);
        printf("integral: %.9f\n", summ);
        printf("its take: %.9f sec\n\n", elapsed);    
        printf("=========================\n\n");
    #endif
    
    


    #ifdef noparal
        summ = 0;
        time(&start);
        summ += r_double_integral(&func, 2, 0, 3, 2, 30000, 30000);
        time(&end);
        elapsed = difftime(end, start);
        printf("integral: %.9f\n", summ);
        printf("its take: %.9f sec\n\n", elapsed);
        printf("=========================\n\n");
    #endif
    

    
    return 0;
}