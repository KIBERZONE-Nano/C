#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

class Time {
private:
    short int hours;
    short int minutes;

    void normalize() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        } else if (minutes < 0) {
            hours -= (-minutes + 59) / 60;
            minutes = (minutes % 60 + 60) % 60;
        }
        
        if (hours >= 24) {
            hours %= 24;
        } else if (hours < 0) {
            hours = (hours % 24 + 24) % 24;
        }
    }

public:
    // Конструкторы
    Time() : hours(0), minutes(0) {}
    
    Time(short int h, short int m) : hours(h), minutes(m) {
        normalize();
    }
    
    Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}
    
    // Геттеры
    short int getHours() const { return hours; }
    short int getMinutes() const { return minutes; }
    
    // Сеттеры с проверкой
    bool setHours(short int h) {
        if (h >= 0 && h < 24) {
            hours = h;
            return true;
        }
        return false;
    }
    
    bool setMinutes(short int m) {
        if (m >= 0 && m < 60) {
            minutes = m;
            return true;
        }
        return false;
    }
    
    // Метод вычитания времени из задания 1
    Time subtract(const Time& other) const {
        int totalMinutes1 = hours * 60 + minutes;
        int totalMinutes2 = other.hours * 60 + other.minutes;
        int diff = totalMinutes1 - totalMinutes2;
        
        if (diff < 0) {
            diff += 24 * 60;
        }
        
        return Time(diff / 60, diff % 60);
    }
    
    // Унарные операции (префиксные и постфиксные)
    
    // Префиксный ++ (добавление минуты)
    Time& operator++() {
        ++minutes;
        normalize();
        return *this;
    }
    
    // Постфиксный ++ (добавление минуты)
    Time operator++(int) {
        Time temp = *this;
        ++(*this);
        return temp;
    }
    
    // Префиксный -- (вычитание минуты)
    Time& operator--() {
        --minutes;
        normalize();
        return *this;
    }
    
    // Постфиксный -- (вычитание минуты)
    Time operator--(int) {
        Time temp = *this;
        --(*this);
        return temp;
    }
    
    // Операции приведения типа
    
    // Неявное приведение к int (количество минут)
    operator int() const {
        return hours * 60 + minutes;
    }
    
    // Явное приведение к bool
    explicit operator bool() const {
        return (hours != 0 || minutes != 0);
    }
    
    // Бинарные операции сравнения
    
    // Оператор < (меньше)
    bool operator<(const Time& other) const {
        return static_cast<int>(*this) < static_cast<int>(other);
    }
    
    // Оператор > (больше)
    bool operator>(const Time& other) const {
        return static_cast<int>(*this) > static_cast<int>(other);
    }
    
    // Оператор <= (меньше или равно)
    bool operator<=(const Time& other) const {
        return static_cast<int>(*this) <= static_cast<int>(other);
    }
    
    // Оператор >= (больше или равно)
    bool operator>=(const Time& other) const {
        return static_cast<int>(*this) >= static_cast<int>(other);
    }
    
    // Оператор == (равно)
    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
    
    // Оператор != (не равно)
    bool operator!=(const Time& other) const {
        return !(*this == other);
    }
    
    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << std::setw(2) << std::setfill('0') << t.hours << ":"
           << std::setw(2) << std::setfill('0') << t.minutes;
        return os;
    }
    
    // Методы для ввода времени
    static Time inputTime(const std::string& prompt) {
        std::string input;
        short int h, m;
        
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            
            std::istringstream iss(input);
            if (iss >> h >> m) {
                std::string extra;
                if (iss >> extra) {
                    std::cout << "Ошибка: введены лишние символы. Введите только часы и минуты.\n";
                    continue;
                }
                
                if (h >= 0 && h < 24 && m >= 0 && m < 60) {
                    return Time(h, m);
                } else {
                    std::cout << "Ошибка: часы должны быть от 0 до 23, минуты от 0 до 59.\n";
                }
            } else {
                std::cout << "Ошибка: неверный формат. Введите два числа (часы и минуты).\n";
                std::cin.clear();
            }
        }
    }
    
    static Time inputTimeFormatted(const std::string& prompt) {
        std::string input;
        char colon;
        short int h, m;
        
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            
            std::istringstream iss(input);
            if (iss >> h >> colon >> m) {
                if (colon == ':') {
                    std::string extra;
                    if (iss >> extra) {
                        std::cout << "Ошибка: введены лишние символы. Используйте формат HH:MM.\n";
                        continue;
                    }
                    
                    if (h >= 0 && h < 24 && m >= 0 && m < 60) {
                        return Time(h, m);
                    } else {
                        std::cout << "Ошибка: часы должны быть от 0 до 23, минуты от 0 до 59.\n";
                    }
                } else {
                    std::cout << "Ошибка: неверный формат. Используйте формат HH:MM (например, 14:30).\n";
                }
            } else {
                std::cout << "Ошибка: неверный формат. Используйте формат HH:MM (например, 14:30).\n";
                std::cin.clear();
            }
        }
    }
};

