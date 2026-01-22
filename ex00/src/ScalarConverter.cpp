/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:50:30 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 11:20:41 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ScalarConverter.cpp
 * @brief Implementation of the scalar type conversion logic.
 */

#include "ScalarConverter.hpp"
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <limits>
#include <cmath>

/**
 * @brief Private constructors and assignment operator.
 * These are private to prevent the utility class from being instantiated.
 */
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

/**
 * @brief Identifies the scalar type of the input string.
 * @param literal The string representation of a literal.
 * @return The detected e_type (CHAR, INT, FLOAT, DOUBLE, or PSEUDO_LITERAL).
 */
ScalarConverter::e_type ScalarConverter::detectType(const std::string& literal)
{
    // 1. Detect pseudo-literals
    if (literal == "nan" || literal == "+inf" || literal == "-inf" ||
        literal == "nanf" || literal == "+inff" || literal == "-inff")
    {
        return PSEUDO_LITERAL;
    }

    // 2. Detect char
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
    {
        return CHAR;
    }

    // 3. Detect float
    if (literal.length() > 1 && literal[literal.length() - 1] == 'f' && literal.find('.') != std::string::npos)
    {
        return FLOAT;
    }
    
    // 4. Detect double
    if (literal.find('.') != std::string::npos)
    {
        return DOUBLE;
    }
    
    // 5. Detect int
    size_t non_digit_count = 0;
    for (size_t i = 0; i < literal.length(); ++i) {
        if (!isdigit(literal[i]) && !(i == 0 && (literal[i] == '-' || literal[i] == '+')))
            non_digit_count++;
    }
    if (non_digit_count == 0 && literal.length() > 0)
        return INT;

    return UNKNOWN;
}

/**
 * @brief Handles the display for special pseudo-literals (nan, inf).
 * These cases ignore char and int conversions as they are "impossible".
 */
void ScalarConverter::displayPseudoLiteral(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    
    if (literal[literal.length() - 1] == 'f' && literal != "inf" && literal != "+inf" && literal != "-inf")
    {
        std::cout << "float: " << literal << std::endl;
        std::cout << "double: " << literal.substr(0, literal.length() - 1) << std::endl;
    }
    else 
    {
        std::cout << "float: " << literal << "f" << std::endl;
        std::cout << "double: " << literal << std::endl;
    }
}

/**
 * @brief Utility to check if a double has no fractional part.
 * Helps in formatting output with .0 as shown in the subject examples.
 */
bool is_integer(double d) {
    double int_part;
    return std::modf(d, &int_part) == 0.0;
}

/**
 * @brief Converts from a detected Char and prints all four types.
 * Uses static_cast for explicit conversion.
 */
void ScalarConverter::convertFromChar(char c)
{
    if (isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << std::fixed << std::setprecision(1); 
    std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

/**
 * @brief Converts from a detected Int and prints all four types.
 * Checks for char displayability and range.
 */
void ScalarConverter::convertFromInt(int i)
{
    /** * Check if the integer value is within the valid range of a char type.
         * If the value is too large or too small to fit in a char, conversion is impossible.
         */
    if (i < std::numeric_limits<char>::min() || i > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    /** * If the value fits in a char but is not a printable character (like 0-31 or 127),
         * we inform the user that it cannot be displayed visually.
         */
    else if (!isprint(static_cast<char>(i)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    
    std::cout << "int: " << i << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(i) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(i) << std::endl;
}

/**
 * @brief Converts from a detected Float and prints all four types.
 * Handles overflows and non-sense conversions by printing "impossible".
 */
void ScalarConverter::convertFromFloat(float f)
{
    if (f != f || f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(static_cast<char>(f)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

    if (f != f || f < static_cast<float>(std::numeric_limits<int>::min()) || f > static_cast<float>(std::numeric_limits<int>::max()))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    if (is_integer(static_cast<double>(f)))
        std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
    else
        std::cout << "float: " << std::setprecision(std::numeric_limits<float>::digits10) << f << "f" << std::endl;
    
    std::cout.unsetf(std::ios::fixed);

    if (is_integer(static_cast<double>(f)))
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
    else
        std::cout << "double: " << std::setprecision(std::numeric_limits<double>::digits10) << static_cast<double>(f) << std::endl;

    std::cout.unsetf(std::ios::fixed);
}

/**
 * @brief Converts from a detected Double and prints all four types.
 */
void ScalarConverter::convertFromDouble(double d)
{
    if (d != d || d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max()) 
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(static_cast<char>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

    if (d != d || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;

    if (d != d || d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max())
        std::cout << "float: impossible" << std::endl;
    else
    {
        if (is_integer(d))
            std::cout << std::fixed << std::setprecision(1);
        else
            std::cout << std::setprecision(7);
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
    }

    if (is_integer(d))
        std::cout << std::fixed << std::setprecision(1);
    else
        std::cout << std::setprecision(15);

    std::cout << "double: " << d << std::endl;
}

/**
 * @brief Main entry point for conversion.
 * Detects the type, parses the string using strtod, and routes to specific conversion functions.
 */
void ScalarConverter::convert(const std::string& literal)
{
    // 1. Identify what the user typed
    e_type type = detectType(literal);
    
    if (type == UNKNOWN)
    {
        std::cerr << "Error: Unknown literal or invalid format." << std::endl;
        return;
    }
    else if (type == PSEUDO_LITERAL)
    {
        displayPseudoLiteral(literal);
        return;
    }
    else if (type == CHAR)
    {
        convertFromChar(literal[1]); 
        return;
    }

    // 2. Parse the string into a numeric value safely
    errno = 0;
    char* endptr = NULL;
    double value = std::strtod(literal.c_str(), &endptr);

    // 3. Validation: Did the parsing finish? Was it a clean number?
    bool conversion_complete = true;
    if (*endptr != '\0')
    {
        if (type == FLOAT && *endptr == 'f' && *(endptr + 1) == '\0')
            conversion_complete = true;
        else
            conversion_complete = false;
    }
    // 4. Handle errors like total overflow or garbage text
    if (errno == ERANGE || !conversion_complete)
    {
        std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
        return;
    }
    
    // 5. Route to the correct conversion logic based on detected type
    if (type == INT)
    {
        if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max())
            convertFromInt(static_cast<int>(value));
        else
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
    }
    else if (type == FLOAT)
        convertFromFloat(static_cast<float>(value));
    else if (type == DOUBLE)
        convertFromDouble(value);
}