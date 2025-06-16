package repository;

import model.Vehicle;

import java.util.List;

public interface IRepository {
    void addVehicle(Vehicle vehicle);
    void removeVehicle(int index);
    List<Vehicle> getAllVehicles();
}
