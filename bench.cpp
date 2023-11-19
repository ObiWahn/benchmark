#include <benchmark/benchmark.h>
#include <vector>

inline void escape(void* pointer) {
    asm volatile("" ::"g"(pointer) : "memory");
}
inline void clobber() {
    asm volatile("" ::: "memory");
}

static void bm_base_case(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        std::vector<int> vec;
        vec.reserve(1);
        escape(&vec);
    }
}
// Register the function as a benchmark
BENCHMARK(bm_base_case);

static void bm_advanced_case(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> vec;
        vec.reserve(1);
        escape(vec.data());
        vec.push_back(42);
        clobber();
    }
}
BENCHMARK(bm_advanced_case);
