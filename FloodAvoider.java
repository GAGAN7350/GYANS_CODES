import java.util.HashMap;
import java.util.TreeSet;
import java.util.Arrays;
import java.util.Map;
import java.util.Scanner;

public class FloodAvoider {

    public String[] avoidFlood(int[] rains) {
        int n = rains.length;
        String[] ans = new String[n];
        
        Map<Integer, Integer> lastRainDay = new HashMap<>();
        TreeSet<Integer> dryDays = new TreeSet<>();
        
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            
            if (lake == 0) {
                dryDays.add(i);
                // Assign a descriptive default action for an unused dry day
                ans[i] = "Dry lake 1 (default)";
            } else {
                // For a rainy day, describe the event
                ans[i] = "Rain on lake " + lake;
                
                if (lastRainDay.containsKey(lake)) {
                    int lastDay = lastRainDay.get(lake);
                    Integer dryDayToUse = dryDays.higher(lastDay);
                    
                    if (dryDayToUse == null) {
                        // Return an empty string array if a flood is unavoidable
                        return new String[0];
                    }
                    
                    // Assign the specific drying action for the used dry day
                    ans[dryDayToUse] = "Dry lake " + lake;
                    dryDays.remove(dryDayToUse);
                }
                
                lastRainDay.put(lake, i);
            }
        }
        
        return ans;
    }

    public static void main(String[] args) {
        FloodAvoider solver = new FloodAvoider();
        
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("--- Welcome to the Flood Avoider Program ---");
            
            while (true) {
                System.out.println("\nEnter the rain schedule as numbers separated by spaces.");
                System.out.println("For example: 1 2 0 0 2 1");
                System.out.print("Type 'exit' to quit.\n> ");
                
                String line = scanner.nextLine();
                
                if ("exit".equalsIgnoreCase(line.trim())) {
                    break;
                }

                try {
                    String[] parts = line.trim().split("\\s+");
                    
                    if (parts.length == 0 || (parts.length == 1 && parts[0].isEmpty())) {
                        continue;
                    }

                    int[] rains = new int[parts.length];
                    for (int i = 0; i < parts.length; i++) {
                        rains[i] = Integer.parseInt(parts[i]);
                    }

                    // The result is now a String array
                    String[] result = solver.avoidFlood(rains);

                    System.out.println("\n--- Result ---");
                    if (result.length == 0) {
                        System.out.println("It's impossible to avoid a flood with this schedule.");
                        System.out.println("Result: []");
                    } else {
                        System.out.println("A valid plan to avoid floods is:");
                        // Arrays.toString() works perfectly for String arrays too
                        System.out.println("Result: " + Arrays.toString(result));
                    }

                } catch (NumberFormatException e) {
                    System.out.println("\n[Error] Invalid input. Please enter only numbers separated by spaces.");
                }
                System.out.println("------------------------------------------");
            }
        }
        
        System.out.println("\nThank you for using the Flood Avoider. Goodbye!");
    }
}