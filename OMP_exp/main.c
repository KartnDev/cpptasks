#include <stdio.h>
#include <omp.h>
#include <math.h>

#define STEPS 17

double exp_imp(double value)
{
    double iter_val = 1; // x^0 / 0!

    double sum = iter_val;

    for(int i = 1; i < STEPS; i++)
    {
        iter_val *= value / i;
        sum += iter_val;
    }
    return sum;
}

double function(double value)
{
    return sqrt(value)/exp_imp(value);
}

double compute_interval(double lower, double upper)
{
    double result = 0;

    for (int thread_num = 0; thread_num < omp_get_num_threads(); ++thread_num)
    {
        if (omp_get_thread_num() == thread_num)
        {
            for (double i =  (thread_num-1) * upper/4 + lower + 0.1; i < thread_num * upper/4; i += 0.1)
            {
                result += function(i) - function(i - 0.1);
            }
        }
    }

    return result;
}


int main()
{
    // Interval from 0.4 to 1.2
    double result;
#pragma omp parallel
    {
        result = compute_interval(0.4, 1.2);
    }
    printf("%f | %f", result, sqrt(1.2)/exp(1.2) - sqrt(0.4)/exp(0.4));

    return 0;
}