#include "motopark.h"
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void initializeDatabase(motopark::MotoDatabase& db) {
    // Добавляем 15 мотоциклов
    vector<motopark::Motorcycle> initialMotorcycles = {
        {0, "Honda", "CBR600RR", 2020, 599.0, 12500.0, "A123BC"},
        {0, "Yamaha", "R6", 2019, 599.0, 11800.0, "B456DE"},
        {0, "Kawasaki", "Ninja ZX-6R", 2021, 636.0, 13500.0, "C789FG"},
        {0, "Suzuki", "GSX-R600", 2018, 599.0, 9800.0, "D012HI"},
        {0, "Ducati", "Panigale V2", 2022, 955.0, 18500.0, "E345JK"},
        {0, "BMW", "S1000RR", 2023, 999.0, 21000.0, "F678LM"},
        {0, "KTM", "RC 390", 2021, 373.0, 6500.0, "G901NO"},
        {0, "Harley-Davidson", "Sportster S", 2022, 1250.0, 15500.0, "H234PQ"},
        {0, "Triumph", "Street Triple RS", 2021, 765.0, 14200.0, "I567RS"},
        {0, "Aprilia", "RS 660", 2023, 659.0, 11900.0, "J890TU"},
        {0, "Honda", "Africa Twin", 2022, 1084.0, 16500.0, "K123VW"},
        {0, "Yamaha", "MT-07", 2020, 689.0, 8500.0, "L456XY"},
        {0, "Kawasaki", "Z900", 2021, 948.0, 11200.0, "M789ZA"},
        {0, "Suzuki", "Hayabusa", 2023, 1340.0, 19500.0, "N012BC"},
        {0, "Ducati", "Monster", 2022, 937.0, 13800.0, "O345DE"}
    };
    
    for (const auto& m : initialMotorcycles) {
        db.addMotorcycle(m);
    }
}

void displayMenu() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "          СИСТЕМА УПРАВЛЕНИЯ МОТОПАРКОМ\n";
    cout << string(50, '=') << "\n";
    cout << "1. Показать все мотоциклы\n";
    cout << "2. Добавить новый мотоцикл\n";
    cout << "3. Удалить мотоцикл\n";
    cout << "4. Сортировать по году выпуска\n";
    cout << "5. Сортировать по объему двигателя\n";
    cout << "6. Сортировать по цене\n";
    cout << "7. Показать статистику\n";
    cout << "8. Найти мотоцикл по ID\n";
    cout << "9. Найти мотоциклы по марке\n";
    cout << "0. Выход\n";
    cout << string(50, '-') << "\n";
    cout << "Выберите действие (0-9): ";
}

motopark::Motorcycle inputMotorcycle() {
    motopark::Motorcycle m;
    
    cout << "\n=== Добавление нового мотоцикла ===\n";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Марка: ";
    getline(cin, m.brand);
    
    cout << "Модель: ";
    getline(cin, m.model);
    
    cout << "Год выпуска: ";
    cin >> m.year;
    
    cout << "Объем двигателя (cc): ";
    cin >> m.engineVolume;
    
    cout << "Цена ($): ";
    cin >> m.price;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Регистрационный номер: ";
    getline(cin, m.licensePlate);
    
    m.id = 0; // ID будет сгенерирован автоматически
    
    return m;
}

int main() {
    motopark::MotoDatabase db;
    
    // Инициализация базы данных 15 мотоциклами
    initializeDatabase(db);
    
    int choice;
    bool running = true;
    
    cout << "Добро пожаловать в систему управления мотопарком!\n";
    cout << "База данных инициализирована с " << db.getTotalCount() << " мотоциклами.\n";
    
    while (running) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 0: // Выход
                running = false;
                cout << "\nСпасибо за использование программы. До свидания!\n";
                break;
                
            case 1: // Показать все
                db.printAll();
                break;
                
            case 2: { // Добавить мотоцикл
                motopark::Motorcycle newMoto = inputMotorcycle();
                if (db.addMotorcycle(newMoto)) {
                    cout << "\n✅ Мотоцикл успешно добавлен!\n";
                } else {
                    cout << "\n❌ Ошибка при добавлении мотоцикла!\n";
                }
                break;
            }
                
            case 3: { // Удалить мотоцикл
                int id;
                cout << "\nВведите ID мотоцикла для удаления: ";
                cin >> id;
                
                if (db.removeMotorcycle(id)) {
                    cout << "✅ Мотоцикл с ID=" << id << " удален.\n";
                } else {
                    cout << "❌ Мотоцикл с ID=" << id << " не найден.\n";
                }
                break;
            }
                
            case 4: // Сортировать по году
                db.sortByYear();
                cout << "\n✅ Сортировка по году выпуска выполнена.\n";
                db.printAll();
                break;
                
            case 5: // Сортировать по объему
                db.sortByEngineVolume();
                cout << "\n✅ Сортировка по объему двигателя выполнена.\n";
                db.printAll();
                break;
                
            case 6: // Сортировать по цене
                db.sortByPrice();
                cout << "\n✅ Сортировка по цене выполнена.\n";
                db.printAll();
                break;
                
            case 7: // Статистика
                db.printSummary();
                break;
                
            case 8: { // Найти по ID
                int id;
                cout << "\nВведите ID мотоцикла: ";
                cin >> id;
                
                motopark::Motorcycle* found = db.findMotorcycleById(id);
                if (found != nullptr) {
                    cout << "\n✅ Найден мотоцикл:\n";
                    cout << "ID: " << found->id << "\n";
                    cout << "Марка: " << found->brand << "\n";
                    cout << "Модель: " << found->model << "\n";
                    cout << "Год: " << found->year << "\n";
                    cout << "Объем: " << found->engineVolume << " cc\n";
                    cout << "Цена: $" << found->price << "\n";
                    cout << "Номер: " << found->licensePlate << "\n";
                } else {
                    cout << "❌ Мотоцикл с ID=" << id << " не найден.\n";
                }
                break;
            }
                
            case 9: { // Найти по марке
                string brand;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nВведите марку мотоцикла: ";
                getline(cin, brand);
                
                vector<motopark::Motorcycle> found = db.findMotorcyclesByBrand(brand);
                if (!found.empty()) {
                    cout << "\n✅ Найдено " << found.size() << " мотоциклов марки " << brand << ":\n";
                    for (const auto& m : found) {
                        cout << "ID: " << m.id << " - " << m.brand << " " << m.model 
                             << " (" << m.year << "), Цена: $" << m.price << "\n";
                    }
                } else {
                    cout << "❌ Мотоциклы марки " << brand << " не найдены.\n";
                }
                break;
            }
                
            default:
                cout << "\n❌ Неверный выбор. Попробуйте снова.\n";
                break;
        }
        
        // Очистка буфера ввода
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }
    }
    
    return 0;
}
