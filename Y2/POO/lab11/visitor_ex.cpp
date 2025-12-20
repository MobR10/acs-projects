// da, e luat de pe geeksforgeeks, dar am inteles
// il scriu de mana pe cel de kotlin

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Circle;
class Square;
class Triangle;

class ShapeVisitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Square& square) = 0;
    virtual void visit(Triangle& triangle) = 0;
    virtual ~ShapeVisitor() = default;
};

class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Square : public Shape {
public:
    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Triangle : public Shape {
public:
    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class AreaCalculator : public ShapeVisitor {
private:
    double totalArea = 0.0;

    double radiusOfCircle = 5.0;
    double sideOfSquare = 4.0;
    double baseOfTriangle = 3.0;
    double heightOfTriangle = 6.0;

public:
    void visit(Circle&) override {
        totalArea += M_PI * pow(radiusOfCircle, 2);
    }

    void visit(Square&) override {
        totalArea += pow(sideOfSquare, 2);
    }

    void visit(Triangle&) override {
        totalArea += (baseOfTriangle * heightOfTriangle) / 2;
    }

    double getTotalArea() const {
        return totalArea;
    }
};

// Main
int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    shapes.push_back(new Triangle());

    AreaCalculator areaCalculator;

    for (Shape* shape : shapes) {
        shape->accept(areaCalculator);
    }

    cout << "Total area: " << areaCalculator.getTotalArea() << endl;

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
