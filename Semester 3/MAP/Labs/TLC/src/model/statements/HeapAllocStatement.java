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

public class HeapAllocStatement implements IStatement {
    private String varName;
    private IExpression expression;

    public HeapAllocStatement(String varName, IExpression expression) {
        this.varName = varName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        if (!prgState.getSymTable().contains(varName)) {
            throw new StatementException("Variable name not in symtable.");
        }

        IValue variableValue = prgState.getSymTable().getValue(varName);
        if (!(variableValue.getType() instanceof RefType)) {
            throw new StatementException("Variable " + varName + " is not a reference.");
        }

        IValue evalExpr = expression.eval(prgState.getSymTable(), prgState.getHeap());
        if (!((RefType) variableValue.getType()).getInner().equals(evalExpr.getType())) {
            throw new StatementException("Types do not match.");
        }

        int addr = prgState.getHeap().allocate(evalExpr);
        prgState.getSymTable().insert(varName, new RefValue(addr, ((RefType) variableValue.getType()).getInner()));

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapAllocStatement(varName, expression.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typevar = typeEnv.getValue(varName);
        IType typexp = expression.typecheck(typeEnv);
        if (typevar.equals(new RefType(typexp))) {
            return typeEnv;
        } else {
            throw new StatementException("Heap allocation: right hand side and left hand side have different types");
        }
    }

    @Override
    public String toString() {
        return "new(" + varName + ", " + expression.toString() + ")";
    }
}