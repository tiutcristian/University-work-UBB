package org.example.tlcgui.model.statements;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.expresions.IExpression;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.IValue;

public class AssignStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;
    public AssignStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException {
        if (!prgState.getSymTable().contains(this.variableName)) {
            throw new StatementException("Variable was not found");
        }
        IValue value = prgState.getSymTable().getValue(this.variableName);
        IValue evalValue = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        if (!value.getType().equals(evalValue.getType())){
            throw new StatementException("Value type mismatch");
        }
        prgState.getSymTable().insert(this.variableName, evalValue);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv)
            throws KeyNotFoundException, ExpressionException, StatementException {
        IType varType = typeEnv.getValue(this.variableName);
        IType expType = expression.typecheck(typeEnv);
        if (varType.equals(expType)) {
            return typeEnv;
        } else {
            throw new StatementException("Assignment: right hand side and left hand side have different types");
        }
    }

    @Override
    public String toString(){
        return this.variableName + " = " + this.expression.toString();
    }
}
