package model.statements;

import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.KeyNotFoundException;
import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.expresions.IExpression;
import model.state.PrgState;
import model.types.IType;
import model.types.StringType;
import model.value.IValue;
import model.value.StringValue;

import java.io.IOException;

public class CloseRFileStatement implements IStatement {
    IExpression expr;

    public CloseRFileStatement(IExpression expr) {
        this.expr = expr;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        IValue evaluatedExpr = expr.eval(prgState.getSymTable(), prgState.getHeap());

        if (!evaluatedExpr.getType().toString().equals("string")) {
            throw new ADTException("File name must be a string");
        }

        if (!prgState.getFileTable().contains((StringValue) evaluatedExpr)) {
            throw new ADTException("File does not exist in the file table");
        }

        prgState.getFileTable()
                .getValue((StringValue) evaluatedExpr)
                .close();

        prgState.getFileTable().remove((StringValue) evaluatedExpr);

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CloseRFileStatement(this.expr.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType exprType = expr.typecheck(typeEnv);

        if (!exprType.equals(new StringType())) {
            throw new StatementException("CloseRFileStatement: expression must be a string");
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return "closeRFile(" + expr.toString() + ")";
    }
}
