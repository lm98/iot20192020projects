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
	private void update() {
		text.appendText("\n");
		text.appendText("ADLEDEF");
	}

	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// TODO Auto-generated method stub
		text.setText("Funziona?");
		this.connect();
		
	}
}
