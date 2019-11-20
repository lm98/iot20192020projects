package application;

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import javax.swing.JTextArea;
import javax.swing.JTabbedPane;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.text.BadLocationException;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JRadioButton;

public class GUI {
    //sostituire con interfaccia
	JFrame frame;
	private JTextField angleField;
	private JTextField speedFieldSingle;
	private JTextField speedFieldAuto;
	private JTextArea textArea;

	/**
	 * Launch the application.
	 */

	public JTextArea getTextArea() {
		return this.textArea;
	}
	/**
	 * Create the application.
	 */
	public GUI(ControllerImpl controller) {
		
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		
		textArea= new JTextArea();
		textArea.setRows(5);
		frame.getContentPane().add(textArea, BorderLayout.SOUTH);
		
		textArea.setText("Welcome");
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		JPanel manualPanel = new JPanel();
		JPanel singlePanel = new JPanel();
		JPanel autoPanel = new JPanel();
		
		//MANUAL
		tabbedPane.addTab("Manual", manualPanel);
		manualPanel.setLayout(null);
		JButton activeManual = new JButton("Active");
		activeManual.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.send("m");
				angleField.setText("");
			}
		});
		activeManual.setBounds(135, 12, 117, 25);
		manualPanel.add(activeManual);
		angleField = new JTextField();
		angleField.setBounds(40, 84, 114, 19);
		manualPanel.add(angleField);
		angleField.setColumns(10);
		
		JButton sendAngle = new JButton("send angle");
		sendAngle.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println(angleField.getText());
				controller.send(angleField.getText());
				angleField.setText("");
			}
		});
		sendAngle.setBounds(203, 81, 117, 25);
		manualPanel.add(sendAngle);
		
		//SINGLE TAb
		tabbedPane.addTab("Single", singlePanel);
		singlePanel.setLayout(null);
		
		JButton activeSingle = new JButton("Active");
		activeSingle.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.send("s");
			}
		});
		activeSingle.setBounds(139, 12, 117, 25);
		singlePanel.add(activeSingle);
		
		speedFieldSingle = new JTextField();
		speedFieldSingle.setBounds(60, 79, 114, 19);
		singlePanel.add(speedFieldSingle);
		speedFieldSingle.setColumns(10);
		JButton sendSpeedS = new JButton("send speed");
		sendSpeedS.setName("sendS");
		sendSpeedS.setBounds(249, 76, 117, 25);
		sendSpeedS.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.send(speedFieldSingle.getText());
				speedFieldSingle.setText("");
			}
		});
		singlePanel.add(sendSpeedS);
		
		//AUTO PANEL
		tabbedPane.addTab("Auto", autoPanel);
		autoPanel.setLayout(null);
		
		JButton activeAuto = new JButton("Active");
		activeAuto.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.send("a");
			}
		});
		activeAuto.setBounds(149, 12, 117, 25);
		autoPanel.add(activeAuto);
		
		speedFieldAuto = new JTextField();
		speedFieldAuto.setBounds(25, 59, 114, 19);
		autoPanel.add(speedFieldAuto);
		speedFieldAuto.setColumns(10);
		
		JButton sendSpeedA = new JButton("send speed");
		sendSpeedA.setBounds(25, 90, 117, 25);
		sendSpeedA.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.send(speedFieldAuto.getText());
				speedFieldAuto.setText("");
			}
		});
		autoPanel.add(sendSpeedA);
		
		JRadioButton alarm = new JRadioButton("Alarm");
		alarm.setEnabled(false);
		alarm.setBounds(243, 45, 149, 23);
		autoPanel.add(alarm);
		
		JRadioButton tracking = new JRadioButton("Tracking");
		tracking.setEnabled(false);
		tracking.setBounds(243, 91, 149, 23);
		autoPanel.add(tracking);
		
		frame.getContentPane().add(tabbedPane, BorderLayout.CENTER);
	}
	
}
