package model;

public class Truck implements Vehicle {
    private double repairCost;
    private int loadCapacity;

    public Truck(double repairCost, int loadCapacity) {
        this.repairCost = repairCost;
        this.loadCapacity = loadCapacity;
    }

    @Override
    public void setRepairCost(double repairCost) {
        this.repairCost = repairCost;
    }

    @Override
    public double getRepairCost() {
        return repairCost;
    }

    public int getLoadCapacity() {
        return loadCapacity;
    }

    public void setLoadCapacity(int loadCapacity) {
        this.loadCapacity = loadCapacity;
    }

    @Override
    public String toString() {
        return "Truck { " +
                "repairCost = " + repairCost +
                ", loadCapacity = " + loadCapacity +
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
        Truck truck = (Truck) obj;
        return Double.compare(truck.repairCost, repairCost) == 0 && loadCapacity == truck.loadCapacity;
    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        temp = Double.doubleToLongBits(repairCost);
        result = (int) (temp ^ (temp >>> 32));
        result = 31 * result + loadCapacity;
        return result;
    }
}
