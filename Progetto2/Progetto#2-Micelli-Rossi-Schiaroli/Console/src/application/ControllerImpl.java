package application;

import jssc.SerialPortList;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class ControllerImpl {
	

	private SerialCommChannel channel;
	private String response;
	private volatile boolean threadRunning = false;
	private volatile boolean threadExist = false;
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
			//msg = "m";
			Thread.sleep(500);
			if (msg.equals("m")) {
				model.update("System connected"); 
				//sets the initial mode
				model.setMode(msg);
				model.update("System connected"); 
				rec.start();
				threadExist = true;
	        }
	        else if(msg.equals("s") || msg.equals("a")){
				model.update("System connected"); 
				//sets the initial mode
				model.setMode(msg);
				rec.start();
				threadExist = true;
			} else {
	        	model.update("error receiving the message");
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//solo per testare
		/*
		 * model.setMode("m"); if(!threadExist) { rec.start(); threadExist = true; }
		 */
		//this.receiver = new Receiver(channel,textArea);
		//thread = new Thread(receiver);
	}
	
	public void sendMode(String msg) {
		/*
		 * if (threadRunning) { //rec.wait(); try { rec.sleep(150); } catch
		 * (InterruptedException e) { // TODO Auto-generated catch block
		 * e.printStackTrace(); } //rec.stopT(); this.threadRunning = false; }
		 */
		//MANDO MESSAGGIO
		//LA PRIMA VOLTA CHE PASSO MANDO IL MESSAGGIO E STARTO IL THREAD		
		model.update("changing mode to "+msg);
		channel.sendMsg(msg);
		model.setMode(msg);
		try {
			this.response = channel.receiveMsg();
			model.update("response "+response);	
			//	if(!this.response.equals("OK")) {
			//	System.exit(1);
			//}
		} catch (Exception e) {
			e.printStackTrace();
		}	
		//ALTRIMENTI MANDO LA NOTIFY
		/*
		 * if(!threadRunning) { //SE IL THREAD NON ESISTE LO CREO, if(!threadExist) {
		 * rec.start(); threadExist = true; }else { //rec.notify(); //rec.restart();
		 * //rec.run(); } threadRunning = true; }
		 */
		
	}
	
	public void send1(String msg) {
		///SE STA ANDANDO FERMO IL THREAD
		if (threadRunning) {
			//rec.wait();
			try {
				rec.sleep(150);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			//rec.stopT();
			model.update(msg);
			this.threadRunning = false;
		}
		//MANDO MESSAGGIO
		//LA PRIMA VOLTA CHE PASSO MANDO IL MESSAGGIO E STARTO IL THREAD
		if(!msg.equals(null)|| !msg.equals("")) {
			model.update("sending "+msg);
			channel.sendMsg(msg);
			try {
				this.response = channel.receiveMsg();
				model.update("response "+response);	
			//	if(!this.response.equals("OK")) {
			//	System.exit(1);
			//}
			} catch (Exception e) {
				e.printStackTrace();
			}	
		}
		
		//ALTRIMENTI MANDO LA NOTIFY
		if(!threadRunning) {
			//SE IL THREAD NON E' CREATO LO CREO,
			/*if(!threadExist) {
				rec.start();
				threadExist = true;
			}else {*/
				//rec.notify();
				//rec.restart();
				//rec.run();
			//}
			threadRunning = true;			
		}
	}
		public void send(String msg) {
			//MANDO MESSAGGIO
			//LA PRIMA VOLTA CHE PASSO MANDO IL MESSAGGIO E STARTO IL THREAD
			if(!msg.equals(null)|| !msg.equals("")) {
				model.update("sending "+msg);
				channel.sendMsg(msg);
				try {
					this.response = channel.receiveMsg();
					model.update("response "+response);	
				//	if(!this.response.equals("OK")) {
				//	System.exit(1);
				//}
				} catch (Exception e) {
					e.printStackTrace();
				}	
			}
		}
		
}
