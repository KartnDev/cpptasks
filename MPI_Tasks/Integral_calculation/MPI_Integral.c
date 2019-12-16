#include <stdio.h>
#include <math.h>
#include <mpi.h>

/*
double r_double_integral(int argc, char** argv,
                         double (*lambda)(double, double), 
                         double first_upper, double first_lower, 
                         double second_upper, double second_lower, 
                         int partition_x, int partition_y, int time_dif)
{
    int rank, size, error, i;


    double _side_first = (first_upper - first_lower)/(double)partition_x; // side of X condition (partition side)
    double _side_second = (second_upper - second_lower)/(double)partition_y; // same as Y

    double integral_sum = 0, result=0;
    double corrent_x, corrent_y;

    double begin_time=0.0, end_time=0.0;
    time_dif = 0;


    begin_time = MPI_Wtime();

    error=MPI_Init (&argc, &argv);
    
    //Get process ID
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    //Get processes Number
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    //Synchronize all processes and get the begin time
    MPI_Barrier(MPI_COMM_WORLD);


    for(int i = rank; i < partition_x * size; i+=size)
    {
        for(int j = 0; j < partition_y; j++)
        {
            corrent_x = first_lower + _side_first/2 + i * _side_first;
            corrent_y = second_lower + _side_second/2 + j * _side_second;
            integral_sum += _side_first * _side_second * lambda(corrent_x, corrent_y);
        }   
    }
    end_time = MPI_Wtime();

    time_dif = end_time-begin_time;

    //Sum up all results
    MPI_Reduce(&result, &integral_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank==0)
    {
        printf("Integral = %.9f\n", integral_sum);
    }


    error=MPI_Finalize();

    return integral_sum;
}


*/
double func(double x, double y)
{
    return 2*x + y;
}



int main (int argc, char** argv)
{
    int dif_time = 0;
    //double value = r_double_integral(&argc, &argv, &func, 2, 0, 3, 2, 30000, 30000, &dif_time);

    int rank, size, error, i;


    double first_upper = 2;
    double first_lower = 0;
    double second_upper = 3;
    double second_lower = 2;
    int partition_x = 30000;
    int partition_y = 30000;
    double time_dif = 0;

    double _side_first = (first_upper - first_lower)/(double)partition_x; // side of X condition (partition side)
    double _side_second = (second_upper - second_lower)/(double)partition_y; // same as Y

    double integral_sum = 0, result=0;
    double corrent_x, corrent_y;

    double begin_time=0.0, end_time=0.0;
    time_dif = 0;


    begin_time = MPI_Wtime();

    error=MPI_Init (&argc, &argv);
    
    //Get process ID
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    //Get processes Number
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    //Synchronize all processes and get the begin time
    MPI_Barrier(MPI_COMM_WORLD);


    for(int i = rank; i < partition_x * size; i+=size)
    {
        for(int j = 0; j < partition_y; j++)
        {
            corrent_x = first_lower + _side_first/2 + i * _side_first;
            corrent_y = second_lower + _side_second/2 + j * _side_second;
            integral_sum += _side_first * _side_second * func(corrent_x, corrent_y);
        }   
    }
    end_time = MPI_Wtime();

    time_dif = end_time-begin_time;

    //Sum up all results
    MPI_Reduce(&result, &integral_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank==0)
    {
        printf("Integral = %.9f\n", integral_sum);
    }


    error=MPI_Finalize();





    //printf("Integral = %.9f\n", value);

    return 0;

}