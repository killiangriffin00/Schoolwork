/*
	NAME: Killian Griffin
	DATE: 4/9/20
	LAB SECTION: 5
	ASSIGNMENT: PA6
	DESCRIPTION: This program takes english characters and converts them to morse code
*/

#include "header.h"

BSTNode :: BSTNode(char newLetter, string newMorse)
{
	letter = newLetter;
	morse = newMorse;
	left = nullptr;
	right = nullptr;
}

BSTNode::BSTNode(BSTNode* copyNode)
{
	if (copyNode == nullptr)
	{
		letter = NULL;
		morse = { '\0' };
		left = copyNode->getLeft();
		right = copyNode->getRight();
		return;
	}
	letter = copyNode->getLetter();
	morse = copyNode->getMorse();
	left = copyNode->getLeft();
	right = copyNode->getRight();
}

char BSTNode :: getLetter()
{
	return letter;
}

string BSTNode :: getMorse()
{
	return morse;
}

BSTNode* BSTNode :: getLeft()
{
	return left;
}

BSTNode* BSTNode :: getRight()
{
	return right;
}

bool BSTNode :: setLetter(char newLetter)
{
	letter = newLetter;
	return true;
}

bool BSTNode :: setMorse(string newMorse)
{
	morse = newMorse;
	return true;
}

bool BSTNode :: setLeft(BSTNode* newNode)
{
	left = newNode;
	return true;
}

bool BSTNode :: setRight(BSTNode* newNode)
{
	right = newNode;
	return true;
}
bool BSTNode::printLetter(BSTNode* nodePtr)
{
	if (nodePtr->getLeft() != NULL)
		nodePtr->printLetter(nodePtr->getLeft());

	cout << nodePtr->getLetter();

	if (nodePtr->getRight() != NULL)
		nodePtr->printLetter(nodePtr->getRight());
	
	return true;
}

MorseBST :: MorseBST(ifstream* file)
{
	root = new BSTNode*;
	*root = nullptr;
	nodeNum = 0;
	char letter;
	string morse;
	while (!file->eof())
	{
		*file >> letter;
		*file >> morse;
		insertNode(letter, morse);
	}
}

MorseBST :: MorseBST(MorseBST* copyTree)
{
	root = copyTree->getRoot();
	nodeNum = copyTree->getNodeNum();
}

BSTNode** MorseBST :: getRoot()
{
	return root;
}

int MorseBST :: getNodeNum()
{
	return nodeNum;
}

bool MorseBST :: printBST()
{
	if (nodeNum == 0)
	{
		return false;
	}

	if((*root)->getLeft() != NULL)
	(*root)->printLetter((*root)->getLeft());

	cout << (*root)->getLetter();

	if ((*root)->getRight() != NULL)
		(*root)->printLetter((*root)->getRight());
	cout << endl;

	return true;
}

char MorseBST :: readLetter(ifstream* file)
{
	char letter;
	*file >> letter;
	return letter;
}

string MorseBST :: readMorse(ifstream* file)
{
	string morse;
	*file >> morse;
	return morse;
}

bool MorseBST :: insertNode(char newLetter, string newMorse)
{
	BSTNode* newNode = new BSTNode(newLetter, newMorse);
	if (nodeNum == 0)
	{
		*root = newNode;
		++nodeNum;
		return false;
	}
	BSTNode* temp(*root);

	while ((temp->getLeft() != NULL && temp->getLetter() > newNode->getLetter()) ||
		(temp->getRight() != NULL && temp->getLetter() < newNode->getLetter()))
	{
		if (temp->getLetter() > newNode->getLetter())
		{
			temp = temp->getLeft();
		}
		else if (temp->getLetter() < newNode->getLetter())
		{
			temp = temp->getRight();
		}
	}
	if (temp->getLetter() > newNode->getLetter())
	{
		temp->setLeft(newNode);
	}
	else if (temp->getLetter() < newNode->getLetter())
	{
		temp->setRight(newNode);
	}
	++nodeNum;
	return false;
}

string MorseBST::searchMorse(char searchLetter)
{
	if ((*root)->getLetter() > searchLetter && (*root)->getLeft() != NULL)
	{
		return (*root)->searchMorse(searchLetter);
	}
	if ((*root)->getLetter() < searchLetter && (*root)->getRight() != NULL)
	{
		return (*root)->searchMorse(searchLetter);
	}
	return (*root)->getMorse();
}

string BSTNode :: searchMorse(char searchLetter)
{
	if (letter > searchLetter && getLeft() != NULL)
	{
		return getLeft()->searchMorse(searchLetter);
	}
	if (letter < searchLetter && getRight() != NULL)
	{
		return getRight()->searchMorse(searchLetter);
	}
	return getMorse();

}