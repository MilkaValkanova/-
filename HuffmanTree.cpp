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
HuffmanTree::Node::Node(Data data) : key(data), left(nullptr), right(nullptr) {};


HuffmanTree::Node::Node(Node* lhs, Node* rhs) : left(lhs), right(rhs), key('M', lhs->key.fcoef + rhs->key.fcoef) {};

HuffmanTree::HuffmanTree(const std::vector<uint64_t>& arr)
{
	my_q queue;
	size_t len = arr.size();
	char c;
	for (size_t i = 0; i < len; ++i)
	{
		if (arr[i] > 0)
		{
			c = i;
			//	std::cout << "CODE: " << i << " ";
			Node* leaf = new Node(Data(c, arr[i]));
			std::cout << " SYMBOL '" << c << "' FREEQ "<<arr[i] << std::endl;
			queue.push(leaf);
		}
	}
	this->root = createTree(queue);
	//creating the dictionary
	std::vector<Word> tmpdictionary;
	std::string word;
	createDictionary(root, word, tmpdictionary);
	this->dictionary = tmpdictionary;
}

HuffmanTree::HuffmanTree(const std::vector<bool>& serializedTree,const std::vector<char>& leafs)
{
	size_t boolPos = 0, charPos = 0;
	 createTreeFromBool(this->root ,serializedTree, leafs, boolPos, charPos);
	
}

void HuffmanTree::createTreeFromBool(Node*& current, const std::vector<bool>& serializedTree, const std::vector<char>& leafs, size_t& boolPos, size_t& charPos)
{
	if (serializedTree[boolPos] == 1)//this is node
	{
		current = new Node(Data('M',0));
		++boolPos;
		createTreeFromBool(current->left, serializedTree, leafs, boolPos, charPos);
		createTreeFromBool(current->right, serializedTree, leafs, boolPos, charPos);
	}
	else
	{
		current = new Node(Data(leafs[charPos], 0));
		charPos++;
		boolPos++;
	}

}
typename HuffmanTree::Node* HuffmanTree::createTree(my_q& queue)
{
	while (queue.size() != 1)
	{
		//take 2 nodes and create new(node1.frequence + node2.freeq)
		//put parrent in the queu
		Node* lhs = queue.top();
		queue.pop();
		Node* rhs = queue.top();
		queue.pop();
		Node* root = new Node(lhs, rhs);
		queue.push(root);
	}
	Node* result = queue.top();

	return result;
}

HuffmanTree::~HuffmanTree()
{
	destroy(root);
}

void HuffmanTree::destroy(Node* element)
{
	if (element != nullptr)
	{
		destroy(element->left);
		destroy(element->right);
		delete[] element;
	}
}

void HuffmanTree::Print()const
{
	print(root);
}

void HuffmanTree::print(const Node* element)const
{
	if (element)
	{
		//std::cout << "\n_______LEFT_________\n";
		print(element->left);
		if (!element->left&& !element->right)
			std::cout << " '" << element->key.symbol << "' - " << element->key.fcoef << "\n";// <<
																							 //if (!element->left&& !element->right)
																							 //	std::cout << "LEAF";
																							 //else {
																							 //	if (element->left)
																							 //		std::cout << " left- '" << element->left->key.symbol << "' - " << element->left->key.fcoef; //<<
																							 //	else std::cout << " left - ";
																							 //	if (element->right)
																							 //		std::cout << " right- '" << element->right->key.symbol << "'- " << element->right->key.fcoef;
																							 //	else std::cout << " right - ";
																							 //	std::cout << "\n_______RIGHT_________\n";
		print(element->right);
		//}

		//std::cout << std::endl;
	}
}

void HuffmanTree::createDictionary(const Node* n, std::string code, std::vector<Word>& dictionary)const
{

	if (n)
	{
		{
			createDictionary(n->left, code + '0', dictionary);
		}
		{
			createDictionary(n->right, code + '1', dictionary);
		}
		if (!n->left && !n->right)
		{
			dictionary.push_back(Word(n->key.symbol, code));
			std::cout << "SYMBOL: " << n->key.symbol << " CODE: " << code.c_str() << std::endl;
		}
	//	std::cout << "SYMBOL: " << n->key.symbol << " CODE: " << code.c_str()<<std::endl;
		//std::cout << code;

	}
}
void HuffmanTree::move(Node*& current, const std::vector<bool>& value, std::string& word , size_t& idx , size_t vectorSIZE)
{
		if (idx == vectorSIZE)
		{
			idx = 0;
			return;
		}
		if (!current->left && !current->right)
		{
			//current = root;
	
			//std::cout << current->key.symbol;
			
			move(root, value, word +=(current->key.symbol),idx , vectorSIZE);
		
		}
		else
		{
			if (value[idx] == 0)
			{
				move(current->left, value, word, ++idx  ,vectorSIZE);
			}
			else if (value[idx] == 1)
			{
				move(current->right, value, word, ++idx, vectorSIZE);
			}
		}
}

void HuffmanTree::_treeToInt(const Node* n, std::string& tree, std::vector<char>& leafData, uint32_t& treeSize)const
{
	if (n)
	{
		if (n->left || n->right)
		{
			tree += '1';
		}
		else
		{
			tree += '0';
			leafData.push_back(n->key.symbol);
		}
		++treeSize;
		_treeToInt(n->left, tree, leafData, treeSize);
		_treeToInt(n->right, tree, leafData, treeSize);
	}
}

void HuffmanTree::treeToInt(std::string& tree, std::vector<char>& leafData, uint32_t& treeSize)const
{
	_treeToInt(this->root, tree,leafData, treeSize);
}

const std::vector<Word>& HuffmanTree::readDictionary()const 
{
	return this->dictionary; 
}
std::string HuffmanTree::getWordCode(size_t idx)const
{ 
	return dictionary[idx].code; 
}
char HuffmanTree::getWordSymb(size_t idx)const
{ 
	return dictionary[idx].symbol; 
}
size_t HuffmanTree::getDSize()const 
{
	return dictionary.size(); 
}