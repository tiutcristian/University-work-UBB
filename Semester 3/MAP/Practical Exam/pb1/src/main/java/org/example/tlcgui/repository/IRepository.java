package org.example.tlcgui.repository;

import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.RepoException;
import org.example.tlcgui.model.state.PrgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void logPrgStateExec(PrgState prgState) throws IOException, KeyNotFoundException, RepoException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> prgStates);
}
