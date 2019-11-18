package application;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import message.CommChannel;
import message.SerialCommChannel;

public class Controller{

	
	private CommChannel channel;
	@FXML 
	private TextArea text;
	
	public Controller() throws Exception {
		//this.channel  = new SerialCommChannel("dev/ttyACM0",9600);
	}
	
	private void sync() throws InterruptedException {
		System.out.println("Waiting Arduino for rebooting...");	
		Thread.sleep(4000);
		System.out.println("Ready.");
	}
	
	public void run() throws Exception {
		this.sync();
		while (true){
			text.setText("Sending ping");
			System.out.println("Sending ping");
			channel.sendMsg("ping");
			String msg = channel.receiveMsg();
			text.setText("Received: "+msg);		
			Thread.sleep(500);
		}
	}
	
}
