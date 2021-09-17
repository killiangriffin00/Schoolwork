#ifndef TWITTER_DATA_H
#define TWITTER_DATA_H

#include <iostream>
#include <string>

class TwitterData
{
public:
	// Are the Big Five necessary?
	// How will this data work with the std::map?


	std::string getUserName() const; // we do want to return a copy of the string, not the pointer
	std::string getActualName() const; // we do want to return a copy of the string, not the pointer
	std::string getEmail() const; // we do want to return a copy of the string, not the pointer
	std::string getCategory() const; // we do want to return a copy of the string, not the pointer
	int getNumTweets() const; // we do want to return a copy of the integer, not the pointer

	void setUserName(const std::string &newUserName); // you need to implement
	void setActualName(const std::string& newActualName); // you need to implement
	void setEmail(const std::string &newEmail); // you need to implement
	void setCategory(const std::string &newCategory); // you need to implement
	void setNumTweets(const int &newNumTweets); // you need to implement

private:
	std::string *mpUserName, *mpActualName, 
		*mpEmail, *mpCategory;
	int *mpNumTweets;	
};

#endif