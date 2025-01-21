package org.example.tlcgui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class InterpreterGUI extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(InterpreterGUI.class.getResource("initial-window-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Toy Language Compiler");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        System.out.println("Executing main method...");
        launch();
        System.out.println("Finished.");
    }
}