#include "BankData.hpp"

BankData::BankData(int iAcctNum, double iSavingsAmount, double iCheckingAmount)
{
	int* t = new int(iAcctNum);
	mpAcctNum = t;

	double* a = new double(iSavingsAmount);
	mpSavingsAmount = a;
	
	double* b = new double(iCheckingAmount);
	mpCheckingAmount = b;
}

int BankData::getAcctNum() const
{
	return *(this->mpAcctNum);
}

double BankData::getSavingsAmount() const
{
	return *(this->mpSavingsAmount);
}

double BankData::getCheckingAmount() const
{
	return *(this->mpCheckingAmount);
}

void BankData::setAcctNum(const int& newAcctNum)
{
	// you need to implement
	int* t = new int(newAcctNum);
	mpAcctNum = t;
}

void BankData::setSavingsAmount(const double& newSavingsAmount)
{
	// you need to implement
	double* t = new double(newSavingsAmount);
	mpSavingsAmount = t;
}

void BankData::setCheckingAmount(const double& newCheckingAmount)
{
	// you need to implement
	double* t = new double(newCheckingAmount);
	mpCheckingAmount = t;
}