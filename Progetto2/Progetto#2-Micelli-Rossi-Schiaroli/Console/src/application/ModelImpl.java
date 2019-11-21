package application;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

public class ModelImpl {

	private JTextArea textArea;
	
	final int SCROLL_BUFFER_SIZE = 3;
	
	
	
	public void init(JTextArea textArea) {
		this.textArea = textArea;
	}
	
	public void update(String msg) {
		  //
		  int numLinesToTrunk = textArea.getLineCount() - SCROLL_BUFFER_SIZE;
		    if(numLinesToTrunk > 0) {
		        try {
		            int posOfLastLineToTrunk = textArea.getLineEndOffset(numLinesToTrunk - 1);
		            textArea.replaceRange("",0,posOfLastLineToTrunk);
		        }
		        catch (BadLocationException ex) {
		            ex.printStackTrace();
		        }
		    }
		    /// fino a qui gestisco la cancellazione delle righe extra
		  textArea.append("\n");
		  textArea.append(msg); 
	}
	
	public JTextArea getTextArea() {
		return this.textArea;
	}
}
