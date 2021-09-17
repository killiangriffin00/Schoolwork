#include "twitterData.h"


std::string TwitterData::getUserName() const
{
	return *(this->mpUserName);
}

std::string TwitterData::getActualName() const
{
	return *(this->mpActualName);
}

std::string TwitterData::getEmail() const
{
	return *(this->mpEmail);
}

std::string TwitterData::getCategory() const
{
	return *(this->mpCategory);
}

int TwitterData::getNumTweets() const
{
	return *(this->mpNumTweets);
}

void TwitterData::setUserName(const std::string& newUserName)
{
	// do we need to allocate space for a std::string here?
    std::string* data = new std::string(newUserName);
	mpUserName = data;
}

void TwitterData::setActualName(const std::string& newActualName)
{
	// do we need to allocate space for a std::string here?
	std::string* data = new std::string(newActualName);
	mpActualName = data;
}

void TwitterData::setEmail(const std::string& newEmail)
{
	// do we need to allocate space for a std::string here?
    std::string* data = new std::string(newEmail);
	mpEmail = data;
}

void TwitterData::setCategory(const std::string& newCategory)
{
	// do we need to allocate space for a std::string here?
    std::string* data = new std::string(newCategory);
	mpCategory = data;
}

void TwitterData::setNumTweets(const int& newNumTweets)
{
	// do we need to allocate space for an int here?
    int* data = new int(newNumTweets);
	mpNumTweets = data;
}