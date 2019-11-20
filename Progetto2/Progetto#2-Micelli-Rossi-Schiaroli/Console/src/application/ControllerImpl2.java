package application;

import jssc.SerialPortList;
import message.SerialCommChannel;

public class ControllerImpl2 {

	private SerialCommChannel channel;
	private String response;
	public ControllerImpl2() {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel(portNames[0],9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
		this.sync();
	}

	private void sync() {
		System.out.println("Waiting Arduino for rebooting...");		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Ready.");	
		System.out.println("Sending ping");
		channel.sendMsg("ping");
		String msg;
		try {
			msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
			if (msg.equals("pong")) {
				System.out.println("System connected"); 
	        }
	        else {
	            System.out.println(msg);
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public void send(String msg) {
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			try {
				this.response = channel.receiveMsg();
				System.out.println(response);
				if(!this.response.equals("OK")) {
					System.exit(1);
				} 
			}catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
