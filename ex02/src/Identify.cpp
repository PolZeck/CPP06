/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:37:38 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 12:52:48 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/* Randomly instantiates A, B, or C and returns it as a Base pointer */
Base * generate(void) {
    // Generate a random number between 0 and 2
    int r = std::rand() % 3;
    
    // Create a new instance of A, B, or C based on the random result
    if (r == 0)
        return new A();
    if (r == 1)
        return new B();
    return new C();
}

/* Identifies the type using a pointer: returns NULL on failure */
void identify(Base* p) {
    // dynamic_cast returns the pointer if successful, or NULL if the type doesn't match
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

/* Identifies the type using a reference: throws an exception on failure */
void identify(Base& p) {
    // Since pointers are forbidden here, we use try/catch blocks
    // If a reference dynamic_cast fails, it throws a std::bad_cast exception
    
    try {
        A &a = dynamic_cast<A&>(p);
        (void)a; // Silence unused variable warning
        std::cout << "A" << std::endl;
        return ;
    } catch (std::exception &e) {} // Catch and ignore failure, then try next type

    try {
        B &b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "B" << std::endl;
        return ;
    } catch (std::exception &e) {}

    try {
        C &c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "C" << std::endl;
        return ;
    } catch (std::exception &e) {}
}