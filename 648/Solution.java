import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
  class TrieNode {
    public char c;
    public boolean isEnd;
    public TrieNode[] successors;
    public TrieNode(char c, boolean isEnd) {
      this.c = c;
      this.isEnd = isEnd;
      this.successors = new TrieNode[26];
    }

    public String toString() {
      StringBuilder sb = new StringBuilder().append(c).append(isEnd ? "-true-" : "-false-");
      for (TrieNode node : successors) {
        if (node != null) {
          sb.append(node.toString());
        }
      }
      return sb.toString();
    }
  }

  class Trie {
    public TrieNode root;
    public Trie() {
      root = new TrieNode('0', false);
    }

    public String findRoot(String word) {
      StringBuilder builder = new StringBuilder();
      TrieNode node = root;
      TrieNode successor = null;
      for (int i = 0, len = word.length(); i < len - 1; ++i) {
        char c = word.charAt(i);
        builder.append(c);
        int index = c - 'a';
        successor = node.successors[index];
        if (successor != null) {
          if (successor.isEnd) {
            return builder.toString();
          } else {
            node = successor;
          }
        } else {
          return word;
        }
      }
      return word;
    }

    public void add(List<String> dict) {
      for (String word : dict) {
        add(word);
      }
    }

    public void add(String word) {
      TrieNode node = root;
      for (int i = 0, len = word.length(); i < len; ++i) {
        node = add(node, word.charAt(i), i == len - 1);
      }
    }

    public TrieNode add(TrieNode node, char c, boolean isEnd) {
      int index = c - 'a';
      TrieNode successor = node.successors[index];
      if (successor == null) {
        successor = new TrieNode(c, isEnd);
        node.successors[index] = successor;
      } else if (isEnd && !successor.isEnd) {
        successor.isEnd = true;
      }
      return successor;
    }

    public String toString() {
      return root.toString();
    }
  }

  public String replaceWords(List<String> dict, String sentence) {
    Trie trie = new Trie();
    trie.add(dict);
    String[] words = sentence.split(" ");
    String[] replaced = new String[words.length];
    Map<String, String> map = new HashMap<String, String>();
    for (int i= 0, len = words.length; i < len; ++i) {
      String word = words[i];
      String replacement = map.get(word);
      if (replacement != null) {
        replaced[i] = replacement;
      } else {
        replacement = trie.findRoot(word);
        replaced[i] = replacement;
        map.put(word, replacement);
      }
    }
    StringBuilder builder = new StringBuilder();
    for (String word : replaced) {
      builder.append(word).append(" ");
    }
    return builder.toString().trim();
  }

  public static void main(String[] args) {
    List<String> dict = new ArrayList<String>();
    dict.add("cat");
    dict.add("bat");
    dict.add("rat");
    String sentence = "the cattle was rattled by the battery";
    Solution s = new Solution();
    String result = s.replaceWords(dict, sentence);
    System.out.println("++" + result + "++");
  }
}
