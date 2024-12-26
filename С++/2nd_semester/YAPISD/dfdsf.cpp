#include <fstream>
#include <math.h>
#define PI 3.14159265358979323846
using namespace std;

enum axes { ox, oy, oz}; // Оси координат

class vector3D {
  double x, y, z; // Координаты вектора
public:
  vector3D() : x(0.0), y(0.0), z(0.0) {}                        // Конструктор по умолчанию
  vector3D(const vector3D& v) : x(v.x), y(v.y), z(v.z) {}       // Конструктор копирования
  vector3D(double x, double y, double z) : x(x), y(y), z(z) {}  // Конструктор инициализации
  ~vector3D() {}                                                // Деструктор
  friend ifstream& operator>> (ifstream&, vector3D&);           // Перегрузка операторов ввода и вывода
  friend ofstream& operator<< (ofstream&, const vector3D&);

  double module() const { return sqrt(x * x + y * y + z * z); } // Метод, вычисляющий модуль числа

  double angle(const vector3D& v) const {                       // Метод, вычисляющий угол между векторами (в градусах)
    return acos((x * v.x + y * v.y + z * v.z) / (this->module() * v.module())) * 180 / PI; 
  }
  
  double AxisAngle(axes key = ox) const {             // Метод, вычисляющий угол между вектором и осью координат (в градусах)
    vector3D xv(1, 0, 0), yv(0, 1, 0), zv(0, 0, 1); // Векторы базиса
    switch (key)
    {
    case ox: return this->angle(xv);
    case oy: return this->angle(yv);
    case oz: return this->angle(zv);
    default: return 0.0;
    }
  }
  double dircos(axes key = ox) const { // Метод, вычисляющий направляющий косинус
    switch (key)
    {
    case ox: return x / this->module();
    case oy: return y / this->module();
    case oz: return z / this->module();
    default: return 0.0;
    }
  }

  bool operator!= (const vector3D& v) const { return (x != v.x || y != v.y || z != v.z); } // Перегрузка операторов сравнения
  bool operator== (const vector3D& v) const { return !(*this != v); }
  bool operator< (const vector3D& v) const { return this->module() < v.module(); }
  bool operator> (const vector3D& v) const { return this->module() > v.module(); }
  bool operator<= (const vector3D& v) const { return !(*this > v); }
  bool operator>= (const vector3D& v) const { return !(*this < v); }
  vector3D& operator= (const vector3D& v) { // Перегрузка оператора присвоения
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }
  vector3D& operator+= (const vector3D& v) { // Перегрузка арифметических операторов
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  vector3D& operator-= (const vector3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  vector3D& operator*= (double v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }
  vector3D& operator/= (double v) {
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }
  const vector3D operator+ (const vector3D& v1) const {
    vector3D v2(*this);
    return v2 += v1;
  }
  const vector3D operator- (const vector3D& v1) const {
    vector3D v2(*this);
    return v2 -= v1;
  }
  const vector3D operator* (double val) const {
    vector3D v(*this);
    return v *= val;
  }
  const vector3D operator/ (double val) const {
    vector3D v(*this);
    return v /= val;
  }
};
ifstream& operator>> (ifstream& in, vector3D& v) {
  in >> v.x >> v.y >> v.z;
  return in;
}
ofstream& operator<< (ofstream& out, const vector3D& v) {
  out << '(' << v.x
    << ", " << v.y
    << ", " << v.z << ')';
  return out;
}
int main() {
  ifstream ifs("input.txt"); // Чтение из файла
  int key;
  vector3D v1, v2;
  ifs >> key;
  ifs >> v1 >> v2;
  ifs.close();
  
  ofstream ofs("output.txt"); // Запись в файл
  switch (key) {              // Вывод результата работы соответствуещего ключу метода
  case 1:
    ofs << v1.module();
    break;
  case 2:
    ofs << v1.AxisAngle(ox) << ' '
      << v1.AxisAngle(oy) << ' '
      << v1.AxisAngle(oz);
    break;
  case 3:
    ofs << v1 + v2 << ' ';
    ofs << v1 - v2 << ' ';
    ofs << v1 * 2 << ' ';
    ofs  << v1 / 2;
    break;
  case 4:
    ofs << v1.angle(v2);
    break;
  case 5:
    ofs << v1.dircos(ox) << ' '
      << v1.dircos(oy) << ' '
      << v1.dircos(oz);
    break;
  default:
    ofs << ((v1 > v2) ? "1-ый вектор больше 2-го" : "1-ый вектор меньше или равен 2-му");
    break;
  }
  ofs.close();
}