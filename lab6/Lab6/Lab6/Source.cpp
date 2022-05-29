#include <barrier>
#include <iostream>
#include <thread>
#include <Windows.h>
#include <fstream>
#include <semaphore>

//zadanie 1

std::barrier bariera(4);

class Pizza
{	
	private:
		std::string nazwa;
		void przygotuj()
		{
			std::cout << nazwa << " jest przygotowywana\n";
			bariera.arrive_and_wait();
			Sleep(500);
			std::cout << nazwa << " zostala wlozona do pieca\n";
			bariera.arrive_and_wait();
		};
	public:
		Pizza(std::string nazwa) { this->nazwa = nazwa; };
		void operator() () { przygotuj(); };
};

//zadanie 2

std::barrier bariera2(3);

class Prostopadloscian
{
private:
	int a;
	int b;
	int c;
	void oblicz()
	{
		int pole = 2 * a * b + 2 * b * c + 2 * a * c;
		std::cout << "pole wynosi: " << pole << "\n";
		bariera2.arrive_and_wait();
		int objetosc = a * b * c;
		std::cout << "objetosc wynosi: " << objetosc << "\n";
	};
public:
	Prostopadloscian(int a, int b, int c) { this->a = a; this->b = b; this->c = c; };
	void operator() () { oblicz(); };
};

class Prostokat
{
private:
	int a;
	int b;
	void oblicz()
	{
		int pole = a * b;
		std::cout << "pole wynosi: " << pole << "\n";
		bariera2.arrive_and_drop();
	};
public:
	Prostokat(int a, int b) { this->a = a; this->b = b; };
	void operator() () { oblicz(); };
};

//zadanie 3
std::binary_semaphore zapisane{ 0 }, odczytane{ 1 };

void zapis() {
	for (int i = 0; i < 3; i++) {
		odczytane.acquire();
		std::ofstream plik("dane.txt");
		plik << i;
		plik.close();
		zapisane.release();
	}
}

void odczyt() {
	for (int i = 0; i < 3; i++) {
		zapisane.acquire();
		std::ifstream plik("dane.txt");
		int x;
		while (plik >> x) {
			std::cout << x << "\n";;
		}
		plik.close();
		odczytane.release();
	}
}

//zadanie 4
std::counting_semaphore zjezdzalnia(3);

class Osoba 
{
private:
	std::string imie;
	void zjezdza()
	{
		zjezdzalnia.try_acquire_for(std::chrono::seconds(30));
		std::cout << imie << " wchodzi na zjezdzalnie \n";
		std::this_thread::sleep_for(std::chrono::seconds(50));
		std::cout << imie << " jest na dole \n";
	}
public:
	Osoba(std::string imie) { this->imie = imie; };
	void operator () () { zjezdza(); };
};

int main()
{
	//zadanie 1
	/*
	Pizza pizza1("pizza1");
	Pizza pizza2("pizza2");
	Pizza pizza3("pizza3");
	Pizza pizza4("pizza4");
	std::thread th1(pizza1);
	std::thread th2(pizza2);
	std::thread th3(pizza3);
	std::thread th4(pizza4);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	*/
	
	//zadanie 2
	/*
	Prostokat prost1(10, 15);
	Prostopadloscian prostopad1(1, 2, 3);
	Prostopadloscian prostopad2(5, 10, 15);
	std::thread th5(prost1);
	std::thread th6(prostopad1);
	std::thread th7(prostopad2);
	th5.join();
	th6.join();
	th7.join();
	*/

	//zadanie 3
	/*
	std::thread th8zapis);
	std::thread th9(odczyt);
	th8.join();
	th9.join();
	*/

	//zadanie 4
	/*
	Osoba os1("Stefan");
	Osoba os2("Tomek");
	Osoba os3("Ola");
	Osoba os4("Andrzej");
	Osoba os5("Marta");
	Osoba os6("Kasia");
	std::thread th10(os1);
	std::thread th11(os2);
	std::thread th12(os3);
	std::thread th13(os4);
	std::thread th14(os5);
	std::thread th15(os6);
	th10.join();
	th11.join();
	th12.join();
	th13.join();
	th14.join();
	th15.join();
	*/
}