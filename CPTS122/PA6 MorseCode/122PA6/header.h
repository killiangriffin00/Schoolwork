/*
	NAME: Killian Griffin
	DATE: 4/9/20
	LAB SECTION: 5
	ASSIGNMENT: PA6
	DESCRIPTION: This program takes english characters and converts them to morse code
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class BSTNode
{
private:
	char letter;
	string morse;
	BSTNode* left;
	BSTNode* right;

public:
	BSTNode(char newLetter, string newMorse);
	BSTNode(BSTNode* copyNode);
	BSTNode(BSTNode** copyNode);
	~BSTNode(){}
	char getLetter();
	string getMorse();
	BSTNode* getLeft();
	BSTNode* getRight();
	bool setLetter(char newLetter);
	bool setMorse(string newMorse);
	bool setLeft(BSTNode* newNode);
	bool setRight(BSTNode* newNode);
	bool printLetter(BSTNode* nodePtr);
	string searchMorse(char searchLetter);
};

class MorseBST
{
private:
	BSTNode** root;
	int nodeNum;

public:
	MorseBST(ifstream* file);
	~MorseBST() {}
	MorseBST(MorseBST* copyTree);
	BSTNode** getRoot();
	int getNodeNum();
	bool printBST();
	char readLetter(ifstream* file);
	string readMorse(ifstream* file);
	bool insertNode(char newLetter, string newMorse);
	string searchMorse(char searchLetter);
};

#endif