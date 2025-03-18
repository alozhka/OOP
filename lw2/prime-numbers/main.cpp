#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound) {
	set<int> primes;
	if (upperBound < 2) {
		return primes;
	}

	vector<bool> sieve(upperBound + 1, true);
	sieve[0] = sieve[1] = false;

	// Обработка четных чисел
	if (upperBound >= 2) {
		sieve[2] = true;
		for (int j = 4; j <= upperBound; j += 2) {
			sieve[j] = false;
		}
	}

	// Просеивание нечетных чисел
	for (int i = 3; i * i <= upperBound; i += 2) {
		if (sieve[i]) {
			for (int j = i * i; j <= upperBound; j += 2 * i) {
				sieve[j] = false;
			}
		}
	}

	// Сбор простых чисел
	vector<int> primesList;
	if (upperBound >= 2) {
		primesList.push_back(2);
	}
	for (int i = 3; i <= upperBound; i += 2) {
		if (sieve[i]) {
			primesList.push_back(i);
		}
	}

	primes.insert(primesList.begin(), primesList.end());
	return primes;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " upperBound" << endl;
		return 1;
	}

	int upperBound;
	try {
		upperBound = stoi(argv[1]);
	} catch (const exception& e) {
		cerr << "Invalid upper bound: must be an integer." << endl;
		return 1;
	}

	if (upperBound < 0 || upperBound > 100000000) {
		cerr << "Upper bound must be between 0 and 100000000." << endl;
		return 1;
	}

	set<int> primes = GeneratePrimeNumbersSet(upperBound);

	for (int prime : primes) {
		cout << prime << endl;
	}

	return 0;
}