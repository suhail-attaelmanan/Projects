/*
	 * Class Name: RepaymentCalculationForm.java		
	 * Purpose: Repayment Calculation Form Class		
	 * Coder: Suhail Attaelmanan			
	 * Date: Apr 7, 2024			
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class RepaymentCalculationForm extends JFrame implements SA_LoanPayable {
	private ArrayList<Student> studentList;
	private int currentIndex;

	private JLabel studentIDLabel;
	private JLabel fullNameLabel;
	private JLabel cslLoanAmountLabel;
	private JLabel oslLoanAmountLabel;
	private JComboBox<String> interestRateComboBox;
	private JTextField amortizationPeriodField;
	private JTextArea resultTextArea;
	private JButton calculateButton;
	private JButton previousButton;
	private JButton nextButton;
	
	public RepaymentCalculationForm(ArrayList<Student> studentList) {
		super("Repayment Calculation Form");
		this.studentList = studentList;
		this.currentIndex = 0;

		// Components:
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500, 400);
		setLocation(800, 158);

		JPanel mainPanel = new JPanel(new GridLayout(6, 1, 5, 5));
		mainPanel.setBackground(new Color(167, 255, 140));
		
		studentIDLabel = new JLabel("Student ID:");
		mainPanel.add(studentIDLabel);

		fullNameLabel = new JLabel("Full Name:");
		mainPanel.add(fullNameLabel);

		cslLoanAmountLabel = new JLabel("CSL Loan Amount:");
		mainPanel.add(cslLoanAmountLabel);

		oslLoanAmountLabel = new JLabel("OSL Loan Amount:");
		mainPanel.add(oslLoanAmountLabel);

		JPanel interestRatePanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		JLabel interestRateLabel = new JLabel("Select Interest Rate:");
		interestRatePanel.add(interestRateLabel);
		String[] interestRates = { "5.25%", "6.75%" };
		interestRateComboBox = new JComboBox<>(interestRates);
		interestRatePanel.add(interestRateComboBox);

		mainPanel.add(interestRatePanel);

		JPanel amortizationPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		JLabel amortizationLabel = new JLabel("Amortization Period (Months):");
		amortizationPanel.add(amortizationLabel);
		amortizationPeriodField = new JTextField(10);
		amortizationPanel.add(amortizationPeriodField);
		mainPanel.add(amortizationPanel);

		JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		previousButton = new JButton("Previous");
		previousButton.addActionListener(new PreviousButtonListener());
		buttonPanel.add(previousButton);
		calculateButton = new JButton("Calculate Payments");
		calculateButton.addActionListener(new CalculateButtonListener());
		buttonPanel.add(calculateButton);
		nextButton = new JButton("Next");
		nextButton.addActionListener(new NextButtonListener());
		buttonPanel.add(nextButton);
		mainPanel.add(buttonPanel);

		resultTextArea = new JTextArea(15, 70);
		resultTextArea.setEditable(true);
		JScrollPane scrollPane = new JScrollPane(resultTextArea);
		mainPanel.add(scrollPane);

		add(mainPanel, BorderLayout.CENTER);

		displayStudentData(currentIndex);
	}

	/*
	Method Name: displayStudentData
	Purpose: to display the Student's data
	Accepts: int
	Returns: void
	*/
	public void displayStudentData(int index) {
		if (index >= 0 && index < studentList.size()) {
			Student student = studentList.get(index);
			String fullName = student.getFirstName() + " " + student.getMiddleName() + " " + student.getSurname();
			studentIDLabel.setText("Student ID: " + student.getStudentID());
			fullNameLabel.setText("Full Name: " + fullName);
			cslLoanAmountLabel.setText("CSL Loan Amount: $" + student.getCslLoanAmount());
			oslLoanAmountLabel.setText("OSL Loan Amount: $" + student.getOslLoanAmount());
		}
	}
	/*
	 * Calculate Button
	 */
	private class CalculateButtonListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			int amortizationPeriod = validateAmortizationPeriod();
			if (amortizationPeriod < 1 || amortizationPeriod > 120) {
				JOptionPane.showMessageDialog(RepaymentCalculationForm.this,
						"Please enter a valid amortization period (1-120 months).");
				return;
			}

			Student s = studentList.get(currentIndex);
			double cslLoanAmount = s.getCslLoanAmount();
			double oslLoanAmount = s.getOslLoanAmount();

			displayPayments(cslLoanAmount, oslLoanAmount);
		}
	}

	/*
	 * Previous Button
	 */
	private class PreviousButtonListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			currentIndex--;
			if (currentIndex < 0) {
				currentIndex = studentList.size() - 1;
			}
			displayStudentData(currentIndex);
		}
	}

	/*
	 * Next Button Listener
	 */
	private class NextButtonListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			currentIndex++;
			if (currentIndex >= studentList.size()) {
				currentIndex = 0;
			}
			displayStudentData(currentIndex);
		}
	}

	/*
	Method Name: validateAmortizationPeriod
	Purpose: validate the Amortization Period
	Accepts: no args
	Returns: int
	*/
	private int validateAmortizationPeriod() {
		try {
			int amortizationPeriod = Integer.parseInt(amortizationPeriodField.getText());
			if (amortizationPeriod < 1 || amortizationPeriod > 120) {
				return -1;
			}
			return amortizationPeriod;
		} catch (NumberFormatException ex) {
			return -1;
		}
	}

	// Implement calculateLoanPayment method
	@Override
	public double calculateLoanPayment(double loanAmount, double annualInterestRate, int amortizationPeriod) {
		// Convert annual interest rate to monthly rate
		double monthlyInterestRate = annualInterestRate * ANNUAL_RATE_TO_MONTHLY_RATE;

		// Calculate monthly payment using the formula
		double powFactor = Math.pow(1 + monthlyInterestRate, amortizationPeriod);
		double monthlyPayment = (loanAmount * monthlyInterestRate * powFactor) / (powFactor - 1);

		try {
			monthlyPayment = validateNegativeInput(monthlyPayment);
		} catch (SA_NegativeValueException ex) {
			ex.printStackTrace();
		}

		return monthlyPayment;
	}

	/*
	Method Name: displayPayments
	Purpose: Print the payments
	Accepts: double, double
	Returns: void
	*/
	public void displayPayments(double cslMonthlyPayment, double oslMonthlyPayment) {
		Student s = studentList.get(currentIndex);

		int amortizationPeriod = Integer.parseInt(amortizationPeriodField.getText());
		String selectedInterestRateStr = (String) interestRateComboBox.getSelectedItem();
		double annualInterestRate = Double.parseDouble(selectedInterestRateStr.replace("%", ""));

		// Calculate CSL loan payment
		double cslLoanAmount = s.getCslLoanAmount(); // Principal amount for CSL loan
		double cslLoanPayment = calculateLoanPayment(cslLoanAmount, annualInterestRate, amortizationPeriod);

		// Calculate OSL loan payment
		double oslLoanAmount = s.getOslLoanAmount(); // Principal amount for OSL loan
		double oslLoanPayment = calculateLoanPayment(oslLoanAmount, annualInterestRate, amortizationPeriod);

		// Display the results
		String resultText = String.format(
				"Monthly Payment (CSL): $%.2f \nMonthly Payment (OSL): $%.2f \nCSL Loan: $%.2f \nOSL Loan: $%.2f",
				cslLoanPayment, oslLoanPayment, cslLoanAmount, oslLoanAmount);
		resultTextArea.setText(resultText);
	}

	/*
	Method Name: validateAndHandleNegativeInput
	Purpose: Handle negative input
	Accepts: double
	Returns: double
	*/
	public double validateNegativeInput(double loanAmount) throws SA_NegativeValueException {
		if (loanAmount < 0) {
			throw new SA_NegativeValueException();
		}
		return loanAmount;
	}

}
