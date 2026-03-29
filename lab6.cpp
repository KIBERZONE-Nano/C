#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <climits>
#include <sstream>

using namespace std;

/// <summary>
/// Класс, реализующий функционал неупорядоченного множества (HashSet)
/// </summary>
/// <typeparam name="T">Тип элементов множества</typeparam>
template <typename T>
class MyHashSet {
private:
    T* data;           // Массив для хранения элементов
    int capacity;      // Вместимость массива
    int size;          // Текущее количество элементов

    /// <summary>
    /// Увеличивает вместимость массива при необходимости
    /// </summary>
    void resize() {
        if (size >= capacity) {
            int newCapacity = capacity == 0 ? 10 : capacity * 2;
            T* newData = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

    /// <summary>
    /// Находит индекс элемента в массиве
    /// </summary>
    /// <param name="item">Элемент для поиска</param>
    /// <returns>Индекс элемента или -1 если не найден</returns>
    int findIndex(const T& item) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == item) {
                return i;
            }
        }
        return -1;
    }

    /// <summary>
    /// Копирует данные из другого объекта
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    void copyFrom(const MyHashSet& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    /// <summary>
    /// Освобождает выделенную память
    /// </summary>
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }

public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    MyHashSet() : data(nullptr), capacity(0), size(0) {}

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    MyHashSet(const MyHashSet& other) : data(nullptr), capacity(0), size(0) {
        copyFrom(other);
    }

    /// <summary>
    /// Оператор присваивания
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    /// <returns>Ссылку на текущий объект</returns>
    MyHashSet& operator=(const MyHashSet& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    /// <summary>
    /// Деструктор
    /// </summary>
    ~MyHashSet() {
        clear();
    }

    /// <summary>
    /// Добавляет элемент в множество
    /// </summary>
    /// <param name="item">Элемент для добавления</param>
    void Add(const T& item) {
        if (!Contains(item)) {
            resize();
            data[size++] = item;
        }
    }

    /// <summary>
    /// Удаляет элемент из множества
    /// </summary>
    /// <param name="item">Элемент для удаления</param>
    /// <returns>true если элемент был удален, false если элемент не найден</returns>
    bool Remove(const T& item) {
        int index = findIndex(item);
        if (index != -1) {
            // Перемещаем последний элемент на место удаляемого
            data[index] = data[--size];
            return true;
        }
        return false;
    }

    /// <summary>
    /// Проверяет наличие элемента в множестве
    /// </summary>
    /// <param name="item">Элемент для проверки</param>
    /// <returns>true если элемент присутствует, false в противном случае</returns>
    bool Contains(const T& item) const {
        return findIndex(item) != -1;
    }

    /// <summary>
    /// Объединяет текущее множество с другим множеством
    /// </summary>
    /// <param name="other">Другое множество для объединения</param>
    /// <returns>Новое множество - объединение текущего и другого</returns>
    MyHashSet Union(const MyHashSet& other) const {
        MyHashSet result = *this;  // Использует конструктор копирования
        for (int i = 0; i < other.size; i++) {
            result.Add(other.data[i]);
        }
        return result;
    }

    /// <summary>
    /// Возвращает разность текущего множества и другого множества
    /// </summary>
    /// <param name="other">Другое множество</param>
    /// <returns>Новое множество - элементы текущего, которых нет в другом</returns>
    MyHashSet Except(const MyHashSet& other) const {
        MyHashSet result;
        for (int i = 0; i < size; i++) {
            if (!other.Contains(data[i])) {
                result.Add(data[i]);
            }
        }
        return result;
    }

    /// <summary>
    /// Возвращает пересечение текущего множества с другим множеством
    /// </summary>
    /// <param name="other">Другое множество</param>
    /// <returns>Новое множество - общие элементы текущего и другого</returns>
    MyHashSet Intersect(const MyHashSet& other) const {
        MyHashSet result;
        for (int i = 0; i < size; i++) {
            if (other.Contains(data[i])) {
                result.Add(data[i]);
            }
        }
        return result;
    }

    /// <summary>
    /// Возвращает текущий размер множества
    /// </summary>
    /// <returns>Количество элементов в множестве</returns>
    int Size() const {
        return size;
    }

    /// <summary>
    /// Оператор для вывода множества в поток
    /// </summary>
    /// <param name="os">Выходной поток</param>
    /// <param name="set">Множество для вывода</param>
    /// <returns>Ссылку на выходной поток</returns>
    friend ostream& operator<<(ostream& os, const MyHashSet<T>& set) {
        os << "{ ";
        for (int i = 0; i < set.size; i++) {
            os << set.data[i];
            if (i < set.size - 1) os << ", ";
        }
        os << " }";
        return os;
    }
};

