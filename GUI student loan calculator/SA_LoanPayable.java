/*
 * Interface Name: SA_LoanPayable.java
 * Purpose: Loan Payable interface
 * Coder: Suhail Attaelmanan
 * Date: Apr 7, 2024
 */

public interface SA_LoanPayable {
	
	final double ANNUAL_RATE_TO_MONTHLY_RATE = 1.0 / 1200.0;

	double calculateLoanPayment(double principalAmount, double annualInterestRate, int amortizationPeriod);
}
