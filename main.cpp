
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


//USED std::vector , std::string , std::priorityque 

#include<iostream>
#include<fstream>
#include"Pack.h"
#include"Unpack.h"

int main()
{

	std::vector<uint64_t> v(256, 0);
	char* filename;
	filename = new char[10001];
	//std::cin.getline(filename, 10000);
	std::fstream file;
	file.open("lasthope.txt", std::ios::binary|std::ios::in);
	if (file.good())//if there is no such directory just scip the file
	{
		generateFreeqTable(file, v);
		compress("lasthope.txt","new3.bin",v);

	}

	file.close();
	delete[] filename;


	std::cout << "NEW FILE\n";
	uint32_t tree;
	uint32_t nodesCnt;
	std::ifstream input;
	input.open("new3.bin", std::ios::binary);
	std::vector<uint32_t> serializedTree;
	std::vector<char> leafs;
	uint32_t leavesCnt;
	char leafVal;
	if (input.good())//if there is no such directory just scip the file
	{
		std::cout << "CREATING TREE\n";
		input.read((char*)&nodesCnt, 4);
	//	std::cout << nodesCnt;
	//	std::cout << "count of nodes: " << nodesCnt << "->" << nodesCnt / 32 + 1 << "  ints to read\n";
		uint32_t vsize = (nodesCnt / 32) + 1;
		for (size_t i = 0; i < vsize; i++)
		{
			input.read((char*)&tree, 4);
			serializedTree.push_back(tree);
			//std::cout << i << " -" << std::bitset<32>(tree) << std::endl;
		}

		input.read((char*)&leavesCnt, 4);
		for (size_t i = 0; i < leavesCnt; i++)
		{
			input.read((char*)&leafVal, 1);
			leafs.push_back(leafVal);
			//std::cout << "LEAF " << i << leafVal<<std::endl;
			//std::cout << i << " -" << std::bitset<32>(tree) << std::endl;
		}
		uint64_t readSize;
		input.read((char*)&readSize, 8);
		std::cout << "READ SIZE: "<<readSize;
			decompress(readSize,serializedTree,leafs,nodesCnt, input,"renew.txt");

	}
return 0;
		
}


//if (file.good())//if there is no such directory just scip the file
//{
//	while (file)
//	{
//		file.read((char*)&nodesCnt, 4);
//		std::cout << "count of nodes: " << nodesCnt << "->" << nodesCnt / 32 + 1 << "  ints to read\n";
//		size_t vsize = nodesCnt / 32 + 1;
//		for (size_t i = 0; i < vsize; i++)
//		{
//			file.read((char*)&tree, 4);
//			serializedTree.push_back(tree);
//			std::cout << i << " -" << std::bitset<32>(tree) << std::endl;
//		}
//
//		//	decompress(serializedTree, nodesCnt, file);
//
//		return 0;
//	}