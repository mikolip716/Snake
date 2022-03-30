#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

//Zadanie 1
void Show_path (const std::filesystem::path& path) {

	int i = 0;
	std::cout << "Wyswietl sciezke dla: " << path << "\n";
	std::cout << "sciezka: ";
	for (const auto& part : path)
	{
		std::cout << part;
	}
	std::cout << '\n';
}

//Zadanie 2
bool Create_dir()
{
	bool test = true;
	std::filesystem::create_directory("test");
	if (!std::filesystem::exists("test"))
	{
		test = false;
	}
	return test;
}

//Zadanie 3
bool Create_txt()
{
	bool test = true;
	std::ofstream("test/test.txt") << "aaaaaaaaaa";
	std::filesystem::copy_file("test/test.txt", "test/test2.txt");
	if (!std::filesystem::exists("test/test2.txt"))
	{
		test = false;
	}
	return test;
}

//Zadanie 4
void File_size()
{
	std::cout << "Rozmiar pliku: " << std::filesystem::file_size("test/test2.txt") << "\n";
}

//Zadanie 5
void Rename_dir()
{
	std::filesystem::rename("test", "new_test");
}

//Zadanie 6
void Resize()
{
	std::cout << "Rozmiar pliku: " << std::filesystem::file_size("new_test/test2.txt") << "\n";
	std::cout << "Ilosc wolnego miejsca: " << std::filesystem::space("new_test/test2.txt").free << "\n";
	std::filesystem::resize_file("new_test/test2.txt", 32 * 1024);
	std::cout << "Rozmiar pliku: " << std::filesystem::file_size("new_test/test2.txt") << "\n";
	std::cout << "Ilosc wolnego miejsca: " << std::filesystem::space("new_test/test2.txt").free << "\n";
}

//Zadanie 7
bool Clear()
{
	bool test = true;
	std::filesystem::remove_all("new_test");
	if (std::filesystem::exists("new_test"))
	{
		test = false;
	}
	return test;
}

int main(int argc, char* argv[])
{
	const std::filesystem::path path{ argc >= 2 ? argv[1] : std::filesystem::current_path() };
	Show_path(path);
	
	if (Create_dir())
	{
		std::cout << "Utworzono katalog \n";
	}
	
	if (Create_txt())
	{
		std::cout << "Utworzono i skopiowano plik \n";
	}

	File_size();
	Rename_dir();
	Resize();
	///*
	if (Clear())
	{
		std::cout << "Usunieto folder";
	}
	//*/
}