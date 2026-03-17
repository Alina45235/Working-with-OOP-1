#include "Triangle.h"

// Конструктор с параметрами
Triangle::Triangle(double X1, double Y1, double X2, double Y2, double X3, double Y3) {
    x1 = X1;
    y1 = Y1;
    x2 = X2;
    y2 = Y2;
    x3 = X3;
    y3 = Y3;
}

// Вспомогательный метод для вычисления длины стороны треугольника
double Triangle::len_side(double x_1, double y_1, double x_2, double y_2) {
    return sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
}

// Метод проверки на существование треугольника
void Triangle::exists() {
    try {
        double a = len_side(x1, y1, x2, y2);
        double b = len_side(x2, y2, x3, y3);
        double c = len_side(x1, y1, x3, y3);

        if ((a + b > c) && (a + c > b) && (b + c > a)) {
            cout << "Треугольник существует" << endl;
        }
        else {
            throw 1; // Добавляем исключение если треугольник не существует
        }
    }
    catch (int e) {
        cout << "Треугольник не существует" << endl;
    }
}

// Метод определения центра тяжести по x и по y
void Triangle::center_Gravity() {
    double cx = (x1 + x2 + x3) / 3;
    double cy = (y1 + y2 + y3) / 3;

    cout << "Центр тяжести по х: " << cx << endl;
    cout << "Центр тяжести по y: " << cy << endl;
}

// Метод рассчета площади треугольника
double Triangle::area() {
    double a = len_side(x1, y1, x2, y2);
    double b = len_side(x2, y2, x3, y3);
    double c = len_side(x3, y3, x1, y1);
    double p = (a + b + c) / 2;            // Рассчет полупериметра

    double res = sqrt(p * (p - a) * (p - b) * (p - c));
    return res;
}

// Метод вывода в консоль площади треугольника
void Triangle::print_area() {
    cout << "Площадь треугольника: " << area() << endl;
}

// Метод рассчета периметра
void Triangle::perimeter() {
    double a = len_side(x1, y1, x2, y2);
    double b = len_side(x2, y2, x3, y3);
    double c = len_side(x3, y3, x1, y1);

    double res = a + b + c;

    cout << "Периметр треугольника: " << res << endl;
}

// Метод сравнения площадей треугольников
void Triangle::compare_area(Triangle other) {
    double first_area = area();
    double second_area = other.area();

    if (first_area > second_area) {
        cout << "Первый треугольник больше второго" << endl;
    }
    else if (first_area < second_area) {
        cout << "Первый треугольник меньше второго" << endl;
    }
    else {
        cout << "Треугольники равны" << endl;
    }
}

// Метод рассчета перемещения на x, y координат
void Triangle::move_triangle(double dx, double dy) {
    double new_x1 = x1 + dx;
    double new_y1 = y1 + dy;
    double new_x2 = x2 + dx;
    double new_y2 = y2 + dy;
    double new_x3 = x3 + dx;
    double new_y3 = y3 + dy;

    cout << " Результат перемещения на (" << dx << ", " << dy << "):" << endl;
    cout << "Новые координаты:" << endl;
    cout << "Вершина 1: (" << new_x1 << ", " << new_y1 << ")" << endl;
    cout << "Вершина 2: (" << new_x2 << ", " << new_y2 << ")" << endl;
    cout << "Вершина 3: (" << new_x3 << ", " << new_y3 << ")" << endl;
    cout << endl;
}

// Метод проверки пересечения двух треугольников
void Triangle::intersection(Triangle other) {
    // Проверка всех комбинаций сторон (вызов метода проверки пересечения отрезков)
    // Математически: проверяем пересечение каждой стороны первого треугольника
    // с каждой стороной второго треугольника (3×3 = 9 проверок)
    if (segmentsIntersect(x1, y1, x2, y2, other.x1, other.y1, other.x2, other.y2) ||
        segmentsIntersect(x1, y1, x2, y2, other.x2, other.y2, other.x3, other.y3) ||
        segmentsIntersect(x1, y1, x2, y2, other.x3, other.y3, other.x1, other.y1) ||

        segmentsIntersect(x2, y2, x3, y3, other.x1, other.y1, other.x2, other.y2) ||
        segmentsIntersect(x2, y2, x3, y3, other.x2, other.y2, other.x3, other.y3) ||
        segmentsIntersect(x2, y2, x3, y3, other.x3, other.y3, other.x1, other.y1) ||

        segmentsIntersect(x3, y3, x1, y1, other.x1, other.y1, other.x2, other.y2) ||
        segmentsIntersect(x3, y3, x1, y1, other.x2, other.y2, other.x3, other.y3) ||
        segmentsIntersect(x3, y3, x1, y1, other.x3, other.y3, other.x1, other.y1) ||

        isInside(other) || other.isInside(*this)) { // Проверка вложения треугольников

        cout << "Треугольники пересекаются" << endl;
    }
    else {
        cout << "Треугольники не пересекаются" << endl;
    }
}

