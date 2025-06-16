package repository;

import model.Vehicle;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class RepositoryImpl implements IRepository {
    final int MAX_SIZE = 100;
    Vehicle[] vehicles = new Vehicle[MAX_SIZE];
    private int currentSize = 0;

    @Override
    public void addVehicle(Vehicle vehicle) throws ArrayIndexOutOfBoundsException {
        if (currentSize == MAX_SIZE) {
            throw new ArrayIndexOutOfBoundsException("Repository is full. Cannot add more vehicles");
        }
        vehicles[currentSize] = vehicle;
        currentSize++;
    }

    @Override
    public void removeVehicle(int index) throws IllegalArgumentException {
        if (index < 0 || index >= currentSize) {
            throw new IllegalArgumentException("Invalid index");
        }
        for (int i = index; i < currentSize - 1; i++) {
            vehicles[i] = vehicles[i + 1];
        }
        currentSize--;
    }

    @Override
    public List<Vehicle> getAllVehicles() {
        return new ArrayList<>(Arrays.asList(vehicles).subList(0, currentSize));
    }
}
