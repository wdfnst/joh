#include <iostream>
#include <immintrin.h>

int has_intel_knl_features()
{
    auto const knl_features = (
        _FEATURE_AVX512F  |
        _FEATURE_AVX512ER |
        _FEATURE_AVX512PF |
        _FEATURE_AVX512CD
    );

    return _may_i_use_cpu_feature(knl_features);
}

int main()
{
    std::cout << "has intel knl features: "
        << has_intel_knl_features() << "\n";
}

