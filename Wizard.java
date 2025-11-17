import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.Arrays;
import java.util.Random;

public class Wizard {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("========================================");
        System.out.println("   Welcome to the Mystic Dungeon!");
        System.out.println("========================================");
        System.out.println("You are in a line of powerful wizards.");
        System.out.println("Choose a starting wizard, and you will be teleported down the line.");
        System.out.println("Your goal is to absorb the maximum possible energy.\n");

        int numberOfWizards = getValidatedInteger(scanner, "Enter the number of wizards in the line: ", 1, Integer.MAX_VALUE);
        int[] energy = getEnergyArray(numberOfWizards);
        int k = getValidatedInteger(scanner, "\nEnter the teleport jump distance (k): ", 1, Math.max(1, numberOfWizards - 1));

        int[] originalEnergy = Arrays.copyOf(energy, energy.length);
        
        CalculationResult result = findMaximumEnergy(energy, k);

        displayResults(originalEnergy, k, result);

        scanner.close();
    }

    private static int[] getEnergyArray(int size) {
        int[] energy = new int[size];
        Random random = new Random();
        System.out.println("\nGenerating random energy levels for the wizards...");
        for (int i = 0; i < size; i++) {
            energy[i] = random.nextInt(2001) - 1000; // Generates a number between -1000 and 1000
            System.out.println("  - Energy for Wizard #" + (i + 1) + ": " + energy[i]);
        }
        return energy;
    }

    private static int getValidatedInteger(Scanner scanner, String prompt, int min, int max) {
        int value = 0;
        while (true) {
            try {
                System.out.print(prompt);
                value = scanner.nextInt();
                if (value >= min && value <= max) {
                    break; 
                } else {
                    System.out.println("  [Error] Please enter a number between " + min + " and " + max + ".");
                }
            } catch (InputMismatchException e) {
                System.out.println("  [Error] Invalid input. Please enter a whole number.");
                scanner.next(); 
            }
        }
        return value;
    }

    public static CalculationResult findMaximumEnergy(int[] energy, int k) {
        int n = energy.length;
        int maxEnergy = Integer.MIN_VALUE;
        int bestStartIndex = -1;

        // Handle case where n <= k, every wizard is a base case.
        if (n <= k) {
             for (int i = 0; i < n; i++) {
                if (energy[i] > maxEnergy) {
                    maxEnergy = energy[i];
                    bestStartIndex = i;
                }
            }
            return new CalculationResult(maxEnergy, bestStartIndex);
        }

        for (int i = n - k; i < n; i++) {
            if (energy[i] > maxEnergy) {
                maxEnergy = energy[i];
                bestStartIndex = i;
            }
        }

        for (int i = n - k - 1; i >= 0; i--) {
            energy[i] += energy[i + k]; 
            if (energy[i] >= maxEnergy) { 
                maxEnergy = energy[i];
                bestStartIndex = i;
            }
        }
        return new CalculationResult(maxEnergy, bestStartIndex);
    }

    private static void displayResults(int[] originalEnergy, int k, CalculationResult result) {
        System.out.println("\n----------------------------------------");
        System.out.println("           Calculation Complete");
        System.out.println("----------------------------------------");

        if (result.startIndex == -1) {
            System.out.println("Could not determine an optimal path.");
            return;
        }

        System.out.println("✨ Maximum Possible Energy: " + result.maxEnergy);
        System.out.println("🧙 To achieve this, you should start with Wizard #" + (result.startIndex + 1));

        System.out.print("👣 Your optimal path and energy gained will be: ");
        StringBuilder path = new StringBuilder();
        for (int i = result.startIndex; i < originalEnergy.length; i += k) {
            path.append(originalEnergy[i]);
            if (i + k < originalEnergy.length) {
                path.append(" + ");
            }
        }
        path.append(" = ").append(result.maxEnergy);
        System.out.println(path.toString());
        System.out.println("----------------------------------------");
    }
}

class CalculationResult {
    final int maxEnergy;
    final int startIndex;

    public CalculationResult(int maxEnergy, int startIndex) {
        this.maxEnergy = maxEnergy;
        this.startIndex = startIndex;
    }
}
