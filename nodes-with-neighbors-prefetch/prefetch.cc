// 64 GB/s without prefetch
// 0.27 Billion nodes/s
//
// 116 GB/s with T0 prefetch
// 0.49 Billion nodes/s
//
// 124 GB/s with T1 prefetch
// 0.52 Billion nodes/s
//
// 125 GB/s with T2 prefetch
// 0.52 Billion nodes/s
//
// 115 GB/s with NTA prefetch (non-temporal access)
// 0.48 Billion nodes/s

#include <iostream>
#include <random>
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
    int a[12];
    int next[4];
} __attribute__((aligned(64)));

long long constexpr maxn = 1'000'000;
t64 a[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++) {
        // for (auto j = 0; j < 12; j++) ret += a[i].a[j];
        // for (auto j = 0; j < 4; j++) ret += a[i].next[j];
        ret += a[i].a[0]; ret += a[i].a[1]; ret += a[i].a[2]; ret += a[i].a[3];
				ret += a[i].a[4]; ret += a[i].a[5]; ret += a[i].a[6]; ret += a[i].a[7];
				ret += a[i].a[8]; ret += a[i].a[9]; ret += a[i].a[10]; ret += a[i].a[11];
        ret += a[a[i].next[0]].a[0]; ret += a[a[i].next[0]].a[1];
				ret += a[a[i].next[0]].a[2]; ret += a[a[i].next[0]].a[3];
				ret += a[a[i].next[0]].a[4]; ret += a[a[i].next[0]].a[5];
				ret += a[a[i].next[0]].a[6]; ret += a[a[i].next[0]].a[7];
				ret += a[a[i].next[0]].a[8]; ret += a[a[i].next[0]].a[9];
				ret += a[a[i].next[0]].a[10]; ret += a[a[i].next[0]].a[11];
        ret += a[a[i].next[0]].next[0]; ret += a[a[i].next[0]].next[1];
				ret += a[a[i].next[0]].next[2]; ret += a[a[i].next[0]].next[3];

        ret += a[a[i].next[1]].a[0]; ret += a[a[i].next[1]].a[1];
				ret += a[a[i].next[1]].a[2]; ret += a[a[i].next[1]].a[3];
				ret += a[a[i].next[1]].a[4]; ret += a[a[i].next[1]].a[5];
				ret += a[a[i].next[1]].a[6]; ret += a[a[i].next[1]].a[7];
				ret += a[a[i].next[1]].a[8]; ret += a[a[i].next[1]].a[9];
				ret += a[a[i].next[1]].a[10]; ret += a[a[i].next[1]].a[11];
        ret += a[a[i].next[1]].next[0]; ret += a[a[i].next[1]].next[1];
				ret += a[a[i].next[1]].next[2]; ret += a[a[i].next[1]].next[3];

        ret += a[a[i].next[2]].a[0]; ret += a[a[i].next[2]].a[1];
				ret += a[a[i].next[2]].a[2]; ret += a[a[i].next[2]].a[3];
				ret += a[a[i].next[2]].a[4]; ret += a[a[i].next[2]].a[5];
				ret += a[a[i].next[2]].a[6]; ret += a[a[i].next[2]].a[7];
				ret += a[a[i].next[2]].a[8]; ret += a[a[i].next[2]].a[9];
				ret += a[a[i].next[2]].a[10]; ret += a[a[i].next[2]].a[11];
        ret += a[a[i].next[2]].next[0]; ret += a[a[i].next[2]].next[1];
				ret += a[a[i].next[2]].next[2]; ret += a[a[i].next[2]].next[3];

        ret += a[a[i].next[3]].a[0]; ret += a[a[i].next[3]].a[1];
				ret += a[a[i].next[3]].a[2]; ret += a[a[i].next[3]].a[3];
				ret += a[a[i].next[3]].a[4]; ret += a[a[i].next[3]].a[5];
				ret += a[a[i].next[3]].a[6]; ret += a[a[i].next[3]].a[7];
				ret += a[a[i].next[3]].a[8]; ret += a[a[i].next[3]].a[9];
				ret += a[a[i].next[3]].a[10]; ret += a[a[i].next[3]].a[11];
        ret += a[a[i].next[3]].next[0]; ret += a[a[i].next[3]].next[1];
				ret += a[a[i].next[3]].next[2]; ret += a[a[i].next[3]].next[3];

        // _MM_HINT_T0, _MM_HINT_T1, _MM_HINT_T2, _MM_HINT_NTA
        // _mm_prefetch((const char*)(a[i + 5].next), _MM_HINT_T1);
				/*
        _mm_prefetch((const char*)(a + a[i + 5].next[0]), _MM_HINT_NTA);
        _mm_prefetch((const char*)(a + a[i + 5].next[1]), _MM_HINT_NTA);
        _mm_prefetch((const char*)(a + a[i + 5].next[2]), _MM_HINT_NTA);
        _mm_prefetch((const char*)(a + a[i + 5].next[3]), _MM_HINT_NTA);
				*/
    }
    return ret;
}

int main()
{
    std::cout << sizeof(t64) << " " << alignof(t64) << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxn - 1);

    // long long rep = 10000;
    // long long memory = maxn * sizeof(t64) * 4 * rep;
    long long rep = 1;
    long long memory = maxn * sizeof(t64) * rep;
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < 12; j++) a[i].a[j] = j + i * i;
        for (int j = 0; j < 4; j++) a[i].next[j] = dis(gen);
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

