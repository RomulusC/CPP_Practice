#include <iostream>

//#ifdef _DEBUG
#if 1
void* operator new(size_t _size)
{
	std::cout << "operator new: " << _size << " bytes." << std::endl;
	void* ptr = malloc(_size);
	if (ptr)
		return ptr;
	else
		throw std::bad_alloc{};
}

void operator delete(void* _ptr, size_t _size)
{
	std::cout << "operator delete " << _size << " bytes." << std::endl;
	std::free(_ptr);
}

void operator delete(void* _ptr)
{
	std::cout << "operator delete occurred." << std::endl;
	std::free(_ptr);
}

#endif
#include "rstring.h"

int main()
{
	std::cout << "-----------TEST 1-----------" << std::endl;
	std::cout << "Construction, destruction, copy construction, copy assignment, move assignment." << std::endl;

	{
		String str("testing"); // Constructor
		String str2 = "one";   // Constructor
		std::cout << "---\nOutPut: " << str << " " << str2 << "\n---\n";

		String str3 = str2;    // Copy Constructor
		str2 = str;            // Copy Assignment
		std::cout << "---\nOutPut: " << str3 << " " << str2 << "\n---\n";


		str2.~String();        // Destructor heap assgined 
		str2 = str3;
		str2.~String();        // Destructor stack assgined 

		str3 = std::move(str); // Move Assignment
		std::cout << "---\nOutPut: " << str3 << "\n---\n"; // str is empty now


		String str4 = std::move(String("temp")); // Constructor, then Destructor 
		// Temp obj gets created, then contents moved, then deleted ^^
		std::cout << "---\nOutPut: " << str4 << "\n---\n";


		// str1 & str2 are empty
		// str3 and str4 have data
	}

	std::cout << "-----------TEST 1 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();

	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 2-----------" << std::endl;
	std::cout << "std string input." << std::endl;

	{
		String str5 = "123";
		std::cout << "ENTER STRING INPUT:" << std::endl;
		std::cin >> str5;
		std::cout << "OutPut:" << str5 << " size: " << str5.Size() << " reserve:" << str5.ReservedSize() << "\n";
		std::cin.get(); // pause so runtime input doest skip
		std::cout << "ENTER STRING INPUT:" << std::endl;
		std::cin >> str5;
		std::cout << "OutPut:" << str5 << " size: " << str5.Size() << " reserve:" << str5.ReservedSize() << "\n";

	}
	std::cout << "-----------TEST 2 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 3-----------" << std::endl;
	std::cout << "String concatenation." << std::endl;

	{
		String str6 = "1";
		String str7 = "23";
		str6 += str7;
		std::cout << "OutPut:" << str6 << " size: " << str6.Size() << " reserve: " << str6.ReservedSize() << "\n";
		str6 += "4567";
		std::cout << "OutPut:" << str6 << " size: " << str6.Size() << " reserve: " << str6.ReservedSize() << "\n";

	}
	std::cout << "-----------TEST 3 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue .\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 4-----------" << std::endl;
	std::cout << "String compare boolean." << std::endl;

	{
		String str = "123";
		String str2 = "234";
		String str3 = str;
		std::cout << "str == str2 | " << (str == str2) << std::endl;
		std::cout << "str3 == str | " << (str3 == str) << std::endl;
	}

	std::cout << "-----------TEST 4 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 5-----------" << std::endl;
	std::cout << "String concatenation by class reference." << std::endl;

	{
		String str1 = "st1";
		String str2 = "st2";
		String str3 = str1 + str2;

		std::cout << str3 << "\n";
	}

	std::cout << "-----------TEST 5 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 6-----------" << std::endl;
	std::cout << "Index operation test." << std::endl;


	{
		String str = "Hello World!";
		std::cout << "Output: " << str[6] << std::endl;
	}

	std::cout << "-----------TEST 6 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 7-----------" << std::endl;
	std::cout << "StringView class test." << std::endl;

	{
		String str = "Hello World!jnkjsndfksjndfvksndfvkjsndfvkjsdfkjvnsdklfvnsdklfjnvslkdfnvlskdfjnvslkdfnvkljn";

		StringView strv(str[6], 5);
		std::cout << "Output: " << strv << std::endl;
	}

	std::cout << "-----------TEST 7 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------TEST 8-----------" << std::endl;
	std::cout << "Another string concat test." << std::endl;

	{
		String str1 = "st1";

		String str3 = str1 + "st2";
		std::cout << str3 << "\n";

		String str4 = "st2" + str1;
		std::cout << str4 << "\n";
	}

	std::cout << "-----------TEST 8 END-----------" <<std::endl << std::endl;
	std::cout << "Press enter to continue.\n\n" << std::endl;
	std::cin.get();
	////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "-----------END-----------" << std::endl;
	std::cout << "Press enter to close.\n\n" << std::endl;
	std::cin.get();
	return 0;
}
// When scope ends, delete all local scope objects
