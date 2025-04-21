#pragma once

#include <vector> // Include the vector header
using namespace std; // Using the std namespace.

// InvestmentData class
class InvestmentData { // Class for investment data.
public: // Public accessors and mutators for private variables in InvestmentData class.
	void setStartingInvestment(double m_startingInvestment); // Mutator for the startingInvestment variable.
	void setMonthlyContribution(double m_monthlyContribution); // Mutator for the monthlyContribution variable.
	void setYearlyInterestRate(double m_yearlyInterestRate); // Mutator for the yearlyInterestRate variable.
	void setTerm(int m_numberOfYears); // Mutator for the numberOfYears variable.

	double getStartingInvestment() { return m_startingInvestment; } // Accessor for the startingInvestment variable.
	double getMonthlyContribution() { return m_monthlyContribution; } // Accessor for the monthlyContribution variable.
	double getYearlyInterestRate() { return m_yearlyInterestRate; } // Accessor for the yearlyInterestRate variable.
	int getTerm() { return m_numberOfYears; } // Accessor for the numberOfYears variable.

private: // Private variables with intial values of 0.
	double m_startingInvestment = 0.0;
	double m_monthlyContribution = 0.0;
	double m_yearlyInterestRate = 0.0;
	int m_numberOfYears = 0;

};