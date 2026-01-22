/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:47:54 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 12:52:18 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base * generate(void);
void identify(Base* p);
void identify(Base& p);

int main() {
    // 1. Seed the random number generator with current time
    std::srand(std::time(0));

    // --- Test 1 ---
    // 2. Randomly instantiate A, B, or C and get it as a Base pointer
    Base* p1 = generate();
    // 3. Identify the real type using the pointer-based function
    std::cout << "Identify via pointer   : "; identify(p1);
    // 4. Identify the real type using the reference-based function
    std::cout << "Identify via reference : "; identify(*p1);
    // 5. Free memory (Base has a virtual destructor for this)
    delete p1;

    std::cout << std::endl << "--- Test 2 ---" << std::endl;
    Base* p2 = generate();
    std::cout << "Identify via pointer   : "; identify(p2);
    std::cout << "Identify via reference : "; identify(*p2);
    delete p2;

    std::cout << std::endl << "--- Test 3 ---" << std::endl;
    Base* p3 = generate();
    std::cout << "Identify via pointer   : "; identify(p3);
    std::cout << "Identify via reference : "; identify(*p3);
    delete p3;

    return 0;
}