/*
	 * Class Name: Student.java		
	 * Purpose:	Student Class		
	 * Coder: Suhail Attaelmanan			
	 * Date: Apr 7, 2024			
*/

public class Student {
	private String studentID;
	private String surname;
	private String middleName;
	private String firstName;
	private String aptNumber;
	private String streetNumber;
	private String streetName;
	private String city;
	private String province;
	private String postalCode;
	private double cslLoanAmount;
	private double oslLoanAmount;

	// Constructor
	public Student(String studentID, String surname, String middleName, String firstName, String aptNumber,
			String streetNumber, String streetName, String city, String province, String postalCode,
			double cslLoanAmount, double oslLoanAmount) {
		this.studentID = studentID;
		this.surname = surname;
		this.middleName = middleName;
		this.firstName = firstName;
		this.aptNumber = aptNumber;
		this.streetNumber = streetNumber;
		this.streetName = streetName;
		this.city = city;
		this.province = province;
		this.postalCode = postalCode;
		this.cslLoanAmount = cslLoanAmount;
		this.oslLoanAmount = oslLoanAmount;
	}

	// Getters and Setters:

	public String getStudentID() {
		return studentID;
	}

	public void setStudentID(String studentID) {
		this.studentID = studentID;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public String getMiddleName() {
		return middleName;
	}

	public void setMiddleName(String middleName) {
		this.middleName = middleName;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getAptNumber() {
		return aptNumber;
	}

	public void setAptNumber(String aptNumber) {
		this.aptNumber = aptNumber;
	}

	public String getStreetNumber() {
		return streetNumber;
	}

	public void setStreetNumber(String streetNumber) {
		this.streetNumber = streetNumber;
	}

	public String getStreetName() {
		return streetName;
	}

	public void setStreetName(String streetName) {
		this.streetName = streetName;
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}

	public String getProvince() {
		return province;
	}

	public void setProvince(String province) {
		this.province = province;
	}

	public String getPostalCode() {
		return postalCode;
	}

	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}

	public double getCslLoanAmount() {
		return cslLoanAmount;
	}

	public void setCslLoanAmount(double cslLoanAmount) {
		this.cslLoanAmount = cslLoanAmount;
	}

	public double getOslLoanAmount() {
		return oslLoanAmount;
	}

	public void setOslLoanAmount(double oslLoanAmount) {
		this.oslLoanAmount = oslLoanAmount;
	}

	// toString method
	@Override
	public String toString() {
		return "Student Name: " + firstName + " " + middleName + " " + surname + "\n" + "Student Number: " + studentID
				+ "\n" + "CSL Amount is $" + cslLoanAmount + "\n" + "OSL Amount is $" + oslLoanAmount;
	}

}
