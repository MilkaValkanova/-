/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valkanova
* @idnumber 45155
* @task 2
* @compiler VCC
*
*/
#pragma once
#include<iostream>
#include <vector>
#include <queue>
#include<fstream>
#include<bitset>
#include "BasicStructs.h"
#include"Unpack.h"
#include"Header.h"

class HuffmanTree
{
	friend void decompress(uint64_t ,const std::vector<uint32_t>&, const std::vector<char>&, uint32_t, std::ifstream&, const char*);
	friend class myPriorityQueue;

private:
	struct Node
	{
		Node* left;
		Node* right;
		Data key;
		Node(Node*, Node*);
		Node(Data);//for the leaves
	};

	struct  compare
	{
		bool operator()(const Node*lhs, const Node* rhs)
		{
			return lhs->key.fcoef > rhs->key.fcoef;
		}
	};

	std::vector<Word>dictionary;
	using my_q = std::priority_queue<Node*, std::vector<Node*>, compare>;
	Node* root;

public:
	
	HuffmanTree(const std::vector<uint64_t>&);//create tree from freequency table
	HuffmanTree(const std::vector<bool>&, const std::vector<char>&);//create tree from serialized HuffmanTree
	HuffmanTree(const HuffmanTree&) = delete;
	HuffmanTree operator=(const HuffmanTree&) = delete;
	~HuffmanTree();

private:
	void createTreeFromBool(Node*& current, const std::vector<bool>&,const std::vector<char>&, size_t& boolPos, size_t& charPos);
	Node* createTree(my_q& queue);
	void destroy(Node*);
	void print(const Node*)const;
	void createDictionary(const Node*, std::string, std::vector<Word>&)const;
	void _treeToInt(const Node*, std::string&, std::vector<char>&, uint32_t&)const;//create string <0.1> 0 -root 1-leaf from the tree(left son , right brother

public:
	void move(Node*&, const std::vector<bool>&, std::string& ,size_t&,size_t = 32);
	void treeToInt(std::string& tree, std::vector<char>&, uint32_t&)const;
	const std::vector<Word>& readDictionary()const;
	std::string getWordCode(size_t)const;
	char getWordSymb(size_t)const;
	size_t getDSize()const;
	
	void Print()const;
};

