package application;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import message.CommChannel;
import message.SerialCommChannel;

public class Controller implements Initializable{

	
	private CommChannel channel;
	@FXML 
	private TextArea text;
	@FXML 
	private TextField temp;
	@FXML 
	private Button manualButton;
	
	
	public Controller() {
	}

	private void connect() {
		try {
			this.channel  = new SerialCommChannel("/dev/ttyACM0",9600);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("Qua non funziona niente");
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
			this.update("Sending modality");
			channel.sendMsg("s");
			
			String msg;	
			msg = channel.receiveMsg();
			System.out.println(msg);
			this.update("Received: "+msg);		
			Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("Qua non funziona niente");
			}
		}
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		// TODO Auto-generated method stub
		//text.setText("Funziona?");
		this.connect();
		this.sync();

	}
	
	public void send() {
		channel.sendMsg(this.temp.getText());
		//System.out.println(this.temp.getText());
	}
	
	public void showAngle() {
		System.out.println("a");
	}
	
	public void register(ActionEvent event) {
		
	}
	
	public void s0() {
		System.out.println("mando 0");
		channel.sendMsg("0");
	}
	public void s90() {
		System.out.println("mando 90");
		channel.sendMsg("90");
	}
	public void s180() {
		System.out.println("mando 180");
		channel.sendMsg("180");
	}
	public void s360() {
		System.out.println("mando 360");
		channel.sendMsg("360");
	}
	public void s2000() {
		System.out.println("mando 2000");
		channel.sendMsg("2000");
	}
}
