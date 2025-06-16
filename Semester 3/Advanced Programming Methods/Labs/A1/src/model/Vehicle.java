package model;

public interface Vehicle {
    public void setRepairCost(double repairCost);
    public double getRepairCost();
    public String toString();
    public boolean equals(Object obj);
    public int hashCode();
}
