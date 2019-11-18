package application;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import message.CommChannel;
import message.SerialCommChannel;

public class UIController{

	
	private CommChannel channel;
	@FXML 
	private TextArea text;
	
	public UIController(String path) {
		try {
			this.channel  = new SerialCommChannel(path,9600);
			System.out.println("Waiting Arduino for rebooting...");	
			Thread.sleep(4000);
			System.out.println("Ready.");		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void run() throws Exception {
		while (true){
			text.setText("Sending ping");
			//System.out.println("Sending ping");
			channel.sendMsg("ping");
			String msg = channel.receiveMsg();
			text.setText("Received: "+msg);		
			Thread.sleep(500);
		}
	}
	
	@FXML
	private void getTab(ActionEvent event) {
	}
	
}
