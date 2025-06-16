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

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements IStatement {
    IExpression expr;

    public OpenRFileStatement(IExpression expr) {
        this.expr = expr;
    }

    @Override
    public PrgState execute(PrgState prgState) throws ADTException, ExpressionException {
        IValue evaluatedExpr = expr.eval(prgState.getSymTable(), prgState.getHeap());

        if (!evaluatedExpr.getType().toString().equals("string")) {
            throw new ADTException("File name must be a string");
        }

        if (prgState.getFileTable().contains((StringValue) evaluatedExpr)) {
            throw new ADTException("File already opened");
        }

        try {
            BufferedReader reader = new BufferedReader(new FileReader(((StringValue) evaluatedExpr).getValue()));
            prgState.getFileTable().insert((StringValue) evaluatedExpr, reader);
        } catch (FileNotFoundException e) {
            throw new ExpressionException("File not found");
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new OpenRFileStatement(this.expr.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType exprType = expr.typecheck(typeEnv);
        if (!exprType.equals(new StringType())) {
            throw new StatementException("File name must be a string");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "openRFile(" + expr.toString() + ")";
    }
}
