package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expresions.IExpression;
import model.state.PrgState;
import model.types.BoolType;
import model.types.IType;
import model.value.BoolValue;
import model.value.IValue;

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
            return prgState;
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
