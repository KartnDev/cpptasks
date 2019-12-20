    #include <stdio.h>
    #include <stdlib.h>
    #include "mpi.h"

    //----------------- Эта функция считает значение функции 5*X^2*Y+2*Y^3
    float Func ( float X , float Y )
    {
    return ( 5*X*X*Y-2*Y*Y*Y );
    }
    //------- Эта функция возвращает случайное число в диапозоне от 0 до 1 
    double GetRandom ()
    {
        return (double) rand ()/RAND_MAX;
    }
    //----------------- Эта функция считает интеграл --------------------
    float DoubleIntegrall ( int N , // Количество отрезков интегрирования
    float AX , float BX ,// Интервал откуда бер╦м случайные значения для X
    float AY , float BY )// Интервал откуда бер╦м случайные значения для Y
    {
    float HX = BX-AX , HY = BY-AY ,x, y, f = 0;
    int i;
    for ( i=0; i<N; i++ )
    {
    x = (float) ( GetRandom ()*HX + AX );
    y = (float) ( GetRandom ()*HY + AY );
    f =+ Func ( x , y );
    }
    return ( HX*HY*f/N );
    }
    //------------------- MAIN -------------------------------
    int main(int argc, char *argv[])
    {
    int My_Rank;     /* ранг текущего процесса */
    int NumProcs;    /* общее число процессов */
    double AX , AY;  /* левый конец интервала */
    double BX , BY;  /* правый конец интервала */
    int N;           /* число точек разбиения */
    double LenX; /*LenY;  /* длина отрезка интегрирования для текущего процесса*/
    double Local_AX , Local_AY;/* левый конец интервала для текущего процесса */
    double Local_BX , Local_BY; /* правый конец интервала для текущего процесса */
    int Local_N;     /* число точек разбиения для текущего процесса */
    double Local_Res;/* значение интеграла в текущем процессе */
    double Result;   /* результат интегрирования */
    double WTime;    /* время работы программы */

    /* Инициализация */
    srand ( ( unsigned ) time ( NULL ) );
    /* Начать работу с MPI */
    MPI_Init(&argc, &argv);
    /* Получить номер текущего процесса в группе всех процессов */
    MPI_Comm_rank(MPI_COMM_WORLD, &My_Rank);
    /* Получить общее количество запущенных процессов */
    MPI_Comm_size(MPI_COMM_WORLD, &NumProcs);
    /* Получить данные */
    if (My_Rank == 0)
    {
        printf("Введите начальное значение X: ");
        scanf("%lf", &AX);
        printf("Введите конечное значение X: ");
        scanf("%lf", &BX);

    printf("Введите начальное значение Y: ");
        scanf("%lf", &AY);
        printf("Введите конечное значение Y: ");
        scanf("%lf", &BY);

    printf("Введите количество случайных значений : ");
        scanf("%d", &N);
    }
    /* Рассылаем данные из процесса 0 остальным */
    MPI_Bcast(&AX, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&BX, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    MPI_Bcast(&AY, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&BY, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /* Синхронизация процессов */
    MPI_Barrier(MPI_COMM_WORLD);
    /* Запускаем таймер */
    WTime = MPI_Wtime();
    /* Вычисляем отрезок интегрирования для текущего процесса */
    LenX = (BX-AX)/NumProcs;
    //LenY = (BY-AY)/NumProcs;

    Local_N = N/NumProcs;

    Local_AX = AX + My_Rank*LenX;
    Local_BX = Local_AX + LenX;

    Local_AY = AY; // + My_Rank*LenY;
    Local_BY = BY; //Local_AY + LenY;
    /* Вычислить интеграл на каждом из процессов */
    Local_Res = DoubleIntegrall (Local_N, Local_AX, Local_BX, Local_AY, Local_BY);
    /* Сложить все ответы и передать процессу 0 */
    MPI_Reduce(&Local_Res, &Result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    /* Синхронизация процессов */
    MPI_Barrier(MPI_COMM_WORLD);
    /* Вычисляем время работы */
    WTime = MPI_Wtime() - WTime;
    /* Напечатать ответ */
    if (My_Rank == 0)
    {
        printf("Integral X:[ %.2lf ; %.2lf ] Y:[ %.2lf ; %.2lf ] = %.8lf\n", AX, BX, AY, BY, Result);
        printf("Working time: %.2lf seconds\n", WTime);
    }
    /* Заканчиваем работу с MPI */
    MPI_Finalize();
    return 0;
    }