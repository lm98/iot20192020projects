package application;

import jssc.SerialPortList;
import message.SerialCommChannel;

public class ControllerImpl {
	

	private SerialCommChannel channel;
	private String response;
	private Receiver rec;
	private ModelImpl model;
	
	public ControllerImpl(ModelImpl model) {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel("COM5",9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
		this.model = model;
	}
	
	public void sync() {
		///THIS initialize also textArea, if we remove we have to initialize it somewhere else
		rec = new Receiver(channel,this.model);
		model.update("Waiting Arduino for rebooting...");		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		model.update("Ready.");	
		model.update("Sending connecting");
		channel.sendMsg("connecting");
		String msg;
		try {
			msg = channel.receiveMsg();
			model.update("Received: "+msg);
			Thread.sleep(500);
			if (msg.equals("m")) {
				model.update("System connected"); 
				//sets the initial mode
				model.setMode(msg);
				model.update("System connected"); 
				rec.start();
	        }
	        else if(msg.equals("s") || msg.equals("a")){
				model.update("System connected"); 
				//sets the initial mode
				model.setMode(msg);
				rec.start();
			} else {
	        	model.update("error receiving the message");
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void sendMode(String msg) {
		model.update("changing mode to "+msg);
		channel.sendMsg(msg);
		model.setMode(msg);
		try {
			this.response = channel.receiveMsg();
			model.update("response "+response);	
		} catch (Exception e) {
			e.printStackTrace();
		}	
		//ALTRIMENTI MANDO LA NOTIFY
	}
	
		public void send(String msg) {
			//send message
			if(!msg.equals(null)|| !msg.equals("")) {
				model.update("sending "+msg);
				channel.sendMsg(msg);
				try {
					this.response = channel.receiveMsg();
					model.update("response "+response);	
				} catch (Exception e) {
					e.printStackTrace();
				}	
			}
		}
		
}
