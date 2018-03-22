// 280 GB/s
#include <iostream>
#include <omp.h>
#include "../../src/utils/timer.hh"

long long constexpr maxn = 1000;
int a[maxn] __attribute__((aligned(64)));

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++)
        ret += a[i];
    return ret;
}

int main()
{
    std::cout << sizeof(a[0]) << " " << alignof(a[0]) << "\n";
    long long rep = 1000;
    long long memory = maxn * 64 * rep;
    for (int i = 0; i < maxn; i++)
        a[i] = i;

    omp_set_num_threads(120);
    auto sum = 0;

    icesp::timer tim;
    tim.start();
    for (auto i = 0; i < rep; i++)
        sum += calc();
    tim.stop();

    std::cout << sum << "\n";
    std::cout << tim.elapsed_seconds() << "\n";
    std::cout << memory / tim.elapsed_seconds() / 1024. / 1024. / 1024. << "\n";
}

