#include <iostream>
#include <string>

// https://www.lemoda.net/c/modulo-operator/
#define MOD(a,b) ((((a)%(b))+(b))%(b))

int main(int _argc, const char* _argv[])
{
	if (_argc > 3 || _argc == 1)
	{
		std::cout << "Please enter one or two perameters!\n";
		std::cout << "[(optional) number to ROT by] [string]" << std::endl;
		return 0;
	}
	if (_argc == 2)
	{
		uint32_t strlength = strlen(_argv[1]);
		std::string str;
		for (int z = 0; z < 26; z++)
		{
			str = _argv[1];
			for (int i = 0; i < strlength; i++)
			{
				if ((int)str[i] <= 90 && (int)str[i] >= 65)
				{
					str[i] += 32;
				}
				if (str[i] >= 97 && str[i] <= 122)
				{
					str[i] = MOD(str[i] - 97 - z, 26) + 97;
				}
			}
			std::cout << str << std::endl;
		}
	}
	else // arg == 3
	{
		int count = std::stoi(_argv[1]);
		int strlength = strlen(_argv[2]);
		std::string str(_argv[2]);
		for (int i = 0; i < strlength; i++)
		{
			if ((int)str[i] <= 90 && (int)str[i] >= 65)
			{
				str[i] += 32;
			}
			if (str[i] >= 97 && str[i] <= 122)
			{
				str[i] = MOD(str[i] - 97 + count, 26) + 97;
			}
		}
		std::cout << str << std::endl;
	}	
	return 0;
}