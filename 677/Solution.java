import java.util.Map;
import java.util.HashMap;

public class Solution {
    public static void main(String[] args) {
        MapSum obj = new MapSum();
        obj.insert("apple", 3);
        int sum = obj.sum("ap");
        System.out.println(sum);
        obj.insert("app", 2);
        sum = obj.sum("ap");
        System.out.println(sum);
        obj.insert("apple", 4);
        sum = obj.sum("ap");
        System.out.println(sum);
    }
}

class MapSum {
    private Map<String, Integer> keySum;
    private Map<String, Integer> keyVal;

    /** Initialize your data structure here. */
    public MapSum() {
        this.keySum = new HashMap<String, Integer>();
        this.keyVal = new HashMap<String, Integer>();
    }
    
    public void insert(String key, int val) {
        boolean shouldUpdate = true;
        int diff = val;
        if (keyVal.containsKey(key)) {
            int cur = keyVal.get(key);
            if (cur == val) {
                shouldUpdate = false;
            } else {
                diff = val - cur;
            }
        }
        keyVal.put(key, val);
        if (shouldUpdate) {
            StringBuilder sb = new StringBuilder();
            for (int i=0, len=key.length(); i<len; ++i) {
                sb.append(key.charAt(i));
                update(sb.toString(), diff);
            }
        }
    }

    private void update(String key, int diff) {
        int newSum = keySum.containsKey(key) ? keySum.get(key) + diff : diff;
        keySum.put(key, newSum);
    }
    
    public int sum(String prefix) {
        return keySum.get(prefix);
    }
}