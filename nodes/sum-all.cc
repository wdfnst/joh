// 280 GB/s
#include <iostream>
#include <omp.h>
#include <iomanip>
#include "../../../src/utils/timer.hh"

struct t64
{
    int a[16];
} __attribute__((aligned(64)));
// };

long long constexpr maxn = 1'000'000;
// int a[maxn] __attribute__((aligned(64)));
t64 a[maxn] __attribute__((aligned(64)));

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++) {
        ret += a[i].a[0];
        ret += a[i].a[1];
        ret += a[i].a[2];
        ret += a[i].a[3];
        ret += a[i].a[4];
        ret += a[i].a[5];
        ret += a[i].a[6];
        ret += a[i].a[7];
        ret += a[i].a[8];
        ret += a[i].a[9];
        ret += a[i].a[10];
        ret += a[i].a[11];
        ret += a[i].a[12];
        ret += a[i].a[13];
        ret += a[i].a[14];
        ret += a[i].a[15];
		}
    return ret;
}

template<unsigned int num_thread>
void outer_cal() {
    long long rep = 1;
		// IMP: 64 --> sizeof(a[0])
    long long memory = maxn * sizeof(a[0]) * rep;
    auto sum = 0;
    omp_set_num_threads(num_thread);
    icesp::timer tim;
    tim.start();
// #pragma omp parallel for default(shared) reduction(+: sum)
    for (auto i = 0; i < rep; i++)
				sum += calc();
    tim.stop();
    std::cout << num_thread << " " << std::setw(10) <<  memory /
        tim.elapsed_seconds() / 1024.  / 1024. / 1024.  << "    \n";
}

int main()
{
    for (int i = 0; i < maxn; i++) {
        a[i].a[0] = i;
        a[i].a[1] = i;
        a[i].a[2] = i;
        a[i].a[3] = i;
        a[i].a[4] = i;
        a[i].a[5] = i;
        a[i].a[6] = i;
        a[i].a[7] = i;
        a[i].a[8] = i;
        a[i].a[9] = i;
        a[i].a[10] = i;
        a[i].a[11] = i;
        a[i].a[12] = i;
        a[i].a[13] = i;
        a[i].a[14] = i;
        a[i].a[15] = i;
		}

    auto sum = 0;

    for (auto i = 0; i < 100; i++)
        sum += calc() * i;

    std::cout << "   " << " bandwidth    \n";
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
    outer_cal<120 + 6 * 10>();
    outer_cal<120 + 7 * 10>();
    outer_cal<120 + 8 * 10>();
    outer_cal<120 + 9 * 10>();
}

