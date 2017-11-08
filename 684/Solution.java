public class Solution {
  public int[] findRedundantConnection(int[][] edges) {
    int MAX = 1000;
    int[] result = new int[2];
    boolean[] visited = new boolean[MAX + 1];
    for (int[] edge : edges) {
      int x = edge[0];
      int y = edge[1];
      if (visited[x] && visited[y]) {
        result[0] = x;
        result[1] = y;
        break;
      }
      visited[x] = visited[y] = true;
    }
    return result;
  }

  public static void main(String[] args) {
    int[][] a = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    int[][] b = {{1,2}, {1,3}, {2,3}};
    Solution s = new Solution();
    int[] r = s.findRedundantConnection(a);
    System.out.println(r[0] + ", " + r[1]);
    r = s.findRedundantConnection(b);
    System.out.println(r[0] + ", " + r[1]);
  }
}