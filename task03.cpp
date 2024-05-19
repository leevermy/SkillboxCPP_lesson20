#include <filesystem>
#include <fstream>
#include <iostream>

int main() {
  std::filesystem::path river_file = "./river.txt";
  std::filesystem::path basket_file = "./basket.txt";

  std::cout << "Enter the name of the fish: ";
  std::string target_fish;
  std::cin >> target_fish;

  std::ifstream in_file(river_file);
  std::ofstream out_file(basket_file, std::ios::app);

  if (!in_file.is_open() || !out_file.is_open()) {
    std::cerr << "Failed to open one of the files.\n";
    return 1;
  }

  int fish_count = 0;
  std::string current_fish;
  while (in_file >> current_fish) {
    if (current_fish == target_fish) {
      out_file << current_fish << '\n';
      ++fish_count;
    }
  }

  in_file.close();
  out_file.close();

  std::cout << "Total caught: " << fish_count << std::endl;

  return 0;
}