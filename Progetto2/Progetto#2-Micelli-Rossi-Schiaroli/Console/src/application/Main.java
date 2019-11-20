package application;

public class Main {

	public static void main(String[] args) {
		ControllerImpl controller= new ControllerImpl();
		GUI window = new GUI(controller);
		window.frame.setVisible(true);	
		controller.sync(window.getTextArea());

	}
}
