package org.example.tlcgui.controller;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.RepoException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyGarbageCollector;
import org.example.tlcgui.model.adt.MyIGarbageCollector;
import org.example.tlcgui.model.adt.MyIHeap;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.repository.IRepository;

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
        this.executor = Executors.newFixedThreadPool(2);
    }

    public void allStep() throws StatementException, ADTException, ExpressionException, IOException, RepoException, InterruptedException {
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

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream().filter(PrgState::isNotCompleted).collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
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
