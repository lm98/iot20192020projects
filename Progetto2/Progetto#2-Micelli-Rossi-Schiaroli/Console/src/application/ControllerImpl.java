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
	private JTextArea textArea;
	public ControllerImpl() {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel(portNames[0],9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
	}
	
	public void sync(JTextArea textArea) {
		this.textArea = textArea;
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
		textArea.append("\n");
		textArea.append(msg);
	}
	
	
	public void send(String msg) {
		if (threadRunning) {
			this.receiver.stop();
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
	}
}
