// 252 GB/s with    alignment
// 198 GB/s without alignment
#include <iostream>
#include <immintrin.h>
#include <omp.h>
#include "../../../src/utils/timer.hh"

struct t64
{
    int a;
} __attribute__((aligned(64)));

long long constexpr maxn = 1'000'000;
// int a[maxn] __attribute__((aligned(64)));
// int * a;
// int a[maxn];
__m512i a[maxn];
t64 b[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++)
        // ret += b[i].a;
        ret += a[i];
    return ret;
}

int main()
{
    std::cout << sizeof(__m512) << " " << alignof(__m512) << "\n";
// #ifdef __MIC__
//     std::cerr << "FUkkkkkkkkkkkkkkkkkkkkCK\n";
// #endif

    long long rep = 10000;
    long long memory = maxn * sizeof(t64) * rep;
    // a = (int*)_mm_malloc(maxn * sizeof(int), 64);
    for (int i = 0; i < maxn; i++)
        b[i].a = i;
    for (int i = 0; i < maxn; i++)
        a[i] = i;

    omp_set_num_threads(120);
    auto sum = 0;

    for (auto i = 0; i < 100; i++)
        sum += calc() * i;

    icesp::timer tim;
    tim.start();
    for (auto i = 0; i < rep; i++)
        sum += calc() * i;
    tim.stop();

    std::cout << sum << "\n";
    std::cout << tim.elapsed_seconds() << "\n";
    std::cout << memory / tim.elapsed_seconds() / 1024. / 1024. / 1024. << " GB/s\n";
    // _mm_free(a);
}

