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
#include<iostream>
#include<fstream>
#include<bitset>
#include"HuffmanTree.h"


uint64_t fileSize(std::fstream&);

//help functions
	void generateFreeqTable(std::fstream&, std::vector<uint64_t>& );
	uint64_t compressText(HuffmanTree& ,std::vector<uint32_t>& compCodes, std::fstream&);//takes chars from steam , and pack their codes (compressed from string<0,1>to int) in int (32bits)
	void compressTree(HuffmanTree&,std::vector<uint32_t>&,std::vector<char>&,uint32_t&);
	void IntToBit(uint32_t& current, size_t& intPos, size_t& strPos, const std::string& code);	//current - element we are working with , \
																					intPos -pos to write int this element ,\
																					strPos - position in the sring - the char we want to convert to bit\
																				code - icode for this char(from the dinctionary)															
//general function
	void compress(const char* , const char* ,const std::vector<uint64_t>&);

	
