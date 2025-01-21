package controller;

import model.Vehicle;
import repository.IRepository;

import java.util.ArrayList;
import java.util.List;

public class Controller {
    IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public List<Vehicle> getAllVehiclesWithRepairCostLargerThan(double cost) {
        List<Vehicle> result = new ArrayList<>();
        for (var vehicle : repository.getAllVehicles()) {
            if (vehicle.getRepairCost() > cost) {
                result.add(vehicle);
            }
        }
        return result;
    }

    public void addVehicle(Vehicle vehicle) {
        repository.addVehicle(vehicle);
    }

    public void removeVehicle(int index) {
        repository.removeVehicle(index);
    }
}
