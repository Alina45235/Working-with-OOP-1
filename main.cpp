#include "Triangle.h"
#include <locale.h>


 int main() {
     setlocale(0, "Russian");

     double x1, y1, x2, y2, x3, y3;

     cout << "Введите координаты первого треугольника (x1 y1 x2 y2 x3 y3): ";
     cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
     Triangle triangle1(x1, y1, x2, y2, x3, y3);

     cout << "Введите координаты второго треугольника (x1 y1 x2 y2 x3 y3): ";
     cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
     Triangle triangle2(x1, y1, x2, y2, x3, y3);

     cout << "\n=== ПЕРВЫЙ ТРЕУГОЛЬНИК ===" << endl;
     triangle1.exists();
     triangle1.center_Gravity();
     triangle1.print_area();
     triangle1.perimeter();

     cout << "\n=== ВТОРОЙ ТРЕУГОЛЬНИК ===" << endl;
     triangle2.exists();
     triangle2.center_Gravity();
     triangle2.print_area();
     triangle2.perimeter();

     cout << "\n=== СРАВНЕНИЕ ПЛОЩАДЕЙ ===" << endl;
     triangle1.compare_area(triangle2);

     cout << "\n=== ПЕРЕМЕЩЕНИЕ ПЕРВОГО ТРЕУГОЛЬНИКА ===" << endl;
     double dx_1, dy_1;
     cout << "Введите смещение (dx dy): ";
     cin >> dx_1 >> dy_1;
     triangle1.move_triangle(dx_1, dy_1);

     cout << "\n=== ПЕРЕМЕЩЕНИЕ ВТОРОГО ТРЕУГОЛЬНИКА ===" << endl;
     double dx_2, dy_2;
     cout << "Введите смещение (dx dy): ";
     cin >> dx_2 >> dy_2;
     triangle2.move_triangle(dx_2, dy_2);

     cout << "\n=== ПРОВЕРКА ПЕРЕСЕЧЕНИЯ ===" << endl;
     triangle1.intersection(triangle2);

     return 0;
 }
