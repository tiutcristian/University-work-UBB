package org.example.tlcgui.model.statements;

import javafx.util.Pair;
import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.expresions.IExpression;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.IntType;
import org.example.tlcgui.model.value.IValue;
import org.example.tlcgui.model.value.IntValue;

import java.io.IOException;
import java.util.ArrayList;

public class NewBarrierStatement implements IStatement {
    private String varName;
    private IExpression exp;
    private static int nextFreeLocation = 0;

    public NewBarrierStatement(String varName, IExpression exp) {
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        IValue nr = exp.eval(prgState.getSymTable(), prgState.getHeap());
        if (!nr.getType().equals(new IntType())) {
            throw new StatementException("The expression is not an integer");
        }
        int index = nextFreeLocation++;
        int n = ((IntValue) nr).getValue();

        synchronized (prgState.getBarrierTable()) {
            prgState.getBarrierTable().add(index, new Pair<>(n, new ArrayList<>()));
            if (prgState.getSymTable().contains(varName) && prgState.getSymTable().getValue(varName).getType().equals(new IntType())) {
                prgState.getSymTable().insert(varName, new IntValue(index));
            } else {
                throw new StatementException("The variable does not exist or is not an integer");
            }
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new NewBarrierStatement(varName, exp.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType varType = typeEnv.getValue(varName);
        IType expType = exp.typecheck(typeEnv);
        if (!expType.equals(new IntType())) {
            throw new StatementException("The expression is not an integer");
        }
        if (!varType.equals(new IntType())) {
            throw new StatementException("The variable is not an integer");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newBarrier(" + varName + ", " + exp.toString() + ")";
    }
}
