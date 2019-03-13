#include <mpi/mpi.h>
#include <stdio.h>
#include <iostream>
/**
 * Show debug line which means end of N process
 */
#define DEBUG

using namespace std;
int main(int argc, char* argv[])
{
    int interval[1];
    double curPi[1];
    double Pi[1];
    double piE = 3.141592653589793238462643;

    int rank, size;
    double startwtime = 0.0, endwtime, sum = 0.0, x, h;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        cout << "Enter the interval: ";
        cin >> interval[0];
        startwtime = MPI_Wtime();
    }
    if (interval[0] != 0)
    {
        MPI_Bcast(interval, 1, MPI_INT, 0, MPI_COMM_WORLD);
        h = 2.0 * interval[0];
        for (int i = rank + 1; i <= interval[0]; i += size)
        {
            x = (2 * i - 1) / h;
            sum += (4.0 / (1.0 + x * x));
        }
        curPi[0] = (1.0 / interval[0]) * sum;
        MPI_Reduce(curPi, Pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
#ifdef DEBUG
        printf("Process number %i finished\n", rank);
#endif
        if (rank == 0)
        {
            endwtime = MPI_Wtime();
            printf("Time: %f\n", (endwtime - startwtime) / 1000);
            printf("Pi: %.25lf\n", Pi[0]);
            printf("Divergence: %.25lf\n", Pi[0] - piE);
            fflush(stdout);
        }
    }
    MPI_Finalize();
    return 0;
}