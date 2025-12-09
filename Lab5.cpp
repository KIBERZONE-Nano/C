#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

class FileTasks {
private:
    // Генератор случайных чисел
    static mt19937& get_random_engine() {
        static mt19937 engine(random_device{}());
        return engine;
    }

public:
    // ==================== ЗАДАНИЕ 1 ====================
    // Заполнение бинарного файла случайными целыми числами
    static void generateBinaryFile1(const string& filename, int count) {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        uniform_int_distribution<int> dist(-1000, 1000);
        auto& gen = get_random_engine();

        for (int i = 0; i < count; i++) {
            int num = dist(gen);
            file.write(reinterpret_cast<const char*>(&num), sizeof(num));
        }
        cout << "Файл " << filename << " создан с " << count << " числами" << endl;
    }

    // Найти разность максимального и минимального элементов
    static void task1(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        int num;
        int min_val = numeric_limits<int>::max();
        int max_val = numeric_limits<int>::min();
        bool has_data = false;

        while (file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            has_data = true;
            if (num < min_val) min_val = num;
            if (num > max_val) max_val = num;
        }

        if (has_data) {
            cout << "Задание 1:" << endl;
            cout << "Минимальный элемент: " << min_val << endl;
            cout << "Максимальный элемент: " << max_val << endl;
            cout << "Разность (max - min): " << (max_val - min_val) << endl;
        } else {
            cout << "Файл пуст!" << endl;
        }
    }

    // ==================== ЗАДАНИЕ 2 ====================
    // Заполнение бинарного файла случайными числами (для задания 2)
    static void generateBinaryFile2(const string& filename, int count) {
        generateBinaryFile1(filename, count); // Используем ту же функцию
    }

