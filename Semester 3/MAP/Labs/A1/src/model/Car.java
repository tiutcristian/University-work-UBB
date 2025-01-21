package model;

import java.util.Objects;

public class Car implements Vehicle {
    private double repairCost;
    private int noOfPassengers;

    public Car(double repairCost, int noOfPassengers) {
        this.repairCost = repairCost;
        this.noOfPassengers = noOfPassengers;
    }

    @Override
    public void setRepairCost(double repairCost) {
        this.repairCost = repairCost;
    }

    @Override
    public double getRepairCost() {
        return repairCost;
    }

    public int getNoOfPassengers() {
        return noOfPassengers;
    }

    public void setNoOfPassengers(int noOfPassengers) {
        this.noOfPassengers = noOfPassengers;
    }

    @Override
    public String toString() {
        return "Car { " +
                "repairCost = " + repairCost +
                ", noOfPassengers = " + noOfPassengers +
                " }";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Car car = (Car) obj;
        return Double.compare(car.repairCost, repairCost) == 0 && noOfPassengers == car.noOfPassengers;
    }

    @Override
    public int hashCode() {
        return Objects.hash(repairCost, noOfPassengers);
    }
}
