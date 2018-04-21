#include <iostream>
#include <omp.h>
#include <iomanip>
#include "../../../src/utils/timer.hh"
struct t64 {
    int a[16];
} __attribute__((aligned(64)));
long long constexpr maxn = 1'000'000;
t64 a[maxn] __attribute__((aligned(64)));
int calc() {
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
    long long memory = maxn * sizeof(a[0]);
    omp_set_num_threads(num_thread);
    icesp::timer tim;
    tim.start();
    calc();
    tim.stop();
    std::cout << num_thread << " " << std::setw(10) <<  memory /
        tim.elapsed_seconds() / 1024.  / 1024. / 1024.  << "    \n";
}

int main()
{
    for (int i = 0; i < maxn; i++) for (int j=0; j<16; j++) a[i].a[j] = i;
    auto sum = 0; for (auto i = 0; i < 100; i++) sum += calc() * i;
    std::cout << "   " << " bandwidth    \n";
    outer_cal<120 + 0 * 10>();
}

