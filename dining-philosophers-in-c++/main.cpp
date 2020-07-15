// Author: Muhammed Emin ÖMÜR
//
// This is an experimental work

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <functional>

class Philosopher
{
public:
	Philosopher() = delete;
	Philosopher(const std::string& name_, std::mutex& lf, std::mutex& rf)
		: name(name_), left_fork(lf), right_fork(rf)
	{
		// Intentionally empty
	}

	const std::string& get_name() const
	{
		return name;
	}

	// scoped_lock or other functions are not used
	// intentionally
	void obtain_forks()
	{
		while (true) {
			left_fork.lock();
			if (right_fork.try_lock()) {
				break;
			} else {
				left_fork.unlock();
				std::this_thread::yield();
			}
		}
	}

	void release_forks()
	{
		left_fork.unlock();
		right_fork.unlock();
	}
private:
	const std::string name;
	std::mutex& left_fork;
	std::mutex& right_fork;
};

void eat(Philosopher& p)
{
	p.obtain_forks();
	std::cout << p.get_name() + " is eating.\n";
	p.release_forks();
}

void think(Philosopher& p)
{
	std::cout << p.get_name() + " is thinking.\n";
}

void live(Philosopher& p)
{
	for (int i = 1; i <= 7; ++i) {
		if (i % 2) {
			think(p);
		} else {
			eat(p);
		}
	}
}

int main(void)
{
	// m means mutex and p means philosopher
	std::mutex m1, m2, m3, m4, m5;
	Philosopher p1("Philosopher 1", m1, m5);
	Philosopher p2("Philosopher 2", m2, m1);
	Philosopher p3("Philosopher 3", m3, m2);
	Philosopher p4("Philosopher 4", m4, m3);
	Philosopher p5("Philosopher 5", m5, m4);

	std::thread thread1(live, std::ref(p1));
	std::thread thread2(live, std::ref(p2));
	std::thread thread3(live, std::ref(p3));
	std::thread thread4(live, std::ref(p4));
	std::thread thread5(live, std::ref(p5));

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();

	return 0;
}
