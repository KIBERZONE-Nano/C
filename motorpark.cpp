#include "motopark.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>

namespace motopark {

bool MotoDatabase::addMotorcycle(const Motorcycle& motorcycle) {
    // Проверка уникальности ID
    for (const auto& m : motorcycles) {
        if (m.id == motorcycle.id) {
            return false;
        }
    }
    
    Motorcycle newMoto = motorcycle;
    if (newMoto.id <= 0) {
        newMoto.id = nextId++;
    } else {
        nextId = std::max(nextId, newMoto.id + 1);
    }
    
    // Валидация данных
    if (newMoto.year < 1900 || newMoto.year > 2100) {
        return false;
    }
    if (newMoto.engineVolume <= 0) {
        return false;
    }
    if (newMoto.price < 0) {
        return false;
    }
    
    motorcycles.push_back(newMoto);
    return true;
}

bool MotoDatabase::removeMotorcycle(int id) {
    auto it = std::remove_if(motorcycles.begin(),
                            motorcycles.end(),
                            [id](const Motorcycle& m) {
                                return m.id == id;
                            });
    
    if (it != motorcycles.end()) {
        motorcycles.erase(it, motorcycles.end());
        return true;
    }
    return false;
}

std::vector<Motorcycle> MotoDatabase::getAllMotorcycles() const {
    return motorcycles;
}

void MotoDatabase::sortById() {
    std::sort(motorcycles.begin(),
              motorcycles.end(),
              [](const Motorcycle& a, const Motorcycle& b) {
                  return a.id < b.id;
              });
}

void MotoDatabase::sortByBrand() {
    std::sort(motorcycles.begin(),
              motorcycles.end(),
              [](const Motorcycle& a, const Motorcycle& b) {
                  if (a.brand == b.brand) {
                      return a.model < b.model;
                  }
                  return a.brand < b.brand;
              });
}

void MotoDatabase::sortByYear() {
    std::sort(motorcycles.begin(),
              motorcycles.end(),
              [](const Motorcycle& a, const Motorcycle& b) {
                  return a.year < b.year;
              });
}

void MotoDatabase::sortByEngineVolume() {
    std::sort(motorcycles.begin(),
              motorcycles.end(),
              [](const Motorcycle& a, const Motorcycle& b) {
                  return a.engineVolume < b.engineVolume;
              });
}

void MotoDatabase::sortByPrice() {
    std::sort(motorcycles.begin(),
              motorcycles.end(),
              [](const Motorcycle& a, const Motorcycle& b) {
                  return a.price < b.price;
              });
}

Motorcycle* MotoDatabase::findMotorcycleById(int id) {
    auto it = std::find_if(motorcycles.begin(),
                          motorcycles.end(),
                          [id](const Motorcycle& m) {
                              return m.id == id;
                          });
    
    if (it != motorcycles.end()) {
        return &(*it);
    }
    return nullptr;
}

std::vector<Motorcycle> MotoDatabase::findMotorcyclesByBrand(
    const std::string& brand) const {
    
    std::vector<Motorcycle> result;
    std::copy_if(motorcycles.begin(),
                motorcycles.end(),
                std::back_inserter(result),
                [&brand](const Motorcycle& m) {
                    return m.brand == brand;
                });
    return result;
}

int MotoDatabase::getTotalCount() const {
    return static_cast<int>(motorcycles.size());
}

double MotoDatabase::getAverageEngineVolume() const {
    if (motorcycles.empty()) {
        return 0.0;
    }
    
    double sum = std::accumulate(motorcycles.begin(),
                                motorcycles.end(),
                                0.0,
                                [](double acc, const Motorcycle& m) {
                                    return acc + m.engineVolume;
                                });
    
    return sum / motorcycles.size();
}

double MotoDatabase::getAveragePrice() const {
    if (motorcycles.empty()) {
        return 0.0;
    }
    
    double sum = std::accumulate(motorcycles.begin(),
                                motorcycles.end(),
                                0.0,
                                [](double acc, const Motorcycle& m) {
                                    return acc + m.price;
                                });
    
    return sum / motorcycles.size();
}

double MotoDatabase::getTotalValue() const {
    return std::accumulate(motorcycles.begin(),
                          motorcycles.end(),
                          0.0,
                          [](double acc, const Motorcycle& m) {
                              return acc + m.price;
                          });
}

void MotoDatabase::printAll() const {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << std::left << std::setw(4) << "ID" 
              << std::setw(15) << "Марка" 
              << std::setw(20) << "Модель"
              << std::setw(8) << "Год" 
              << std::setw(10) << "Объем(cc)"
              << std::setw(15) << "Цена($)"
              << "Номер\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (const auto& m : motorcycles) {
        std::cout << std::left << std::setw(4) << m.id 
                  << std::setw(15) << m.brand 
                  << std::setw(20) << m.model
                  << std::setw(8) << m.year 
                  << std::setw(10) << std::fixed << std::setprecision(1) << m.engineVolume
                  << std::setw(15) << std::fixed << std::setprecision(2) << m.price
                  << m.licensePlate << std::endl;
    }
    std::cout << std::string(80, '=') << "\n";
}

void MotoDatabase::printSummary() const {
    std::cout << "\n=== СТАТИСТИКА МОТОПАРКА ===\n";
    std::cout << "Всего мотоциклов: " << getTotalCount() << "\n";
    std::cout << "Средний объем двигателя: " << std::fixed << std::setprecision(1) 
              << getAverageEngineVolume() << " cc\n";
    std::cout << "Средняя цена: $" << std::fixed << std::setprecision(2) 
              << getAveragePrice() << "\n";
    std::cout << "Общая стоимость парка: $" << std::fixed << std::setprecision(2) 
              << getTotalValue() << "\n";
}

} // namespace motopark
