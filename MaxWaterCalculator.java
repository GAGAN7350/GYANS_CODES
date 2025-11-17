import java.util.Scanner;
import java.util.InputMismatchException;

public class MaxWaterCalculator {
    public int[] maxArea(int[] height) {
        if (height == null || height.length < 2) {
            return new int[]{0, 0, 0};
        }

        int left = 0;
        int right = height.length - 1;
        int maxArea = 0;
        int bestLeft = 0;
        int bestRight = 0;

        while (left < right) {
            int width = right - left;
            int h = Math.min(height[left], height[right]);
            int currentArea = width * h;
            
            if (currentArea > maxArea) {
                maxArea = currentArea;
                bestLeft = left;
                bestRight = right;
            }

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return new int[]{maxArea, bestLeft, bestRight};
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MaxWaterCalculator calculator = new MaxWaterCalculator();

        try {
            System.out.print("Enter the number of lines: ");
            int n = scanner.nextInt();

            if (n < 2) {
                System.out.println("Error: At least two lines are required.");
                return;
            }

            int[] heights = new int[n];
            System.out.println("Enter the height for each line:");

            for (int i = 0; i < n; i++) {
                System.out.print("Line " + i + ": ");
                heights[i] = scanner.nextInt();
            }

            int[] result = calculator.maxArea(heights);
            int maxAreaValue = result[0];
            int finalLeftIndex = result[1];
            int finalRightIndex = result[2];

            System.out.println("\nMaximum Area: " + maxAreaValue);
            System.out.println("This area is formed by the lines at:");
            System.out.println("- Index " + finalLeftIndex + " (Height: " + heights[finalLeftIndex] + ")");
            System.out.println("- Index " + finalRightIndex + " (Height: " + heights[finalRightIndex] + ")");

        } catch (InputMismatchException e) {
            System.out.println("\nError: Invalid input. Please enter numbers only.");
        } finally {
            scanner.close();
        }
    }
}

