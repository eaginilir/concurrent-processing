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
        double total_time_plain = 0.0, total_time_optimized = 0.0,total_unroll = 0.0;

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

            // auto time_1 = high_resolution_clock::now();

            //平凡算法
            vector<int> sum(n, 0);
            // for (int i = 0; i < n; ++i)
            // {
            //     for (int j = 0; j < n; ++j)
            //     {
            //         sum[i] += matrix[j][i] * alpha[j];
            //     }
            // }

            // auto time_2 = high_resolution_clock::now();
            // fill(sum.begin(), sum.end(), 0);

            //优化算法
            // auto time_3 = high_resolution_clock::now();
            // for (int j = 0; j < n; ++j)
            // {
            //     for (int i = 0; i < n; ++i)
            //     {
            //         sum[i] += matrix[j][i] * alpha[j];
            //     }
            // }
            // auto time_4 = high_resolution_clock::now();
            
            
            //unroll算法
            fill(sum.begin(), sum.end(), 0);
            auto time_5 = high_resolution_clock::now();
            for (int j = 0; j < n; ++j)
            {
                int a_j = alpha[j];
                for (int i = 0; i + 3 < n; i += 4)
                {
                    sum[i] += matrix[j][i] * a_j;
                    sum[i + 1] += matrix[j][i + 1] * a_j;
                    sum[i + 2] += matrix[j][i + 2] * a_j;
                    sum[i + 3] += matrix[j][i + 3] * a_j;
                }
                for (int i = (n / 4) * 4; i < n; ++i)
                {
                    sum[i] += matrix[j][i] * a_j;
                }
            }
            auto time_6 = high_resolution_clock::now();

            // double time_plain = duration<double>(time_2 - time_1).count();
            // double time_optimized = duration<double>(time_4 - time_3).count();
            double time_unroll = duration<double>(time_6 - time_5).count();

            // total_time_plain += time_plain;
            // total_time_optimized += time_optimized;
            total_unroll += time_unroll;
        }

        // double avg_time_plain = total_time_plain / num_tests;
        // double avg_time_optimized = total_time_optimized / num_tests;
        double avg_time_unroll = total_unroll / num_tests;

        // printf("%-10d | %-20.10f | %-20.10f\n", n, avg_time_plain, avg_time_optimized);
        printf("%-10d | %-20.10f \n", n, avg_time_unroll);
    }

    return 0;
}
