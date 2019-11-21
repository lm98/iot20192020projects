package application;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class Receiver2laVendetta extends Thread{


	final int SCROLL_BUFFER_SIZE = 3;

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	private ModelImpl model;
	private JTextArea textArea;
	private String[] words;
	
	public Receiver2laVendetta(SerialCommChannel channel, ModelImpl model) {	
		this.channel = channel;
		this.model = model;
		this.textArea = model.getTextArea();
	}
	 
	public void run() {
		System.out.println("Thread started");
		while (!stop) {
			try {
				this.msg = channel.receiveMsg();
				model.update("recieved " + msg);
			} catch (Exception e) {
				e.printStackTrace();
			}
			words = msg.split(" ");
		}
		System.out.println("Thread Stopped");
	}

	public void stopT() {
		this.stop = true;
	}
}
