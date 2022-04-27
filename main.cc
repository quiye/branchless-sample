#include <bits/stdc++.h>
#include <immintrin.h>

#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

using namespace std;
int branchless_lower_bound1(vector<int>& v, int target) {
  int len = v.size();
  int start = 0;
  while (len > 1) {
    int mid = len >> 1;
    start = target <= v[start + mid] ? start : start + mid;
    len = target <= v[start + mid] ? mid : len - mid;
  }
  return start + len;
}
int branchless_lower_bound2(vector<int>& v, int target) {
  int end = v.size();
  int start = 0;
  while (end - start > 1) {  //ここのsubが遅い?
    int mid = (start + end) >> 1;
    start = target <= v[mid] ? start : mid;
    end = target <= v[mid] ? mid : end;
  }
  return end;
}
int branchless_lower_bound3(vector<int>& v, int target) {
  int start = 0;
  auto len = v.size();
  while (len > 0) {
    int mid = len >> 1;
    auto ss = start + mid + 1;
    auto cmp = v[ss - 1];
    start = target <= cmp ? start : ss;
    len = target <= cmp ? mid : len - (mid + 1);
  }
  return start;
}

#include "benchmark/include/benchmark/benchmark.h"

static void test1(benchmark::State& state) {
  vector<int> v;
  for (int i = 0; i < state.range(0); i++) {
    v.push_back(i);  // 0, 3, 6
  }
  for (auto _ : state) {
    for (size_t i = 0; i < 19999; i++) {
      branchless_lower_bound1(v, 77);
    }
  }
}
BENCHMARK(test1)->DenseRange(0, 300, 50);

static void test2(benchmark::State& state) {
  vector<int> v;
  for (int i = 0; i < state.range(0); i++) {
    v.push_back(i);  // 0, 3, 6
  }
  for (auto _ : state) {
    for (size_t i = 0; i < 19999; i++) {
      branchless_lower_bound2(v, 77);
    }
  }
}
BENCHMARK(test2)->DenseRange(0, 300, 50);

static void test3(benchmark::State& state) {
  vector<int> v;
  for (int i = 0; i < state.range(0); i++) {
    v.push_back(i);  // 0, 3, 6
  }
  for (auto _ : state) {
    for (size_t i = 0; i < 19999; i++) {
      branchless_lower_bound3(v, 77);
    }
  }
}
BENCHMARK(test3)->DenseRange(0, 300, 50);

static void test4(benchmark::State& state) {
  vector<int> v;
  for (int i = 0; i < state.range(0); i++) {
    v.push_back(i);  // 0, 3, 6
  }
  for (auto _ : state) {
    for (size_t i = 0; i < 19999; i++) {
      std::lower_bound(v.begin(), v.end(), 7);
    }
  }
}
BENCHMARK(test4)->DenseRange(0, 300, 50);

BENCHMARK_MAIN();