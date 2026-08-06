#pragma once

#include <algorithm>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <vector>

std::vector<double> loadBinaryInput_d(const std::filesystem::path& relativePath,
                                    std::size_t numElements) {
  std::filesystem::path filePath =
      std::filesystem::path(TEST_DATA_DIR) / relativePath;

  std::ifstream in(filePath, std::ios::binary);
  if (!in) {
    throw std::runtime_error("Failed to open file: " + filePath.string());
  }

  std::vector<double> temp(numElements);
  in.read(reinterpret_cast<char*>(temp.data()),
          temp.size() * sizeof(double));

  if (in.gcount() !=
      static_cast<std::streamsize>(temp.size() * sizeof(double))) {
    throw std::runtime_error("Failed to read expected number of bytes from: " +
                             filePath.string());
  }

  // Uncomment the following lines for debugging purposes
  std::cout << filePath.string() << " loaded successfully. First few values:\n";
  for (size_t i = 0; i < std::min<size_t>(10, temp.size()); ++i)
    std::cout << temp[i] << '\n';

  for (double x : temp) {
    if (!std::isfinite(x))
      std::cout << "Non-finite value found\n";
  }

  auto [mn, mx] = std::minmax_element(temp.begin(), temp.end());
  std::cout << "min = " << *mn << ", max = " << *mx << '\n';

  return std::vector<double>(temp.begin(), temp.end());
}


std::vector<float> loadBinaryInput_f(const std::filesystem::path& relativePath,
                                    std::size_t numElements) {
  std::filesystem::path filePath =
      std::filesystem::path(TEST_DATA_DIR) / relativePath;

  std::ifstream in(filePath, std::ios::binary);
  if (!in) {
    throw std::runtime_error("Failed to open file: " + filePath.string());
  }

  std::vector<double> temp(numElements);
  in.read(reinterpret_cast<char*>(temp.data()),
          temp.size() * sizeof(double));

  if (in.gcount() !=
      static_cast<std::streamsize>(temp.size() * sizeof(double))) {
    throw std::runtime_error("Failed to read expected number of bytes from: " +
                             filePath.string());
  }

  // Uncomment the following lines for debugging purposes
  std::cout << filePath.string() << " loaded successfully. First few values:\n";
  for (size_t i = 0; i < std::min<size_t>(10, temp.size()); ++i)
    std::cout << temp[i] << '\n';

  for (double x : temp) {
    if (!std::isfinite(x))
      std::cout << "Non-finite value found\n";
  }

  auto [mn, mx] = std::minmax_element(temp.begin(), temp.end());
  std::cout << "min = " << *mn << ", max = " << *mx << '\n';

  return std::vector<float>(temp.begin(), temp.end());
}