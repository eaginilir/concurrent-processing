#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void sum_re(int n, vector<int>& a);

int main()
{
    int num_tests = 100;
    vector<int> sizes = {10, 50, 100, 200, 300, 500, 1000, 2000, 3000, 5000, 10000, 100000, 1000000};
    // vector<int> sizes = {1000000};

    cout << "数组规模 | 测试次数 | 平凡算法总时间 (秒) | 平凡算法平均时间 (秒) | 优化算法1总时间 (秒) | 优化算法1平均时间 (秒) | 优化算法2总时间 (秒) | 优化算法2平均时间 (秒) | 优化算法3总时间 (秒) | 优化算法3平均时间 (秒)" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int n : sizes)
    {
        double total_time_plain = 0.0, total_time_opt1 = 0.0, total_time_opt2 = 0.0, total_time_opt3 = 0.0;

        for (int t = 0; t < num_tests; ++t)
        {
            vector<int> a(n);
            for (int i = 0; i < n; ++i)
            {
                a[i] = 2 * i;
            }

            int sum = 0;
            auto start_1 = high_resolution_clock::now();
            for (int i = 0; i < n; ++i)
            {
                sum += a[i];
            }
            auto end_1 = high_resolution_clock::now();

            sum = 0;
            int sum_1 = 0, sum_2 = 0;
            auto start_2 = high_resolution_clock::now();
            for (int i = 0; i < n; i += 2)
            {
                sum_1 += a[i];
                if (i + 1 < n)
                    sum_2 += a[i + 1];
            }
            sum = sum_1 + sum_2;
            auto end_2 = high_resolution_clock::now();

            vector<int> b = a;
            auto start_3 = high_resolution_clock::now();
            sum_re(n, b);
            auto end_3 = high_resolution_clock::now();

            vector<int> c = a;
            auto start_4 = high_resolution_clock::now();
            for (int m = n; m > 1; m /= 2)
            {
                for (int i = 0; i < m / 2; ++i)
                {
                    c[i] = c[i * 2] + c[i * 2 + 1];
                }
            }
            auto end_4 = high_resolution_clock::now();

            total_time_plain += duration<double>(end_1 - start_1).count();
            total_time_opt1 += duration<double>(end_2 - start_2).count();
            total_time_opt2 += duration<double>(end_3 - start_3).count();
            total_time_opt3 += duration<double>(end_4 - start_4).count();
        }

        double avg_time_plain = total_time_plain / num_tests;
        double avg_time_opt1 = total_time_opt1 / num_tests;
        double avg_time_opt2 = total_time_opt2 / num_tests;
        double avg_time_opt3 = total_time_opt3 / num_tests;

        printf("%-10d | %-8d | %-18.10f | %-18.10f | %-18.10f | %-18.10f | %-18.10f | %-18.10f | %-18.10f | %-18.10f\n",n, num_tests, total_time_plain, avg_time_plain, total_time_opt1, avg_time_opt1, total_time_opt2, avg_time_opt2, total_time_opt3, avg_time_opt3);
        // printf("%-10d | %-8d | %-18.10f | %-18.10f | \n",n, num_tests, total_time_opt3, avg_time_opt3);
        
    }

    cout << "程序已退出。" << endl;
    return 0;
}

void sum_re(int n, vector<int>& a)
{
    if (n == 1)
    {
        return;
    }
    else
    {
        for (int i = 0; i < n / 2; ++i)
        {
            a[i] += a[n - i - 1];
        }
        n = n / 2;
        sum_re(n, a);
    }
}