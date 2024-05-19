#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <algorithm>

void InputFromUser(std::string& content);
bool isValidDate(const std::string date);
bool isLeapYear(int year);
int daysInMonth(int month, int year);
bool isValidData(const std::string& data, bool alpha = true);

int main() {
    std::filesystem::path file_path{"./payments.txt"};
    std::ofstream file(file_path, std::ios::app);

    if (file.is_open()) {
        std::string content;
        InputFromUser(content);
        file << content;
    } else {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return 1;
    }
    return 0;
}

void InputFromUser(std::string& content) {
    bool ok = false;
    std::cout << "Enter the name of the employee: ";
    std::string name;
    std::cin >> name;
    while (!isValidData(name)) {
        std::cout << "Invalid name. Only alphabetic characters allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> name;
    }

    std::cout << "Enter the surname of the employee: ";
    std::string surname;
    std::cin >> surname;
    while (!isValidData(surname)) {
        std::cout << "Invalid surname. Only alphabetic characters allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> surname;
    }

    std::cout << "Enter the date of the salary(dd.mm.yyyy): ";
    std::string date;
    std::cin >> date;
    while(!isValidDate(date)) {
        std::cout << "Wrong date. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> date;
    }

    std::cout << "Enter the payment amount in rubles: ";
    std::string salary;
    std::cin >> salary;
    while(!isValidData(salary, false)) {
        std::cout << "Invalid payment. Only digits allowed. Try again: ";
        std::cin.fail();
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cin >> salary;
    }

    content = name + " " + surname + " " + date + " " + salary + "\n";
}

bool isValidDate(const std::string date) {
    if (date.length() != 10) return false;
    
    int size = date.length();
    for (int i = 0; i < size; ++i) {
        if ((i == 2 || i == 5) && date[i] != '.') 
            return false;
        else if ((i != 2 && i != 5) && !std::isdigit(date[i])) 
            return false;
    }

    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    return (month <= 12 && month >= 1 && day >= 1 && day <= daysInMonth(month, year));
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1:
        case 3: 
        case 5: 
        case 7:
        case 8:
        case 10:
        case 12: return 31;
        case 4:
        case 6:
        case 9:
        case 11: return 30;
        case 2: return isLeapYear(year) ? 29 : 28;
        default: return 0;
    }
}

bool isValidData(const std::string& data, bool alpha) {
    return std::all_of(data.begin(), data.end(), [alpha](unsigned char c) {
        return alpha ? std::isalpha(c) : std::isdigit(c);
    });
}