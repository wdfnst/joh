// 230 GB/s with    alignment
// 100 GB/s without alignment
#include <iostream>
#include <iomanip>
#include <omp.h>
#include "../../../src/utils/timer.hh"

struct t64
{
    int a;
} __attribute__((aligned(64)));
// };

long long constexpr maxn = 1'000'000;
int a[maxn] __attribute__((aligned(64)));
// int a[maxn];
t64 b[maxn];
int rank[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++)
        ret += b[rank[i]].a;
    return ret;
}

template<int num_thread>
int outer_cal() {
    long long rep = 10000;
    long long memory = maxn * sizeof(t64) * rep;
    auto sum = 0;
    omp_set_num_threads(num_thread);
    icesp::timer tim;
    tim.start();
    // #pragma omp parallel for default(shared) reduction(+: sum)
    for (auto i = 0; i < rep; i++)
            sum += calc() * i;
    tim.stop();
    std::cout << num_thread << " " << std::setw(10) <<  memory /
        tim.elapsed_seconds() / 1024.  / 1024. / 1024.  << "\n";
}


int main()
{
    long long rep = 10000;
    long long memory = maxn * sizeof(t64) * rep;
    for (int i = 0; i < maxn; i++)
        a[i] = b[i].a = rank[i] = i;

    auto sum = 0;
    for (auto i = 0; i < rep; i++)
            sum += calc() * i;
    // std::cout << "sum 1: " << sum << std::endl;
    std::cout << " " << " bandwidth\n";
		/*
    outer_cal<120 - 9 * 10>();
    outer_cal<120 - 8 * 10>();
    outer_cal<120 - 7 * 10>();
    outer_cal<120 - 6 * 10>();
    outer_cal<120 - 5 * 10>();
    outer_cal<120 - 4 * 10>();
    outer_cal<120 - 3 * 10>();
    outer_cal<120 - 2 * 10>();
    outer_cal<120 + 1 * 10>();
    outer_cal<120 + 0 * 10>();
    outer_cal<120 + 1 * 10>();
    outer_cal<120 + 2 * 10>();
    outer_cal<120 + 3 * 10>();
    outer_cal<120 + 4 * 10>();
    outer_cal<120 + 5 * 10>();
		*/
    outer_cal<120 + 6 * 10>();
    outer_cal<120 + 7 * 10>();
    outer_cal<120 + 8 * 10>();
    outer_cal<120 + 9 * 10>();
}

