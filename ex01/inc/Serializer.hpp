/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:08:30 by pledieu           #+#    #+#             */
/*   Updated: 2026/01/13 10:26:48 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>
# include <stdint.h> //  uintptr_t

struct Data; // Forward declaration

class Serializer {
    private:
        Serializer();
        Serializer(Serializer const & src);
        ~Serializer();
        Serializer & operator=(Serializer const & rhs);

    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif