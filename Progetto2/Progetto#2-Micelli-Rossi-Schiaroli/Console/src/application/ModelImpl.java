package application;

import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

public class ModelImpl {
	
	final int SCROLL_BUFFER_SIZE = 9;
	
	private GUI gui;
	private String mode;
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
	
	public JRadioButton getAlarm() {
		return this.gui.getAlarm();
	}
	
	public JRadioButton getTracking() {
		return this.gui.getTracking();
	}
	
	public JRadioButton getDetected() {
		return this.gui.getTracking();
	}
	
	private void exitMan() {
		this.gui.getActiveManual().setEnabled(true);
		this.gui.getSendAngle().setEnabled(false);
	}
	
	private void exitSingle() {
		this.gui.getActiveSingle().setEnabled(true);
	}
	
	private void exit() {
	}
	
	public void setMode(String mode) {
		this.mode = mode;
	}
	
}