/// <summary>
/// Класс, реализующий функционал словаря (Dictionary)
/// </summary>
/// <typeparam name="K">Тип ключей</typeparam>
/// <typeparam name="V">Тип значений</typeparam>
template <typename K, typename V>
class MyDictionary {
private:
    struct KeyValuePair {
        K key;
        V value;
        bool occupied;
        
        KeyValuePair() : occupied(false) {}
    };
    
    KeyValuePair* data;     // Массив для хранения пар ключ-значение
    int capacity;           // Вместимость массива
    int size;               // Текущее количество элементов
    
    /// <summary>
    /// Увеличивает вместимость массива при необходимости
    /// </summary>
    void resize() {
        if (size >= capacity * 0.7) {  // 70% заполнения
            int newCapacity = capacity == 0 ? 10 : capacity * 2;
            KeyValuePair* newData = new KeyValuePair[newCapacity];
            
            // Перехеширование всех элементов
            for (int i = 0; i < capacity; i++) {
                if (data[i].occupied) {
                    int index = hashFunction(data[i].key) % newCapacity;
                    while (newData[index].occupied) {
                        index = (index + 1) % newCapacity;
                    }
                    newData[index] = data[i];
                }
            }
            
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }
    
    /// <summary>
    /// Хэш-функция для ключа
    /// </summary>
    /// <param name="key">Ключ</param>
    /// <returns>Хэш-значение</returns>
    int hashFunction(const K& key) const {
        hash<K> hashFunc;
        size_t hashValue = hashFunc(key);
        return static_cast<int>(hashValue);
    }
    
    /// <summary>
    /// Копирует данные из другого объекта
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    void copyFrom(const MyDictionary& other) {
        capacity = other.capacity;
        size = other.size;
        data = new KeyValuePair[capacity];
        
        for (int i = 0; i < capacity; i++) {
            if (other.data[i].occupied) {
                data[i] = other.data[i];
            }
        }
    }
    
    /// <summary>
    /// Освобождает выделенную память
    /// </summary>
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }
    
public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    MyDictionary() : data(nullptr), capacity(0), size(0) {
        resize();  // Инициализируем начальную емкость
    }
    
    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    MyDictionary(const MyDictionary& other) : data(nullptr), capacity(0), size(0) {
        copyFrom(other);
    }
    
