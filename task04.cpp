#include <filesystem>
#include <fstream>
#include <iostream>

void displayATM(const int banknotes[], const int banknotes_amount[], const int& arr_size); // вывод инфы через массивы
void withdrawATM(const int banknotes[], int banknotes_amount[], const int& arr_size); // снятие через массивы
void fillATM(const int banknotes[], int banknotes_amount[], const int& arr_size, const int& MAX_AMOUNT); // заполнение массивов
bool saveATM(const int banknotes_amount[], const int& arr_size, const std::filesystem::path ATM_path); // загрузка инфы из массивов в файл
bool loadATM(int banknotes_amount[], const int& arr_size, const std::filesystem::path ATM_path); // загрузка инфы из файла в массивы

int main() {
  const int MAX_AMOUNT = 1000;
  const int banknotes[]{100, 200, 500, 1000, 2000, 5000};
  const int arr_size = sizeof(banknotes) / sizeof(banknotes[0]);
  int banknotes_amount[]{0, 0, 0, 0, 0, 0};

  std::filesystem::path ATM_path = "./bank.bin";
  std::ifstream in_bank(ATM_path, std::ios::binary);
 

  if (loadATM(banknotes_amount, arr_size,ATM_path)) {
    displayATM(banknotes, banknotes_amount, arr_size);
  } else {
    std::cout << "The ATM is empty" << std::endl;
  }

  
  while (true) {
    std::cout << "Enter '+' to fill ATM, '-' to withdraw, or 'q' to quit: ";
    char operation;
    std::cin >> operation;
    std::cin.ignore(1000, '\n');

    if (operation == '+') {
      fillATM(banknotes, banknotes_amount, arr_size, MAX_AMOUNT);
      displayATM(banknotes, banknotes_amount, arr_size);

    } else if (operation == '-') {
      withdrawATM(banknotes, banknotes_amount, arr_size);
      displayATM(banknotes, banknotes_amount, arr_size);

    } else if (operation == 'q') {
      std::cout << "Terminating programm..." << std::endl;
      saveATM(banknotes_amount, arr_size,ATM_path);
      break;

    } else {
      std::cout << "Incorrect operation. ";
    }
  } 

  return 0;
}

void displayATM(const int banknotes[], const int banknotes_amount[], const int& arr_size) {
  std::cout << "\nATM State:" << std::endl;
  int total_sum = 0;
  for (int i = 0; i < arr_size; ++i) {
    std::cout << banknotes[i] << " RUB: " << banknotes_amount[i] << " bills" << std::endl;
    total_sum += banknotes[i] * banknotes_amount[i];
  }
  std::cout << "Total sum: " << total_sum << " RUB\n" << std::endl;
}

void withdrawATM(const int banknotes[], int banknotes_amount[], const int& arr_size) {
  int amount;
  std::cout << "Enter amount to withdraw: ";
  std::cin >> amount;
  while (amount % 100 != 0 || amount <= 0 || std::cin.fail()) {
    std::cout << "Amount must be a positive multiple of 100." << std::endl;
    std::cout << "Enter amount to withdraw: ";
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cin >> amount;
  }

  int check_sum = 0;
  for (int i = 0; i < arr_size; ++i) {
    check_sum += banknotes[i] * banknotes_amount[i];
    if (check_sum >= amount) {
      break;
    }
  }

  if (check_sum < amount) {
    std::cout << "Insufficient funds or denominations to fulfill the withdrawal." << std::endl;
    return;
  }


  int i = arr_size - 1;
  while (amount > 0 && i >= 0) {
    if (amount >= banknotes[i] && banknotes_amount[i] > 0) {
      amount -= banknotes[i];
      --banknotes_amount[i];
    } else {
      --i;
    }
  }
  std::cout << "Withdrawal successful." << std::endl;
}

void fillATM(const int banknotes[], int banknotes_amount[], const int& arr_size, const int& MAX_AMOUNT) {
  srand(time(nullptr));

  int current_amount = 0;
  for (int i = 0; i < arr_size; ++i) {
    current_amount += banknotes_amount[i];
  }

  while(current_amount < MAX_AMOUNT) {
    int i = rand() % arr_size;
    ++banknotes_amount[i];
    ++current_amount;
  }

  std::cout << "The ATM is full." << std::endl;
}

bool loadATM(int banknotes_amount[], const int& arr_size, const std::filesystem::path ATM_path) {
  std::ifstream in_bank(ATM_path, std::ios::binary);
  if (!in_bank) return false;

  in_bank.read(reinterpret_cast<char*>(banknotes_amount), arr_size * sizeof(int));
  in_bank.close();
  return true;
}

bool saveATM(const int banknotes_amount[], const int& arr_size, const std::filesystem::path ATM_path) {
  std::ofstream out_bank(ATM_path, std::ios::binary);
  if (!out_bank) {
    std::cerr << "Error opening file for writing: " << ATM_path << std::endl;
    return false;
  }

  out_bank.write(reinterpret_cast<const char*>(banknotes_amount), arr_size * sizeof(int));
  out_bank.close();
  return true;
}