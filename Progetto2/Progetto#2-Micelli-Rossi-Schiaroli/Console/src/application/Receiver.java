package application;

import message.SerialCommChannel;

public class Receiver extends Thread{


	private final int DETECTED = 2;
	private final int ALARM = 2;
	private final int TRACKING = 3;
	
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
			
			if (channel.isMsgAvailable()) {
				try {
					this.msg = channel.receiveMsg();
				} catch (Exception e) {
					e.printStackTrace();
				}
				//if msg begins with c, s or a divide the string in words
				if (msg.startsWith("c")||msg.startsWith("s")||msg.startsWith("a")) {
					words = msg.split(" ");
					int args = words.length;
					//CHANGING MODE?
					if (words[0].equals("c")) {
						model.update("changing mode");
						//it's 2 words for sure
						model.setMode(words[1]);
					}
					
					//SINGLE MODE?
					if(words[0].equals("s")) {
						if( args == DETECTED ) {
							if(!model.getDetected().isSelected()) {
								model.getDetected().setSelected(true);
							}
						}else {
							if(model.getDetected().isSelected()) {
								model.getDetected().setSelected(false);
							}
						}	
					} 
					
					//AUTO MODE?
					if(words[0].equals("a")) {
						if (args == ALARM) {
							if(!model.getAlarm().isSelected()) {
								model.getAlarm().setSelected(true);
							}
							if(model.getTracking().isSelected()) {
								model.getTracking().setSelected(false);
							}
						}else if (args == TRACKING) {
							if(!model.getAlarm().isSelected()) {
								model.getAlarm().setSelected(true);
							}
							if(!model.getTracking().isSelected()) {
								model.getTracking().setSelected(true);
							}
							
						} else {
							if(model.getAlarm().isSelected()) {
								model.getAlarm().setSelected(false);
							}
							if(model.getTracking().isSelected()) {
								model.getTracking().setSelected(false);
							}
						}
					}
				}else {
					//else simply print on gui
					model.update(msg);	
				}
			}

		}
	System.out.println("Thread Stopped");
	}

	public void stopT() {
		this.stop = true;
	}
	
	public void restart() {
		this.stop = false;
	}
}
