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
	private Receiver2laVendetta rec;
	private ModelImpl model;
	
	public ControllerImpl(ModelImpl model) {
		String[] portNames = SerialPortList.getPortNames();
		try {
			this.channel = new SerialCommChannel(portNames[0],9600);
		} catch (Exception e) {
			e.printStackTrace();
			}
		this.model = model;
	}
	
	public void sync() {
		///THIS initialize also textArea, if we remove we have to initialize it somewhere else
		rec = new Receiver2laVendetta(channel,this.model);
		model.update("Waiting Arduino for rebooting...");		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		model.update("Ready.");	
		model.update("Sending ping");
		channel.sendMsg("ping");
		String msg;
		try {
			msg = channel.receiveMsg();
			model.update("Received: "+msg);		
			Thread.sleep(500);
			if (msg.equals("pong")) {
				model.update("System connected"); 
	        }
	        else {
	        	model.update(msg);
	            System.exit(1);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//this.receiver = new Receiver(channel,textArea);
		//thread = new Thread(receiver);
	}
	
	public void send(String msg) {
		///SE STA ANDANDO FERMO IL THREAD
		if (threadRunning) {
			try {
				//rec.wait();
				rec.sleep(150);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			model.update(msg);
			this.threadRunning = false;
		}
		//MANDO MESSAGGIO
		//LA PRIMA VOLTA CHE PASSO MANDO IL MESSAGGIO E STARTO IL THREAD
		if(!msg.equals(null)|| !msg.equals("")) {
			channel.sendMsg(msg);
			System.out.println("sending " +msg);
			model.update(msg);
			try {
				this.response = channel.receiveMsg();
				System.out.println(response);
				
			//	if(!this.response.equals("OK")) {
			//	System.exit(1);
			//}
			}catch (Exception e) {
				e.printStackTrace();
			}	
		}
		
		//ALTRIMENTI MANDO LA NOTIFY
		if(!threadRunning) {
			//SE IL THREAD NON E' CREATO LO CREO,
			if(!threadExist) {
				rec.start();
				threadExist = true;
			}else {
				//rec.notify();
			}
			threadRunning = true;			
		}
		
	}
}
