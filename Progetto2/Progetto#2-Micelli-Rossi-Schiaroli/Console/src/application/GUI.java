package application;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JTabbedPane;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JRadioButton;

public class GUI {
    //sostituire con interfaccia
	JFrame frame;
	private IntegerJTextField angleField;
	private IntegerJTextField speedFieldSingle;
	private IntegerJTextField speedFieldAuto;
	private JTextArea textArea;

	private JButton activeManual;
	private JButton activeSingle;
	private JButton activeAuto;
	
	private JButton sendAngle; 
	private JButton sendSpeedA;
	private JButton sendSpeedS;
	
	private JRadioButton tracking;
	private JRadioButton alarm;
	private JRadioButton detected;

	private boolean checkAngle() {
		Integer angle = Integer.parseInt(angleField.getText());
		if(angle>=0 && angle <= 180) {
			return true;
		} 
		textArea.append("\n");
		textArea.append("send a reasonable angle between 0 & 180");
		return false;
	}
	
	private boolean checkSpeedS() {
		Integer speed = Integer.parseInt(speedFieldSingle.getText());
		if(speed>=0 && speed <= 500) {
			return true;
		} 
		textArea.append("\n");
		textArea.append("send a reasonable speed between 0 & 500");
		return false;
	}
	
	private boolean checkSpeedA() {
		Integer speed = Integer.parseInt(speedFieldAuto.getText());
		if(speed>=0 && speed <= 500) {
			return true;
		} 
		textArea.append("\n");
		textArea.append("send a reasonable speed between 0 & 500");
		return false;
	}
	
	//getter for JTextArea
	public JTextArea getTextArea() {
		return this.textArea;
	}	
	//getter for JRadioButton
	public JRadioButton getTracking() {
		return this.tracking;
	}
	public JRadioButton getAlarm() {
		return this.alarm;
	}
	public JRadioButton getDetected() {
		return this.detected;
	}
	//getter for JButton
	public JButton getActiveManual() {
		return this.activeManual;
	}
	public JButton getActiveSingle() {
		return this.activeSingle;
	}
	public JButton getActiveAuto() {
		return this.activeAuto;
	}
	public JButton getSendAngle() {
		return this.sendAngle;
	}
	public JButton getSendSpeedS() {
		return this.sendSpeedS;
	}
	public JButton getSendSpeedA() {
		return this.sendSpeedA;
	}
	
	/**
	 * Create the gui.
	 */
	public GUI(ControllerImpl controller) {
		
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 450);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		frame.setResizable(false);
		textArea= new JTextArea();
		textArea.setRows(10);
		frame.getContentPane().add(textArea, BorderLayout.SOUTH);
		
		textArea.setText("Welcome");
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		JPanel manualPanel = new JPanel();
		JPanel singlePanel = new JPanel();
		JPanel autoPanel = new JPanel();
		
		//MANUAL TAB
		tabbedPane.addTab("Manual", manualPanel);
		manualPanel.setLayout(null);
		activeManual = new JButton("Active");
		activeManual.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.sendMode("m");
			}
		});
		activeManual.setBounds(135, 12, 117, 25);
		manualPanel.add(activeManual);
		angleField = new IntegerJTextField();
		angleField.setBounds(40, 84, 114, 19);
		manualPanel.add(angleField);
		angleField.setColumns(10);
		
		sendAngle = new JButton("send angle");
		sendAngle.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(checkAngle()) {
					controller.send(angleField.getText());
				}
				angleField.setText("");
			}
		});
		sendAngle.setBounds(203, 81, 117, 25);
		manualPanel.add(sendAngle);
		sendAngle.setEnabled(false);
		
		//SINGLE TAb
		tabbedPane.addTab("Single", singlePanel);
		singlePanel.setLayout(null);
		
		activeSingle = new JButton("Active");
		activeSingle.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.sendMode("s");
			}
		});
		activeSingle.setBounds(139, 12, 117, 25);
		singlePanel.add(activeSingle);
		
		speedFieldSingle = new IntegerJTextField();
		speedFieldSingle.setBounds(25, 59, 114, 19);
		singlePanel.add(speedFieldSingle);
		speedFieldSingle.setColumns(10);
		sendSpeedS = new JButton("send speed");
		sendSpeedS.setEnabled(false);
		sendSpeedS.setName("sendS");
		sendSpeedS.setBounds(25, 90, 117, 25);
		sendSpeedS.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(checkSpeedS()) {
					controller.send(speedFieldSingle.getText());
				}
				speedFieldSingle.setText("");
			}
		});
		singlePanel.add(sendSpeedS);
		
		detected = new JRadioButton("object found");
		detected.setEnabled(false);
		detected.setBounds(243, 45, 149, 23);
		singlePanel.add(detected);
		
		//AUTO TAB
		tabbedPane.addTab("Auto", autoPanel);
		autoPanel.setLayout(null);
		
		activeAuto = new JButton("Active");
		activeAuto.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.sendMode("a");
			}
		});
		activeAuto.setBounds(149, 12, 117, 25);
		autoPanel.add(activeAuto);
		
		speedFieldAuto = new IntegerJTextField();
		speedFieldAuto.setBounds(25, 59, 114, 19);
		autoPanel.add(speedFieldAuto);
		speedFieldAuto.setColumns(10);
		
		sendSpeedA = new JButton("send speed");
		sendSpeedA.setEnabled(false);
		sendSpeedA.setBounds(25, 90, 117, 25);
		sendSpeedA.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(checkSpeedA()) {
					controller.send(speedFieldSingle.getText());
				}
				speedFieldSingle.setText("");
			}
		});
		autoPanel.add(sendSpeedA);
		
		alarm = new JRadioButton("Alarm");
		alarm.setEnabled(false);
		alarm.setBounds(243, 45, 149, 23);
		autoPanel.add(alarm);
		
		tracking = new JRadioButton("Tracking");
		tracking.setEnabled(false);
		tracking.setBounds(243, 91, 149, 23);
		autoPanel.add(tracking);
		
		frame.getContentPane().add(tabbedPane, BorderLayout.CENTER);
	}
	
}
