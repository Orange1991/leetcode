import java.util.LinkedList;
import java.util.Queue;

class Solution {
  public String predictPartyVictory(String senate) {
    Queue<Integer> qR = new LinkedList<Integer>();
    Queue<Integer> qD = new LinkedList<Integer>();
    int len = senate.length();
    for (int i = 0; i < len; ++i) {
      char c = senate.charAt(i);
      if (c == 'R') {
        qR.add(i);
      } else {
        qD.add(i);
      }
    }
    while (!qR.isEmpty() && !qD.isEmpty()) {
      int indexR = qR.poll();
      int indexD = qD.poll();
      if (indexR < indexD) {
        qR.add(indexR + len);
      } else {
        qD.add(indexD + len);
      }
    }
    return qR.isEmpty() ? "Dire" : "Radiant";
  }
}