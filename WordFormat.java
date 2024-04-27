import java.util.Arrays;
import java.util.Scanner;

public class WordFormat {
    public static Scanner scan = Word.scan;

    public static String format(String word) {          //格式化空格
        word = word.replaceAll("\\s+", " ");
        int and = word.indexOf('&');
        if (and != -1) {
            word = word.substring(0, and) + "&" + word.substring(and + 2);
        }
        return word;
    }

    public static void main(String[] args) {
        String test = "test v. 测试";
        System.out.println(new Word(test));
        Word word = new Word("brake   n. 闸 vi. 刹车");
        System.out.println(word);
        System.out.println(word.getWord());
        System.out.print(word.getPart(1));
        System.out.println(" "+word.getChinese(1));
        System.out.println(word.getPart(2)+" "+word.getChinese(2));
    }
}

class Word {
    public static Scanner scan = new Scanner(System.in);

    enum Parts {
        unknown,        //未知词性
        n,              //名词
        adj,            //形容词
        adv,            //副词
        v,              //动词
        prep,           //介词
        pron,           //代词
        num,            //数词
        conj,           //助词
        vt,             //及物动词
        vi,             //不及物动词
        a               //形容性的词
    }

    private String word;
    private Parts[] part;
    private String[] Chinese;
    private String specialPart;
    int tot;


    Word() {
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Word) {
            Word wordObject = (Word) obj;
            return this.word.equals(wordObject.word);
        }
        return false;
    }

    Word(String str) {
        String[] in = StringTool.separate(str);
        word = in[0];
        tot = (in.length - 1) / 2;
        part = new Parts[tot];
        Chinese = new String[tot];
        for (int i = 1; i < in.length; i++) {
            part[i / 2] = partConversion(in[i]);
            i++;
            Chinese[i / 2 - 1] = in[i];
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder(word);
        for (int i = 0; i < part.length; i++) {
            s.append(" ").append(part[i]).append(". ").append(Chinese[i]);
        }
        return s.toString();
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    private Parts[] getPart() {
        return part;
    }

    public Parts getPart(int posi) {
        return part[posi - 1];
    }

    public int getTot() {
        return tot;
    }

    public void setPart(Parts[] part) {
        //int length = part.length;
        this.part = Arrays.copyOf(part, part.length);
    }

    public String[] getChinese() {
        return Chinese;
    }

    public String getChinese(int posi) {
        return Chinese[posi - 1];
    }

    public void setChinese(String[] chinese) {
        Chinese = Arrays.copyOf(chinese, chinese.length);
    }

    private static Parts partConversion(String str) {
        switch (str) {
            case "n":
            case "n.":
                return Parts.n;
            case "adj":
            case "adj.":
                return Parts.adj;
            case "adv":
            case "adv.":
                return Parts.adv;
            case "v":
            case "v.":
                return Parts.v;
            case "prep":
            case "prep.":
                return Parts.prep;
            case "pron":
            case "pron.":
                return Parts.pron;
            case "num":
            case "num.":
                return Parts.num;
            case "conj":
            case "conj.":
                return Parts.conj;
            case "vt":
            case "vt.":
                return Parts.vt;
            case "vi":
            case "vi.":
                return Parts.vi;
            case "a":
            case "a.":
                return Parts.a;
            default:
                return Parts.unknown;
        }
    }
}
