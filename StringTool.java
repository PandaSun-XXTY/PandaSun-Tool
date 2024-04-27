import java.util.Arrays;
/**
 * 这个类被设计来存储一些有关String的工具
 * This class is being designed to store some tools about String
 */

public class StringTool {
    public static void main(String[] args) {
        String a = "Hello World I know that the universe love me.";
        System.out.println(1);
        System.out.println(Arrays.toString(separate(a)));
        String[] test = new String[]{"A sentence", "Two sentences", "PadaSun"};
        System.out.println(Arrays.toString(test));
    }

    //test
    /*test*/

    /**
     * 将字符串按空格拆分，返回拆分后的String数组
     * Split the String by space and return the split string array
     *
     * @param str
     * @return String[]
     */
    public static String[] separate(String str) {
        String[] result;
        int first = str.indexOf(" ");
        if (first == -1) {
            return new String[]{str};
        } else {
            str = format(str);
            int tot = 0;
            int posi = 0;
            str = format(str);
            while (true) {
                posi = str.indexOf(" ", posi + 1);
                if (posi == -1) {
                    break;
                } else {
                    tot++;
                    //System.out.println(tot);
                }
            }
            result = new String[tot + 1];
            int front = -1;
            posi = 0;
            for (int i = 0; i < tot; i++) {
                posi = str.indexOf(" ", posi + 1);
                result[i] = str.substring(front + 1, posi);
                front = posi;
            }
            result[tot] = str.substring(front + 1);
            return result;
        }
    }

    public static String format(String word) {
        word = word.replaceAll("\\s+", " ");
        int and = word.indexOf('&');
        if (and != -1) {
            word = word.substring(0, and) + "&" + word.substring(and + 2);
        }
        return word;
    }
}
