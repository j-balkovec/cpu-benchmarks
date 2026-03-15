// Jakob Balkovec
// cache_benchmark.cpp

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

double time_row_major (const std::vector<int>& matrix, int N) {

  volatile long long sum = 0;

  auto start = std::chrono::high_resolution_clock::now ();

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      sum += matrix[i * N + j];

  auto end = std::chrono::high_resolution_clock::now ();

  return std::chrono::duration<double> (end - start).count ();
}


double time_column_major (const std::vector<int>& matrix, int N) {

  volatile long long sum = 0;

  auto start = std::chrono::high_resolution_clock::now ();

  for (int j = 0; j < N; j++)
    for (int i = 0; i < N; i++)
      sum += matrix[i * N + j];

  auto end = std::chrono::high_resolution_clock::now ();

  return std::chrono::duration<double> (end - start).count ();
}


int main () {

  std::vector<int> sizes = { 1024, 2048, 4096 };

  std::string output_file = "results/cache_results.csv";

  bool file_exists = std::ifstream (output_file).good ();
  std::ofstream csv (output_file, std::ios::app);

  if (!file_exists) {
    csv << "matrix_size,row_major,column_major\n";
  }

  for (int N : sizes) {

    std::vector<int> matrix (N * N, 1);

    double t1 = time_row_major (matrix, N);
    double t2 = time_column_major (matrix, N);

    csv << N << "x" << N << "," << t1 << "," << t2 << "\n";
  }

  csv.close ();

  return 0;
}
