#include <iostream>
#include <thread>
#include <future>
#include <Windows.h>

//zadanie 1

int hp1 = 100;
int hp2 = 100;

void f1()
{
	while (hp1 > 0)
	{
		if (hp1 <= 0)
		{
			break;
		}
		hp2 = hp2 - 10;
		if (hp2 > 0)
		{
			std::cout << "F2 otrzymal 10 obrazen, aktualny stan HP: " << hp2 << '\n';
			Sleep(2000);
		}
		else
		{
			std::cout << "Przeciwnik F2 zostal pokonany";
			break;
		}
	}
}

void f2()
{
	while (hp2 > 0)
	{
		if (hp2 <= 0)
		{
			break;
		}
		hp1 = hp1 - 6;
		if (hp1 > 0)
		{
			std::cout << "F1 otrzymal 6 obrazen, aktualny stan HP: " << hp1 << '\n';
			Sleep(1100);
		}
		else
		{
			std::cout << "Przeciwnik F1 zostal pokonany";
			break;
		}
	}
}

//zadanie 2

int fib(int x)
{
	if (x == 0)
	{
		return 0;
	}
	if (x == 1)
	{
		return 1;
	}
	return fib(x - 1) + fib(x - 2);
}

//zadanie 3

int factorial(std::future<int>& f)
{
	int res = 1;
	int n = f.get();
	for (n; n > 1; n--)
	{
		res = res * n;
	}
	return res;
}

int main()
{
	//zadanie 1
	/*
	std::thread th1(f1);
	std::thread th2(f2);
	th1.join();
	th2.join();
	*/

	//zadanie 2
	/*
	std::packaged_task<int(int)> pck_task{ fib };
	std::future<int> res = pck_task.get_future();
	std::thread th1(std::move(pck_task), 4);
	th1.join();
	std::cout << "Czwarty element to: " << res.get() << '\n';
	*/

	//zadanie 3
	/*
	int x = 7;
	std::promise<int> pr;
	std::future<int> f = pr.get_future();
	std::future<int> f2 = std::async(std::launch::async, factorial, std::ref(f));
	std::this_thread::sleep_for(std::chrono::seconds(2));
	pr.set_value(x);
	std::cout << "wynik: " << f2.get();
	*/
}

