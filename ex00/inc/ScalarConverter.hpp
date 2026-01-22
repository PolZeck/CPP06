/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:44:48 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 10:00:36 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <limits> // For numeric limits
#include <cmath>  // For nan, inf, etc.

class ScalarConverter
{
    private:
        // Enumeration to easily identify the type of input literal
        enum e_type {
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
            PSEUDO_LITERAL, // For nan, inf, nanf, inff
            UNKNOWN
        };

        // Private constructors/destructor to prevent instantiation
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();
        
        // Private helper methods for type detection and conversion logic
        static e_type   detectType(const std::string& literal);
        static void     convertFromChar(char c);
        static void     convertFromInt(int i);
        static void     convertFromFloat(float f);
        static void     convertFromDouble(double d);
        static void     displayPseudoLiteral(const std::string& literal);


    public:
        // The single static method required by the subject
        static void convert(const std::string& literal);
};

#endif // SCALARCONVERTER_HPP