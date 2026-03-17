#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Triangle {
private:
    // Поля класса
    double x1, y1, x2, y2, x3, y3;

public:
    // Конструктор с параметрами
    Triangle(double X1, double Y1, double X2, double Y2, double X3, double Y3);

    // Вспомогательный метод для вычисления длины стороны треугольника
    double len_side(double x_1, double y_1, double x_2, double y_2);

    // Метод проверки на существование треугольника
    void exists();

    // Метод определения центра тяжести по x и по y
    void center_Gravity();

    // Метод рассчета площади треугольника
    double area();

    // Метод вывода в консоль площади треугольника
    void print_area();

    // Метод рассчета периметра
    void perimeter();

    // Метод сравнения площадей треугольников
    void compare_area(Triangle other);

    // Метод рассчета перемещения на x, y координат
    void move_triangle(double dx, double dy);

    // Метод проверки пересечения
    void intersection(Triangle other);

private:
    // Вспомогательный метод проверки пересечения отрезков
    bool segmentsIntersect(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy);

    // Вспомогательный метод проверки лежит ли точка на отрезке
    bool onSegment(double Ax, double Ay, double Bx, double By, double Px, double Py);

    // Вспомогательный метод проверки - находится ли треугольник внутри другого
    bool isInside(Triangle other);

    // Вспомогательный метод проверки - находится ли точка внутри треугольника
    bool pointInTriangle(double Px, double Py, double Ax, double Ay, double Bx, double By, double Cx, double Cy);
};
