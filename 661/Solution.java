class Solution {
  public int[][] imageSmoother(int[][] M) {
    int h = M.length;
    int w = M[0].length;
    int[][] res = new int[h][w];
    for (int i=0; i<h; ++i) {
      for (int j=0; j<w; ++j) {
        res[i][j] = smooth(M, h, w, i, j);
      }
    }
    return res;
  }

  private static int[] moveX = {-1, -1, -1, 0, 1, 1, 1, 0};
  private static int[] moveY = {-1, 0, 1, 1, 1, 0, -1, -1};

  private int smooth(int[][] M, int height, int width, int row, int col) {
    int sum = M[row][col];
    int cell = 1;
    for (int i=0; i<8; ++i) {
      int val = gray(M, height, width, row + moveX[i], col + moveY[i]);
      if (val != -1) {
        ++cell;
        sum += val;
      }
    }
    return sum / cell;
  }

  private int gray(int[][] M, int height, int width, int x, int y) {
    if (x < 0 || x >= height || y < 0 || y >= width) {
      return -1;
    }
    return M[x][y];
  }

  public static void print(int[][] M) {
    int h = M.length;
    int w = M[0].length;
    for (int i=0; i<h; ++i) {
      for (int j=0; j<w; ++j) {
        System.out.print(M[i][j] + ", ");
      }
      System.out.println("");
    }
  }

  public static void main(String[] args) {
    int[][] M = {
      {2, 3, 4},
      {5, 6, 7},
      {8, 9, 10},
      {11, 12, 13},
      {14, 15, 16}
    };
    Solution s = new Solution();
    print(M);
    M = s.imageSmoother(M);
    print(M);
  }
}