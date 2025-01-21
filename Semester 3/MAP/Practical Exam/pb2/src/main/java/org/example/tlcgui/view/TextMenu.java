package org.example.tlcgui.view;

import org.example.tlcgui.controller.Controller;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.KeyNotFoundException;
import org.example.tlcgui.exceptions.StatementException;
import org.example.tlcgui.model.adt.*;
import org.example.tlcgui.model.state.PrgState;
import org.example.tlcgui.model.statements.IStatement;
import org.example.tlcgui.repository.IRepository;
import org.example.tlcgui.repository.Repository;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private Map<String, Command> commands;

    public TextMenu() {
        commands = new HashMap<>();
    }

    public TextMenu (List<IStatement> programs) {
        commands = new HashMap<>();
        addCommand(new ExitCommand("0", "exit"));
        int index = 1;
        for (IStatement initialStmt : programs) {
            try {
                initialStmt.typecheck(new MyDictionary<>());
            } catch (KeyNotFoundException | ExpressionException | StatementException e) {
                System.err.println("Typecheck error for program " + index + ": [" + initialStmt + "]\n" +
                        "\t" + e.getMessage());
                continue;
            }
            PrgState prg = new PrgState(
                    new MyDictionary<>(),
                    new MyStack<>(),
                    new MyList<>(),
                    new MyDictionary<>(),
                    new MyHeap(),
                    new MyBarrierTable(),
                    initialStmt
            );
            IRepository repo = new Repository(prg, "log" + index + ".txt");
            Controller ctrl = new Controller(repo);
            addCommand(new RunExample(Integer.toString(index), initialStmt.toString(), ctrl));
            index++;
        }
    }

    public void addCommand(Command c) {
        commands.put(c.getKey(),c);
    }

    private void printMenu() {
        for(Command com : commands.values()){
            String line = String.format("%4s : %s", com.getKey(), com.getDescription());
            System.out.println(line);
        }
    }

    public void show(){
        Scanner scanner=new Scanner(System.in);
        while(true) {
            printMenu();
            System.out.print("Input the option: ");
            String key = scanner.nextLine();
            Command com = commands.get(key);
            if (com == null){
                System.out.println("Invalid option");
                continue;
            }
            com.execute();
        }
    }

    public Map<String, Command> getCommands() {
        return commands;
    }
}