#include <ctime>
#include <fstream>
#include <iostream>

void generateBinaryPicture(int width, int height, const std::string& filename) {
  std::ofstream outFile(filename);
  if (!outFile) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      outFile << (rand() % 2);
    }
    outFile << '\n';
  }
  outFile.close();
}

int main() {
  std::srand(time(nullptr));

  int width, height;
  std::cout << "Enter the width of the picture: ";
  std::cin >> width;
  std::cout << "Enter the height of the picture: ";
  std::cin >> height;

  if (width <= 0 || height <= 0) {
    std::cerr << "Width and height must be positive integers." << std::endl;
    return 1;
  }
  std::filesystem::path file_path = "./picture.txt";
  generateBinaryPicture(width, height, file_path);
  std::cout << "Binary picture generated in " << file_path << "." << std::endl;

  return 0;
}
