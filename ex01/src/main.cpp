/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:16:36 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 12:15:32 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
    // 1. Initialize a Data structure with some values
    Data myData;
    myData.s1 = "Hello 42";
    myData.n = 42;
    myData.s2 = "Module 06 is wow";

    // 2. Display original information for comparison
    std::cout << "--- Original Data ---" << std::endl;
    std::cout << "Address of myData  : " << &myData << std::endl;
    std::cout << "Content of s1      : " << myData.s1 << std::endl;
    std::cout << "Content of n       : " << myData.n << std::endl;
    std::cout << "--------------------------" << std::endl << std::endl;

    // 3. Serialize: Convert the pointer (address) into an integer (uintptr_t)
    uintptr_t raw = Serializer::serialize(&myData);
    std::cout << "Serialized value (uintptr_t) : " << raw << std::endl;

    // 4. Deserialize: Convert the integer back into a pointer
    Data* ptr = Serializer::deserialize(raw);

    // 5. Display the result of deserialization
    std::cout << std::endl << "--- After Deserialization ---" << std::endl;
    std::cout << "Address of obtained pointer : " << ptr << std::endl;

    // 6. Verify if the recovered pointer matches the original address
    if (ptr == &myData)
    {
        std::cout << "✅ SUCCESS: The pointers are identical!" << std::endl;
        std::cout << "Data verification: " << ptr->s1 << ", " << ptr->n << std::endl;
    }
    else
    {
        std::cout << "❌ ERROR: The pointers are different..." << std::endl;
    }

    return 0;
}