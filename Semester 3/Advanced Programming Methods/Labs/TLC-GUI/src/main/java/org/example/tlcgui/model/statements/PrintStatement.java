package org.example.tlcgui.model.statements;

import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.expresions.IExpression;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.IValue;

public class PrintStatement implements IStatement {
    private final IExpression expression;
    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws ADTException, ExpressionException {
        IValue result = this.expression.eval(prgState.getSymTable(), prgState.getHeap());
        prgState.getOutput().add(result.toString());
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(this.expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        this.expression.typecheck(typeEnv);
        return typeEnv;
    }

    public String toString(){
        return "Print(" + expression.toString() + ")";
    }
}
