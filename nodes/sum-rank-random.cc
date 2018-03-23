// 217 GB/s with    alignment for random = 100'000
// 60  GB/s without alignment for random = 100'000
// 150 GB/s with    alignment for random = 1'000'000
// 9   GB/s without alignment for random = 1'000'000
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <omp.h>
#include "../../../src/utils/timer.hh"

struct t64
{
    int a[16];
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
    for (auto i = 0; i < maxn; i++) {
        ret += b[rank[i]].a[0];
        ret += b[rank[i]].a[1];
        ret += b[rank[i]].a[2];
        ret += b[rank[i]].a[3];
        ret += b[rank[i]].a[4];
        ret += b[rank[i]].a[5];
        ret += b[rank[i]].a[6];
        ret += b[rank[i]].a[7];
        ret += b[rank[i]].a[8];
        ret += b[rank[i]].a[9];
        ret += b[rank[i]].a[10];
        ret += b[rank[i]].a[11];
        ret += b[rank[i]].a[12];
        ret += b[rank[i]].a[13];
        ret += b[rank[i]].a[14];
        ret += b[rank[i]].a[15];
		}
    return ret;
}

template<unsigned int num_thread>
void outer_cal() {
    long long rep = 1;
		// IMP: 64 --> sizeof(a[0])
    long long memory = maxn * sizeof(b[0]) * rep + sizeof(rank);
    auto sum = 0;
    omp_set_num_threads(num_thread);
    icesp::timer tim;
    tim.start();
    for (auto i = 0; i < rep; i++)
				sum += calc();
    tim.stop();
    std::cout << num_thread << " " << std::setw(10) <<  memory /
        tim.elapsed_seconds() / 1024.  / 1024. / 1024.  << "    \n";
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
    long long rep = 1;
    long long memory = maxn * sizeof(t64) * rep;
    for (int i = 0; i < maxn; i++) {
        a[i] = b[i].a[0] = rank[i] = i;
        a[i] = b[i].a[1] = rank[i] = i;
        a[i] = b[i].a[2] = rank[i] = i;
        a[i] = b[i].a[3] = rank[i] = i;
        a[i] = b[i].a[4] = rank[i] = i;
        a[i] = b[i].a[5] = rank[i] = i;
        a[i] = b[i].a[6] = rank[i] = i;
        a[i] = b[i].a[7] = rank[i] = i;
        a[i] = b[i].a[8] = rank[i] = i;
        a[i] = b[i].a[9] = rank[i] = i;
        a[i] = b[i].a[10] = rank[i] = i;
        a[i] = b[i].a[11] = rank[i] = i;
        a[i] = b[i].a[12] = rank[i] = i;
        a[i] = b[i].a[13] = rank[i] = i;
        a[i] = b[i].a[14] = rank[i] = i;
        a[i] = b[i].a[15] = rank[i] = i;
		}

    // random_swap(1'000'000);
    random_swap(1000'000);
    // for (int i = 0; i < 100; i++)
    //     std::cout << rank[i] << " " << " ";
    // std::cout << "\n";

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
    outer_cal<120 + 10 * 10>();
    outer_cal<120 + 11 * 10>();
    outer_cal<120 + 12 * 10>();
    outer_cal<120 + 13 * 10>();
    outer_cal<120 + 14 * 10>();
    outer_cal<120 + 15 * 10>();
    outer_cal<120 + 16 * 10>();
}

