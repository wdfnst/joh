// 230 GB/s with    alignment
// 100 GB/s without alignment
#include <iostream>
#include <iomanip>
#include<hbwmalloc.h>
#include <omp.h>
#include "../../../src/utils/timer.hh"

struct t64 { int a[16]; } __attribute__((aligned(64)));

long long constexpr maxn = 1 << 22;
t64 *b; //[maxn];
int *rank; //[maxn];

int calc()
{
    auto ret = 0;
#pragma omp parallel for default(shared) reduction(+: ret)
    for (auto i = 0; i < maxn; i++) {
        ret += b[rank[i]].a[0];
        ret += b[rank[i]].a[1];
//         ret += b[rank[i]].a[2];
//         ret += b[rank[i]].a[3];
//         ret += b[rank[i]].a[4];
//         ret += b[rank[i]].a[5];
//         ret += b[rank[i]].a[6];
//         ret += b[rank[i]].a[7];
//         ret += b[rank[i]].a[8];
//         ret += b[rank[i]].a[9];
//         ret += b[rank[i]].a[10];
//         ret += b[rank[i]].a[11];
//         ret += b[rank[i]].a[12];
//         ret += b[rank[i]].a[13];
//         ret += b[rank[i]].a[14];
//         ret += b[rank[i]].a[15];
		}
    return ret;
}

int main()
{
    long long rep = 10000;
    b = (t64*)hbw_malloc(maxn * sizeof(t64));
    rank = (int*)hbw_malloc(maxn * sizeof(int));
    for (int i = 0; i < maxn; i++) {
        b[i].a[0] = rank[i] = i;
        b[i].a[1] = rank[i] = i;
        b[i].a[2] = rank[i] = i;
        b[i].a[3] = rank[i] = i;
        b[i].a[4] = rank[i] = i;
        b[i].a[5] = rank[i] = i;
        b[i].a[6] = rank[i] = i;
        b[i].a[7] = rank[i] = i;
        b[i].a[8] = rank[i] = i;
        b[i].a[9] = rank[i] = i;
        b[i].a[10] = rank[i] = i;
        b[i].a[11] = rank[i] = i;
        b[i].a[12] = rank[i] = i;
        b[i].a[13] = rank[i] = i;
        b[i].a[14] = rank[i] = i;
        b[i].a[15] = rank[i] = i;
		}

    auto sum = 0;
    for (auto i = 0; i < rep; i++) sum += calc() * i;

    long long memory = maxn * sizeof(t64) + sizeof(rank);
    omp_set_num_threads(120);
    icesp::timer tim;
    tim.start();
    calc();
    tim.stop();
    std::cout << memory / 1024. / 1024. / 1024. << " GB\n";
    std::cout << 120 << " " << std::setw(10) <<  memory /
        tim.elapsed_seconds() / 1024.  / 1024. / 1024.  << "  GB/s\n";
}

