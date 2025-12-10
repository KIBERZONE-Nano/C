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
    Time() : hours(0), minutes(0) {}
    
    Time(short int h, short int m) : hours(h), minutes(m) {
        normalize();
    }
    
    Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}
    
    short int getHours() const { return hours; }
    short int getMinutes() const { return minutes; }
    
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
    
    Time subtract(const Time& other) const {
        int totalMinutes1 = hours * 60 + minutes;
        int totalMinutes2 = other.hours * 60 + other.minutes;
        int diff = totalMinutes1 - totalMinutes2;
        
        if (diff < 0) {
            diff += 24 * 60;
        }
        
        return Time(diff / 60, diff % 60);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << std::setw(2) << std::setfill('0') << t.hours << ":"
           << std::setw(2) << std::setfill('0') << t.minutes;
        return os;
    }
    
    static Time inputTime(const std::string& prompt) {
        std::string input;
        short int h, m;
        
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            
            std::istringstream iss(input);
            if (iss >> h >> m) {
                // Проверяем, нет ли лишних символов
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
                // Очищаем флаги ошибок потока
                std::cin.clear();
            }
        }
    }
    
    // Дополнительный метод для ввода времени в формате HH:MM
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
                    // Проверяем, нет ли лишних символов
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

int main() {
    std::cout << "=== Тестирование класса Time ===\n\n";
    
    // Тест 1: Конструкторы
    std::cout << "1. Тест конструкторов:\n";
    Time t1;
    std::cout << "   Конструктор по умолчанию: " << t1 << std::endl;
    
    Time t2(14, 30);
    std::cout << "   Конструктор с параметрами (14, 30): " << t2 << std::endl;
    
    Time t3(t2);
    std::cout << "   Конструктор копирования (из t2): " << t3 << std::endl;
    
    Time t4(25, 70);
    std::cout << "   Конструктор с нормализацией (25, 70): " << t4 << std::endl;
    
    // Тест 2: Ввод времени
    std::cout << "\n2. Ввод времени с клавиатуры:\n";
    std::cout << "   Можно вводить в двух форматах:\n";
    std::cout << "   - Два числа через пробел (например: 14 30)\n";
    std::cout << "   - В формате HH:MM (например: 14:30)\n\n";
    
    Time time1 = Time::inputTime("Введите первое время (часы и минуты через пробел): ");
    std::cout << "   Первое время: " << time1 << std::endl;
    
    Time time2 = Time::inputTimeFormatted("Введите второе время (в формате HH:MM): ");
    std::cout << "   Второе время: " << time2 << std::endl;
    
    // Тест 3: Вычитание времени
    std::cout << "\n3. Тест вычитания времени:\n";
    Time result = time1.subtract(time2);
    std::cout << "   " << time1 << " - " << time2 << " = " << result << std::endl;
    
    // Тест 4: Дополнительные тесты вычитания
    std::cout << "\n4. Дополнительные тесты вычитания:\n";
    
    Time morning(8, 0);
    Time late(9, 30);
    Time diff1 = morning.subtract(late);
    std::cout << "   " << morning << " - " << late << " = " << diff1 
              << " (переход через полночь)" << std::endl;
    
    Time afternoon(15, 45);
    Time noon(12, 30);
    Time diff2 = afternoon.subtract(noon);
    std::cout << "   " << afternoon << " - " << noon << " = " << diff2 << std::endl;
    
    Time same1(10, 15);
    Time same2(10, 15);
    Time diff3 = same1.subtract(same2);
    std::cout << "   " << same1 << " - " << same2 << " = " << diff3 << std::endl;
    
    std::cout << "\n=== Все тесты завершены ===\n";
    
    return 0;
}