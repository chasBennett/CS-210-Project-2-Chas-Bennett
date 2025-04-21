
using namespace std; // Using the std namespace.

#include "InvestmentData.h" // Include the InvestmentData header file.
#include <vector> // Included vector library for use in functions.

void InvestmentData::setStartingInvestment(double m_startingInvestment) { // Sets a double value for the startingInvestment variable.
	this->m_startingInvestment = m_startingInvestment;
}

void InvestmentData::setMonthlyContribution(double m_monthlyContribution) { // Sets a double value for the monthlyContribution variable.
	this->m_monthlyContribution = m_monthlyContribution;
}

void InvestmentData::setYearlyInterestRate(double m_yearlyInterestRate) { // Sets a double value for the yearlyInterestRate variable.
	this->m_yearlyInterestRate = m_yearlyInterestRate;
}

void InvestmentData::setTerm(int m_numberOfYears) { // Sets an int value for the numberOfYears variable.
	this->m_numberOfYears = m_numberOfYears;
}