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
#include "Pack.h"
#include <bitset>



uint64_t compressText( HuffmanTree& T,std::vector<uint32_t>& compCodes, std::fstream& input)//
{
	std::cout << "COMPRESSING TEXT\n";
	uint32_t current = 0;//current int we use
	size_t currPos = 0;//position in int we use fo comp
	size_t idx = 0;//index of the char we want to compress
	size_t posWord = 0;//position of the bit we have to set 
	uint64_t textSize = 0;
	const size_t  SIZE = T.getDSize();
	while(!input.eof())
	{ 
		//read char 
		char c;
		input.read((char*)&c, 1);
		posWord = 0;
		//find it in  dictionary
		for (size_t i = 0; i < SIZE; ++i)
		{
			if (c == T.getWordSymb(i))
			{
				idx = i;
				textSize +=T.getWordCode(i).size();
				//std::cout << T.getWordCode(i).c_str();
				break;
			}
		}
		//compress some stuffs
		IntToBit(current, currPos, posWord, T.getWordCode(idx));

		//ceck what is happening
		while( (currPos == 31)&& (posWord <T.getWordCode(idx).size()))//one code may be bigger than int
		{
			compCodes.push_back(current);
			current = 0;
			currPos = 0;
			IntToBit(current, currPos, posWord, T.getWordCode(idx));
		}
		//we have reached end of the code for this char so we have to take new one 
	}
	if (currPos < 31) compCodes.push_back(current);
	//std::cout << compCodes.size();
	return textSize;
}
void IntToBit(uint32_t& current, size_t& intPos, size_t& strPos, const std::string& code)
{
	size_t SIZE = code.size();
	uint32_t mask;
	for (; strPos < SIZE; strPos++, ++intPos)
	{
		if (intPos == 31) return;//we have to strat fill new int 
		//take current char from the code and converti it to a single bit
		{
			mask = uint32_t(code[strPos] == '1') << (31 - intPos);
			current |= mask;
		}
	}
}

void compressTree(HuffmanTree& H ,std::vector<uint32_t>& v, std::vector<char>& leafs ,uint32_t& treeSize)
{
	std::cout << "\nCOMPRESSING TREE\n";
	uint32_t temp = 0;
	uint32_t current = 0;//current int we use
	size_t currPos = 0;//position in int we use fo comp
	size_t posWord = 0;//position of the bit we have to set 
	std::string tree;
	H.treeToInt(tree,leafs,treeSize);
	size_t n = tree.size();
	while(posWord<tree.size())
	{
		//char c = tree[i];
		//posWord = 0;
		//compress some stuffs
		IntToBit(current, currPos, posWord, tree);

			//ckeck what is happening
			while ((currPos == 31) && (posWord < tree.size()))//one code may be bigger than int
			{
				v.push_back(current);
				//std::cout << std::bitset<32>(current) << std::endl;
				current = 0;
				currPos = 0;
				IntToBit(current, currPos, posWord, tree);
			}
			//we have reached end of the code for this char so we have to take new one 
		}
	if (currPos < 32) v.push_back(current);

}
void compress(const char* input, const char* output,const std::vector<uint64_t>& freeqT)
{
	
	HuffmanTree H(freeqT);
	//H.Print();
	double fileSIZE = 0;
	uint32_t lenght = 0;
	uint32_t size = 0;
	uint32_t TreeSize = 0;

	std::fstream ifile,ofile;
	ofile.open(output, std::ios::binary|std::ios::out|std::ios::ate|std::ios::trunc);
	ifile.open(input, std::ios::binary|std::ios::in);

	//create vectors for the compressed info and then write them in file
	std::vector<uint32_t>intVector;
	std::vector<char>charVector;
	if (ofile.good() && ifile.good())
	{
	//std::cout << "Here";
		//write the tree
		compressTree(H,intVector , charVector, TreeSize);
		ofile.write((char*)&TreeSize, 4);//how many leafs
		//std::cout <<std::endl<< TreeSize<<std::endl;

		size = intVector.size();
		ofile.write((char*)intVector.data(), 4 * size);
		//std::cout <<" NUMER OF NODES(int) :" <<size;

		
		size = charVector.size();
		ofile.write((char*)&size, 4);
		ofile.write((char*)charVector.data(), 1 * size);
		
		intVector.clear();
		//write the text
		uint64_t sizeBit = compressText(H,intVector , ifile);//size of the commpressed text in bits
		ofile.write((char*)&sizeBit, 8);//write size oftext in bits	
		//std::cout << "Writing sizeBit = " << sizeBit << "\n";
		size = intVector.size();
		ofile.write((char*)intVector.data(), 4 * size);

	}

	
	ifile.close();
	ofile.close();
	std::cout << "READY\n";
}
 
void generateFreeqTable(std::fstream& file, std::vector<uint64_t>& v)
{
	uint64_t s = fileSize(file);
	unsigned char chunk;
	for (size_t i = 0; i < s; i++)
	{
		file.read((char*)&chunk, 1);
		{
			v[chunk]++;
			//std::cout << atoi((const char*)&chunk)+'0';
			//v[atoi((const char*)&chunk)]++;

		}
	}
}



uint64_t fileSize(std::fstream& file)
{
	file.seekg(0, std::ios::end);
	uint64_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	return size;

}