    // Скопировать элементы в матрицу n×n и заменить максимальные элементы на 0
    static void task2(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        // Считываем все числа из файла
        vector<int> numbers;
        int num;
        while (file.read(reinterpret_cast<char*>(&num), sizeof(num))) {
            numbers.push_back(num);
        }

        if (numbers.empty()) {
            cout << "Файл пуст!" << endl;
            return;
        }

        // Находим максимальный элемент
        int max_elem = *max_element(numbers.begin(), numbers.end());

        // Определяем размер матрицы n
        size_t n = static_cast<size_t>(ceil(sqrt(numbers.size())));
        
        // Создаем матрицу
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        
        // Копируем элементы из вектора в матрицу
        size_t index = 0;
        for (size_t i = 0; i < n && index < numbers.size(); i++) {
            for (size_t j = 0; j < n && index < numbers.size(); j++) {
                matrix[i][j] = numbers[index++];
            }
        }

        cout << "\nЗадание 2:" << endl;
        cout << "Исходная матрица " << n << "x" << n << ":" << endl;
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << setw(6) << val;
            }
            cout << endl;
        }

        // Заменяем максимальные элементы на 0
        for (auto& row : matrix) {
            for (auto& val : row) {
                if (val == max_elem) {
                    val = 0;
                }
            }
        }

        cout << "\nМатрица после замены максимального элемента (" 
             << max_elem << ") на 0:" << endl;
        for (const auto& row : matrix) {
            for (int val : row) {
                cout << setw(6) << val;
            }
            cout << endl;
        }
    }

    // ==================== ЗАДАНИЕ 3 ====================
    // Структура для игрушки
    struct Toy {
        char name[50];
        double price;
        int min_age;
        int max_age;
    };

    // Заполнение бинарного файла структурами Toy
    static void generateBinaryFile3(const string& filename, int count) {
        ofstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        vector<string> toy_names = {
            "Кукла", "Машинка", "Конструктор", "Мяч", "Пазл",
            "Кубики", "Робот", "Настольная игра", "Плюшевый мишка", "Самолет"
        };

        uniform_int_distribution<int> name_dist(0, toy_names.size() - 1);
        uniform_real_distribution<double> price_dist(100.0, 5000.0);
        uniform_int_distribution<int> min_age_dist(0, 10);
        uniform_int_distribution<int> max_age_dist(1, 14);
        auto& gen = get_random_engine();

        for (int i = 0; i < count; i++) {
            Toy toy;
            
            // Заполняем название
            string name = toy_names[name_dist(gen)] + " " + to_string(i + 1);
            strncpy(toy.name, name.c_str(), sizeof(toy.name) - 1);
            toy.name[sizeof(toy.name) - 1] = '\0';
            
            // Заполняем остальные поля
            toy.price = price_dist(gen);
            toy.min_age = min_age_dist(gen);
            
            // Гарантируем, что max_age >= min_age
            do {
                toy.max_age = max_age_dist(gen);
            } while (toy.max_age < toy.min_age);

            file.write(reinterpret_cast<const char*>(&toy), sizeof(toy));
        }
        cout << "\nФайл " << filename << " создан с " << count << " игрушками" << endl;
    }

    // Вывести названия наиболее дорогих игрушек
    static void task3(const string& filename, double k) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        vector<Toy> toys;
        Toy toy;
        double max_price = 0.0;

        // Читаем все игрушки и находим максимальную цену
        while (file.read(reinterpret_cast<char*>(&toy), sizeof(toy))) {
            toys.push_back(toy);
            if (toy.price > max_price) {
                max_price = toy.price;
            }
        }

        if (toys.empty()) {
            cout << "Файл пуст!" << endl;
            return;
        }

        cout << "\nЗадание 3 (k = " << k << "):" << endl;
        cout << "Самая дорогая игрушка стоит: " << max_price << " руб." << endl;
        cout << "\nНаиболее дорогие игрушки (отличаются не более чем на " 
             << k << " руб.):" << endl;
        
        bool found = false;
        for (const auto& t : toys) {
            if (max_price - t.price <= k) {
                cout << "Название: " << t.name 
                     << ", Цена: " << t.price << " руб."
                     << ", Возраст: " << t.min_age << "-" << t.max_age << " лет" 
                     << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Нет игрушек, удовлетворяющих условию!" << endl;
        }
    }

    // ==================== ЗАДАНИЕ 4 ====================
    // Заполнение текстового файла целыми числами (по одному в строке)
    static void generateTextFile4(const string& filename, int count) {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        uniform_int_distribution<int> dist(1, 100);
        auto& gen = get_random_engine();

        for (int i = 0; i < count; i++) {
            file << dist(gen) << endl;
        }
        cout << "\nФайл " << filename << " создан с " << count << " числами" << endl;
    }

    // Подсчитать количество вхождений максимального элемента
    static void task4(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        int num;
        int max_val = numeric_limits<int>::min();
        int count = 0;

        while (file >> num) {
            if (num > max_val) {
                max_val = num;
                count = 1;
            } else if (num == max_val) {
                count++;
            }
        }

        cout << "\nЗадание 4:" << endl;
        cout << "Максимальный элемент: " << max_val << endl;
        cout << "Количество вхождений: " << count << endl;
    }

    // ==================== ЗАДАНИЕ 5 ====================
    // Заполнение текстового файла целыми числами (по несколько в строке)
    static void generateTextFile5(const string& filename, int total_numbers, int max_per_line) {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        uniform_int_distribution<int> num_dist(1, 100);
        uniform_int_distribution<int> count_dist(1, max_per_line);
        auto& gen = get_random_engine();

        int numbers_written = 0;
        while (numbers_written < total_numbers) {
            int numbers_in_line = min(count_dist(gen), total_numbers - numbers_written);
            
            for (int i = 0; i < numbers_in_line; i++) {
                file << num_dist(gen);
                if (i < numbers_in_line - 1) {
                    file << " ";
                }
            }
            file << endl;
            numbers_written += numbers_in_line;
        }
        cout << "\nФайл " << filename << " создан с " << total_numbers 
             << " числами (по несколько в строке)" << endl;
    }

    // Вычислить количество чётных элементов
    static void task5(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        int num;
        int even_count = 0;
        int total_count = 0;

        while (file >> num) {
            total_count++;
            if (num % 2 == 0) {
                even_count++;
            }
        }

        cout << "\nЗадание 5:" << endl;
        cout << "Всего чисел: " << total_count << endl;
        cout << "Чётных чисел: " << even_count << endl;
        cout << "Нечётных чисел: " << (total_count - even_count) << endl;
    }

    // ==================== ЗАДАНИЕ 6 ====================
    // Заполнение текстового файла строками
    static void generateTextFile6(const string& filename, int line_count) {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        vector<string> sample_lines = {
            "Сегодня старшеклассники выполняли ЕГЭ по информатике и ИКТ",
            "Программирование требует логического мышления",
            "Компьютерные технологии развиваются быстро",
            "Студенты изучают алгоритмы и структуры данных",
            "Искусственный интеллект - перспективное направление",
            "Кибербезопасность важна для защиты информации",
            "Веб-разработка включает фронтенд и бэкенд",
            "Мобильные приложения популярны среди пользователей",
            "Базы данных хранят структурированную информацию",
            "Сети и коммуникации соединяют компьютеры"
        };

        uniform_int_distribution<int> dist(0, sample_lines.size() - 1);
        auto& gen = get_random_engine();

        for (int i = 0; i < line_count; i++) {
            file << sample_lines[dist(gen)] << endl;
        }
        cout << "\nФайл " << filename << " создан с " << line_count << " строками" << endl;
    }

    // Переписать строки, содержащие заданную комбинацию символов
    static void task6(const string& input_filename, const string& output_filename, 
                      const string& pattern) {
        ifstream input(input_filename);
        ofstream output(output_filename);
        
        if (!input) {
            cerr << "Ошибка открытия файла: " << input_filename << endl;
            return;
        }
        if (!output) {
            cerr << "Ошибка создания файла: " << output_filename << endl;
            return;
        }

        string line;
        int matched_lines = 0;
        int total_lines = 0;

        cout << "\nЗадание 6 (поиск комбинации: \"" << pattern << "\"):" << endl;
        cout << "Строки, содержащие комбинацию \"" << pattern << "\":" << endl;

        while (getline(input, line)) {
            total_lines++;
            if (line.find(pattern) != string::npos) {
                output << line << endl;
                cout << line << endl;
                matched_lines++;
            }
        }

        cout << "\nВсего строк в исходном файле: " << total_lines << endl;
        cout << "Найдено строк с комбинацией \"" << pattern << "\": " << matched_lines << endl;
        cout << "Результат записан в файл: " << output_filename << endl;
    }

    // Основной метод для демонстрации всех заданий
    static void runAllTasks() {
        cout << "====== ЛАБОРАТОРНАЯ РАБОТА: ОБРАБОТКА ФАЙЛОВ ======" << endl;
        
        // Задание 1
        generateBinaryFile1("task1_data.bin", 20);
        task1("task1_data.bin");
        
        // Задание 2
        generateBinaryFile2("task2_data.bin", 12); // 12 чисел для матрицы 4x4 (16 элементов)
        task2("task2_data.bin");
        
        // Задание 3
        generateBinaryFile3("task3_data.bin", 8);
        task3("task3_data.bin", 500.0); // k = 500 рублей
        
        // Задание 4
        generateTextFile4("task4_data.txt", 25);
        task4("task4_data.txt");
        
        // Задание 5
        generateTextFile5("task5_data.txt", 30, 5);
        task5("task5_data.txt");
        
        // Задание 6
        generateTextFile6("task6_data.txt", 10);
        task6("task6_data.txt", "task6_result.txt", "форма");
        
        cout << "\n====== ВСЕ ЗАДАНИЯ ВЫПОЛНЕНЫ ======" << endl;
    }
};

int main() {
    // Установка локали для корректного отображения русских символов
    setlocale(LC_ALL, "Russian");
    
    // Запуск всех заданий
    FileTasks::runAllTasks();
    
    return 0;
}