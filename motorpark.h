#ifndef MOTO_PARK_H
#define MOTO_PARK_H

#include <string>
#include <vector>

namespace motopark {

struct Motorcycle {
    int id;
    std::string brand;
    std::string model;
    int year;
    double engineVolume;
    double price;           // Добавили цену
    std::string licensePlate;
};

class MotoDatabase {
public:
    MotoDatabase() = default;
    
    // Основные операции
    bool addMotorcycle(const Motorcycle& motorcycle);
    bool removeMotorcycle(int id);
    std::vector<Motorcycle> getAllMotorcycles() const;
    
    // Сортировка
    void sortById();
    void sortByBrand();
    void sortByYear();
    void sortByEngineVolume();
    void sortByPrice();     // Добавили сортировку по цене
    
    // Поиск
    Motorcycle* findMotorcycleById(int id);
    std::vector<Motorcycle> findMotorcyclesByBrand(const std::string& brand) const;
    
    // Статистика
    int getTotalCount() const;
    double getAverageEngineVolume() const;
    double getAveragePrice() const;     // Добавили среднюю цену
    double getTotalValue() const;       // Добавили общую стоимость
    
    // Вспомогательные функции
    void printAll() const;
    void printSummary() const;

private:
    std::vector<Motorcycle> motorcycles;
    int nextId = 1;
};

} // namespace motopark

#endif // MOTO_PARK_H
