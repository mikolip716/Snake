export module Funkcje;
export import :Ala;
import <string>;
export const char* A() { return "A\n"; };
export void B() { std::cout << "B\n"; };
export {
	void C() { std::cout << "C\n"; };
	void D() { std::cout << "D\n"; };
	void E() { std::cout << "E\n"; };
};
static std::string F()
{ 
	std::string s = "F\n";
	return s; 
};
export namespace Nazwa{
	const char* G() { return "G\n"; }
	const char* H() { return "H\n"; }
};