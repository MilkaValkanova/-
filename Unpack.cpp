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
#include"HuffmanTree.h"
#include "Unpack.h"


void generateVectorBitToBool(std::vector<bool>& bitVector,  const std::vector<uint32_t>& intVector, uint32_t sizeInBits)
{
	size_t size = intVector.size();
	std::vector<bool>buffer(32, false);
	for (size_t i = 0; i < size - 1; ++i)
	{
		buffer = intToBool(intVector[i]);
		for (size_t j = 0; j < 32; ++j)
		{
			bitVector.push_back(buffer[j]);
		}
		buffer.clear();
	}

	buffer = intToBool(intVector[size-1]);
	for (size_t j = 0; j < sizeInBits % 32; ++j)
	{
		bitVector.push_back(buffer[j]);
	}

}
std::vector<bool> intToBool(const int number)
{
	std::vector<bool> tmp(32, false);
	for (size_t i = 0; i < 32; i++)
	{
		//std::cout << (number >> 0) & 1;
		tmp[i] = (number >> (31 - i)) & 1;
	//	std::cout <"\n"<< (number >> 0) & 1)"";
	}

	return tmp;
}


void decompress(uint64_t readSize ,const std::vector<uint32_t>& intVector ,const std::vector<char>&charVector, uint32_t sizeInBits,std::ifstream& input , const char* output)
{
	std::vector<bool> bitVector;
	generateVectorBitToBool(bitVector, intVector,sizeInBits);//convert int arr to bool arr
	HuffmanTree H(bitVector , charVector);
	H.Print();

	std::ofstream ofile(output, std::ios::binary);
	HuffmanTree::Node* current = H.root;
	size_t idx = 0;
	uint32_t buffer;
	std::string word;
	std::cout << "DECOMPRESSING THE FILE\n";
	
	for (size_t i = 0; i < readSize / 32;++i)
	{
		input.read((char*)&buffer, 4);
		bitVector = intToBool(buffer);
		H.move(current, bitVector, word, idx);
		for (size_t i = 0; i < bitVector.size(); ++i)
		{
			std::cout << bitVector[i];
		}
		std::cout << std::endl;
		if (word.size() != 0)
		{
			ofile.write((char*)word.data(), word.size() * 1);
			std::cout << "WORD IN FOR:  " <<i<<"" << word << std::endl;
		}

		word.clear();
		bitVector.clear();
	}

	input.read((char*)&buffer, 4);
	bitVector = intToBool(buffer);

	while (bitVector.size()> readSize % 32)
	{
		bitVector.pop_back();
	}
	for (size_t i = 0; i < bitVector.size(); ++i)
	{
		std::cout << bitVector[i];
	}
	word.clear();
	H.move(current, bitVector, word, idx, readSize % 32);
	if (word.size() != 0)
	{
		ofile.write((char*)word.data(), word.size()*1);
		std::cout << "LEFT WORD: "<<word<<"\n";
	}

	word.clear();
//	bitVector.clear();
	ofile.close();
	
	std::cout << "READY\n";

}


