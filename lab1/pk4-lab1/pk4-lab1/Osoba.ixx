export module klasa:Osoba;

import<string>;
import <iostream>;

export class Osoba
{
private:
	int wiek;
	std::string imie;
public:
	void setImie(std::string _imie) { imie = _imie; }
	void setWiek(int _wiek) { wiek = _wiek; }
	std::string getImie() { return imie; }
	int getWiek() { return wiek; }
	void print() { std::cout << imie << " " << wiek << std::endl; }
	Osoba(std::string _imie, int _wiek) { imie = _imie; wiek = _wiek; }
};