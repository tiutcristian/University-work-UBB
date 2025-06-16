package org.example.tlcgui.repository;

import org.example.tlcgui.exceptions.RepoException;
import org.example.tlcgui.model.state.PrgState;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    List<PrgState> prgStates;
    String logFilePath;

    public Repository(PrgState initialPrgState, String logFilePath) {
        this.prgStates = new ArrayList<>();
        this.prgStates.add(initialPrgState);
        this.logFilePath = logFilePath;
    }

    @Override
    public void logPrgStateExec(PrgState prgState) throws RepoException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.println(prgState.toString());
            logFile.close();
        } catch (IOException e) {
            throw new RepoException("Could not write to log file");
        }
    }

    @Override
    public List<PrgState> getPrgList() {
        return prgStates;
    }

    @Override
    public void setPrgList(List<PrgState> prgStates) {
        this.prgStates = prgStates;
    }
}