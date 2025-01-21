package view;

import controller.Controller;
import exceptions.ADTException;
import exceptions.ExpressionException;
import exceptions.RepoException;
import exceptions.StatementException;

import java.io.IOException;

public class RunExample extends Command {
    private Controller ctr;

    public RunExample(String key, String desc,Controller ctr) {
        super(key, desc);
        this.ctr = ctr;
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
