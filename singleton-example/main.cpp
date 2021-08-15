// Author: Muhammed Emin ÖMÜR
//
// Note: Do not forget adding "-lpthread --std=c++2a" arguments while compiling!

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <exception>

struct UninitializedSingletonException : public std::exception
{
	const char *what() const noexcept override
	{
		return "You tried to use Singleton object before initialization";
	}
};

class Singleton
{
public:
	static Singleton& get_instance()
	{
		std::call_once(init_once_flag, init);
		if (!ptr) {
			throw UninitializedSingletonException();
		}
		return *ptr;
	}

	void do_smth() const
	{
		std::cout << "I am doing something\n";
	}

	void do_smth_else() const
	{
		std::cout << "I am doing something else\n";
	}

	~Singleton()
	{
		std::cout << "Singleton object is leaving\n";
	}
private:
	Singleton()
	{
		std::cout << "Creating a Singleton object\n";
	}

	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

	static void init()
	{
		std::cout << "p is initializing\n";
		ptr.reset(new Singleton);
	}

	static std::unique_ptr<Singleton> ptr;
	static std::once_flag init_once_flag;
};

std::unique_ptr<Singleton> Singleton::ptr;
std::once_flag Singleton::init_once_flag;

void foo()
{
	Singleton::get_instance().do_smth();
}

void bar()
{
	Singleton::get_instance().do_smth_else();
}

int main()
{
	try {
		std::jthread t1(foo);
		std::jthread t2(bar);

		Singleton::get_instance().do_smth();
		Singleton::get_instance().do_smth_else();
	} catch (std::system_error& e) {
		std::cerr << e.what() << '\n';
		std::cerr << e.code() << '\n';
	} catch (UninitializedSingletonException& e ) {
		std::cout << e.what() << '\n';
	}

	return 0;
}
