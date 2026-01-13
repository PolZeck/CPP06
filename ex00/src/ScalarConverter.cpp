/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:50:30 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/13 09:51:16 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iomanip>
#include <cstdlib> // For strtod, strtof, strtol
#include <cerrno>  // For errno
#include <limits>
#include <cmath>   // For std::modf

// --- Private Part: Constructors and Destructor ---
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// --- Private Part: Type Detection ---

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

// --- Private Part: Conversion Functions (Using static_cast) ---

// Helper function to check if a double value is an integer
bool is_integer(double d) {
    double int_part;
    return std::modf(d, &int_part) == 0.0;
}

void ScalarConverter::convertFromChar(char c)
{
    // char
    if (isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    
    // int
    std::cout << "int: " << static_cast<int>(c) << std::endl;

    // float (Forcing .0f precision as it's an integer value)
    std::cout << std::fixed << std::setprecision(1); 
    std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;

    // double
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

void ScalarConverter::convertFromInt(int i)
{
    // char
    if (i < std::numeric_limits<char>::min() || i > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(static_cast<char>(i)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    
    // int
    std::cout << "int: " << i << std::endl;

    // float
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(i) << "f" << std::endl;

    // double
    std::cout << "double: " << static_cast<double>(i) << std::endl;
}

void ScalarConverter::convertFromFloat(float f)
{
    // 1. Display char
    if (f != f || f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(static_cast<char>(f)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

    // 2. Display int
    if (f != f || f < static_cast<float>(std::numeric_limits<int>::min()) || f > static_cast<float>(std::numeric_limits<int>::max()))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    // 3. Display float
    // If it's an integer, we force .0f [cite: 159, 169]
    if (is_integer(static_cast<double>(f)))
        std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
    else
        std::cout << "float: " << std::setprecision(std::numeric_limits<float>::digits10) << f << "f" << std::endl;
    
    // IMPORTANT: Reset fixed format so it doesn't affect the double output
    std::cout.unsetf(std::ios::fixed);

    // 4. Display double
    // We must check if it's an integer again to display .0 [cite: 160, 170]
    if (is_integer(static_cast<double>(f)))
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
    else
        std::cout << "double: " << std::setprecision(std::numeric_limits<double>::digits10) << static_cast<double>(f) << std::endl;

    // Reset fixed format one last time for future calls
    std::cout.unsetf(std::ios::fixed);
}

void ScalarConverter::convertFromDouble(double d)
{
    // char
    if (d != d || d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max()) 
        std::cout << "char: impossible" << std::endl;
    else if (!isprint(static_cast<char>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

    // int
    if (d != d || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;

    // float
    // Need to check for float overflow
    if (d != d || d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max())
        std::cout << "float: impossible" << std::endl;
    else
    {
        if (is_integer(d))
            std::cout << std::fixed << std::setprecision(1);
        else
            std::cout << std::setprecision(7); // Default float precision
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
    }

    // double (Corrected formatting)
    if (is_integer(d))
        std::cout << std::fixed << std::setprecision(1);
    else
        std::cout << std::setprecision(15); // Default double precision

    std::cout << "double: " << d << std::endl;
}

// --- Public Part: The convert method ---

void ScalarConverter::convert(const std::string& literal)
{
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
        // Handle CHAR detection directly to avoid strtod error paths
        convertFromChar(literal[1]); 
        return;
    }

    // Reset errno before conversion
    errno = 0;
    
    // Use strtod for parsing all numeric types safely in C++98
    char* endptr = NULL;
    double value = std::strtod(literal.c_str(), &endptr);

    // Check for trailing characters after the number (only 'f' is allowed for float input)
    bool conversion_complete = true;
    if (*endptr != '\0')
    {
        if (type == FLOAT && *endptr == 'f' && *(endptr + 1) == '\0')
            conversion_complete = true;
        else
            conversion_complete = false;
    }


    if (errno == ERANGE || !conversion_complete)
    {
        // This handles INT, FLOAT, DOUBLE conversion errors
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    if (type == INT)
    {
        // INT overflow check must happen here before static_cast<int>
        if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max())
            convertFromInt(static_cast<int>(value));
        else
        {
            // Custom overflow message for int input
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
        }
    }
    else if (type == FLOAT)
    {
        convertFromFloat(static_cast<float>(value));
    }
    else if (type == DOUBLE)
    {
        convertFromDouble(value);
    }
}