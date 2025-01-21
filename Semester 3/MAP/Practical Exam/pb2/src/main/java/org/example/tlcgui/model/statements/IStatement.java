package org.example.tlcgui.model.statements;
import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;

import java.io.IOException;

public interface IStatement {
    PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException;
    IStatement deepCopy();
    MyIDictionary<String, IType> typecheck(MyIDictionary<String,IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException;
}
