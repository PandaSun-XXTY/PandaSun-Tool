import java.util.Scanner;
public class Lyric {
	public static Scanner scan = new Scanner(System.in);
	public LyricTime time;
	public String origin;
	public String translation;
	public Lyric(String str) {
		time = new LyricTime(str.substring(0, 11));
		int length = str.length();
		for (int i = 11; i <= length; i++) {
			if (i == length) {
				this.origin = str.substring(11, length);
				this.translation = "";
			} else if (str.charAt(i) > 128) {
				if((str.charAt(i)=='α')||(str.charAt(i)=='β')||(str.charAt(i)=='π')){
					continue;
				}
				origin = str.substring(11, i);
				translation = str.substring(i, length);
				break;
			}
		}
	}
	
	public String toString() {
		return time.toString() + origin + translation;
	}
	
	public String getOrigin(boolean need) {
		if (need) {
			return time.toString() + origin;
		} else {
			return origin;
		}
	}
	
	public String getTranslation() {
		return translation;
	}
	
	public Lyric() {}
	
	public LyricTime getTime() {
		return time;
	}
	
	public static void main(String[] args) {
		
	}
}

class LyricTime {
	int minute;
	int second;
	int ms;
	
	public String toString() {
		StringBuilder str = new StringBuilder("[");
		if (minute < 10) {
			str.append("0" + minute);
		} else {
			str.append("" + minute);
		}
		str.append(":");
		if (second < 10) {
			str.append("0" + second);
		} else {
			str.append("" + second);
		}
		str.append(":");
		if (ms < 10) {
			str.append("00" + ms);
		} else if (ms < 100) {
			str.append("0" + ms);
		} else {
			str.append("" + ms);
		}
		return str.append("]").toString();
	}
	
	public LyricTime() {}
	
	public LyricTime(LyricTime b) {
		this.minute = b.minute;
		this.second = b.second;
		this.ms = b.ms;
	}
	
	public LyricTime add(int time) {
		LyricTime r = new LyricTime(this);
		r.ms += time;
		r.second += r.ms / 1000;
		r.ms %= 1000;
		r.minute += r.second / 60;
		r.second %= 60;
		return r;
	}
	
	public LyricTime reduce(int time) {
		return new LyricTime(this.toInt() - time);
	}
	
	public LyricTime(int time) {
		minute = time / 60000;
		second = time / 1000 - minute * 60;
		ms = time % 1000;
	}
	
	public int toInt() {
		return minute * 60000 + second * 1000 + ms;
	}
	
	public LyricTime(String str) {
		minute = Integer.valueOf(str.substring(1, 3)).intValue();
		second = Integer.valueOf(str.substring(4, 6)).intValue();
		ms = Integer.valueOf(str.substring(7, 10)).intValue();
	}
}