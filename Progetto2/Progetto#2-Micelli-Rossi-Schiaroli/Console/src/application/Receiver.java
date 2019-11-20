package application;

import message.SerialCommChannel;

//Thread who recieves every message
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
		System.out.println("Thread started");
		while(!stop) {
			try {
				this.msg = channel.receiveMsg();
				System.out.println(msg);
				System.out.println("recieved "+ msg);
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
		System.out.println("Thread Stopped");
	}
	
	public void stop() {
		this.stop = true;
	}
}
