/*
	 * Class Name: StudentLoanApp.java		
	 * Purpose: Student Loan App Class			
	 * Coder: Suhail Attaelmanan			
	 * Date: Apr 7, 2024			
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class StudentLoanApp extends JFrame {

	private ArrayList<Student> studentList;

	private JTextField studentIDField;
	private JTextField surnameField;
	private JTextField middleNameField;
	private JTextField firstNameField;
	private JTextField aptNumberField;
	private JTextField streetNumberField;
	private JTextField streetNameField;
	private JTextField cityField;
	private JTextField provinceField;
	private JTextField postalCodeField;
	private JTextField cslLoanAmountField;
	private JTextField oslLoanAmountField;
	private JLabel title;

	// Getters and Setters for StudentList
	public ArrayList<Student> getStudentList() {
		return studentList;
	}

	public void setStudentList(ArrayList<Student> studentList) {
		this.studentList = studentList;
	}

	public StudentLoanApp() {
		super("Suhail Attaelmanan - 1123077");
		studentList = new ArrayList<>();

		// Set up the frame
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(400, 500);
		setLocation(400, 158);

		// Title
		title = new JLabel("This is Suhail Attaelmanan’s Student Loan Calculator", SwingConstants.CENTER);
		add(title, BorderLayout.NORTH);

		// Create components:

		JPanel inputPanel = new JPanel(new GridLayout(0, 2, 5, 5));
		inputPanel.setBackground(new Color(250, 216, 182));

		inputPanel.add(new JLabel("Student ID:"));
		studentIDField = new JTextField();
		inputPanel.add(studentIDField);

		inputPanel.add(new JLabel("Surname:"));
		surnameField = new JTextField();
		inputPanel.add(surnameField);

		inputPanel.add(new JLabel("Middle Name:"));
		middleNameField = new JTextField();
		inputPanel.add(middleNameField);

		inputPanel.add(new JLabel("First Name:"));
		firstNameField = new JTextField();
		inputPanel.add(firstNameField);

		inputPanel.add(new JLabel("Apt Number:"));
		aptNumberField = new JTextField();
		inputPanel.add(aptNumberField);

		inputPanel.add(new JLabel("Street Number:"));
		streetNumberField = new JTextField();
		inputPanel.add(streetNumberField);

		inputPanel.add(new JLabel("Street Name:"));
		streetNameField = new JTextField();
		inputPanel.add(streetNameField);

		inputPanel.add(new JLabel("City:"));
		cityField = new JTextField();
		inputPanel.add(cityField);

		inputPanel.add(new JLabel("Province:"));
		provinceField = new JTextField();
		inputPanel.add(provinceField);

		inputPanel.add(new JLabel("Postal Code:"));
		postalCodeField = new JTextField();
		inputPanel.add(postalCodeField);

		inputPanel.add(new JLabel("CSL Loan Amount:"));
		cslLoanAmountField = new JTextField();
		inputPanel.add(cslLoanAmountField);

		inputPanel.add(new JLabel("OSL Loan Amount:"));
		oslLoanAmountField = new JTextField();
		inputPanel.add(oslLoanAmountField);

		JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		JButton submitButton = new JButton("Submit");
		submitButton.addActionListener(new SubmitButtonListener(cslLoanAmountField, oslLoanAmountField, studentList));
		buttonPanel.add(submitButton);

		JButton clearButton = new JButton("Clear");
		clearButton.addActionListener(new ClearButtonListener());
		buttonPanel.add(clearButton);

		add(inputPanel, BorderLayout.CENTER);
		add(buttonPanel, BorderLayout.SOUTH);

		// Testing data:

		class PopulateButtonListener implements ActionListener {
			@Override
			public void actionPerformed(ActionEvent e) {
				// Predefined values
				String studentID = "12345";
				String surname = "Attaelmanan";
				String middleName = "Something";
				String firstName = "Suhail";
				String aptNumber = "Apt 123";
				String streetNumber = "123";
				String streetName = "Main St";
				String city = "City";
				String province = "Province";
				String postalCode = "12345";
				double cslLoanAmount = 2500d;
				double oslLoanAmount = 0d;

				studentIDField.setText(studentID);
				surnameField.setText(surname);
				middleNameField.setText(middleName);
				firstNameField.setText(firstName);
				aptNumberField.setText(aptNumber);
				streetNumberField.setText(streetNumber);
				streetNameField.setText(streetName);
				cityField.setText(city);
				provinceField.setText(province);
				postalCodeField.setText(postalCode);
				cslLoanAmountField.setText(String.valueOf(cslLoanAmount));
				oslLoanAmountField.setText(String.valueOf(oslLoanAmount));
			}
		}
		JButton populateButton = new JButton("Populate Fields");
		populateButton.addActionListener(new PopulateButtonListener());
		buttonPanel.add(populateButton);
	}

	/*
	 * Submit Button Listener
	 */
	public class SubmitButtonListener implements ActionListener {
		private JTextField cslLoanAmountField;
		private JTextField oslLoanAmountField;
		private ArrayList<Student> studentList;

		// Constructor to initialize the fields
		public SubmitButtonListener(JTextField cslLoanAmountField, JTextField oslLoanAmountField,
				ArrayList<Student> studentList) {
			this.cslLoanAmountField = cslLoanAmountField;
			this.oslLoanAmountField = oslLoanAmountField;
			this.studentList = studentList;
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			// Retrieve input values
			String studentID = studentIDField.getText();
			String surname = surnameField.getText();
			String middleName = middleNameField.getText();
			String firstName = firstNameField.getText();
			String aptNumber = aptNumberField.getText();
			String streetNumber = streetNumberField.getText();
			String streetName = streetNameField.getText();
			String city = cityField.getText();
			String province = provinceField.getText();
			String postalCode = postalCodeField.getText();
			double cslLoanAmount = Double.parseDouble(cslLoanAmountField.getText());
			double oslLoanAmount = Double.parseDouble(oslLoanAmountField.getText());

			try {
				// Handle negative loan amounts
				if (cslLoanAmount < 0 || oslLoanAmount < 0) {
					throw new SA_NegativeValueException();
				}

				// Create Student object and add to ArrayList
				Student student = new Student(studentID, surname, middleName, firstName, aptNumber, streetNumber,
						streetName, city, province, postalCode, cslLoanAmount, oslLoanAmount);
				studentList.add(student);

				clearFields();

				// Open RepaymentCalculationForm GUI
				RepaymentCalculationForm repaymentForm = new RepaymentCalculationForm(studentList);
				repaymentForm.setVisible(true);
				
			} catch (SA_NegativeValueException ex) {
				// warning message
				SA_NegativeValueException.displayWarningMessage();
			} catch (NumberFormatException ex) {
				// invalid  input
				JOptionPane.showMessageDialog(null, "Invalid loan amount input. Please enter a valid number.", "Error",
						JOptionPane.ERROR_MESSAGE);
			}
		}
	}

	/*
	 *  Clear button Listener 
	 */
	private class ClearButtonListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			// Clear all input fields
			clearFields();
		}

	}

	// Method to clear all input fields
	private void clearFields() {
		studentIDField.setText("");
		surnameField.setText("");
		middleNameField.setText("");
		firstNameField.setText("");
		aptNumberField.setText("");
		streetNumberField.setText("");
		streetNameField.setText("");
		cityField.setText("");
		provinceField.setText("");
		postalCodeField.setText("");
		cslLoanAmountField.setText("");
		oslLoanAmountField.setText("");

		studentIDField.requestFocusInWindow(); // AFter clear button is clicked it sets the focus of input to studentIDField
												
	}

}
