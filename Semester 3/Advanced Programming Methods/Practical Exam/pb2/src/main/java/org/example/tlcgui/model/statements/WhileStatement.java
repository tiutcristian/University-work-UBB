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

import java.io.IOException;

public class WhileStatement implements IStatement {
    private IExpression expression;
    private IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        IValue evalExpr = expression.eval(prgState.getSymTable(), prgState.getHeap());
        if (!(evalExpr.getType() instanceof BoolType)) {
            throw new StatementException("Expression is not a boolean");
        }

        if (!((BoolValue) evalExpr).getValue()) {
            return null;
        }

        prgState.getExeStack().push(this);
        prgState.getExeStack().push(statement);

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(expression.deepCopy(), statement.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExpression = expression.typecheck(typeEnv);

        if (!typeExpression.equals(new BoolType())) {
            throw new StatementException("The condition of WHILE has not the type bool");
        }

        statement.typecheck(typeEnv.deepCopy());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "While (" + expression + ") {" + statement + "}";
    }
}