// Функция для демонстрации дружественного интерфейса
void demonstrateFriendInterface(const Time& t1, const Time& t2) {
    std::cout << "\n=== Демонстрация дружественного интерфейса ===\n";
    
    // Использование оператора вывода (дружественная функция)
    std::cout << "Время 1: " << t1 << std::endl;
    std::cout << "Время 2: " << t2 << std::endl;
    
    // Вычисление разности с использованием метода subtract
    std::cout << "Разность (t1 - t2): " << t1.subtract(t2) << std::endl;
}

int main() {
    std::cout << "=== Лабораторная работа 2: Класс Time с перегруженными операторами ===\n\n";
    
    // Часть 1: Демонстрация работы из задания 1
    std::cout << "--- Часть 1: Функциональность из задания 1 ---\n";
    
    // Ввод времени
    Time time1 = Time::inputTime("Введите первое время (часы и минуты через пробел): ");
    Time time2 = Time::inputTimeFormatted("Введите второе время (в формате HH:MM): ");
    
    std::cout << "\nПервое время: " << time1 << std::endl;
    std::cout << "Второе время: " << time2 << std::endl;
    
    // Вычитание времени (метод из задания 1)
    Time subtractionResult = time1.subtract(time2);
    std::cout << "Результат вычитания (time1 - time2): " << subtractionResult << std::endl;
    
    // Часть 2: Демонстрация перегруженных операторов
    std::cout << "\n--- Часть 2: Перегруженные операторы ---\n";
    
    // Тестирование унарных операторов
    std::cout << "\n1. Тестирование унарных операторов:\n";
    
    Time t1 = time1;
    std::cout << "   Исходное время: " << t1 << std::endl;
    
    // Префиксный ++
    std::cout << "   Префиксный ++: " << ++t1 << " (после: " << t1 << ")" << std::endl;
    
    // Постфиксный ++
    Time t2 = t1;
    std::cout << "   Постфиксный ++: " << t2++ << " (после: " << t2 << ")" << std::endl;
    
    // Префиксный --
    std::cout << "   Префиксный --: " << --t1 << " (после: " << t1 << ")" << std::endl;
    
    // Постфиксный --
    t2 = t1;
    std::cout << "   Постфиксный --: " << t2-- << " (после: " << t2 << ")" << std::endl;
    
    // Тестирование переходов через полночь
    std::cout << "\n   Тест переходов через полночь:\n";
    Time midnight(23, 59);
    std::cout << "   Исходное время: " << midnight << std::endl;
    std::cout << "   ++ (префиксный): " << ++midnight << std::endl;
    
    Time zeroTime(0, 0);
    std::cout << "   Исходное время: " << zeroTime << std::endl;
    std::cout << "   -- (префиксный): " << --zeroTime << std::endl;
    
    // Тестирование операций приведения типа
    std::cout << "\n2. Тестирование операций приведения типа:\n";
    
    Time t3(2, 30);
    std::cout << "   Время: " << t3 << std::endl;
    
    // Неявное приведение к int
    int minutes = t3;  // Неявное преобразование
    std::cout << "   Неявное приведение к int: " << minutes << " минут" << std::endl;
    
    // Использование в арифметических выражениях
    int totalMinutes = t3 + 60;  // 2:30 + 60 минут = 150 + 60 = 210 минут
    std::cout << "   t3 + 60 минут = " << totalMinutes << " минут" << std::endl;
    
    // Явное приведение к bool
    Time zeroTime2(0, 0);
    Time nonZeroTime(0, 1);
    
    std::cout << "   Время " << zeroTime2 << " в bool: " << (static_cast<bool>(zeroTime2) ? "true" : "false") << std::endl;
    std::cout << "   Время " << nonZeroTime << " в bool: " << (static_cast<bool>(nonZeroTime) ? "true" : "false") << std::endl;
    
    // Использование в условиях
    if (t3) {
        std::cout << "   t3 (" << t3 << ") преобразуется в true" << std::endl;
    }
    if (!zeroTime2) {
        std::cout << "   zeroTime2 (" << zeroTime2 << ") преобразуется в false" << std::endl;
    }
    
    // Тестирование бинарных операторов сравнения
    std::cout << "\n3. Тестирование бинарных операторов сравнения:\n";
    
    Time earlyTime(8, 30);
    Time lateTime(14, 45);
    Time sameAsEarly(8, 30);
    
    std::cout << "   earlyTime: " << earlyTime << " (" << static_cast<int>(earlyTime) << " минут)" << std::endl;
    std::cout << "   lateTime: " << lateTime << " (" << static_cast<int>(lateTime) << " минут)" << std::endl;
    std::cout << "   sameAsEarly: " << sameAsEarly << " (" << static_cast<int>(sameAsEarly) << " минут)" << std::endl;
    
    // Оператор <
    std::cout << "   earlyTime < lateTime: " << (earlyTime < lateTime ? "true" : "false") << std::endl;
    std::cout << "   lateTime < earlyTime: " << (lateTime < earlyTime ? "true" : "false") << std::endl;
    
    // Оператор >
    std::cout << "   earlyTime > lateTime: " << (earlyTime > lateTime ? "true" : "false") << std::endl;
    std::cout << "   lateTime > earlyTime: " << (lateTime > earlyTime ? "true" : "false") << std::endl;
    
    // Оператор <=
    std::cout << "   earlyTime <= lateTime: " << (earlyTime <= lateTime ? "true" : "false") << std::endl;
    std::cout << "   earlyTime <= sameAsEarly: " << (earlyTime <= sameAsEarly ? "true" : "false") << std::endl;
    
    // Оператор >=
    std::cout << "   lateTime >= earlyTime: " << (lateTime >= earlyTime ? "true" : "false") << std::endl;
    std::cout << "   earlyTime >= sameAsEarly: " << (earlyTime >= sameAsEarly ? "true" : "false") << std::endl;
    
    // Оператор ==
    std::cout << "   earlyTime == lateTime: " << (earlyTime == lateTime ? "true" : "false") << std::endl;
    std::cout << "   earlyTime == sameAsEarly: " << (earlyTime == sameAsEarly ? "true" : "false") << std::endl;
    
    // Оператор !=
    std::cout << "   earlyTime != lateTime: " << (earlyTime != lateTime ? "true" : "false") << std::endl;
    std::cout << "   earlyTime != sameAsEarly: " << (earlyTime != sameAsEarly ? "true" : "false") << std::endl;
    
    // Демонстрация дружественного интерфейса
    demonstrateFriendInterface(time1, time2);
    
    // Дополнительные тесты
    std::cout << "\n--- Дополнительные тесты ---\n";
    
    // Тестирование с использованием в выражениях
    Time t4(10, 0);
    Time t5(9, 59);
    
    std::cout << "t4: " << t4 << ", t5: " << t5 << std::endl;
    std::cout << "t4 < t5: " << (t4 < t5 ? "true" : "false") << std::endl;
    std::cout << "t4 > t5: " << (t4 > t5 ? "true" : "false") << std::endl;
    
    // Использование в сортировке или других алгоритмах
    Time times[] = {Time(23, 30), Time(1, 15), Time(12, 0), Time(6, 45)};
    std::cout << "\nМассив времен до сортировки: ";
    for (const auto& t : times) {
        std::cout << t << " ";
    }
    
    // Простая пузырьковая сортировка с использованием оператора <
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3 - i; ++j) {
            if (times[j + 1] < times[j]) {
                std::swap(times[j], times[j + 1]);
            }
        }
    }
    
    std::cout << "\nМассив времен после сортировки (по возрастанию): ";
    for (const auto& t : times) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== Все тесты завершены ===\n";
    
    return 0;
}