package controller;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.RepoException;
import exceptions.StatementException;
import model.adt.MyGarbageCollector;
import model.adt.MyIGarbageCollector;
import model.adt.MyIHeap;
import model.adt.MyIStack;
import model.state.PrgState;
import repository.IRepository;
import model.statements.IStatement;

import java.io.IOException;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repository;
    private MyIGarbageCollector garbageCollector;
    private ExecutorService executor;

    public Controller(IRepository repository) {
        this.repository = repository;
        this.garbageCollector = new MyGarbageCollector();
    }

    public void allStep() throws StatementException, ADTException, ExpressionException, IOException, RepoException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);

        List<PrgState> prgList = removeCompletedPrg(repository.getPrgList());

        while (!prgList.isEmpty()) {
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

            oneStepForAllPrg(prgList);

            prgList = removeCompletedPrg(repository.getPrgList());
        }

        executor.shutdownNow();

        repository.setPrgList(prgList);
    }

    List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream().filter(PrgState::isNotCompleted).collect(Collectors.toList());
    }

    private void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
        prgList.forEach(
            prg -> {
                try {
                    repository.logPrgStateExec(prg);
                } catch (Exception e) {
                    throw new RuntimeException(e.getMessage());
                }
            }
        );

        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>)(p::oneStep))
                .toList();

        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(
                    future -> {
                        try {
                            return future.get();
                        } catch (InterruptedException | ExecutionException e) {
                            throw new RuntimeException(e.getMessage());
                        }
                    }
                )
                .filter(Objects::nonNull)
                .toList();

        prgList.addAll(newPrgList);

        prgList.forEach(
            prg -> {
                try {
                    repository.logPrgStateExec(prg);
                } catch (Exception e) {
                    throw new RuntimeException(e.getMessage());
                }
            }
        );

        repository.setPrgList(prgList);
    }
}
