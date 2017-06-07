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
//system info:
//1 4bytes(uint32_t nodes cnt)
//2 nodes cnt/4 +1 ints - serialized Huffman tree
//3 char value for each leaf
//4  8byes size of text - in bits(unit64_t)
//Text
//5 size of text/ 4 +1 int of serialized original text


//general function
void decompress(uint64_t , const std::vector<uint32_t>&, const std::vector<char>&, uint32_t, std::ifstream&, const char*);
void generateTree(std::vector<bool>&, const std::vector<uint32_t>&,uint32_t);
std::vector<bool> intToBool(const int);

