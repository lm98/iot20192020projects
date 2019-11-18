package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
	

	@Override
	public void start(Stage primaryStage) {
		try {
			FXMLLoader loader = new FXMLLoader(getClass().getResource("View.fxml"));
			Controller controller = new Controller();
			Parent root = loader.load();
			controller = loader.getController();
			Scene scene = new Scene(root);
			primaryStage.setTitle("Console");
			primaryStage.setScene(scene);
			primaryStage.setResizable(false);
			primaryStage.show();
			controller.run();

		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
