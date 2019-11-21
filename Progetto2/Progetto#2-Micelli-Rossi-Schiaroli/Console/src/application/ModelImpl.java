package application;

import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

public class ModelImpl {
	
	final int SCROLL_BUFFER_SIZE = 3;
	
	private GUI gui;
	
	public void init(GUI gui) {
		this.gui = gui;
	}
	
	public void update(String msg) {
		  //
		  int numLinesToTrunk = gui.getTextArea().getLineCount() - SCROLL_BUFFER_SIZE;
		    if(numLinesToTrunk > 0) {
		        try {
		            int posOfLastLineToTrunk = gui.getTextArea().getLineEndOffset(numLinesToTrunk - 1);
		            gui.getTextArea().replaceRange("",0,posOfLastLineToTrunk);
		        }
		        catch (BadLocationException ex) {
		            ex.printStackTrace();
		        }
		    }
		    /// fino a qui gestisco la cancellazione delle righe extra
		 gui.getTextArea().append("\n");
		 gui.getTextArea().append(msg); 
	}
	
	public JTextArea getTextArea() {
		return gui.getTextArea();
	}
}
