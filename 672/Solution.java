import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

class Solution {
  private Map<String, Set<String>> actResult;

  public int flipLights(int n, int m) {
    StringBuilder builder = new StringBuilder();
    for (int i=0; i<n; ++i) {
      builder.append("1");
    }
    String initState = builder.toString();
    actResult = new HashMap<String, Set<String>>();
    Set<String> curStates = new HashSet<String>();
    curStates.add(initState);
    while (m-- > 0) {
      curStates = flipLights(curStates, n);
    }
    return curStates.size();
  }

  /**
   * Press anyone button to flip lights once
   * @param {List<String>} curStates, all possible current states
   * @param {Integer} n, count of all lights
   * @return {Set<String>} all possible states after flip
   */
  public Set<String> flipLights(Set<String> curStates, int n) {
    Set<String> results = new HashSet<String>();
    Iterator<String> it = curStates.iterator();
    while (it.hasNext()) {
      Set<String> resultsFromOneState = flipLights((String)it.next(), n);
      Iterator<String> resIt = resultsFromOneState.iterator();
      while (resIt.hasNext()) {
        results.add((String)resIt.next());
      }
    }
    return results;
  }

  /**
   * Press anyone button to flip lights once 
   * @param {String} cur, current state
   * @param {Integer} n, count of all lights
   * @return {Set<String>} all possible states after flip
   */
  public Set<String> flipLights(String cur, int n) {
    // try to use the cache
    if (actResult.containsKey(cur)) {
      return actResult.get(cur);
    }


    StringBuilder b1= new StringBuilder();
    StringBuilder b2= new StringBuilder();
    StringBuilder b3= new StringBuilder();
    StringBuilder b4= new StringBuilder();

    for (int i=0; i<n; ++i) {
      char origin = cur.charAt(i);
      char opposite = (char)(97 - (int)cur.charAt(i));
      // if press first button: flip all lights
      b1.append(opposite);
      // if press second button: flip lights with even numbers
      // the light is labeled start with 1, so the even number light correspons to odd index 'i' here
      b2.append(i % 2 == 1 ? opposite : origin);
      // if press third button: flip lights with even numbers
      // as explained above, the odd number light correspons to even index 'i' here
      b3.append(i % 2 == 0 ? opposite : origin);
      // if press fourth button: flip the light with 3k + 1 numbers
      // as explained above, the 3k + 1 light correspons to those 'i's which could be divided by 3 with no remainder
      b4.append(i % 3 == 0 ? opposite : origin);
    }

    Set<String> result = new HashSet<String>();
    result.add(b1.toString());
    result.add(b2.toString());
    result.add(b3.toString());
    result.add(b4.toString());
    actResult.put(cur, result);
    return result;
  }

  public static void main(String[] args) {
    Solution s = new Solution();
    System.out.println(s.flipLights(1, 1));
    System.out.println(s.flipLights(2, 1));
    System.out.println(s.flipLights(3, 1));
  }
}