package org.example.tlcgui.model.statements;

import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;

public class VarDeclStatement implements IStatement {
    String name;
    IType type;

    public VarDeclStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState prgState) {
        prgState.getSymTable().insert(name, type.getDefaultValue());
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(name, type);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        typeEnv.insert(name, type);
        return typeEnv;
    }

    @Override
    public String toString() {
        return type.toString() + " " + name;
    }
}
