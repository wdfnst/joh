// 254 GB/s with alignment
// 4.26 Billion nodes/s

#include <iostream>
#include <immintrin.h>
#include <omp.h>
#include "../../../src/utils/timer.hh"

auto constexpr KB = 1024ll;
auto constexpr MB = KB * 1024.;
auto constexpr GB = MB * 1024.;
auto constexpr K = 1000;
auto constexpr M = K * 1000;
auto constexpr B = M * 1000;

auto constexpr thread_num = 120;

struct t64
{
    int a[16];
} __attribute__((aligned(64)));

long long constexpr maxn = 1'000'000;
t64 a[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++) {
        // for (auto j = 0; j < 16; j++) ret += a[i].a[j];
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

int main()
{
    std::cout << sizeof(t64) << " " << alignof(t64) << "\n";

    long long rep = 1;
    long long memory = maxn * sizeof(t64) * rep;
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < 16; j++)
            a[i].a[j] = j + i * i;
    }

    omp_set_num_threads(thread_num);
    auto sum = 0;

    for (auto i = 0; i < 100; i++)
        sum += calc() * i;

    icesp::timer tim;
    tim.start();
    for (auto i = 0; i < rep; i++)
        sum += calc() * i;
    tim.stop();

    auto seconds = tim.elapsed_seconds();

    std::cout << sum << "\n";
    std::cout << seconds << " s\n";
    std::cout << (memory / GB) / seconds << " GB/s\n";
    std::cout << (maxn * rep / B) / seconds << " Billion nodes/s\n";
}

