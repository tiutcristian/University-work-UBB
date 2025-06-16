package org.example.tlcgui.controller;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.Pair;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.repository.IRepository;

import java.util.List;
import java.util.stream.Collectors;

public class PrgStateService {
    private final IRepository repository;
    private final ObservableList<PrgState> observablePrgStates;
    ObservableValue<Integer> currentPrgStateIndex;

    public PrgStateService(IRepository repository) {
        this.repository = repository;
        this.observablePrgStates = FXCollections.observableArrayList(repository.getPrgList());
        this.currentPrgStateIndex = new SimpleIntegerProperty(0).asObject();
    }

    public int getCurrentPrgStateIndex() {
        return currentPrgStateIndex.getValue();
    }

    public void setCurrentPrgStateIndex(int currentPrgStateIndex) {
        this.currentPrgStateIndex = new SimpleIntegerProperty(currentPrgStateIndex).asObject();
    }

    public ObservableList<PrgState> getObservablePrgStates() {
        return observablePrgStates;
    }

    public void setObservablePrgStates(List<PrgState> prgStates) {
        observablePrgStates.setAll(prgStates);
        repository.setPrgList(prgStates);
    }

    public int getNoOfPrgStates() {
        return observablePrgStates.size();
    }

    public ObservableList<String> getPrgStatesIds() {
        return FXCollections.observableArrayList(
                observablePrgStates.stream()
                        .map(PrgState::getId)
                        .map(String::valueOf)
                        .collect(Collectors.toList())
        );
    }

    public ObservableList<Pair<Integer, IValue>> getHeapTableContent() {
        return FXCollections.observableArrayList(
                observablePrgStates.get(currentPrgStateIndex.getValue())
                        .getHeap().entrySet().entrySet().stream()
                        .map(e -> new Pair<>(e.getKey(), e.getValue()))
                        .collect(Collectors.toList())
        );
    }

    public ObservableList<Pair<String, IValue>> getSymTableContent() {
        return FXCollections.observableArrayList(
                observablePrgStates.get(currentPrgStateIndex.getValue())
                        .getSymTable().getContent().entrySet().stream()
                        .map(e -> new Pair<>(e.getKey(), e.getValue()))
                        .collect(Collectors.toList())
        );
    }

    public ObservableList<String> getExeStackContent(boolean getWholeExeStack) {
        String[] exeStack = observablePrgStates.get(currentPrgStateIndex.getValue())
                .getExeStack()
                .toString()
                .split("\n");
        String wholeExeStack = exeStack[0];
        String executingStatement = (exeStack.length > 1) ? exeStack[1] : "";
        if (getWholeExeStack) {
            return FXCollections.observableArrayList(wholeExeStack.split(";"));
        }
        return FXCollections.observableArrayList(executingStatement);
    }

    public ObservableList<String> getFileTableContent() {
        return FXCollections.observableArrayList(
                observablePrgStates.get(currentPrgStateIndex.getValue())
                        .getFileTable().getContent().entrySet().stream()
                        .map(e -> e.getKey() + " -> " + e.getValue())
                        .collect(Collectors.toList())
        );
    }

    public ObservableList<String> getOutputContent() {
        return FXCollections.observableArrayList(
                observablePrgStates.get(currentPrgStateIndex.getValue())
                        .getOutput()
                        .getAll()
        );
    }

    public void updateObservablePrgStates() {
        observablePrgStates.setAll(repository.getPrgList());
    }

    public ObservableList<Pair<Integer, Pair<Integer, List<Integer>>>> getBarrierTableContent() {
        return FXCollections.observableArrayList(
                observablePrgStates.get(currentPrgStateIndex.getValue())
                        .getBarrierTable().getContent().entrySet().stream()
                        .map(e -> new Pair<>(e.getKey(), e.getValue()))
                        .collect(Collectors.toList())
        );
    }
}
