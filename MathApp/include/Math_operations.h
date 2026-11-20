#pragma once

class MathOperations
{
private:
    static MathOperations *instance;

    MathOperations() {} // Private constructor to prevent direct instantiation

public:
    /************************************************************************************************************************
     * Description     : Get the singleton instance of MathOperations class.
     * Parameters      : None
     * Return value    : MathOperations * => Pointer to the MathOperations instance
     ************************************************************************************************************************/
    static MathOperations *getInstance();

    /************************************************************************************************************************
     * Description     : Perform addition of two numbers.
     * Parameters      : 1) float num_1 => First number
     *                   2) float num_2 => Second number
     * Return value    : double => Result of the addition
     ************************************************************************************************************************/
    double add(float num_1, float num_2);

    /************************************************************************************************************************
     * Description     : Perform multiplication of two numbers.
     * Parameters      : 1) float num_1 => First number
     *                   2) float num_2 => Second number
     * Return value    : double => Result of the multiplication
     ************************************************************************************************************************/
    double multiply(float num_1, float num_2);

    /************************************************************************************************************************
     * Description     : Perform subtraction of two numbers.
     * Parameters      : 1) double num_1 => First number
     *                   2) double num_2 => Second number
     * Return value    : float => Result of the subtraction
     ************************************************************************************************************************/
    float subtract(double num_1, double num_2);

    /************************************************************************************************************************
     * Description     : Perform division of two numbers.
     * Parameters      : 1) double num_1 => First number
     *                   2) double num_2 => Second number
     * Return value    : float => Result of the division
     ************************************************************************************************************************/
    float divide(double num_1, double num_2);

    /************************************************************************************************************************
     * Description     : Perform modulo operation on two numbers.
     * Parameters      : 1) double num_1 => First number
     *                   2) double num_2 => Second number
     * Return value    : float => Result of the modulo operation
     ************************************************************************************************************************/
    float modulo(double num_1, double num_2);

    /************************************************************************************************************************
     * Description     : Calculate the power of a number.
     * Parameters      : 1) float base     => Base number
     *                   2) float exponent => Exponent
     * Return value    : double => Result of the power calculation
     ************************************************************************************************************************/
    double power(float base, float exponent);

    /************************************************************************************************************************
     * Description     : Calculate the factorial of a number.
     * Parameters      : 1) float num => Number for which factorial is calculated
     * Return value    : double => Result of the factorial calculation
     ************************************************************************************************************************/
    double factorial(float num);

    /************************************************************************************************************************
     * Description     : Calculate the square root of a number.
     * Parameters      : 1) double num_1 => Number for which square root is calculated
     * Return value    : float => Result of the square root calculation
     ************************************************************************************************************************/
    float squareRoot(double num_1);

    /************************************************************************************************************************
     * Description     : Calculate the absolute value of a number.
     * Parameters      : 1) double num_1 => Number for which absolute value is calculated
     * Return value    : double => Result of the absolute value calculation
     ************************************************************************************************************************/
    double absolute(double num_1);

    /************************************************************************************************************************
     * Description     : Calculate the maximum of two numbers.
     * Parameters      : 1) double num_1 => First number
     *                   2) double num_2 => Second number
     * Return value    : double => Maximum of the two numbers
     ************************************************************************************************************************/
    double max(double num_1, double num_2);

    /************************************************************************************************************************
     * Description     : Calculate the minimum of two numbers.
     * Parameters      : 1) double num_1 => First number
     *                   2) double num_2 => Second number
     * Return value    : double => Minimum of the two numbers
     ************************************************************************************************************************/
    double min(double num_1, double num_2);
};
