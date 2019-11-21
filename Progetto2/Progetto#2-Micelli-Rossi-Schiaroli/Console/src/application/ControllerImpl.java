package application;

import jssc.SerialPortList;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class ControllerImpl {
	
	final int SCROLL_BUFFER_SIZE = 3;

	private SerialCommChannel channel;
	private String response;
	private volatile boolean threadRunning;
	private Receiver receiver;
	private Thread thread;
	private JTextArea textArea;
	private boolean threadStarted = false;
	private Receiver2laVendetta rec;
	
	public ControllerImpl() {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel(portNames[0],9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
	}
	
	public void sync(JTextArea textArea) {
		///THIS initialize also textArea, if we remove we have to initialize it somewhere else
		this.textArea = textArea;
		rec=new Receiver2laVendetta(channel, textArea);
		update("Waiting Arduino for rebooting...");		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		update("Ready.");	
		update("Sending ping");
		channel.sendMsg("ping");
		String msg;
		try {
			msg = channel.receiveMsg();
			update("Received: "+msg);		
			Thread.sleep(500);
			if (msg.equals("pong")) {
				update("System connected"); 
	        }
	        else {
	        	update(msg);
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.receiver = new Receiver(channel,textArea);
		thread = new Thread(receiver);
	}
	
	private void update(String msg) {
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
		textArea.append("\n");
		textArea.append(msg);
	}
	
	/*
	public void send(String msg) {
		if (threadRunning) {
			try {
				this.thread.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			this.update(msg);
			this.threadRunning = false;
		}
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			System.out.println("sending " +msg);
			this.update(msg);

			try {
				this.response = channel.receiveMsg();
				this.update(response);
				if(!this.response.equals("OK")) {
					System.exit(1);
				}
				System.out.println("starting thread");
				if (!threadStarted) {
					thread = new Thread(receiver);
					this.threadStarted = true;
					this.threadRunning = true;
					thread.start();
				}
			if (!threadRunning) {
				this.thread.notify();
				threadRunning=true;
			}	
			}catch (Exception e) {
				e.printStackTrace();
			}
		}	
	}*/
	
	
	/*public void send(String msg) {
		if (threadRunning) {
			this.thread.destroy();
			this.update(msg);
			this.threadRunning = false;
		}
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			System.out.println("sending " +msg);
			this.update(msg);

			try {
				this.response = channel.receiveMsg();
				this.update(response);

				if(!this.response.equals("OK")) {
					System.exit(1);
				}
				System.out.println("starting thread");
				thread = new Thread(receiver);
				thread.start();
				threadRunning=true;
			}catch (Exception e) {
				e.printStackTrace();
			}
		}	
	}*/
	public void send(String msg) {
		if (threadRunning) {
			rec.stopT();
			this.update(msg);
			this.threadRunning = false;
		}
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			System.out.println("sending " +msg);
			this.update(msg);

			try {
				this.response = channel.receiveMsg();
				this.update(response);

				if(!this.response.equals("OK")) {
					System.exit(1);
				}
				System.out.println("starting thread");
				rec.start();
				threadRunning=true;
			}catch (Exception e) {
				e.printStackTrace();
			}
		}	
	}
}
