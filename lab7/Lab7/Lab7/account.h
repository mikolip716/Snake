#pragma once
#include <string>
#include <mutex>
std::mutex mx;
class Account {
	long long int balance;
	std::string name, surname;
public:
	Account(const std::string& name, const std::string& surname, const int& balance) : name(name), surname(surname), balance(balance) {}
	void transfer(const unsigned int& val) { mx.lock(); balance += val; mx.unlock(); }
	int get_balance() const { return balance; }
	std::string get_name() const { return name; }
	std::string get_surname() const { return surname; }
};
