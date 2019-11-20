package application;

import message.SerialCommChannel;

public class Receiver implements Runnable {

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	
	public Receiver(SerialCommChannel channel) {
		this.channel = channel;
		//this.text = text;
	}
	
	@Override
	public void run() {
		while(!stop) {
			try {
				this.msg = channel.receiveMsg();
				System.out.println(msg);
				System.out.println("recieved "+ msg);
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	public void stop() {
		this.stop = true;
	}
}
