package application;

import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

public class ModelImpl {
	
	final int SCROLL_BUFFER_SIZE = 9;
	
	private GUI gui;
	private String mode = "Not specified";
	
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
		    //to delete the extra lines
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
		this.update("exiting Manual mode");
		this.gui.getActiveManual().setEnabled(true);
		this.gui.getSendAngle().setEnabled(false);
	}
	
	private void exitSingle() {
		this.update("exiting Single mode");
		this.gui.getActiveSingle().setEnabled(true);
		this.gui.getSendSpeedS().setEnabled(false);
		this.gui.getDetected().setSelected(false);
	}
	
	private void exitAuto() {
		this.update("exiting Auto mode");
		this.gui.getActiveAuto().setEnabled(true);
		this.gui.getSendSpeedA().setEnabled(false);
		this.gui.getAlarm().setSelected(false);
		this.gui.getTracking().setSelected(false);
	}
	
	
	private void enterMode(String mode) {
		if (mode.equals("m")) {
			this.gui.getActiveManual().setEnabled(false);
			this.gui.getSendAngle().setEnabled(true);
		}else if(mode.equals("s")) {
			this.gui.getActiveSingle().setEnabled(false);
			this.gui.getSendSpeedS().setEnabled(true);
		}else if(mode.equals("a")) {
			this.gui.getActiveAuto().setEnabled(false);
			this.gui.getSendSpeedA().setEnabled(true);
		}
	}

	private void exitCurrentMode() {
		if (mode.equals("m")) {
			this.exitMan();
		}else if(mode.equals("s")) {
			this.exitSingle();
		}else if(mode.equals("a")) {
			this.exitAuto();
		}
	}
	
	public void setMode(String mode) {
		if(!this.mode.equals(mode)) {
			this.exitCurrentMode();
			this.mode = mode;
			this.update("Entering "+mode +" mode");
			this.enterMode(mode);
		}
	}
	
}
