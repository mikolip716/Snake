export module Funkcje:Ala;
export import <iostream>;
void Ala() { std::cout << "Ala "; };
void Ma() { std::cout << "ma "; };
void Kota() { std::cout << "kota\n"; };
export void AMK()
{
	Ala();
	Ma();
	Kota();
};
