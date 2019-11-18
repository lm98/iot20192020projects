package application;

import message.CommChannel;
import message.SerialCommChannel;

public class ModelImpl implements Model{

	private CommChannel channel;
	
	private void reset() {
		
	}
	
	public ModelImpl(String path) {
		try {
			this.channel = new SerialCommChannel(path,9600);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void sendMsg(String msg){
		this.channel.sendMsg(msg);
	}

	
	
	public void sync() {
		
	}
}
