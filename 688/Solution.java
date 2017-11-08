
public class Solution {
    private static class Move {
        public int x;
        public int y;
        public Move(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    private static Move[] moves = {
       new Move(-2, 1), new Move(-1, 2), new Move(1, 2), new Move(2, 1), new Move(2, -1), new Move(1, -2), new Move(-1, -2), new Move(-2, -1)
    };
    private double probabilityCache[][][];
    public double knightProbability(int N, int K, int r, int c) {
        probabilityCache = new double[N][N][K + 1];
        for (int i=0; i<N; ++i) {
          for (int j=0; j<N; ++j) {
            for (int k=0; k<K+1; ++k) {
              probabilityCache[i][j][k] = -1.0;
            }
          }
        }
        return this.onBoardProbabilityAfterKMove(N, K, r, c);
    }

    public double onBoardProbabilityAfterKMove(int N, int K, int r, int c) {
        if (r < 0 || r >= N || c < 0 || c >= N) {
            return 0.0;
        } else if (probabilityCache[r][c][K] >= 0.0) {
            return probabilityCache[r][c][K];
        } else if (K <= 0) {
            probabilityCache[r][c][K] = 1.0;
        } else if (N < 3) {
            probabilityCache[r][c][K] = 0.0;
        } else {
            double probability = 0.0;
            for (Move m : moves) {
                probability += this.onBoardProbabilityAfterKMove(N, K - 1, r + m.x, c + m.y) / 8.0;
            }
            probabilityCache[r][c][K] = probability;
        }
        return probabilityCache[r][c][K];
    }

    public static void main(String[] args) {
        System.out.println(new Solution().knightProbability(8, 30, 6, 4));
    }
}