    /// <summary>
    /// Оператор присваивания
    /// </summary>
    /// <param name="other">Другой объект для копирования</param>
    /// <returns>Ссылку на текущий объект</returns>
    MyDictionary& operator=(const MyDictionary& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    /// <summary>
    /// Деструктор
    /// </summary>
    ~MyDictionary() {
        clear();
    }
    
    /// <summary>
    /// Добавляет пару ключ-значение в словарь
    /// </summary>
    /// <param name="key">Ключ</param>
    /// <param name="value">Значение</param>
    /// <returns>true если добавлено успешно, false если ключ уже существует</returns>
    bool Add(const K& key, const V& value) {
        if (ContainsKey(key)) {
            return false;  // Ключ уже существует
        }
        
        resize();
        
        int index = hashFunction(key) % capacity;
        while (data[index].occupied) {
            index = (index + 1) % capacity;
        }
        
        data[index].key = key;
        data[index].value = value;
        data[index].occupied = true;
        size++;
        
        return true;
    }
    
    /// <summary>
    /// Удаляет элемент по ключу
    /// </summary>
    /// <param name="key">Ключ для удаления</param>
    /// <returns>true если элемент удален, false если ключ не найден</returns>
    bool Remove(const K& key) {
        int index = findIndex(key);
        if (index != -1) {
            data[index].occupied = false;
            size--;
            return true;
        }
        return false;
    }
    
    /// <summary>
    /// Проверяет наличие ключа в словаре
    /// </summary>
    /// <param name="key">Ключ для проверки</param>
    /// <returns>true если ключ существует, false в противном случае</returns>
    bool ContainsKey(const K& key) const {
        return findIndex(key) != -1;
    }
    
    /// <summary>
    /// Получает значение по ключу
    /// </summary>
    /// <param name="key">Ключ</param>
    /// <returns>Значение, соответствующее ключу</returns>
    V Get(const K& key) const {
        int index = findIndex(key);
        if (index != -1) {
            return data[index].value;
        }
        throw runtime_error("Key not found");
    }
    
    /// <summary>
    /// Устанавливает значение по ключу (добавляет или обновляет)
    /// </summary>
    /// <param name="key">Ключ</param>
    /// <param name="value">Значение</param>
    void Set(const K& key, const V& value) {
        int index = findIndex(key);
        if (index != -1) {
            data[index].value = value;
        } else {
            Add(key, value);
        }
    }
    
    /// <summary>
    /// Возвращает текущий размер словаря
    /// </summary>
    /// <returns>Количество элементов в словаре</returns>
    int Size() const {
        return size;
    }
    
private:
    /// <summary>
    /// Находит индекс элемента по ключу
    /// </summary>
    /// <param name="key">Ключ для поиска</param>
    /// <returns>Индекс элемента или -1 если не найден</returns>
    int findIndex(const K& key) const {
        if (capacity == 0) return -1;
        
        int index = hashFunction(key) % capacity;
        int startIndex = index;
        
        while (data[index].occupied) {
            if (data[index].key == key) {
                return index;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break;
        }
        
        return -1;
    }
};

/// <summary>
/// Базовый класс Person, представляющий человека с именем
/// </summary>
class Person {
protected:
    string name;
    
public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    Person() : name("Unknown") {}
    
    /// <summary>
    /// Конструктор с именем
    /// </summary>
    /// <param name="name">Имя человека</param>
    Person(const string& name) : name(name) {}
    
    /// <summary>
    /// Виртуальный деструктор
    /// </summary>
    virtual ~Person() {}
    
    /// <summary>
    /// Получает имя человека
    /// </summary>
    /// <returns>Имя человека</returns>
    virtual string GetName() const {
        return name;
    }
    
    /// <summary>
    /// Устанавливает имя человека
    /// </summary>
    /// <param name="newName">Новое имя</param>
    virtual void SetName(const string& newName) {
        name = newName;
    }
    
    /// <summary>
    /// Выводит информацию о человеке
    /// </summary>
    virtual void PrintInfo() const {
        cout << "Имя: " << name << endl;
    }
};

/// <summary>
/// Класс, представляющий человека с датой рождения
/// </summary>
class PersonWithBirthday : public Person {
private:
    int day;
    int month;
    int year;
    
    /// <summary>
    /// Проверяет корректность даты рождения
    /// </summary>
    /// <returns>true если дата корректна, false в противном случае</returns>
    bool isValidDate() const {
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        
        // Проверка дней в месяце
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Учет високосного года
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeap) daysInMonth[1] = 29;
        }
        
        return day <= daysInMonth[month - 1];
    }
    
public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    PersonWithBirthday() : Person(), day(1), month(1), year(2000) {}
    
    /// <summary>
    /// Конструктор с параметрами
    /// </summary>
    /// <param name="name">Имя человека</param>
    /// <param name="day">День рождения</param>
    /// <param name="month">Месяц рождения</param>
    /// <param name="year">Год рождения</param>
    PersonWithBirthday(const string& name, int day, int month, int year)
        : Person(name), day(day), month(month), year(year) {
        if (!isValidDate()) {
            this->day = 1;
            this->month = 1;
            this->year = 2000;
        }
    }
    
