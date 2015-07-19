import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;

public class Solution {
    public int ladderLength(String beginWord, String endWord, Set<String> wordDict) {
        Map<String, Integer> map = new HashMap<String, Integer>();
        int index = 0;
        map.put(beginWord, ++index);
        map.put(endWord, ++index);
        for (Iterator<String> it = wordDict.iterator(); it.hasNext();)
            map.put(it.next(), ++index);
        
        Iterator it = map.keySet().iterator();
        String tmp;
        while (it.hasNext()) {
            tmp = it.next().toString();
            System.out.println(tmp + " -> " + map.get(tmp));
        }
        return map.size();
    }
    
    public static void main(String[] args) {
        String startWord = "hit", endWord = "cog";
        Set<String> wordDict = new HashSet<String>();
		wordDict.add("hot");
        wordDict.add("dot");
        wordDict.add("dog");
        wordDict.add("lot");
        wordDict.add("log");
        new Solution().ladderLength(startWord, endWord, wordDict);
        System.out.println("OK");
    }
}
