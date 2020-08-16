<p align="center">
    <h1>Regex Bench</h1>
</p>
<p align="center">
    <strong>A C++ STD vs Boost Regex Benchmark.</strong>
</p>

A quick test of both std::regex and boost::regex side by side.

This benchmark is based upon the performance test in boost-regex but has been
adapted to rely less on the rest of the boost framework and makes use of Google
Benchmark to get accurate results of the tests, also each match is currently ran
1024 times to get accurate results.

## Results

These results are taken from a AMD Ryzen 2700X:
```
08/16/20 17:00:30
Running E:\programming\tests\regex-bench\build\Release\regex_bench.exe
Run on (16 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 65K (x8)
  L2 Unified 524K (x8)
  L3 Unified 8388K (x2)
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
bm_std_regex     44662340 ns     43750000 ns           15
bm_boost_regex    4875681 ns      4849138 ns          145
```