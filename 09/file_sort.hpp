#ifndef FILE_SORT_HPP_
#define FILE_SORT_HPP_
#define TEMP_SIZE 1000

#include <fstream>
#include <thread>
#include <algorithm>
#include <vector>
#include <string>

void mergeFiles(std::vector<std::string> tempFiles) {
  size_t j = 0;
  uint64_t number;
  uint64_t *temp = new uint64_t[TEMP_SIZE / 2];
  for (size_t i = 1; i < tempFiles.size(); i++) {
    std::ifstream input1(tempFiles[i]);
    input1.read(reinterpret_cast<char *>(temp),
          (TEMP_SIZE / 2) * sizeof(uint64_t));
    auto scaned = input1.gcount() / sizeof(uint64_t);
    input1.close();
    std::ifstream input2(tempFiles[i - 1]);
    input2.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
    j = 0;
    if (i == tempFiles.size() - 1) {
      tempFiles[i] = "output.txt";
    }
    std::ofstream output(tempFiles[i]);
    while (!input2.eof() && j < scaned) {
      if (number <= temp[j]) {
        output.write(reinterpret_cast<char *>(&number), sizeof(uint64_t));
        input2.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
      } else {
        output.write(reinterpret_cast<char *>(&temp[j]), sizeof(uint64_t));
        j++;
      }
    }
    if (input2.eof()) {
      output.write(reinterpret_cast<char *>(&temp[j]),
             sizeof(uint64_t) * (TEMP_SIZE / 2 - j));
    }
    while (!input2.eof()) {
      output.write(reinterpret_cast<char *>(&number), sizeof(uint64_t));
      input2.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
    }
    input2.close();
    output.close();
  }
  delete [] temp;
}

void fileSort(const std::string filename) {
  std::ifstream input(filename);
  std::vector<std::string> tempFiles;
  size_t counter = 0;
  uint64_t *temp = new uint64_t[TEMP_SIZE];
  while (!input.eof()) {
    input.read(reinterpret_cast<char*>(temp), TEMP_SIZE * sizeof(uint64_t));
    auto scaned = input.gcount() / sizeof(uint64_t);
    if (scaned > 0) {
      tempFiles.push_back("temp_" + std::to_string(counter));
      counter++;
      tempFiles.push_back("temp_" + std::to_string(counter));
      counter++;
      std::thread thread1([temp, scaned]() {
        std::sort(temp, temp + scaned / 2);
      });
      std::thread thread2([temp, scaned]() {
        std::sort(temp + scaned / 2, temp + scaned);
      });
      thread1.join();
      thread2.join();
      std::ofstream tempFile1(tempFiles[counter - 2]);
      for (size_t i = 0; i < scaned / 2; ++i) {
        tempFile1.write(reinterpret_cast<char *>(&temp[i]), sizeof(uint64_t));
      }
      tempFile1.close();
      std::ofstream tempFile2(tempFiles[counter - 1]);
      for (size_t i = scaned / 2; i < scaned; ++i) {
        tempFile2.write(reinterpret_cast<char *>(&temp[i]), sizeof(uint64_t));
      }
      tempFile2.close();
    }
  }
  delete [] temp;
  mergeFiles(tempFiles);
}

#endif  // FILE_SORT_HPP_
