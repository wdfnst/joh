// 280 GB/s
#include <iostream>
#include <omp.h>
#include "../../../src/utils/timer.hh"

long long constexpr maxn = 1'000'000;
int a[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
// #pragma omp parallel for
    for (auto i = 0; i < maxn; i++)
        ret += a[i];
    return ret;
}

int main()
{
    long long rep = 100;
    long long memory = maxn * sizeof(int) * rep;
    for (int i = 0; i < maxn; i++)
        a[i] = i*i;

    omp_set_num_threads(120);
    auto sum = 0;

    for (auto i = 0; i < 100; i++)
        sum += calc() * i;

    icesp::timer tim;
    tim.start();
#pragma omp parallel for default(shared) reduction(+: sum)
		for (auto i = 0; i < rep; i++)
				sum += calc() * i;
    tim.stop();

    std::cout << sum << "\n";
    std::cout << tim.elapsed_seconds() << "\n";
    std::cout << memory << "\n";
    std::cout << memory / tim.elapsed_seconds() / 1024. / 1024. / 1024. << " GB/s\n";
}

