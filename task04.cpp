#include <filesystem>
#include <fstream>
#include <iostream>

void displayATM(const std::filesystem::path& ATM_path);
void withdrawATM(const std::filesystem::path& ATM_path);
void fillATM(const std::filesystem::path& ATM_path);
void saveATM(const std::filesystem::path& ATM_path);
void loadATM(const std::filesystem::path& ATM_path);

int main() {
  const int MAX_AMOUNT = 1000;
  const int notes[]{100, 200, 500, 1000, 2000, 5000};
  int notes_amount[]{0, 0, 0, 0, 0, 0};

  std::filesystem::path ATM_path = "./bank.bin";
  std::ifstream in_bank(ATM_path, std::ios::binary);
  std::ofstream out_bank(ATM_path, std::ios::binary);

  if (in_bank.is_open()) {
    loadATM(ATM_path);
  } else {
    std::cout << "The ATM is empty" << std::endl;
  }

  char operation;
  do {
    std::cout << "Enter '+' to fill ATM, '-' to withdraw, or 'q' to quit: ";
    std::cin >> operation;

    if (operation == '+') {
      displayATM(ATM_path);

    } else if (operation == '-') {
      withdrawATM(ATM_path);
      displayATM(ATM_path);

    } else {
      std::cout << "Terminating programm..." << std::endl;
    }
  } while (operation != 'q');

  return 0;
}
