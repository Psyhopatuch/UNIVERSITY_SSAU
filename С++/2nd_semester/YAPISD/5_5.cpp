#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

enum AXES // Базисные векторы в системе координат
{
    OX,
    OY,
    OZ
};

class VECTOR_3D
{
    double x, y, z;

public:
    // 1 Модуль вектора
    long double mod() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    // 2 Углы с осями
    double angles_with_axes(AXES id = OX)
    {
        switch (id)
        {
        case OX:
        {
            VECTOR_3D oX(1, 0, 0); // Ось абсцисс
            return this->angle_between(oX);
        }
        case OY:
        {
            VECTOR_3D oY(0, 1, 0); // Ось ординат
            return this->angle_between(oY);
        }
        case OZ:
        {
            VECTOR_3D oZ(0, 0, 1); // Ось аппликат
            return this->angle_between(oZ);
        }
        default:
            return 0;
        }
    }

    // 3 Перегрузим арифметические операции
    VECTOR_3D &operator+=(const VECTOR_3D &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    VECTOR_3D &operator-=(const VECTOR_3D &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    VECTOR_3D &operator*=(double val)
    {
        x *= val;
        y *= val;
        z *= val;
        return *this;
    }

    VECTOR_3D &operator/=(double val)
    {
        x /= val;
        y /= val;
        z /= val;
        return *this;
    }

    const VECTOR_3D operator+(const VECTOR_3D &other) const
    {
        VECTOR_3D temp(*this);
        return temp += other;
    }

    const VECTOR_3D operator-(const VECTOR_3D &other) const
    {
        VECTOR_3D temp(*this);
        return temp -= other;
    }

    const VECTOR_3D operator*(double val) const
    {
        VECTOR_3D temp(*this);
        return temp *= val;
    }

    const VECTOR_3D operator/(double val) const
    {
        VECTOR_3D temp(*this);
        return temp /= val;
    }

    // 4 Угол между двумя векторами
    double angle_between(VECTOR_3D other)
    {
        return acosl((x * other.x + y * other.y + z * other.z) / (mod() * other.mod())) * 180 / M_PI;
    }

    // 5 Направляющие косинусы
    double guid_cos(AXES id = OX)
    {
        switch (id)
        {
        case OX:
            return x / mod();
        case OY:
            return y / mod();
        case OZ:
            return z / mod();
        default:
            return 0;
        }
    }

    // Перегрузим операторы сравнения
    bool operator<(const VECTOR_3D &other) const { return this->mod() < other.mod(); }
    bool operator>(const VECTOR_3D &other) const { return this->mod() > other.mod(); }
    bool operator<=(const VECTOR_3D &other) const { return !(*this > other); }
    bool operator>=(const VECTOR_3D &other) const { return !(*this < other); }
    bool operator!=(const VECTOR_3D &other) const { return (x != other.x || y != other.y || z != other.z); }
    bool operator==(const VECTOR_3D &other) const { return !(*this != other); }

    // Перегрузим оператор присвоения
    VECTOR_3D &operator=(const VECTOR_3D &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    VECTOR_3D() : x(0), y(0), z(0){};                                         // Конструктор по умолчанию
    VECTOR_3D(double a, double b, double c) : x(a), y(b), z(c) {}             // Конструктор инициализации
    VECTOR_3D(const VECTOR_3D &other) : x(other.x), y(other.y), z(other.z) {} // Конструктор копирования
    ~VECTOR_3D() {}                                                           // Деструктор

    // Дружественные классу функции
    friend istream &operator>>(istream &in, VECTOR_3D &obj);
    friend ostream &operator<<(ostream &out, const VECTOR_3D &obj);
};

// Перегрузка оператора ввода
istream &operator>>(istream &in, VECTOR_3D &obj)
{
    in >> obj.x >> obj.y >> obj.z;
    return in;
}

// Перегрузка оператора вывода
ostream &operator<<(ostream &out, const VECTOR_3D &obj)
{
    out << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
    return out;
}

int main()
{
    ifstream fin("input.txt");             // Откроем поток ввода
    ofstream fout("output.txt");           // Откроем поток вывода
    if (!fin.is_open() && !fout.is_open()) // Потоки не открылись--переидём к возвращению значений
        return 1;
    unsigned int key = 1; // Переменная, хранящая ключ для выбора метода
    fin >> key;           // По условию первое число в файле--ключ

    switch (key)
    {
    case 1: // Модуль вектора
    {
        VECTOR_3D vec;
        fin >> vec;
        fout << vec.mod();
        break;
    }
    case 2: // Углы с осями
    {
        VECTOR_3D vec;
        fin >> vec;
        fout << vec.angles_with_axes() << ' ' << vec.angles_with_axes(OY) << ' ' << vec.angles_with_axes(OZ);
        break;
    }
    case 3: // Арифметика
    {
        VECTOR_3D vec1, vec2;
        fin >> vec1 >> vec2;
        fout << vec1 + vec2 << ' ';
        fout << vec1 - vec2 << ' ';
        fout << vec1 * 2 << ' ';
        fout << vec1 / 2;
        break;
    }
    case 4: // Угол между двумя векторами
    {
        VECTOR_3D vec1, vec2;
        fin >> vec1 >> vec2;
        fout << vec1.angle_between(vec2);
        break;
    }
    case 5: // Направляющие косинусы
    {
        VECTOR_3D vec;
        fin >> vec;
        fout << vec.guid_cos() << ' ' << vec.guid_cos(OY) << ' ' << vec.guid_cos(OZ);
        break;
    }
    case 6: // Проверка операций сравнения
    {
        VECTOR_3D vec1, vec2;
        fin >> vec1 >> vec2;
        if (vec1 > vec2)
        {
            fout << "1-ый вектор больше 2-го";
            break;
        }
        if (vec1 < vec2)
        {
            fout << "1-ый вектор меньше 2-го";
            break;
        }
        fout << "1-ый вектор равен 2-му";
        break;
    }
    default: // Если ключ не верный, напишем сообщение об ошибке
        fout << "Exseption: incorrect key";
        break;
    }
    fin.close();  // Закроем поток ввода
    fout.close(); // Закроем поток вывода
    return 0;     // Вернём ноль
}