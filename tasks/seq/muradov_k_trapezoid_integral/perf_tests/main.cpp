#include <gtest/gtest.h>

#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>

#include "seq/muradov_k_trapezoid_integral/include/ops_seq.hpp"

namespace muradov_k_trapezoid_integral_seq {

// Test #1: measure performance of entire "task run".
TEST(muradov_k_trapezoid_integral_seq, test_task_run) {
  std::function<double(double)> f = [](double x) { return x * sin(x); };
  double a = 0.0;
  double b = 10.0;
  int n = 10000000;

  auto start = std::chrono::high_resolution_clock::now();
  double result = GetIntegralTrapezoidalRuleSequential(f, a, b, n);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  std::cout << "[Seq Task Run] Result: " << result << ", Time: " << elapsed.count() << " seconds\n";
  SUCCEED();
}

// Test #2: measure performance of "pipeline".
TEST(muradov_k_trapezoid_integral_seq, test_pipeline_run) {
  std::function<double(double)> f = [](double x) { return exp(x); };
  double a = -6.0;
  double b = 6.0;
  int n = 10000000;

  auto start = std::chrono::high_resolution_clock::now();
  double result = GetIntegralTrapezoidalRuleSequential(f, a, b, n);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  std::cout << "[Seq Pipeline Run] Result: " << result << ", Time: " << elapsed.count() << " seconds\n";
  SUCCEED();
}

}  // namespace muradov_k_trapezoid_integral_seq
