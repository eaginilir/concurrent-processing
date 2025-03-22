#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main()
{
    int n;
    int num_tests = 100;
    vector<int> sizes = {10, 50, 100, 200, 300, 500, 1000, 2000, 3000, 5000, 10000};
    cout << "矩阵规模 | 测试次数 | 平凡算法总时间 (秒) | 平凡算法平均时间 (秒) | 优化算法总时间 (秒) | 优化算法平均时间 (秒)" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
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

            auto start = high_resolution_clock::now();

            //平凡算法
            vector<int> sum(n, 0);
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    sum[i] += matrix[j][i] * alpha[j];
                }
            }

            auto mid = high_resolution_clock::now();
            fill(sum.begin(), sum.end(), 0);

            //优化算法
            for (int j = 0; j < n; ++j)
            {
                for (int i = 0; i < n; ++i)
                {
                    sum[i] += matrix[j][i] * alpha[j];
                }
            }

            auto end = high_resolution_clock::now();

            double time_plain = duration<double>(mid - start).count();
            double time_optimized = duration<double>(end - mid).count();

            total_time_plain += time_plain;
            total_time_optimized += time_optimized;
        }


        double avg_time_plain = total_time_plain / num_tests;
        double avg_time_optimized = total_time_optimized / num_tests;

        printf("%-10d | %-8d | %-18.10f | %-18.10f | %-18.10f | %-18.10f\n", n, num_tests, total_time_plain, avg_time_plain, total_time_optimized, avg_time_optimized);
    }

    cout << "程序已退出。" << endl;
    return 0;
}
