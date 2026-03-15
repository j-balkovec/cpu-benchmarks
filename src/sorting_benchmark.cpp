// Jakob Balkovec
// sorting_benchmark.cpp

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

std::vector<int> load_data (const std::string& filename) {
  std::vector<int> data;
  std::ifstream file (filename);

  int value;
  while (file >> value)
    data.push_back (value);

  return data;
}


void bubble_sort (std::vector<int>& arr) {

  int n = arr.size ();

  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        std::swap (arr[j], arr[j + 1]);
}


double time_bubble (std::vector<int> data) {

  auto start = std::chrono::high_resolution_clock::now ();

  bubble_sort (data);

  auto end = std::chrono::high_resolution_clock::now ();

  return std::chrono::duration<double> (end - start).count ();
}


double time_std_sort (std::vector<int> data) {

  auto start = std::chrono::high_resolution_clock::now ();

  sort (data.begin (), data.end ());

  auto end = std::chrono::high_resolution_clock::now ();

  return std::chrono::duration<double> (end - start).count ();
}


int main (int argc, char* argv[]) {

  std::vector<std::string> datasets = {

      "data/random_small.txt",
      "data/random_medium.txt",
      "data/random_large.txt",

      "data/sorted_small.txt",
      "data/sorted_medium.txt",
      "data/sorted_large.txt",

      "data/reverse_small.txt",
      "data/reverse_medium.txt",
      "data/reverse_large.txt"
  };

  std::string output_file = "results/sorting_results.csv";

  bool file_exists = std::ifstream (output_file).good ();

  std::ofstream csv (output_file, std::ios::app);

  if (!file_exists) {
    csv << "dataset,bubble_sort,std_sort\n";
  }

  for (const std::string& file : datasets) {

    std::vector<int> data = load_data (file);

    double t1 = time_bubble (data);
    double t2 = time_std_sort (data);

    csv << file << "," << t1 << "," << t2 << "\n";
  }

  csv.close ();

  return 0;
}
