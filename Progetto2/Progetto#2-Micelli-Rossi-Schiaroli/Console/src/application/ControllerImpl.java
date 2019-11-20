package application;

import jssc.SerialPortList;

import javax.swing.JTextArea;
import message.SerialCommChannel;

public class ControllerImpl {

	private SerialCommChannel channel;
	private String response;
	private volatile boolean threadRunning;
	private Receiver receiver;
	private Thread thread;
	
	public ControllerImpl() {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel(portNames[0],9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
		this.receiver = new Receiver(channel);
		thread = new Thread(receiver);
	}
	
	public void sync(JTextArea textArea) {
		update("Waiting Arduino for rebooting...",textArea);		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		update("Ready.", textArea);	
		update("Sending ping", textArea);
		channel.sendMsg("ping");
		String msg;
		try {
			msg = channel.receiveMsg();
			update("Received: "+msg,textArea);		
			Thread.sleep(500);
			if (msg.equals("pong")) {
				update("System connected",textArea); 
	        }
	        else {
	        	update(msg,textArea);
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	private void update(String msg, JTextArea  textArea) {
		textArea.append("\n");
		textArea.append(msg);
	}
	
	
	public void send(String msg, JTextArea textArea) {
		if (threadRunning) {
			this.receiver.stop();
			this.update(msg, textArea);
			this.threadRunning = false;
		}
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			System.out.println("sending " +msg);
			this.update(msg, textArea);

			try {
				this.response = channel.receiveMsg();
				this.update(response, textArea);

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
	}
}
