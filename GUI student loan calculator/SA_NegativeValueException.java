/*
	 * Class Name: SA_NegativeValueException.java		
	 * Purpose: Negative Value Exception Class			
	 * Coder: Suhail Attaelmanan			
	 * Date: Apr 7, 2024			
*/

import javax.swing.JOptionPane;

public class SA_NegativeValueException extends Exception {

	public SA_NegativeValueException() {
		super("Negative value entered. Converting to positive value.");
	}

	/*
	Method Name: displayWarningMessage
	Purpose: To display warning message
	Accepts: no args
	Returns: void
	*/
	public static void displayWarningMessage() {
		JOptionPane.showMessageDialog(null, "Negative value entered. Please convert to positive value.", "Warning",
				JOptionPane.WARNING_MESSAGE);
	}
}
