package model;

public class Motorcycle implements Vehicle {
    private double repairCost;
    private double aerodynamicCoefficient;

    public Motorcycle(double repairCost, double aerodynamicCoefficient) {
        this.repairCost = repairCost;
        this.aerodynamicCoefficient = aerodynamicCoefficient;
    }

    @Override
    public void setRepairCost(double repairCost) {
        this.repairCost = repairCost;
    }

    @Override
    public double getRepairCost() {
        return repairCost;
    }

    public double getAerodynamicCoefficient() {
        return aerodynamicCoefficient;
    }

    public void setAerodynamicCoefficient(double aerodynamicCoefficient) {
        this.aerodynamicCoefficient = aerodynamicCoefficient;
    }

    @Override
    public String toString() {
        return "Motorcycle { " +
                "repairCost = " + repairCost +
                ", aerodynamicCoefficient = " + aerodynamicCoefficient +
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
        Motorcycle motorcycle = (Motorcycle) obj;
        return Double.compare(motorcycle.repairCost, repairCost) == 0 && Double.compare(motorcycle.aerodynamicCoefficient, aerodynamicCoefficient) == 0;
    }

    @Override
    public int hashCode() {
        int result = 17;
        long longBits = Double.doubleToLongBits(repairCost);
        result = 31 * result + (int) (longBits ^ (longBits >>> 32));
        longBits = Double.doubleToLongBits(aerodynamicCoefficient);
        result = 31 * result + (int) (longBits ^ (longBits >>> 32));
        return result;
    }
}
