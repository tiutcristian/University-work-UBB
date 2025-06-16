package org.example.tlcgui.view;

import org.example.tlcgui.controller.Controller;
import org.example.tlcgui.exceptions.ADTException;
import org.example.tlcgui.exceptions.ExpressionException;
import org.example.tlcgui.exceptions.RepoException;
import org.example.tlcgui.exceptions.StatementException;

import java.io.IOException;

public class RunExample extends Command {
    private Controller ctr;

    public RunExample(String key, String desc,Controller ctr) {
        super(key, desc);
        this.ctr = ctr;
    }

    public Controller getController() {
        return ctr;
    }

    @Override
    public void execute() {
        try {
            ctr.allStep();
        } catch (StatementException e) {
            System.out.println("Statement exception: " + e.getMessage());
        } catch (ADTException e) {
            System.out.println("ADT exception: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO exception: " + e.getMessage());
        } catch (RepoException e) {
            System.out.println("Repo exception: " + e.getMessage());
        } catch (ExpressionException e) {
            System.out.println("Expression exception: " + e.getMessage());
        } catch (InterruptedException e) {
            System.out.println("Interrupted Exception: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
