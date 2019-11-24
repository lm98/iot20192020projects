package application;

public class Main {

	public static void main(String[] args) {
		ModelImpl model = new ModelImpl();
		ControllerImpl controller= new ControllerImpl(model);
		GUI window = new GUI(controller);
		window.frame.setVisible(true);	
		model.init(window);
		controller.sync();

	}
}
