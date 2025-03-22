#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main()
{
    int num_tests = 1;
    vector<int> sizes = {10000};
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < sizes.size();++i)
    {
        int n = sizes[i];
        double total_time_plain = 0.0, total_time_optimized = 0.0;

        for (int t = 0; t < num_tests; ++t)
        {
            vector<vector<int>> matrix(n, vector<int>(n));
            vector<int> alpha(n);
            for (int i = 0; i < n; ++i)
            {
                alpha[i] = i;
                for (int j = 0; j < n; ++j)
                {
                    matrix[i][j] = i + j;
                }
            }

            vector<int> sum(n, 0);
            // auto start = high_resolution_clock::now();
            // for (int i = 0; i < n; ++i)
            // {
            //     for (int j = 0; j < n; ++j)
            //     {
            //         sum[i] += matrix[j][i] * alpha[j];
            //     }
            // }


            fill(sum.begin(), sum.end(), 0);
            auto mid = high_resolution_clock::now();
            for (int j = 0; j < n; ++j)
            {
                for (int i = 0; i < n; ++i)
                {
                    sum[i] += matrix[j][i] * alpha[j];
                }
            }

            auto end = high_resolution_clock::now();

            // double time_plain = duration<double>(mid - start).count();
            double time_optimized = duration<double>(end - mid).count();

            // total_time_plain += time_plain;
            total_time_optimized += time_optimized;
        }

        // double avg_time_plain = total_time_plain / num_tests;
        double avg_time_optimized = total_time_optimized / num_tests;

        // printf("%-10d | %-20.10f | %-20.10f\n", n, avg_time_plain, avg_time_optimized);
        printf("%-10d | %-20.10f \n", n, avg_time_optimized);
    }

    return 0;
}