    /// <summary>
    /// Получает возраст человека
    /// </summary>
    /// <returns>Возраст в годах</returns>
    int GetAge() const {
        time_t now = time(0);
        tm* currentTime = localtime(&now);
        int currentYear = currentTime->tm_year + 1900;
        int currentMonth = currentTime->tm_mon + 1;
        int currentDay = currentTime->tm_mday;
        
        int age = currentYear - year;
        
        // Если день рождения еще не наступил в этом году, уменьшаем возраст на 1
        if (currentMonth < month || (currentMonth == month && currentDay < day)) {
            age--;
        }
        
        return age;
    }
    
    /// <summary>
    /// Получает знак зодиака
    /// </summary>
    /// <returns>Строку с названием знака зодиака</returns>
    string GetZodiacSign() const {
        // Границы знаков зодиака
        if ((month == 3 && day >= 21) || (month == 4 && day <= 19)) return "Овен";
        if ((month == 4 && day >= 20) || (month == 5 && day <= 20)) return "Телец";
        if ((month == 5 && day >= 21) || (month == 6 && day <= 20)) return "Близнецы";
        if ((month == 6 && day >= 21) || (month == 7 && day <= 22)) return "Рак";
        if ((month == 7 && day >= 23) || (month == 8 && day <= 22)) return "Лев";
        if ((month == 8 && day >= 23) || (month == 9 && day <= 22)) return "Дева";
        if ((month == 9 && day >= 23) || (month == 10 && day <= 22)) return "Весы";
        if ((month == 10 && day >= 23) || (month == 11 && day <= 21)) return "Скорпион";
        if ((month == 11 && day >= 22) || (month == 12 && day <= 21)) return "Стрелец";
        if ((month == 12 && day >= 22) || (month == 1 && day <= 19)) return "Козерог";
        if ((month == 1 && day >= 20) || (month == 2 && day <= 18)) return "Водолей";
        return "Рыбы";
    }
    
