/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:47:54 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/13 10:48:02 by pledieu          ###   ########.fr       */
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
    std::srand(std::time(0));

    std::cout << "--- Test 1 ---" << std::endl;
    Base* p1 = generate();
    std::cout << "Identify via pointer   : "; identify(p1);
    std::cout << "Identify via reference : "; identify(*p1);
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