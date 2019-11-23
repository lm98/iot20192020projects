package application;

import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import message.SerialCommChannel;

public class Receiver extends Thread{


	final int SCROLL_BUFFER_SIZE = 3;

	private SerialCommChannel channel;
	private String msg;
	private volatile boolean stop = false;
	private ModelImpl model;
	private String[] words;
	
	public Receiver(SerialCommChannel channel, ModelImpl model) {	
		this.channel = channel;
		this.model = model;
	}

	public void run() {
		System.out.println("Thread started");
		while (!stop) {
			//if (channel.isMsgAvailable()) {
				try {
					this.msg = channel.receiveMsg();
					//model.update("recieved " + msg);
				} catch (Exception e) {
					e.printStackTrace();
				}
				//scompongo la stringa in parole
				words = msg.split(" ");
				//CHANGING MODE?
				if (words[0].equals("c")) {
					model.update("changing mode");
					model.setMode(words[1]);
				}
				//SINGLE MODE?
				if(words[0].equals("s")) {
					if(words[1].equals("dtct")) {
						if(!model.getDetected().isSelected()) {
							model.getDetected().setSelected(true);
						}
					}else {
						if(!model.getDetected().isSelected()) {
							model.getDetected().setSelected(false);
						}
					}	
				} 
				//AUTO MODE?
				if(words[0].equals("a")) {
					
					if (words[1].equals("alrm")) {
						if(!model.getAlarm().isSelected()) {
							model.getAlarm().setSelected(true);
							if(words[2].equals("trck")) {
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
			//}
			model.update(msg);
		}
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
	 * se la prima parola is "m": ricevo quello che vuoi
	 * 						"s": se il led blinka devo ricevere "dtct"
	 * 								 come seconda parola poi quello che vuoi
	 * 
	 * 						"a" se e' in alarm sec parola "alrm"
	 * 						se e' in track terza parola "trck"
	 * 						poi quello che vuoi	 
	 * 
	 */
}
