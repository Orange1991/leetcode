import java.util.Set;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Queue;
import java.util.LinkedList;
import java.util.HashMap;

public class Solution {

    public int ladderLength(String beginWord, String endWord, Set<String> wordDict) {
        if (beginWord == null || endWord == null || beginWord.equals(endWord) || beginWord.length() != endWord.length())
            return 0;

        if (isOneCharDiff(beginWord, endWord))
            return 2;

        /* 广度优先遍历 
         * 遍历到的新点入队列queue
         * 同时将源点beginWord到新点的距离存在visited中 */
        Queue<String> queue = new LinkedList<String>();
        queue.add(beginWord);
        HashMap<String, Integer> visited = new HashMap<String, Integer>();
        visited.put(beginWord, 1);
         
        String tmp, sbStr;
        int len, distance;
        while (!queue.isEmpty()) {
            // 获取队首元素
            tmp = queue.poll();
            // 依次将字符串的某一位替换为a-z中的字母
            len = tmp.length();
            for (int i = 0; i < len; ++i) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    // 如果替换后字符串没有变化，则跳过此次尝试
                    if (tmp.charAt(i) == c) continue;

                    // 拷贝原字符串，并修改某一位为某一个字符
                    StringBuilder sb = new StringBuilder(tmp);
                    sb.setCharAt(i, c);
                    sbStr = sb.toString();
                    distance = visited.get(tmp) + 1; // 从visited中获取beginWord到tmp的距离并加1

                    // 如果新字符串就是endWord，返回距离
                    if (sbStr.equals(endWord))
                        return distance;

                    // 如果字典中有这个字符串，并且这个字符串是第一次被遍历到
                    // 则将其作为新字符串添加到队列queue中，并添加到visited中&记录距离
                    if (wordDict.contains(sbStr) && !visited.containsKey(sbStr)) {
                        queue.add(sbStr);
                        visited.put(sbStr, distance);
                    }
                }
            }
        }

        // 执行至此，说明图为非连通图，beginWord和endWord之间不能转换
        return 0;
    }
    
    /**
     * 判断两个字符串的差异度是否为1
     * 字符串长度相同，比较每一位字母，判断差异度
     * @param str1 字符串1
     * @param str2 字符串2
     * @return 两字符串差异度为1则返回true，否则返回false
     */
    private boolean isOneCharDiff(String str1, String str2) {
        int count = 0, len = str1.length();
        for (int i = 0; i < len; ++i) {
            if (str1.charAt(i) != str2.charAt(i)) {
                ++count;
                if (count > 1)
                    return false;
            }
        }

        return count == 1;
    }

    public static void main(String[] args) {
        String startWord = "hit", endWord = "cog";
        Set<String> wordDict = new HashSet<String>();
		wordDict.add("hot");
        wordDict.add("dot");
        wordDict.add("dog");
        wordDict.add("lot");
        wordDict.add("log");
        System.out.println(new Solution().ladderLength(startWord, endWord, wordDict));
        

        Set<String> dict = new HashSet<String>();
		dict.add("a");
        dict.add("b");
        dict.add("c");
        System.out.println(new Solution().ladderLength("a", "b", dict));
    }
}
