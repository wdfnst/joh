// 217 GB/s with    alignment for random = 100'000
// 60  GB/s without alignment for random = 100'000
// 150 GB/s with    alignment for random = 1'000'000
// 9   GB/s without alignment for random = 1'000'000
#include <iostream>
#include <algorithm>
#include <random>
#include <omp.h>
#include "../../src/utils/timer.hh"

struct t64
{
    int a;
// } __attribute__((aligned(64)));
};

long long constexpr maxn = 1'000'000;
// int a[maxn] __attribute__((aligned(64)));
int a[maxn];
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

void random_swap(int tot)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxn - 1);
    for (int i = 0; i < tot; i++) {
        auto id1 = dis(gen);
        auto id2 = dis(gen);
        std::swap(rank[id1], rank[id2]);
    }
}

int main()
{
    long long rep = 10000;
    long long memory = maxn * sizeof(t64) * rep;
    for (int i = 0; i < maxn; i++)
        a[i] = b[i].a = rank[i] = i;

    random_swap(1'000'000);
    // for (int i = 0; i < 100; i++)
    //     std::cout << rank[i] << " " << " ";
    // std::cout << "\n";

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
}

