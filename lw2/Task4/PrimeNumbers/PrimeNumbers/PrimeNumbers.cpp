#include "PrimeNumbers.h"
#include <vector>
#include <math.h>

namespace
{
	// upperBound = 9 выводит 9
	using namespace std;
	using BoolsVector = vector<bool>;

	const Number MIN_PRIME_NUMBER = 2;
	const Number MIN_ODD_PRIME_NUMBER = 3;

	void SieveVector(BoolsVector& sieve) // Смотреть по длине вектора
	{
		// можно еще меньше корень из числа 
		for (Number i = MIN_ODD_PRIME_NUMBER; i <= sqrt(sieve.size()); i++)
		{
			if (sieve[i])
			{
				//с шагом два вечеркивать числа только 2
				// можно нач. с квадрата числа
				for (Number j = i * i; j <= sieve.size(); j += i * 2)// i*2 // не использовать pow
				{
					sieve[j] = false;
				}
			}
		}
	}

	NumbersSet GetPrimeNumbersSetFromVector(BoolsVector const& sieve) {
		NumbersSet primeNumbers;
		// only odd
		// проверять тестами граничные значения (<)
		primeNumbers.insert(primeNumbers.end(), MIN_PRIME_NUMBER);
		for (Number i = MIN_ODD_PRIME_NUMBER; i <= sieve.size(); i += 2)
		{
			if (sieve[i])
			{
				primeNumbers.insert(primeNumbers.end(), i); // add hint
			}
		}
		return primeNumbers;
	}
}

NumbersSet GeneratePrimeNumbersSet(Number upperBound)
{
	NumbersSet primeNumbers;
	if (upperBound < MIN_PRIME_NUMBER)
	{
		return primeNumbers;
	}
	BoolsVector sieve(upperBound + 1, true);
	sieve[0] = sieve[1] = false;
	SieveVector(sieve);
	primeNumbers = GetPrimeNumbersSetFromVector(sieve);

	return primeNumbers;
}