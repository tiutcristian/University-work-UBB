package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expresions.IExpression;
import model.state.PrgState;
import model.types.IType;
import model.types.RefType;
import model.value.IValue;
import model.value.RefValue;

import java.io.IOException;

public class HeapWriteStatement implements IStatement {
    private String varName;
    private IExpression expression;

    public HeapWriteStatement(String varName, IExpression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState)
            throws StatementException, ADTException, ExpressionException, IOException {
        if (!prgState.getSymTable().contains(varName))
            throw new StatementException("Variable " + varName + " is not defined");

        IValue varValue = prgState.getSymTable().getValue(varName);
        if (!(varValue.getType() instanceof RefType)) {
            throw new StatementException("Variable " + varName + " is not a reference type");
        }

        int address = ((RefValue) varValue).getAddr();
        if (!prgState.getHeap().contains(address)) {
            throw new StatementException("Address " + address + " is not allocated in the heap");
        }

        IValue evaluatedExpression = expression.eval(prgState.getSymTable(), prgState.getHeap());
        if (!((RefType) varValue.getType()).getInner().equals(evaluatedExpression.getType())) {
            throw new StatementException("Types do not match");
        }

        prgState.getHeap().update(address, evaluatedExpression);

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapWriteStatement(varName, expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType varType = typeEnv.getValue(varName);
        IType expressionType = expression.typecheck(typeEnv);

        if (!varType.equals(new RefType(expressionType))) {
            throw new StatementException("HeapWriteStatement: right hand side and left hand side have different types");
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return "writeHeap(" + varName + ", " + expression.toString() + ")";
    }
}
