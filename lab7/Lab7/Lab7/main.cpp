#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <condition_variable>
#include "account.h"
#include "logger.h"

//zadanie 1
/*
std::random_device rd;
std::mt19937::result_type seed = rd() ^ (
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
std::mt19937 gen(seed);
std::uniform_int_distribution<unsigned> distrib(100000, 1000000);

unsigned int generate_pseudorandom_number() { return distrib(gen); }
*/
//zadanie 2
/*
Logger logger("logs.txt");

void is_prime(const int& val) {
	if (val < 0) {
		logger.error("invalid argument");
		return;
	}
	if (val == 0 || val == 1) {
		logger.info(std::to_string(val) + " to nie liczba pierwsza");
		return;
	}

	for (int i = 2; i < val / 2; i++) {
		logger.debug(std::to_string(val) + " % " + std::to_string(i));
		if (val % i == 0) {
			logger.info(std::to_string(val) + " to nie liczba pierwsza");
			return;
		}
	}
	logger.info(std::to_string(val) + " to liczba pierwsza");
}
*/

//zadanie 3
/*
std::random_device rd;
std::mt19937::result_type seed = rd() ^ (
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
std::mt19937 gen(seed);
std::uniform_int_distribution<unsigned> distrib(0, 100);

unsigned int generate_pseudorandom_number() { return distrib(gen); }

std::atomic<unsigned long long int> parallel_sum = 0;

void sum(const std::vector<unsigned int>& v, const unsigned int& first_index, const unsigned int& end_index) {
	for (unsigned int i = first_index; i != end_index; i++)
		parallel_sum += v[i];
}
*/

//zadanie 4
std::random_device rd;
std::mt19937::result_type seed = rd() ^ (
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
	(std::mt19937::result_type)
	std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
std::mt19937 gen(seed);
std::uniform_int_distribution<unsigned> distrib(0, 5);

unsigned int generate_pseudorandom_number() { return distrib(gen); }

class Car {
	std::string brand;
	bool is_broken;
public:
	std::mutex m;
	std::condition_variable c_var;
	Car(const std::string& brand, const bool& is_broken = false) : brand(brand), is_broken(is_broken) {}
	std::string get_brand() const { return brand; }
	bool get_is_broken() const { return is_broken; }
	void booom() { is_broken = true; std::cout << "BOOM!\n"; }
	void repair() { std::this_thread::sleep_for(std::chrono::seconds(3)); is_broken = false; }
};

int main() {
	//zadanie 1
	/*
	unsigned long long int expected = generate_pseudorandom_number();
	Account account = Account("Jan", "Nowak", expected);

	const unsigned int THREADS_NUM = 3;

	std::vector<std::thread> threads;
	for (unsigned int i = 0; i < THREADS_NUM; i++) {
		unsigned int to_add = generate_pseudorandom_number();
		threads.emplace_back(std::thread{ [&account, to_add]() {
			for (unsigned int i = 0; i < to_add; i++)
				account.transfer(1);
		} });
		expected += to_add;
	}

	for (auto& t : threads)
		t.join();

	std::cout << account.get_name() << ' ' << account.get_surname() << ' ';
	if (account.get_balance() != expected)
		std::cout << "NIE ";
	std::cout << "jest zadowolony.\nBalans oczekiwany: " << expected << ", balans faktyczny: " << account.get_balance();
	*/

	//zadanie 2
	/*
	std::thread t1(is_prime, -1);
	std::thread t2(is_prime, 0);
	std::thread t3(is_prime, 1);
	std::thread t4(is_prime, 2);
	std::thread t5(is_prime, 957);
	std::thread t6(is_prime, 2677);
	std::thread t7(is_prime, 7919);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	*/
	//zadanie 3
	/*
	std::vector<unsigned int> to_sum;
	const unsigned long long int TO_SUM_LENGTH = 10000000;
	unsigned long long int actual_sum = 0;
	for (unsigned int i = 0; i < TO_SUM_LENGTH; i++) {
		unsigned long long int temp = generate_pseudorandom_number();
		to_sum.push_back(temp);
		actual_sum += temp;
	}

	auto start = std::chrono::system_clock::now();
	sum(to_sum, 0, TO_SUM_LENGTH);
	std::chrono::duration<double> serial_duration = std::chrono::system_clock::now() - start;
	unsigned long long int serial_sum = parallel_sum;
	parallel_sum = 0;

	std::vector<std::thread> threads;
	const unsigned int THREADS_NUM = 2;
	const unsigned int LENGTH = TO_SUM_LENGTH / THREADS_NUM;
	unsigned int i = 0;
	start = std::chrono::system_clock::now();
	for (; i < THREADS_NUM - 1; i++)
		threads.emplace_back(sum, to_sum, i * LENGTH, (i + 1) * LENGTH);
	threads.emplace_back(sum, to_sum, i * LENGTH, TO_SUM_LENGTH);
	for (auto& t : threads)
		t.join();
	std::chrono::duration<double> parallel_duration = std::chrono::system_clock::now() - start;

	std::cout << "Rownolegle sumowanie ";
	if (parallel_sum != actual_sum)
		std::cout << "NIE ";
	std::cout << "zadzialalo poprawnie\nactual_sum: " << actual_sum << ", serial_sum: " << serial_sum << ", pararrel_sum: " << parallel_sum << "\nczas szeregowo: " << serial_duration.count() << ", czas rownolegle: " << parallel_duration.count() << "\nprzyspieszenie: " << serial_duration.count() / parallel_duration.count();
	*/

	//zadanie 4
	Car car("BMW");
	std::jthread mechanic([&car] {
		std::unique_lock<std::mutex> lock(car.m);
		while (true) {
			car.c_var.wait(lock, [&car]() { return car.get_is_broken(); });
			std::cout << "repairing...\n";
			car.repair();
			std::cout << "repaired.\n";
			car.c_var.notify_one();
		}
		});

	std::jthread driver([&car] {
		std::unique_lock<std::mutex> lock(car.m);
		while (true) {
			if (car.get_is_broken())
				car.c_var.notify_one();
			car.c_var.wait(lock, [&car]() { return !car.get_is_broken(); });
			std::cout << "driving " << car.get_brand() << "...\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});

	while (true) {
		if (!car.get_is_broken() && !generate_pseudorandom_number())
			car.booom();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}