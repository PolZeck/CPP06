/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:16:36 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/13 10:26:39 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
    Data myData;
    myData.s1 = "Hello 42";
    myData.n = 42;
    myData.s2 = "Module 06 is fun";

    std::cout << "--- Données Originales ---" << std::endl;
    std::cout << "Adresse de myData  : " << &myData << std::endl;
    std::cout << "Contenu de s1      : " << myData.s1 << std::endl;
    std::cout << "Contenu de n       : " << myData.n << std::endl;
    std::cout << "--------------------------" << std::endl << std::endl;

    uintptr_t raw = Serializer::serialize(&myData);
    std::cout << "Valeur sérialisée (uintptr_t) : " << raw << std::endl;

    Data* ptr = Serializer::deserialize(raw);

    std::cout << std::endl << "--- Après Désérialisation ---" << std::endl;
    std::cout << "Adresse du pointeur obtenu : " << ptr << std::endl;

    if (ptr == &myData)
    {
        std::cout << "✅ SUCCÈS : Les pointeurs sont identiques !" << std::endl;
        std::cout << "Vérification des données : " << ptr->s1 << ", " << ptr->n << std::endl;
    }
    else
    {
        std::cout << "❌ ERREUR : Les pointeurs sont différents..." << std::endl;
    }

    return 0;
}