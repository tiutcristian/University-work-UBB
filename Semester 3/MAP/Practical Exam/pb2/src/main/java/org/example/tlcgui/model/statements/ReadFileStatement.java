package org.example.tlcgui.model.statements;
import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.MyIDictionary;
import org.example.tlcgui.model.expresions.IExpression;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.types.IType;
import org.example.tlcgui.model.types.IntType;
import org.example.tlcgui.model.types.StringType;
import org.example.tlcgui.model.value.IntValue;
import org.example.tlcgui.model.value.StringValue;
import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private IExpression exp;
    private String varName;

    public ReadFileStatement(IExpression exp, String varName){
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public PrgState execute(PrgState prgState) throws StatementException, ADTException, ExpressionException, IOException {
        var table = prgState.getSymTable();
        if(!table.contains(varName)){
            throw new StatementException("The variable was not defined");
        }
        if(!table.getValue(varName).getType().equals(new IntType())){
            throw new StatementException("The type is incorrect");
        }
        var res = exp.eval(table, prgState.getHeap());
        if(!res.getType().equals(new StringType())){
            throw new StatementException("The result is not a String Type!");
        }
        BufferedReader reader = prgState.getFileTable().getValue((StringValue)res);
        String read = reader.readLine();
        if(read.isEmpty()){
            read = "0";
        }
        int parser = Integer.parseInt(read);
        table.insert(varName, new IntValue(parser));
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws KeyNotFoundException, ExpressionException, StatementException {
        IType typeVar = typeEnv.getValue(varName);
        IType typeExp = exp.typecheck(typeEnv);
        if(!typeVar.equals(new IntType())){
            throw new StatementException("The variable is not an integer");
        }
        if(!typeExp.equals(new StringType())){
            throw new StatementException("The expression is not a string");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "ReadFile(" + exp.toString() + ", " + varName + ")";
    }
}