#include <cmath>
#include "Math_operations.h"
MathOperations *MathOperations::instance = nullptr;

MathOperations *MathOperations::getInstance()
{
    if (!instance)
    {
        instance = new MathOperations();
    }
    return instance;
}
double MathOperations::add(float num_1, float num_2)
{
    return static_cast<double>(num_1) + static_cast<double>(num_2);
}

double MathOperations::multiply(float num_1, float num_2)
{
    return static_cast<double>(num_1) * static_cast<double>(num_2);
}

float MathOperations::subtract(double num_1, double num_2)
{
    return static_cast<float>(num_1 - num_2);
}

float MathOperations::divide(double num_1, double num_2)
{
    if (num_2 == 0.0)
    {
        // Handle division by zero
        return 0.0; // You can modify this behavior as needed
    }
    return static_cast<float>(num_1 / num_2);
}

float MathOperations::modulo(double num_1, double num_2)
{
    if (num_2 == 0.0)
    {
        // Handle division by zero
        return 0.0; // You can modify this behavior as needed
    }
    return static_cast<float>(fmod(num_1, num_2));
}

double MathOperations::power(float base, float exponent)
{
    return std::pow(static_cast<double>(base), static_cast<double>(exponent));
}

double MathOperations::factorial(float num)
{
    if (num < 0)
    {
        // Handle negative values
        return 0.0; // You can modify this behavior as needed
    }
    if (num == 0 || num == 1)
    {
        return 1.0;
    }
    double result = 1.0;
    for (int i = 2; i <= num; ++i)
    {
        result *= static_cast<double>(i);
    }
    return result;
}

float MathOperations::squareRoot(double num_1)
{
    if (num_1 < 0)
    {
        // Handle negative values
        return 0.0; // You can modify this behavior as needed
    }
    return static_cast<float>(std::sqrt(num_1));
}

double MathOperations::absolute(double num_1)
{
    return std::abs(num_1);
}

double MathOperations::max(double num_1, double num_2)
{
    return (num_1 > num_2) ? num_1 : num_2;
}

double MathOperations::min(double num_1, double num_2)
{
    return (num_1 < num_2) ? num_1 : num_2;
}