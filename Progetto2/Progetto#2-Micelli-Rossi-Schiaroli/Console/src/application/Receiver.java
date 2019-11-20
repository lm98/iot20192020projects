package application;

import javax.swing.JTextArea;

import message.SerialCommChannel;

//Thread who recieves every message
public class Receiver implements Runnable {

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	private JTextArea textArea;

	public Receiver(SerialCommChannel channel, JTextArea textArea) {
		this.channel = channel;
		this.textArea = textArea;
	}

	
	  private void update(String msg) {
		  textArea.append("\n");
		  textArea.append(msg); 
	  }
	 
	@Override
	public void run() {
		update("Thread started");
		while (!stop) {
			try {
				this.msg = channel.receiveMsg();
				System.out.println(msg);
				System.out.println("recieved " + msg);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		System.out.println("Thread Stopped");
	}

	public void stop() {
		this.stop = true;
	}
}
