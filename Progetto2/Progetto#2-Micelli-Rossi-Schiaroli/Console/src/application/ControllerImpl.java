package application;

import java.util.Scanner;

import jssc.SerialPortList;
import message.CommChannel;
import message.SerialCommChannel;

public class ControllerImpl {
	
	private CommChannel channel;
	private Scanner scanner;
	private String mode;
	private String angle;
	private String response;
	private String input;
	
	public ControllerImpl() {
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
	
	public void chooseMode() {
		System.out.println("Welcome!");
		System.out.println("Write m to choose Manual mode");
		System.out.println("Write s to choose Single mode");
		System.out.println("Write a to choose Auto mode");
		mode = scanner.nextLine();
		if (mode.equals("m") || mode.equals("M")){
			channel.sendMsg(mode);
			this.waitForOk();
			this.manualMode();
		}else if(mode.equals("s") || mode.equals("S")){
			channel.sendMsg(mode);
			this.waitForOk();
			this.singleMode();
		}else if(mode.equals("a") || mode.equals("A")){
			channel.sendMsg(mode);
			this.waitForOk();
			this.singleMode();
		}
}

	private void waitForOk(){
		try {
			this.response = channel.receiveMsg();
			System.out.println(response);
			if(response.startsWith("OK")) {
				//TODO
			}else {
				System.exit(1);
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	private void wornTheIdiots() {
		System.out.println("Press q to exit manual mode");
	}
	
	//come back to change mode if input == q
	private void checkExitCond(String input) {
		if (input.equals("q")){
			input = null;
			this.chooseMode();
		}
	}
	
	private void manualMode() {
		this.wornTheIdiots();
		while (true){
			System.out.println("write the angle between 0 and 180: ");
			this.angle = scanner.nextLine();
			this.checkExitCond(this.angle); 
			Integer intAngle = Integer.parseInt(angle);
			if(intAngle <= 180 || intAngle >= 0) {
				channel.sendMsg(this.angle);
				this.listenM();
			}else {
				System.out.println("Try agin pal ;)");
			}
		}
	}
	
	private void listenM() {
		// TODO Auto-generated method stub
		
	}

	private void singleMode() {
		this.wornTheIdiots();
		this.listenS();
	}

	private void checkSpeed() {
		//if input is not null check if user wants to change mode else send that message 
		//and reset input to null
		if(!this.input.equals(null)) {
			this.checkExitCond(input);
			this.channel.sendMsg(input);
			Integer intInput = Integer.parseInt(input);
			if(intInput <= 10 || intInput >= 3) {
				channel.sendMsg(this.input);
			}
			this.input = null;
			this.input=scanner.nextLine();
		}
	}

		private void listenS() {
			this.input = scanner.nextLine();
			while(true) {
				checkSpeed();
				try {
					System.out.println(channel.receiveMsg());
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

		public void send() {
			// TODO Auto-generated method stub
			
		}
}
