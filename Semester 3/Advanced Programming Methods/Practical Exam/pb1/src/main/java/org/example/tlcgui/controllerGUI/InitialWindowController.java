package org.example.tlcgui.controllerGUI;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import org.example.tlcgui.InterpreterGUI;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyDictionary;
import org.example.tlcgui.model.statements.IStatement;

import java.io.IOException;
import java.util.List;

import static org.example.tlcgui.InterpreterCLI.*;

public class InitialWindowController {
    @FXML
    private ListView<IStatement> programsListView;

    @FXML
    private Label errorLabel;

    private void updateProgramsListView(List<IStatement> programs) {
        programsListView.getItems().clear();
        programs.forEach(program -> programsListView.getItems().add(program));
    }

    @FXML
    protected void onBasicExamplesButtonClicked() {
        updateProgramsListView(basicExamples());
    }

    @FXML
    protected void onDynamicAllocationExamplesButtonClicked() {
        updateProgramsListView(dynamicAllocationExamples());
    }

    @FXML
    protected void onWhileExampleButtonClicked() {
        updateProgramsListView(whileExample());
    }

    @FXML
    protected void onForkExampleButtonClicked() {
        updateProgramsListView(forkExample());
    }

    @FXML
    protected void onTypeCheckerFailingExampleButtonClicked() {
        updateProgramsListView(typeCheckerFailingExample());
    }

    @FXML
    protected void onRepUntilButtonClicked() {
        updateProgramsListView(repUntilExample());
    }

    @FXML
    protected void onQuitButtonClicked() {
        System.out.println("Exiting...");
        System.exit(0);
    }

    @FXML
    protected void onGoButtonClicked() throws IOException {
        IStatement selectedProgram = programsListView.getSelectionModel().getSelectedItem();

        // no program selected
        if (selectedProgram == null) {
            errorLabel.setText("No program selected!");
            return;
        }

        // typecheck
        try {
            selectedProgram.typecheck(new MyDictionary<>());
        } catch (KeyNotFoundException | ExpressionException | StatementException e) {
            errorLabel.setText("Typecheck error:\n" + e.getMessage());
            return;
        }

        // if everything is ok
        errorLabel.setText("");

        FXMLLoader fxmlLoader = new FXMLLoader(InterpreterGUI.class.getResource("main-window-view.fxml"));
        Stage stage = new Stage();
        stage.setTitle("Program execution");
        stage.setScene(new Scene(fxmlLoader.load()));

        MainWindowController controller = fxmlLoader.getController();
        controller.setInitialStatement(selectedProgram);

        stage.show();
    }
}