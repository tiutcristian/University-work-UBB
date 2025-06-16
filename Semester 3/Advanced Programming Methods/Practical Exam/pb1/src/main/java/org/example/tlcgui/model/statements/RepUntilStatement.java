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

public class RepUntilStatement implements IStatement {
    IStatement stmt;

    public RepUntilStatement(IStatement stmt, IExpression expr) {
        this.stmt = stmt;
        this.expr = expr;
    }

    IExpression expr;

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        IValue evalExpr = expr.eval(prgState.getSymTable(), prgState.getHeap());

        if (((BoolValue) evalExpr).getValue()) {
            return null;
        }

        prgState.getExeStack().push(new CompStatement(stmt, new RepUntilStatement(stmt, expr)));

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new RepUntilStatement(stmt.deepCopy(), expr.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeExpression = expr.typecheck(typeEnv);

        if (!typeExpression.equals(new BoolType())) {
            throw new StatementException("The condition of WHILE has not the type bool");
        }

        stmt.typecheck(typeEnv.deepCopy());

        return typeEnv;
    }

    @Override
    public String toString() {
        return "repeat (" + stmt.toString() + ") until " + expr.toString();
    }
}
