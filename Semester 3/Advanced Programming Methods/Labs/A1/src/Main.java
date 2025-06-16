import controller.Controller;
import model.Car;
import model.Motorcycle;
import model.Truck;
import repository.IRepository;
import repository.RepositoryImpl;
import view.View;

public class Main {
    public static void main(String[] args) {
        // Create a new instance of Repository
        IRepository repository = new RepositoryImpl();

        // Create Controller instance and pass the repository to it
        Controller controller = new Controller(repository);

        controller.addVehicle(new Car(1000, 2));
        controller.addVehicle(new Car(2000, 4));
        controller.addVehicle(new Truck(10000, 60));
        controller.addVehicle(new Truck(20000, 120));
        controller.addVehicle(new Motorcycle(500, 0.2));

        // Create View instance and pass the controller to it
        View view = new View(controller);

        // Call the run method of the view
        view.run();
//        view.runHardcoded();
    }
}