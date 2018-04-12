#pragma once
#include <random>

class RandomNumber
{
public:

	RandomNumber() : m_mt(m_rand()) {}

	// generates a user-defined variabel type between the min and max values
	template <typename T>
	T Generate(T min, T max)
	{
		std::uniform_real_distribution<T> num(min, max);
		return num(m_mt);
	}

	// generates a random integer between min and max values
	int GenerateInt(int min, int max)
	{
		std::uniform_int_distribution<int> num(min, max);
		return num(m_mt);
	}

	// generates a random inetger, allowing the geneartion of negative numbers
	// nonZero - if set to true, if the random number generated is zero, will loop until 
	// a non-zero number is generated
	int GenerateNegInt(int min, int max, bool nonZero)
	{
		int posmin = 0;
		int minmax = 0;

		if (min < 0) {
			posmin = fabs(min);
			minmax = max + posmin;
		}

		int gen = 0;
		std::uniform_int_distribution<int> num(0, minmax);
		gen = num(m_mt) - posmin;

		if (nonZero) {
			while (gen == 0) {
				std::uniform_int_distribution<int> num(0, minmax);
				gen = num(m_mt) - posmin;
			}
		}
		return gen;
	}

	// returns true if a random number of one is generated with the percentage chance of this 
	// occuring define by the user
	bool RandomChance(int percentage)
	{
		int max = percentage / 100;
		std::uniform_int_distribution<int> num(1, max);
		return num(m_mt) == 1;
	}

private:

	std::random_device m_rand;
	std::mt19937 m_mt;

};
