package model.adt;


import java.util.ArrayList;
import java.util.List;


public class MyList<T> implements MyIList<T>{
    private List<T> list;

    public MyList(){
        this.list = new ArrayList<>();
    }

    @Override
    public synchronized void add(T element) {
        this.list.add(element);
    }

    @Override
    public synchronized List<T> getAll() {
        return this.list;
    }


    @Override
    public synchronized String toString(){
        StringBuilder sb = new StringBuilder();
        for(T element: this.list){
            sb.append(element.toString()).append("\n");
        }
        return sb.toString();
    }
}
