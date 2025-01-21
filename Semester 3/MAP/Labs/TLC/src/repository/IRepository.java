package repository;

import exceptions.KeyNotFoundException;
import exceptions.RepoException;
import model.state.PrgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void logPrgStateExec(PrgState prgState) throws IOException, KeyNotFoundException, RepoException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> prgStates);
}