    /// <summary>
    /// Получает дату рождения в формате строки
    /// </summary>
    /// <returns>Дату рождения в формате ДД.ММ.ГГГГ</returns>
    string GetBirthDate() const {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
    
    /// <summary>
    /// Устанавливает дату рождения
    /// </summary>
    /// <param name="day">День рождения</param>
    /// <param name="month">Месяц рождения</param>
    /// <param name="year">Год рождения</param>
    void SetBirthDate(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
        if (!isValidDate()) {
            this->day = 1;
            this->month = 1;
            this->year = 2000;
        }
    }
    
    /// <summary>
    /// Выводит информацию о человеке
    /// </summary>
    void PrintInfo() const override {
        Person::PrintInfo();
        cout << "Дата рождения: " << GetBirthDate() << endl;
        cout << "Возраст: " << GetAge() << " лет" << endl;
        cout << "Знак зодиака: " << GetZodiacSign() << endl;
    }
};

/// <summary>
/// Функция для решения задачи 1 (HashSet)
/// </summary>
void solveTask1() {
    cout << "=== Задание 1: Анализ предпочтений в шоколаде ===" << endl;
    
    // Создаем множества для сладкоежек
    MyHashSet<string> sweetTooth1, sweetTooth2, sweetTooth3;
    
    // Добавляем предпочтения первой сладкоежки
    sweetTooth1.Add("Alpen Gold");
    sweetTooth1.Add("Milka");
    sweetTooth1.Add("Babaevsky");
    
    // Добавляем предпочтения второй сладкоежки
    sweetTooth2.Add("Milka");
    sweetTooth2.Add("Russia");
    sweetTooth2.Add("Alpen Gold");
    
    // Добавляем предпочтения третьей сладкоежки
    sweetTooth3.Add("Babaevsky");
    sweetTooth3.Add("Alpen Gold");
    sweetTooth3.Add("Ritter Sport");
    
    // Создаем общее множество всех шоколадов
    MyHashSet<string> allChocolates;
    allChocolates.Add("Alpen Gold");
    allChocolates.Add("Milka");
    allChocolates.Add("Babaevsky");
    allChocolates.Add("Russia");
    allChocolates.Add("Ritter Sport");
    allChocolates.Add("Korkunov");
    
    cout << "Все виды шоколада: " << allChocolates << endl;
    
    // Анализируем каждый шоколад
    cout << "\nРезультаты анализа:" << endl;
    
    // Для анализа нужен доступ к элементам, добавим временную функцию
    // В реальной реализации нужно было бы добавить итератор, но по условию нельзя обращаться по индексу
    // Для решения задачи создадим массив с названиями
    string chocolates[] = {"Alpen Gold", "Milka", "Babaevsky", "Russia", "Ritter Sport", "Korkunov"};
    
    for (const auto& chocolate : chocolates) {
        int likes = 0;
        if (sweetTooth1.Contains(chocolate)) likes++;
        if (sweetTooth2.Contains(chocolate)) likes++;
        if (sweetTooth3.Contains(chocolate)) likes++;
        
        cout << chocolate << ": ";
        if (likes == 3) {
            cout << "нравится всем сладкоежкам" << endl;
        } else if (likes > 0) {
            cout << "нравится " << likes << " сладкоежкам" << endl;
        } else {
            cout << "не нравится никому" << endl;
        }
    }
    
    // Демонстрация операций с множествами
    cout << "\nДемонстрация операций с множествами:" << endl;
    MyHashSet<string> unionSet = sweetTooth1.Union(sweetTooth2).Union(sweetTooth3);
    cout << "Объединение всех предпочтений: " << unionSet << endl;
    
    MyHashSet<string> common = sweetTooth1.Intersect(sweetTooth2);
    cout << "Общие у первой и второй сладоежки: " << common << endl;
    
    MyHashSet<string> onlyFirst = sweetTooth1.Except(sweetTooth2);
    cout << "Только у первой сладоежки: " << onlyFirst << endl;
}

/// <summary>
/// Функция для решения задачи 2 (Dictionary)
/// </summary>
void solveTask2() {
    cout << "\n=== Задание 2: Мониторинг цен на сметану ===" << endl;
    
    // Структура для хранения информации о минимальной цене
    struct PriceInfo {
        int minPrice;
        int count;
        
        PriceInfo() : minPrice(INT_MAX), count(0) {}
        PriceInfo(int price) : minPrice(price), count(1) {}
    };
    
    // Создаем словарь для хранения информации по жирности
    MyDictionary<int, PriceInfo> priceData;
    
    // Чтение данных из файла
    ifstream inputFile("sour_cream.txt");
    if (!inputFile.is_open()) {
        // Если файла нет, создаем тестовые данные
        cout << "Файл sour_cream.txt не найден. Используются тестовые данные." << endl;
        
        // Тестовые данные
        string testData[] = {
            "Перекресток Короленко 25 90",
            "Магнит Ленина 15 85",
            "Пятерочка Гагарина 20 95",
            "Дикси Пушкина 25 90",
            "Магнит Советская 15 80",
            "Пятерочка Мира 20 95",
            "Перекресток Центральная 25 88",
            "Магнит Гагарина 15 85",
            "Дикси Ленина 20 92",
            "Пятерочка Короленко 25 90"
        };
        
        for (const auto& line : testData) {
            stringstream ss(line);
            string store, street;
            int fat, price;
            
            ss >> store >> street >> fat >> price;
            
            if (priceData.ContainsKey(fat)) {
                PriceInfo info = priceData.Get(fat);
                if (price < info.minPrice) {
                    info.minPrice = price;
                    info.count = 1;
                } else if (price == info.minPrice) {
                    info.count++;
                }
                priceData.Set(fat, info);
            } else {
                priceData.Add(fat, PriceInfo(price));
            }
        }
    } else {
        // Чтение из файла
        int n;
        inputFile >> n;
        inputFile.ignore(); // Игнорируем перевод строки
        
        for (int i = 0; i < n; i++) {
            string line;
            getline(inputFile, line);
            
            stringstream ss(line);
            string store, street;
            int fat, price;
            
            ss >> store >> street >> fat >> price;
            
            if (priceData.ContainsKey(fat)) {
                PriceInfo info = priceData.Get(fat);
                if (price < info.minPrice) {
                    info.minPrice = price;
                    info.count = 1;
                } else if (price == info.minPrice) {
                    info.count++;
                }
                priceData.Set(fat, info);
            } else {
                priceData.Add(fat, PriceInfo(price));
            }
        }
        inputFile.close();
    }
    
    // Вывод результатов
    cout << "Результаты мониторинга цен:" << endl;
    
    int fats[] = {15, 20, 25};
    for (int fat : fats) {
        if (priceData.ContainsKey(fat)) {
            PriceInfo info = priceData.Get(fat);
            cout << "Сметана " << fat << "%: минимальная цена " << info.minPrice 
                 << " руб., магазинов: " << info.count << endl;
        } else {
            cout << "Сметана " << fat << "%: не продается" << endl;
        }
    }
    
    // Вывод в требуемом формате
    cout << "\nКоличество магазинов с минимальной ценой: ";
    for (int fat : fats) {
        if (priceData.ContainsKey(fat)) {
            PriceInfo info = priceData.Get(fat);
            cout << info.count << " ";
        } else {
            cout << "0 ";
        }
    }
    cout << endl;
}

/// <summary>
/// Функция для решения задачи 3 (Наследование)
/// </summary>
void solveTask3() {
    cout << "\n=== Задание 3: Люди с датой рождения ===" << endl;
    
    // Создаем несколько людей с датами рождения
    PersonWithBirthday person1("Иван Иванов", 15, 5, 1990);
    PersonWithBirthday person2("Мария Петрова", 23, 7, 1985);
    PersonWithBirthday person3("Алексей Сидоров", 4, 2, 2000);
    PersonWithBirthday person4("Елена Козлова", 30, 11, 1995);
    
    // Создаем массив указателей на базовый класс
    Person* people[] = {&person1, &person2, &person3, &person4};
    
    // Выводим информацию о каждом человеке
    for (int i = 0; i < 4; i++) {
        cout << "\n--- Человек " << (i + 1) << " ---" << endl;
        people[i]->PrintInfo();
        
        // Для демонстрации работы с производным классом
        PersonWithBirthday* personWithBirthday = dynamic_cast<PersonWithBirthday*>(people[i]);
        if (personWithBirthday) {
            cout << "Дата рождения (через метод): " << personWithBirthday->GetBirthDate() << endl;
            cout << "Знак зодиака: " << personWithBirthday->GetZodiacSign() << endl;
            cout << "Возраст: " << personWithBirthday->GetAge() << " лет" << endl;
        }
    }
    
    // Демонстрация полиморфизма
    cout << "\n=== Демонстрация полиморфизма ===" << endl;
    Person regularPerson("Обычный человек");
    PersonWithBirthday specialPerson("Человек с днем рождения", 1, 1, 2000);
    
    Person* polyPeople[] = {&regularPerson, &specialPerson};
    
    for (int i = 0; i < 2; i++) {
        cout << "\n--- Через указатель на базовый класс ---" << endl;
        polyPeople[i]->PrintInfo();
    }
}

/// <summary>
/// Основная функция программы
/// </summary>
/// <returns>Код завершения программы</returns>
int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "Лабораторная работа: Реализация классов HashSet, Dictionary и наследования" << endl;
    cout << "=========================================================================" << endl;
    
    try {
        solveTask1();
        solveTask2();
        solveTask3();
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    cout << "\n=========================================================================" << endl;
    cout << "Все задания выполнены успешно!" << endl;
    
    return 0;
}