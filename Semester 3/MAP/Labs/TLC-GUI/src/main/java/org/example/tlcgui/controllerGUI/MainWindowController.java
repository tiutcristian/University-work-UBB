package org.example.tlcgui.controllerGUI;

import javafx.application.Platform;
import javafx.collections.ListChangeListener;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.util.Pair;
import org.example.tlcgui.controller.Controller;
import org.example.tlcgui.controller.PrgStateService;
import org.example.tlcgui.model.adt.*;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.statements.IStatement;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.repository.IRepository;
import org.example.tlcgui.repository.Repository;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainWindowController implements Initializable {
    @FXML
    private Label wholePrgLabel;

    @FXML
    private Label noOfStatesLabel;

    @FXML
    private TableView<Pair<Integer, IValue>> heapTableView;

    @FXML
    private ListView<String> outputListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<String> programStateListView;

    @FXML
    private TableView<Pair<String, IValue>> symbolTableView;

    @FXML
    private ListView<String> exeStackListView;

    @FXML
    private Button runOneStepButton;

    @FXML
    private Label crtStmtLabel;

    private IStatement initialStatement;
    private IRepository repo;
    private Controller ctr;
    private PrgStateService prgStateService;
    private ExecutorService executor;
    private MyIGarbageCollector garbageCollector;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Platform.runLater(() -> {
            initializeNonUIComponents();
            addPrgStatesListener();
            initializeUIComponents();
        });
    }

    public void setInitialStatement(IStatement initialStatement) {
        this.initialStatement = initialStatement;
    }

    private void initializeHeapTableView() {
        TableColumn<Pair<Integer, IValue>, String> addressColumn = new TableColumn<>("Address");
        addressColumn.setCellValueFactory(new PropertyValueFactory<>("key"));

        TableColumn<Pair<Integer, IValue>, String> valueColumn = new TableColumn<>("Value");
        valueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));

        heapTableView.getColumns().add(addressColumn);
        heapTableView.getColumns().add(valueColumn);

        addressColumn.prefWidthProperty().bind(heapTableView.widthProperty().multiply(0.5));
        valueColumn.prefWidthProperty().bind(heapTableView.widthProperty().multiply(0.5));

        heapTableView.setItems(prgStateService.getHeapTableContent());
    }

    private void initializeSymTableView() {
        TableColumn<Pair<String, IValue>, String> variableNameColumn = new TableColumn<>("Variable name");
        variableNameColumn.setCellValueFactory(new PropertyValueFactory<>("key"));

        TableColumn<Pair<String, IValue>, String> valueColumn = new TableColumn<>("Value");
        valueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));

        symbolTableView.getColumns().add(variableNameColumn);
        symbolTableView.getColumns().add(valueColumn);

        variableNameColumn.prefWidthProperty().bind(symbolTableView.widthProperty().multiply(0.5));
        valueColumn.prefWidthProperty().bind(symbolTableView.widthProperty().multiply(0.5));

        symbolTableView.setItems(prgStateService.getSymTableContent());
    }

    private void initializeUIComponents() {
        wholePrgLabel.setText("[" + initialStatement.toString() + "]");
        crtStmtLabel.setText("Current statement: ");
        initializeHeapTableView();
        initializeSymTableView();
        updateUIComponents();
    }

    private void initializeNonUIComponents() {
        PrgState prg = new PrgState(
                new MyDictionary<>(),
                new MyStack<>(),
                new MyList<>(),
                new MyDictionary<>(),
                new MyHeap(),
                initialStatement
        );
        repo = new Repository(prg, "log.txt");
        prgStateService = new PrgStateService(repo);
        ctr = new Controller(repo);
        garbageCollector = new MyGarbageCollector();
        executor = Executors.newFixedThreadPool(2);
    }

    private void updateUIComponents() {
        crtStmtLabel.setText("Current statement: " + prgStateService.getExeStackContent(false).getFirst());
        heapTableView.setItems(prgStateService.getHeapTableContent());
        outputListView.setItems(prgStateService.getOutputContent());
        fileTableListView.setItems(prgStateService.getFileTableContent());
        noOfStatesLabel.setText(String.valueOf(prgStateService.getNoOfPrgStates()));
        symbolTableView.setItems(prgStateService.getSymTableContent());
        programStateListView.setItems(prgStateService.getPrgStatesIds());
        exeStackListView.setItems(prgStateService.getExeStackContent(true));
    }

    private void displayErrorPopup(String message) {
        Stage dialog = new Stage();
        dialog.initModality(Modality.APPLICATION_MODAL);

        VBox dialogVbox = new VBox(20);
        dialogVbox.setAlignment(Pos.CENTER);

        Text messageText = new Text(message);
        messageText.wrappingWidthProperty().bind(dialogVbox.widthProperty());
        messageText.setStyle("-fx-fill: red;");
        messageText.setTextAlignment(javafx.scene.text.TextAlignment.CENTER);
        dialogVbox.getChildren().add(messageText);

        Button okButton = new Button("OK");
        okButton.setOnAction(_ -> dialog.close());
        okButton.setPrefWidth(100);
        dialogVbox.getChildren().add(okButton);

        Scene dialogScene = new Scene(dialogVbox, 300, 200);
        dialog.setScene(dialogScene);

        dialog.show();
    }

    private void addPrgStatesListener() {
        prgStateService.getObservablePrgStates().addListener((ListChangeListener<PrgState>) _ -> {
            if (!prgStateService.getObservablePrgStates().isEmpty()) {
                // if the selected program state has finished execution, select the first one
                if (prgStateService.getCurrentPrgStateIndex() >= prgStateService.getObservablePrgStates().size()) {
                    prgStateService.setCurrentPrgStateIndex(0);
                }
                updateUIComponents();
            } else {
                executor.shutdownNow();
                repo.setPrgList(List.of());

                programStateListView.getItems().clear();
                programStateListView.setDisable(true);
                exeStackListView.getItems().clear();
                exeStackListView.setDisable(true);
                noOfStatesLabel.setText("0");
                runOneStepButton.setDisable(true);
            }
        });
    }

    @FXML
    protected void onRunOneStepClicked() {
        try {
            List<PrgState> prgList = repo.getPrgList();
            MyIHeap heap = prgList.getFirst().getHeap();
            heap.setContent(
                    garbageCollector.safeGarbageCollector(
                            garbageCollector.getAddrFromAllSymTables(
                                    prgList.stream()
                                            .map(PrgState::getSymTable)
                                            .toList()
                            ),
                            heap.entrySet()
                    )
            );
            ctr.oneStepForAllPrg(prgList);

            prgStateService.updateObservablePrgStates();
            prgStateService.setObservablePrgStates(ctr.removeCompletedPrg(prgList));
        } catch (Exception e) {
            displayErrorPopup(e.getClass().getSimpleName() + ": " + e.getMessage());
        }
    }

    @FXML
    protected void onPrgStateSelected() {
        if (prgStateService.getNoOfPrgStates() == 0) {
            displayErrorPopup("The selected program state has finished execution.");
        } else {
            prgStateService.setCurrentPrgStateIndex(programStateListView.getSelectionModel().getSelectedIndex());
            updateUIComponents();
        }
    }
}
