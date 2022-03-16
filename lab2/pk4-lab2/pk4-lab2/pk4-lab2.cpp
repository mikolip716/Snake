#include <iostream>
#include <regex>
#include <string>

void sprawdz_dopasowanie(std::string str_test, std::regex reg_test)
{
    if (std::regex_search(str_test, reg_test))
    {
        std::cout << "Znaleziono dopasowanie\n";
    }
    else
    {
        std::cout << "Nie znaleziono dopasowania\n";
    }
}

int main()
{
    //zadanie 1
    std::string str_test = "abc123";
    std::regex reg_test("abc123");
    std::cout << "Zadanie 1\n";
    sprawdz_dopasowanie(str_test, reg_test);

    //zadanie 2
    reg_test = "abc";
    std::cout << "Zadanie 2\n";
    sprawdz_dopasowanie(str_test, reg_test);

    //zadanie 3
    str_test = "abc123!";
    reg_test = "[!@#\\$%^&\\*\\(\\)_]";
    std::cout << "Zadanie 3\n";
    sprawdz_dopasowanie(str_test, reg_test);

    //zadanie 4
    str_test = "123abc!123";
    std::regex reg1("^(123)");
    std::regex reg2("(123)$");
    std::cout << "Zadanie 4\n";
    sprawdz_dopasowanie(str_test, reg1);
    sprawdz_dopasowanie(str_test, reg2);

    //zadanie 5
    str_test = "mikolip716@student.polsl.pl";
    reg_test = "[\\w\\.]+@{1}\\w+\\.[\\w\\.]{2,}";
    std::cout << "Zadanie 5\n";
    sprawdz_dopasowanie(str_test, reg_test);

    //zadanie 6
    std::smatch dopasowanie;
    std::regex_search(str_test, dopasowanie, reg_test);
    std::cout << "Dopasowane wyrazenie: " << dopasowanie[0] << "\n";
}