package model.statements;

import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.state.PrgState;
import model.types.IType;

public class CompStatement implements IStatement {
    private final IStatement statement1;
    private final IStatement statement2;

    public CompStatement(IStatement statement1, IStatement statement2) {
        this.statement1 = statement1;
        this.statement2 = statement2;
    }

    @Override
    public PrgState execute(PrgState prgState) {
        prgState.getExeStack().push(statement2);
        prgState.getExeStack().push(statement1);

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CompStatement(statement1.deepCopy(), statement2.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        return statement2.typecheck(statement1.typecheck(typeEnv));
    }

    @Override
    public String toString() {
        return statement1.toString() + ";" + statement2.toString();
    }

}