// Вспомогательный метод проверки пересечения двух отрезков
// Математическая основа: алгоритм проверки пересечения отрезков с помощью векторных произведений
// Отрезок AB (A(x1,y1) - B(x2,y2)) и отрезок CD (C(x3,y3) - D(x4,y4))
bool Triangle::segmentsIntersect(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy) {
    // Вычисляем векторные произведения для определения взаимного расположения точек
    // d1 = (B-A) × (C-A) - определяет с какой стороны от AB находится точка C
    double d1 = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax);
    // d2 = (B-A) × (D-A) - определяет с какой стороны от AB находится точка D
    double d2 = (Bx - Ax) * (Dy - Ay) - (By - Ay) * (Dx - Ax);
    // d3 = (D-C) × (A-C) - определяет с какой стороны от CD находится точка A
    double d3 = (Dx - Cx) * (Ay - Cy) - (Dy - Cy) * (Ax - Cx);
    // d4 = (D-C) × (B-C) - определяет с какой стороны от CD находится точка B
    double d4 = (Dx - Cx) * (By - Cy) - (Dy - Cy) * (Bx - Cx);

    // Отрезки пересекаются если точки C и D лежат по разные стороны от AB (d1*d2 < 0)
    // и точки A и B лежат по разные стороны от CD (d3*d4 < 0)
    if (d1 * d2 < 0 && d3 * d4 < 0)
        return true;

    // Проверяем особые случаи, когда точки лежат на отрезках (коллинеарность)
    // Если точка C лежит на отрезке AB (d1 = 0) и находится между A и B
    if (d1 == 0 && onSegment(Ax, Ay, Bx, By, Cx, Cy))
        return true;
    // Если точка D лежит на отрезке AB (d2 = 0) и находится между A и B
    if (d2 == 0 && onSegment(Ax, Ay, Bx, By, Dx, Dy))
        return true;
    // Если точка A лежит на отрезке CD (d3 = 0) и находится между C и D
    if (d3 == 0 && onSegment(Cx, Cy, Dx, Dy, Ax, Ay))
        return true;
    // Если точка B лежит на отрезке CD (d4 = 0) и находится между C и D
    if (d4 == 0 && onSegment(Cx, Cy, Dx, Dy, Bx, By))
        return true;

    return false;
}

// Вспомогательный метод проверки лежит ли точка P на отрезке AB
// Математически: точка P принадлежит отрезку AB если выполняются условия:
// 1. P лежит на прямой AB 
// 2. Координаты P находятся между координатами A и B
bool Triangle::onSegment(double Ax, double Ay, double Bx, double By, double Px, double Py) {
    // Проверяем, что координата X точки P находится между X-координатами A и B
    // и координата Y точки P находится между Y-координатами A и B
    // Это гарантирует, что P лежит внутри границы отрезка AB
    if (Px >= min(Ax, Bx) && Px <= max(Ax, Bx) && Py >= min(Ay, By) && Py <= max(Ay, By)) {
        return true;
    }
    return false;
}

// Вспомогательный метод проверки - находится ли текущий треугольник внутри другого
// Математически: треугольник A содержится в треугольнике B если все вершины A лежат внутри B
bool Triangle::isInside(Triangle other) {
    // Проверяем, все ли вершины этого треугольника находятся внутри другого треугольника
    // Для этого каждая вершина (x1,y1), (x2,y2), (x3,y3) проверяется на принадлежность
    // треугольнику с вершинами (other.x1,other.y1), (other.x2,other.y2), (other.x3,other.y3)
    if (pointInTriangle(x1, y1, other.x1, other.y1, other.x2, other.y2, other.x3, other.y3) &&
        pointInTriangle(x2, y2, other.x1, other.y1, other.x2, other.y2, other.x3, other.y3) &&
        pointInTriangle(x3, y3, other.x1, other.y1, other.x2, other.y2, other.x3, other.y3)) {
        return true;
    }
    return false;
}

// Вспомогательный метод проверки - находится ли точка P внутри треугольника ABC
// Математическая основа: метод площадей
// Точка P находится внутри треугольника ABC если сумма площадей треугольников
// PAB, PBC, PCA равна площади треугольника ABC
bool Triangle::pointInTriangle(double Px, double Py, double Ax, double Ay, double Bx, double By, double Cx, double Cy) {
    // Создаем временные треугольники для вычисления площадей
    Triangle mainTriangle(Ax, Ay, Bx, By, Cx, Cy);  // Основной треугольник ABC
    Triangle triangle1(Px, Py, Bx, By, Cx, Cy);     // Треугольник PBC
    Triangle triangle2(Px, Py, Cx, Cy, Ax, Ay);     // Треугольник PCA
    Triangle triangle3(Px, Py, Ax, Ay, Bx, By);     // Треугольник PAB

    // Вычисляем площади
    double areaABC = mainTriangle.area();
    double areaPBC = triangle1.area();
    double areaPCA = triangle2.area();
    double areaPAB = triangle3.area();

    // Точка находится внутри треугольника если сумма площадей PAB, PBC, PCA
    // равна площади ABC (с учетом погрешности вычислений с плавающей точкой)
    return (abs((areaPBC + areaPCA + areaPAB) - areaABC) < 1e-9);
}
