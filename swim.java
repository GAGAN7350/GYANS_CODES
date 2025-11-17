import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

public class swim {

    private static final int[][] DIRECTIONS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    static class PathResult {
        double totalTime;
        List<int[]> path;

        public PathResult(double totalTime, List<int[]> path) {
            this.totalTime = totalTime;
            this.path = path;
        }
    }

    public PathResult findFastestPath(int[][] grid, double speedInBlocksPerMinute) {
        int n = grid.length;
        double swimTimePerBlockInSeconds = 60.0 / speedInBlocksPerMinute;

        double[][] minTime = new double[n][n];
        for (double[] row : minTime) {
            Arrays.fill(row, Double.POSITIVE_INFINITY);
        }

        int[][][] parent = new int[n][n][2];

        PriorityQueue<double[]> pq = new PriorityQueue<>(Comparator.comparingDouble(a -> a[0]));

        minTime[0][0] = grid[0][0];
        pq.offer(new double[]{minTime[0][0], 0, 0});
        parent[0][0] = new int[]{-1, -1};

        while (!pq.isEmpty()) {
            double[] current = pq.poll();
            double currentTime = current[0];
            int r = (int) current[1];
            int c = (int) current[2];

            if (currentTime > minTime[r][c]) {
                continue;
            }

            if (r == n - 1 && c == n - 1) {
                break;
            }

            for (int[] dir : DIRECTIONS) {
                int newRow = r + dir[0];
                int newCol = c + dir[1];

                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n) {
                    double requiredWaterLevel = Math.max(grid[r][c], grid[newRow][newCol]);
                    double departureTime = Math.max(currentTime, requiredWaterLevel);
                    double newArrivalTime = departureTime + swimTimePerBlockInSeconds;

                    if (newArrivalTime < minTime[newRow][newCol]) {
                        minTime[newRow][newCol] = newArrivalTime;
                        parent[newRow][newCol] = new int[]{r, c};
                        pq.offer(new double[]{newArrivalTime, newRow, newCol});
                    }
                }
            }
        }

        List<int[]> path = new ArrayList<>();
        if (minTime[n-1][n-1] != Double.POSITIVE_INFINITY) {
            int[] curr = {n - 1, n - 1};
            while (curr[0] != -1) {
                path.add(new int[]{curr[0], curr[1]});
                curr = parent[curr[0]][curr[1]];
            }
            Collections.reverse(path);
        }
        
        return new PathResult(minTime[n - 1][n - 1], path);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter the size of the grid (n x n): ");
            int n = scanner.nextInt();

            if (n <= 0) {
                System.out.println("Grid size must be positive.");
                return;
            }

            int[][] grid = new int[n][n];
            System.out.println("Enter the grid elements, one row at a time.");
            for (int i = 0; i < n; i++) {
                System.out.printf("Enter %d numbers for row %d (space-separated): ", n, i + 1);
                for (int j = 0; j < n; j++) {
                    grid[i][j] = scanner.nextInt();
                }
            }
            
            // *** THIS IS THE FIX ***
            // Consume the leftover newline character from the last nextInt() call
            scanner.nextLine(); 
            
            System.out.print("\nEnter the swimmer's speed in blocks per minute (e.g., 60 for 60 blocks per minute): ");
            double speed = scanner.nextDouble();

            if (speed <= 0) {
                System.out.println("Speed must be positive.");
                return;
            }

            swim solution = new swim();
            PathResult result = solution.findFastestPath(grid, speed);

            System.out.println("\n--- Results ---");
            if (result.path.isEmpty()) {
                System.out.println("No path found to the destination.");
            } else {
                System.out.printf("Fastest possible time to reach destination: %.2f seconds\n", result.totalTime);
                System.out.println("Path taken by the swimmer (row, col):");
                for (int[] pos : result.path) {
                    System.out.printf(" -> (%d, %d)\n", pos[0], pos[1]);
                }
            }

        } catch (Exception e) {
            System.out.println("An error occurred. Please enter valid numbers only.");
        } finally {
            scanner.close();
        }
    }
}