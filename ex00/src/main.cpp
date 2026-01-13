/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:45:21 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/13 09:41:54 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

void test_convert(const std::string& literal) {
    std::cout << "\n==============================================" << std::endl;
    std::cout << "Testing literal: ./convert " << literal << std::endl;
    std::cout << "==============================================" << std::endl;
    ScalarConverter::convert(literal);
}

int main(int argc, char **argv)
{
    // If the user passes a command line argument, test that argument
    if (argc == 2)
    {
        test_convert(argv[1]);
        return 0;
    }
    
    // Standard test cases based on the subject examples and common edge cases:
    
    std::cout << "--- Subject Examples ---" << std::endl;
    test_convert("0");      // Example 1: int 
    test_convert("nan");    // Example 2: pseudo-literal (double)
    test_convert("42.0f");  // Example 3: float
    
    std::cout << "\n--- Additional Tests ---" << std::endl;

    // Char tests
    test_convert("'z'");    // Displayable char
    test_convert("' '");    // Space (displayable)
    test_convert("32");     // Int value of ' ' (Non displayable if out of range)
    test_convert("127");    // Borderline char/non-displayable

    // Limit/Overflow tests
    test_convert("2147483648");     // Int overflow (should print impossible)
    test_convert("-2147483649");    // Int underflow (should print impossible)
    test_convert("1.79769e+308");   // Double Max (check float overflow)

    // Pseudo-literals
    test_convert("+inf");           
    test_convert("-inff");
    test_convert("nanf");

    // Decimals
    test_convert("3.14159");        // Double
    test_convert("123.45f");        // Float
    test_convert("-0.0");           // Double

    // Invalid input test
    test_convert("invalid_string");

    return 0;
}