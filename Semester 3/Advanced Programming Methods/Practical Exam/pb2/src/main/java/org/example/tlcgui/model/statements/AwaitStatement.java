package org.example.tlcgui.model.statements;

import javafx.util.Pair;
import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.IntType;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.IntValue;

import java.io.IOException;
import java.util.List;

public class AwaitStatement implements IStatement {
    String var;

    public AwaitStatement(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        IValue val = prgState.getSymTable().getValue(var);
        if (!val.getType().equals(new IntType())) {
            throw new StatementException("Variable " + var + " is not an integer");
        }

        int foundIndex = ((IntValue)prgState.getSymTable().getValue(var)).getValue();

        synchronized (prgState.getBarrierTable()) {
            if (!prgState.getBarrierTable().contains(foundIndex)) {
                throw new StatementException("Index " + foundIndex + " not found in cyclic barrier");
            }

            Pair<Integer, List<Integer>> foundBarrier = prgState.getBarrierTable().get(foundIndex);
            int N1 = foundBarrier.getKey();
            int NL = foundBarrier.getValue().size();

            if (N1 > NL) {
                if (!foundBarrier.getValue().contains(prgState.getId())) {
                    foundBarrier.getValue().add(prgState.getId());
                }
                prgState.getExeStack().push(this);
            }
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new AwaitStatement(var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(var);
        if (!typeVar.equals(new IntType())) {
            throw new StatementException("Variable " + var + " is not an integer");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "await(" + var + ")";
    }
}
