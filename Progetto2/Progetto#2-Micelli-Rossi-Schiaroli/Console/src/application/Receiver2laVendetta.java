package application;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class Receiver2laVendetta extends Thread{


	final int SCROLL_BUFFER_SIZE = 3;

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	private ModelImpl model;
	private JTextArea textArea;
	private String[] words;
	
	public Receiver2laVendetta(SerialCommChannel channel, ModelImpl model) {	
		this.channel = channel;
		this.model = model;
		this.textArea = model.getTextArea();
	}

	public void run() {
		System.out.println("Thread started");
		while (!stop) {
			try {
				this.msg = channel.receiveMsg();
				//model.update("recieved " + msg);
			} catch (Exception e) {
				e.printStackTrace();
			}
			words = msg.split(" ");
			if(words[0].equals("single")) {
				if(words[1].equals("detected")) {
					if(!model.getDetected().isSelected()) {
						model.getDetected().setSelected(true);
					}
				}else {
					if(!model.getDetected().isSelected()) {
						model.getDetected().setSelected(false);
					}
				}
				
			} else if(words[0].equals("auto")) {
				if (words[1].equals("alarm")) {
					if(!model.getAlarm().isSelected()) {
						model.getAlarm().setSelected(true);
						if(words[2].equals("tracking")) {
							if(!model.getTracking().isSelected()) {
								model.getTracking().setSelected(true);
							}
						}
					}else {
						if(model.getAlarm().isSelected()) {
							model.getAlarm().setSelected(false);	
						if(model.getTracking().isSelected()) {
							model.getTracking().setSelected(false);
						}
					}
					}
				}	
			}
		}
		model.update(msg);
	System.out.println("Thread Stopped");
	}

	public void stopT() {
		this.stop = true;
	}
	
	public void restart() {
		this.stop = false;
	}
	
	/*
	 * tutto quello che scrivo is preciso,
	 * tutto lettera piccola e come lo scrivo io
	 * 
	 * stringhe:
	 * se la prima parola is "manual": ricevo quello che vuoi
	 * 						"single": se il led blinka devo ricevere "detected"
	 * 								 come seconda parola poi quello che vuoi
	 * 
	 * 						"auto" se e' in alarm sec parola alarm
	 * 						se e' in track terza parola "tracking"
	 * 						poi quello che vuoi
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
}
