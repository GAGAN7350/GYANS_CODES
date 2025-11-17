import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.InputMismatchException;

public class WaterFlow {
    public List<List<Integer>> pacificAtlantic(int[][] heights) {
        List<List<Integer>> result = new ArrayList<>();
        if (heights == null || heights.length == 0 || heights[0].length == 0) {
            return result;
        }

        int m = heights.length;
        int n = heights[0].length;

        boolean[][] pacificReachable = new boolean[m][n];
        boolean[][] atlanticReachable = new boolean[m][n];

        // Start DFS from the borders for Pacific (top and left)
        for (int col = 0; col < n; col++) {
            dfs(0, col, heights, pacificReachable);
        }
        for (int row = 0; row < m; row++) {
            dfs(row, 0, heights, pacificReachable);
        }

        // Start DFS from the borders for Atlantic (bottom and right)
        for (int col = 0; col < n; col++) {
            dfs(m - 1, col, heights, atlanticReachable);
        }
        for (int row = 0; row < m; row++) {
            dfs(row, n - 1, heights, atlanticReachable);
        }

        // Find the intersection of cells that can reach both oceans
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacificReachable[i][j] && atlanticReachable[i][j]) {
                    result.add(Arrays.asList(i, j));
                }
            }
        }

        return result;
    }

    /**
     * Performs a Depth First Search to find all cells reachable from an ocean border.
     */
    private void dfs(int row, int col, int[][] heights, boolean[][] reachable) {
        // Base case: if already visited, stop.
        if (reachable[row][col]) {
            return;
        }
        
        reachable[row][col] = true;

        int m = heights.length;
        int n = heights[0].length;
        
        // Directions for neighbors (up, down, left, right)
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            // Check if the neighbor is valid: within bounds
            if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n) {
                continue;
            }
            
            // Check if we can "flow" from the current cell to the neighbor (uphill)
            if (heights[newRow][newCol] >= heights[row][col]) {
                dfs(newRow, newCol, heights, reachable);
            }
        }
    }

    /**
     * Main method to handle user input and run the algorithm.
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("--- Pacific Atlantic Water Flow Solver ---");

        try {
            System.out.print("Enter the number of rows (m): ");
            int m = scanner.nextInt();

            System.out.print("Enter the number of columns (n): ");
            int n = scanner.nextInt();

            if (m <= 0 || n <= 0) {
                System.out.println("Error: Dimensions must be positive integers.");
                return;
            }

            int[][] heights = new int[m][n];

            System.out.println("Enter the heights for each cell (row by row):");
            for (int i = 0; i < m; i++) {
                System.out.printf("Row %d (enter %d space-separated numbers): ", i, n);
                for (int j = 0; j < n; j++) {
                    heights[i][j] = scanner.nextInt();
                }
            }
            
            System.out.println("\nInput Matrix:");
            for (int[] row : heights) {
                System.out.println(Arrays.toString(row));
            }

            WaterFlow solver = new WaterFlow();
            List<List<Integer>> result = solver.pacificAtlantic(heights);

            System.out.println("\nResult: Coordinates that can flow to both oceans:");
            if (result.isEmpty()) {
                System.out.println("No such coordinates found.");
            } else {
                 for (List<Integer> coord : result) {
                    System.out.println(coord);
                }
            }

        } catch (InputMismatchException e) {
            System.out.println("Error: Invalid input. Please enter integers only.");
        } finally {
            scanner.close();
        }
    }
}
