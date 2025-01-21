package org.example.tlcgui.model.statements;


import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.expresions.IExpression;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.BoolType;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.value.BoolValue;
import org.example.tlcgui.model.value.IValue;

public class IfStatement implements IStatement {
    private final IStatement statementThen;
    private final IStatement statementElse;
    private final IExpression expression;

    public IfStatement(IExpression expression, IStatement statementThan, IStatement statementElse) {
        this.statementThen = statementThan;
        this.statementElse = statementElse;
        this.expression = expression;
    }

    public PrgState execute(PrgState state) throws StatementException, ADTException, ExpressionException {
        IValue value = expression.eval(state.getSymTable(), state.getHeap());
        if(!value.getType().equals(new BoolType())){
            throw new StatementException("Expression is not boolean");
        }
        if(((BoolValue) value).getValue()){
            state.getExeStack().push(statementThen);
        }
        else {
            state.getExeStack().push(statementElse);
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new IfStatement(expression.deepCopy(), statementThen.deepCopy(), statementElse.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExp = expression.typecheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            statementThen.typecheck(typeEnv.deepCopy());
            statementElse.typecheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else {
            throw new StatementException("The condition of IF has not the type bool");
        }
    }

    @Override
    public String toString() {
        return "If " + expression + " Then " + statementThen + " Else " + statementElse;
    }

}
