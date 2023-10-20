//
// Created by cx9ps3 on 28.01.23.
//
#pragma once

#include <random>
#include <sstream>
#include "../Types.hpp"

/**
 * @brief Generates a UUID V4 string.
 *
 * This function generates a UUID V4 string by generating random numbers
 * and formatting them into the standard UUID format. The generated UUID
 * is in the form of 8-4-4-4-12 hexadecimal digits.
 *
 * @return std::string The generated UUID string.
 *
 * Example usage:
 * @code
 * std::string uuid = generateUUIDV4();
 * @endcode
 *
 * Note: This function depends on the random number generation capabilities
 * of the std::random_device, std::mt19937 and std::uniform_int_distribution<>
 * from the Standard Library.
 */
HEXEN_INLINE std::string generateUUIDV4()
{
	HEXEN_ADD_TO_PROFILE();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);
	std::uniform_int_distribution<> dis2(8, 11);
	std::stringstream ss;
	hexen::engine::core::i32 i;
	ss << std::hex;
	for (i = 0; i < 8; i++)
	{
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 4; i++)
	{
		ss << dis(gen);
	}
	ss << "-4";
	for (i = 0; i < 3; i++)
	{
		ss << dis(gen);
	}
	ss << "-";
	ss << dis2(gen);
	for (i = 0; i < 3; i++)
	{
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 12; i++)
	{
		ss << dis(gen);
	};
	return ss.str();
}
