/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:09:07 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/22 12:07:20 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

/* Converts a pointer to an unsigned integer (uintptr_t) */
uintptr_t Serializer::serialize(Data* ptr) {
    // reinterpret_cast is used to treat the memory address bits as a raw number
    return reinterpret_cast<uintptr_t>(ptr);
}

/* Converts an unsigned integer (uintptr_t) back to a Data* pointer */
Data* Serializer::deserialize(uintptr_t raw) {
    // Reverse the process to recover the original memory address
    return reinterpret_cast<Data*>(raw); 
}