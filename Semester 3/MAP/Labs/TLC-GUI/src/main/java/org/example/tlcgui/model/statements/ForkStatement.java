package org.example.tlcgui.model.statements;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.adt.MyStack;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;

import java.io.IOException;

public class ForkStatement implements IStatement {
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState prgState)
            throws StatementException, ADTException, ExpressionException, IOException {
        return new PrgState(
                prgState.getSymTable().deepCopy(),
                new MyStack<>(),
                prgState.getOutput(),
                prgState.getFileTable(),
                prgState.getHeap(),
                this.statement
        );
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(this.statement.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv)
            throws KeyNotFoundException, ExpressionException, StatementException {
        statement.typecheck(typeEnv.deepCopy());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "fork(" + this.statement.toString() + ")";
    }
}
