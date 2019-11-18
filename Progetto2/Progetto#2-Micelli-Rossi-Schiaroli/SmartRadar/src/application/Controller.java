package application;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextArea;
import message.CommChannel;
import message.SerialCommChannel;

public class Controller implements Initializable{

	
	private CommChannel channel;
	@FXML 
	private TextArea text;
	
	public Controller() {
	}

	private void connect() {
		try {
			this.channel  = new SerialCommChannel("dev/ttyUSB0",9600);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void update(String s) {
		text.appendText("\n");
		text.appendText(s);
	}

	private void sync() {
		this.update("Waiting Arduino for rebooting...");		
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.update("Ready.");	
	}
	
	public void run() {
			try {
			this.update("Sending ping");
			channel.sendMsg("ping");
			String msg;	
			msg = channel.receiveMsg();	
			this.update("Received: "+msg);		
			Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// TODO Auto-generated method stub
		text.setText("Funziona?");
		this.connect();
		this.sync();

	}
}
