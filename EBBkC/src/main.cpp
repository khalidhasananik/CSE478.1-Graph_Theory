// #include <iostream>
// #include <cstdlib>
// #include <cstdio>
// #include <cstring>
// #include <ctime>
// #include <set>
// #include <algorithm>
// #include <string>
// #include <omp.h>
// #include <cassert>
// #include "set_operation.h"
// #include "def.h"
// #include "edge_oriented.h"

// using namespace std;
// int K, L;
// unsigned long long N = 0;

// int main(int argc, char **argv)
// {
//     double runtime;
//     string act(argv[1]);

//     if (act == "p")
//     { // pre-process
//         printf("Pre-process %s\n", argv[2]);
//         string src_filename(argv[2]);
//         string suffix = src_filename.substr(src_filename.find_last_of('.'));
//         if (suffix != ".edges" && suffix != ".mtx")
//             exit(0);
//         string prefix = src_filename.substr(0, src_filename.find_last_of('.'));
//         string clean_filename = prefix + ".clean";
//         clean_edges(src_filename.c_str(), clean_filename.c_str());
//         //        string index_filename = prefix + ".index";
//         //        runtime = EBBkC_t::truss_order(clean_filename.c_str(), index_filename.c_str());
//         printf("Pre-processed in %.2lf ms\n\n", runtime);
//     }

//     else if (act == "e")
//     { // EBBkC+ET
//         string src_filename(argv[2]);
//         //        string suffix = src_filename.substr(src_filename.find_last_of('.'));
//         //        if (suffix != ".index") exit(0);

//         K = atoi(argv[3]);
//         L = atoi(argv[4]);

//         runtime = EBBkC_t::list_k_clique(argv[2]);
//         printf("Number of %u-cliques: %llu\n", K, N);
//         printf("EBBkC+ET (t = %d) runtime %.2lf ms\n\n", L, runtime);
//     }

//     else if (act == "ep")
//     { // EBBkC+ET (parallel)
//         string src_filename(argv[2]);
//         //        string suffix = src_filename.substr(src_filename.find_last_of('.'));
//         //        if (suffix != ".index") exit(0);

//         K = atoi(argv[3]);
//         L = atoi(argv[4]);

//         omp_set_num_threads(atoi(argv[5]));

//         runtime = EBBkC_t::list_k_clique_parallel(argv[2]);
//         printf("Number of %u-cliques: %llu\n", K, N);
//         printf("EBBkC+ET (t = %d) runtime %.2lf ms\n\n", L, runtime);
//     }

//     else
//     {
//         printf("Wrong usage.\n");
//         exit(0);
//     }

//     return 0;
// }

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <set>
#include <algorithm>
#include <string>
#include <omp.h>
#include <cassert>
#include <chrono> // Add this header for timing
#include "set_operation.h"
#include "def.h"
#include "edge_oriented.h"

using namespace std;
using namespace std::chrono; // For easier use of chrono functions

int K, L;
unsigned long long N = 0;

int main(int argc, char **argv)
{
    double runtime, total_runtime = 0; // To store total runtime
    int runs = 2;                      // Set the number of runs
    string act(argv[1]);

    if (act == "p")
    { // pre-process
        printf("Pre-process %s\n", argv[2]);
        string src_filename(argv[2]);
        string suffix = src_filename.substr(src_filename.find_last_of('.'));
        if (suffix != ".edges" && suffix != ".mtx")
            exit(0);
        string prefix = src_filename.substr(0, src_filename.find_last_of('.'));
        string clean_filename = prefix + ".clean";
        clean_edges(src_filename.c_str(), clean_filename.c_str());
        printf("Pre-processed in %.2lf ms\n\n", runtime);
    }

    else
    {
        for (int i = 0; i < runs; ++i)
        {

            auto start = high_resolution_clock::now(); // Start timing

            string src_filename(argv[2]);
            K = atoi(argv[3]); // atoi means "ASCII to Integer"
            L = atoi(argv[4]);
            runtime = EBBkC_t::list_k_clique(argv[2]);
            printf("Number of %u-cliques: %llu\n", K, N);
            printf("EBBkC+ET (t = %d) runtime %.2lf ms\n\n", L, runtime);

            // if (act == "e")
            // { // EBBkC+ET
            //     string src_filename(argv[2]);
            //     K = atoi(argv[3]);
            //     L = atoi(argv[4]);
            //     runtime = EBBkC_t::list_k_clique(argv[2]);
            //     printf("Number of %u-cliques: %llu\n", K, N);
            //     printf("EBBkC+ET (t = %d) runtime %.2lf ms\n\n", L, runtime);
            // }

            // else if (act == "ep")
            // { // EBBkC+ET (parallel)
            //     string src_filename(argv[2]);
            //     K = atoi(argv[3]);
            //     L = atoi(argv[4]);
            //     omp_set_num_threads(atoi(argv[5]));
            //     runtime = EBBkC_t::list_k_clique_parallel(argv[2]);
            //     printf("Number of %u-cliques: %llu\n", K, N);
            //     printf("EBBkC+ET (t = %d) runtime %.2lf ms\n\n", L, runtime);
            // }

            // else
            // {
            //     printf("Wrong usage.\n");
            //     exit(0);
            // }

            auto end = high_resolution_clock::now();               // End timing
            duration<double, std::milli> run_time = end - start;   // Calculate runtime in ms
            printf("Run %d: %.2lf ms\n", i + 1, run_time.count()); // Print individual run time

            total_runtime += run_time.count(); // Add to total runtime
        }

        // Calculate and print the average runtime
        double average_runtime = total_runtime / runs;
        printf("Average runtime over %d runs: %.2lf ms\n", runs, average_runtime);
    }

    return 0;
}