/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valknova
* @idnumber 45155
* @task 2
* @compiler VCC
*
*/
#pragma once
#include<string>
struct Data
{
	char symbol;
	unsigned long long fcoef;

	Data(char c, unsigned long long f) :fcoef(f), symbol(c) {};
};

struct Word
{
	char symbol;
	//uint32_t intCode;
	std::string code;
	Word(char c, std::string str) :symbol(c), code(str)
	{
		//intCode = 0;
		//uint32_t mask;// = ~0;
		//for (size_t i = 0; i < str.size(); i++)
		//{
		//	mask = uint32_t(str[i]=='1') << (31 - i);
		//	intCode |= mask;
		//}
		//std::cout << symbol << " == " << code.c_str()<<"\n";
	}
};

