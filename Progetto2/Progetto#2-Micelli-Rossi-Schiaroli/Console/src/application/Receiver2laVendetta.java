package application;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class Receiver2laVendetta extends Thread{


	final int SCROLL_BUFFER_SIZE = 3;

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	private JTextArea textArea;

	public Receiver2laVendetta(SerialCommChannel channel, JTextArea textArea) {
		
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
		this.channel = channel;
		this.textArea = textArea;
	}

	
	  private void update(String msg) {
		  textArea.append("\n");
		  textArea.append(msg); 
	  }
	 
	public void run() {
		System.out.println("Thread started");
		while (!stop) {
			try {
				this.msg = channel.receiveMsg();
				update("recieved " + msg);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		System.out.println("Thread Stopped");
	}

	public void stopT() {
		this.stop = true;
	}
}
