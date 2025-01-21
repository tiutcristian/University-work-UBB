package view;

import controller.Controller;
import model.Car;
import model.Motorcycle;
import model.Truck;
import model.Vehicle;

import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class View {
    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    private void displayMenu() {
        System.out.println("\nMenu:");
        System.out.println("1. Add a vehicle");
        System.out.println("2. Remove a vehicle");
        System.out.println("3. Display vehicles with repair cost larger than ...");
        System.out.println("4. Run hardcoded example");
        System.out.println("0. Exit");
    }

    public void addVehicle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the type of vehicle (car, truck, motorcycle): ");
        String type = scanner.nextLine();
        System.out.println("Enter the repair cost: ");
        double repairCost = scanner.nextDouble();
        switch (type) {
            case "car":
                System.out.println("Enter the number of passengers: ");
                int noOfPassengers = scanner.nextInt();
                controller.addVehicle(new Car(repairCost, noOfPassengers));
                break;
            case "truck":
                System.out.println("Enter the load capacity: ");
                int loadCapacity = scanner.nextInt();
                controller.addVehicle(new Truck(repairCost, loadCapacity));
                break;
            case "motorcycle":
                System.out.println("Enter the aerodynamic coefficient: ");
                double aerodynamicCoefficient = scanner.nextDouble();
                controller.addVehicle(new Motorcycle(repairCost, aerodynamicCoefficient));
                break;
            default:
                System.out.println("Invalid vehicle type");
        }
    }

    public void removeVehicle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index of the vehicle to remove: ");
        int index = scanner.nextInt();
        controller.removeVehicle(index);
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        int option = -1;
        while (option != 0) {
            displayMenu();
            System.out.print("Enter option: ");
            try {
                option = scanner.nextInt();
                switch (option) {
                    case 1:
                        runHardcoded();
                        break;
                    case 2:
                        runHardcoded();
                        break;
                    case 3:
                        runHardcoded();
                        break;
                    case 4:
                        runHardcoded();
                        break;
                    case 0:
                        System.out.println("Exiting...");
                        break;
                    default:
                        System.out.println("Invalid option");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input");
                scanner.nextLine();
            } catch (Exception e) {
                System.out.println(e.getMessage());
                scanner.nextLine();
            }
        }
    }

    public void runHardcoded() {
        try{
            List<Vehicle> vehicles = controller.getAllVehiclesWithRepairCostLargerThan(1000);
            System.out.println("\nVehicles with repair cost larger than 1000:");
            vehicles.forEach(vehicle -> System.out.println("\t- " + vehicle));
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println("\nAIOB Exception: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("\nAn exception occurred: " + e.getMessage());
        }
    }
}
