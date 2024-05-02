#ifndef BigInt
#define BigInt
#include <iostream>
#include <string>
#define null nullptr;
using namespace std;
typedef string String;

class Bint {
	private:
		virtual Bint reduce(Bint &b, String str)const {			//已被废弃
			int length = (this->length > b.getLength()) ? (this->length) : (b.getLength());
			int* tmp = new int[length] {0};
			tmp[0] = 0;
			for (int i = 0; i < length; i++) {		//实行减法
				if (this->length - i - 1 >= 0 && b.length - i - 1 >= 0) {
					tmp[length - 1 - i] = this->num[this->length - 1 - i] - b.num[b.length - 1 - i];
				} else if (this->length - 1 - i >= 0) {
					tmp[length - 1 - i] = this->length - 1 - i;
				} else {
					tmp[length - 1 - i] = -b.length - 1 - i;
				}
			}
			for (int i = length - 1; i > 0; i-- ) {
				if (tmp[i] < 0) {
					tmp[i - 1] += tmp[i] / 10 - 1;
					tmp[i] = tmp[i] % 10 + 10;
				}
			}
			if (tmp[0] > 0) {
				return Bint(1, tmp, length, true, 0);
			} else if (tmp[0] < 0) {
				return Bint(-1, tmp, length, true, 0);
			} else {
				for (int i = 0; i < length; i++) {
					if (tmp[i] != 0) {
						if (tmp[i] > 0) {
							for (int s = 0; s < length; s++) {

							}
							return Bint(1, tmp, length - i, true, i);
						} else {
							return Bint(-1, tmp, length - i, true, i);
						}
					}
				}
				return Bint(0);
			}
		}

		static String format(String a) {		//未审查		//格式化		//已被废弃
			int length = a.length();
			for (int i = length - 1; i >= 0; i--) {
				a[i - 1] += (a[i] - '0') / 10;
				a[i] = (a[i] - '0') % 10 + '0';
			}
			return a;
		}

		Bint(String str, int length) {		//废弃
			if (str == "length") {
				num = new int[length] {0};
			}
		}

	protected:
		int sign;			//1 is +,0 is zero,-1 is -
		int* num;
		int length;

		//public:
		//	static const int INTMAX = 2147483647;
		//	static const int INTMIN = -2147483648;
		//	static const long long LONGMAX = 9223372036854775807LL;
		//	static const long long LONGMIN = -9223372036854775808LL;
		//	static const unsigned long long ULONGMAX = 18446744073709551615ULL;


	public:
		virtual Bint reduce(const Bint &b, bool big)const {	//2024.2.11编写通过	//保证减数大于被减数
			int length = this->length;
			int* tmp = new int[length] {0};
			for (int i = 0; i < length; i++) {		//初始化
				tmp[i] = 0;
			}
			//this->length - i - 1是a的末位
			//b.length - i - 1是b的末位

			for (int i = 0; i < length; i++) {			//执行减法
				if (b.length - 1 - i >= 0) {		//索引不越界
					if (this->num[this->length - i - 1] + tmp[length - 1 - i] >= b.num[b.length - 1 - i]) {
						tmp[length - 1 - i] += this->num[this->length - i - 1] - b.num[b.length - 1 - i];
					} else {
						tmp[length - 1 - i] += this->num[this->length - i - 1] - b.num[b.length - 1 - i] + 10;
						tmp[length - 2 - i]--;
					}
				} else {
					tmp[length - 1 - i] += this->num[this->length - i - 1];
				}
			}
			if (tmp[0] > 0) {		//正数，最高位不为0
				if (big) {
					return Bint(1, tmp, length, true, 0);
				} else {
					return Bint(-1, tmp, length, true, 0);
				}
			} else {
				for (int i = 0; i < length; i++) {
					if (tmp[i] != 0) {		//在此处最高位不为0
						if (tmp[i] > 0) {		//正数
							if (big) {
								return Bint(1, tmp, length - i, true, i);
							} else {
								return Bint(-1, tmp, length - i, true, i);
							}
						}
					}
				}
			}
		}

		static String toString(long long a) {	//2024.2.11审查通过		//数字转字符串
			String back = "";
			if (a == 0) {
				return "0";
			} else if (a < 0) {
				a = -a;
				while (a) {
					back = (char)(a % 10 + '0') + back;
					a /= 10;
				}
				back = "-" + back;
				return back;
			}
			while (a) {
				back = (char)(a % 10 + '0') + back;
				a /= 10;
			}
			return back;
		}

	public :
		virtual String toString() {
			return get();
		}

		virtual ~Bint() {		//析构函数
			delete[] num;
		}

		Bint(istream &in) {
			String str;
			in >> str;
			int i = 0;
			int s;
			int* tmp;
			if (str == "0") {
				sign = 0;
				num = new int[1] {0};
				length = 0;
				num[0] = 0;
				return;
			} else if (str[0] == '-') {
				sign = -1;
				s = 1;
				tmp = new int[str.length() - 1] {0};
				length = str.length() - 1;
			} else {
				sign = 1;
				s = 0;
				tmp = new int[str.length()] {0};
				length = str.length();
			}
			int tmpLength = str.length();
			bool first = true;		//是第一位
			int tot = 0;		//统计实际长度
			for (; s < tmpLength; s++) {
				if (first) {
					if (str[s] > '9' || str[s] < '0') {		//不是数字
						delete[] tmp;
						length = -1;
						num = null;
						return;
					} else if (str[s] != '0') {
						first = false;
						tmp[i] = str[s] - '0';
						tot++;
						i++;
					}
				} else {
					if (str[s] > '9' || str[s] < '0') {		//不是数字
						delete[] tmp;
						length = -1;
						num = null;
						return;
					} else {
						tmp[i] = str[s] - '0';
						tot++;
						i++;
					}
				}
			}
			if (tot == 0) {
				sign = 0;
				delete[] tmp;
				num = new int[1] {0};
				length = 0;
				num[0] = 0;
				return;
			} else {
				num = new int[tot] {0};
				length = tot;
				for (int i = 0; i < tot; i++) {			//新的i，与原来的不同
					num[i] = tmp[i];
				}
				delete[] tmp;
			}
		}

		Bint(String str) {			//2024.2.6  编写通过
			int i = 0;
			int s;
			int* tmp;
			if (str == "0") {
				sign = 0;
				num = new int[1] {0};
				length = 0;
				num[0] = 0;
				return;
			} else if (str[0] == '-') {
				sign = -1;
				s = 1;
				tmp = new int[str.length() - 1] {0};
				length = str.length() - 1;
			} else {
				sign = 1;
				s = 0;
				tmp = new int[str.length()] {0};
				length = str.length();
			}
			int tmpLength = str.length();
			bool first = true;		//是第一位
			int tot = 0;		//统计实际长度
			for (; s < tmpLength; s++) {
				if (first) {
					if (str[s] > '9' || str[s] < '0') {		//不是数字
						delete[] tmp;
						length = -1;
						num = null;
						return;
					} else if (str[s] != '0') {
						first = false;
						tmp[i] = str[s] - '0';
						tot++;
						i++;
					}
				} else {
					if (str[s] > '9' || str[s] < '0') {		//不是数字
						delete[] tmp;
						length = -1;
						num = null;
						return;
					} else {
						tmp[i] = str[s] - '0';
						tot++;
						i++;
					}
				}
			}
			if (tot == 0) {
				sign = 0;
				delete[] tmp;
				num = new int[1] {0};
				length = 0;
				num[0] = 0;
				return;
			} else {
				num = new int[tot] {0};
				length = tot;
				for (int i = 0; i < tot; i++) {			//新的i，与原来的不同
					num[i] = tmp[i];
				}
				delete[] tmp;
			}
		}

		Bint(long long a) {			//2024.2.6  审查通过
			if (a == 0) {
				sign = 0;
				num = new int[1] {0};
				num[0] = 0;
				length = 0;
				return;
			} else if (a < 0) {
				sign = -1;
				a *= -1;
			} else {
				sign = 1;
			}
			length = 0;
			long long b = a;
			while (a) {
				length++;
				a = a / 10;
			}
			num = new int[length] {0};
			for (int i = 1; i <= length; i++) {
				num[length - i] = b % 10;
				b /= 10;
			}
		}

		Bint() {}

		Bint(const Bint &a) {		//2024.2.6审查通过		//自定义复制构造函数
			if (a.sign == 0) {
				this->sign = 0;
				num = new int[1];
				num[0] = 0;
				this->length = 0;
				return;
			}
			sign = a.sign;
			length = a.length;
			num = new int[length] {0};
			for (int i = 0; i < length; i++) {
				num[i] = a.num[i];
			}
		}

		virtual Bint operator=(const Bint& b) {
			if (b.sign == 0) {
				this->sign = 0;
				delete[] num;
				num = new int[1];
				num[0] = 0;
				this->length = 0;
				return (*this);
			}
			delete[] num;
			this->length = b.length;
			this->sign = b.sign;
			num = new int[this->length];
			for (int i = 0; i < this->length; i++) {
				num[i] = b.num[i];
			}
			return *this;
		}

		virtual Bint operator+(const Bint &b) const {
			return add(b);
		}

		virtual void operator+=(const Bint &b) {
			*this = this->add(b);
		}

		virtual Bint operator-(const Bint &b)const {
			return reduce(b);
		}

		virtual void operator-=(const Bint &b) {
			*this = this->reduce(b);
		}

		virtual Bint operator*(const Bint &b)const {
			return multiplication(b);
		}

		virtual void operator*=(const Bint &b) {
			*this = b.multiplication(*this);
		}

		virtual bool operator>(const Bint &b)const {
			return this->compareTo(b) == 1;
		}

		virtual bool operator<(const Bint &b)const {
			return this->compareTo(b) == -1;
		}

		Bint(int sign, int* numIn, int length, bool del, int start) {	//2024.2.11审查通过		//给出所有参数情况下的复制
			this->sign = sign;
			this->length = length;
			num = new int[length] {0};
			for (int i = length - 1; i >= 0; i--) {
				num[i] = numIn[start + i];
			}
			if (del) {
				delete[] numIn;
			}
		}

		virtual Bint add(const Bint &b) const {		//2024.2.11审查通过		//加法
			if (this->sign == 0) {
				return Bint(b);
			} else if (b.sign == 0) {
				return (*this);
			}
			if (this->sign == b.sign) {
				int length = (this->length > b.length) ? (this->length) : (b.length);
				int* tmp = new int[length + 1] {0};
				tmp[0] = 0;
				for (int i = 0; i < length; i++) {			//进行加法
					if (this->length - 1 - i >= 0 && b.length - 1 - i >= 0) {
						tmp[length  - i] = this->num[this->length - i - 1] + b.num[b.length - i - 1];
					} else if (this->length - 1 - i >= 0) {
						tmp[length  - i] = this->num[this->length - i - 1];
					} else {
						tmp[length  - i] = b.num[b.length - i - 1];
					}
				}
				for (int i = length ; i > 0; i--) {			//格式化
					tmp[i - 1] += tmp[i] / 10;
					tmp[i] %= 10;
				}
				if (tmp[0] == 0) {
					if (b.sign > 0) {
						return Bint(1, tmp, length, true, 1);
					} else {
						return Bint(-1, tmp, length, true, 1);
					}
				} else {
					if (b.sign > 0) {
						return Bint(1, tmp, length + 1, true, 0);
					} else {
						return Bint(-1, tmp, length + 1, true, 0);
					}
				}
			} else {
				if (this->sign == 1) {
					Bint temp = b;
					temp.sign = 1;
					return (*this).reduce(temp);
				} else {
					return b.add(*this);
				}
			}
		}

		virtual Bint reduce(const Bint &b)const {	//2024.2.11审查通过			//减法
			if (this->sign == 0) {
				Bint result = b;
				result.sign *= -1;
				return result;
			} else if (b.sign == 0) {
				return (*this);
			} else if (this->sign != b.sign) {
				Bint c = b;
				c.sign *= -1;
				return (*this).add(c);
			}
			//保证传入两个正数
			if (this->sign == 1) {
				int compare = (*this).compareTo(b);
				if (compare > 0) {
					return (*this).reduce(b, true);
				} else if (compare == 0) {
					return Bint(0);
				} else {
					return b.reduce((*this), false);
				}
			} else {
				Bint m = (*this);
				Bint n = b;
				m.sign = 1;
				n.sign = 1;
				Bint result = m.reduce(n);
				result.sign = -1;
				return result;
			}
		}

		//递归快速幂
		//https://zhuanlan.zhihu.com/p/95902286
		static Bint pow(const Bint &a, int n) {
			if (n == 0)
				return Bint(1);
			else if (n % 2 == 1)
				return pow(a, n - 1).multiplication(a);
			else {
				Bint temp = pow(a, n / 2);
				return temp.multiplication(temp);
			}
		}

		virtual int compareTo(const Bint &b) const {	//2024.2.6审查通过		//比较大小
			if (this->sign > b.getSign()) {			//正数大于0大于负数
				return 1;
			} else if (this->sign < b.getSign()) {		//负数小于0小于正数
				return -1;
			} else if (this->sign == 0) {			//0不大于0
				return 0;
			} else if (this->sign > 0) {			//正数比较
				if (this->length > b.getLength()) {
					return 1;				//位数多的数大
				} else if (this->length < b.getLength()) {
					return -1;				//位数少的数小
				} else {
					//int* bnum = b.getNum();
					for (int i = 0; i < length; i++) {
						if (this->num[i] > b.num[i]) {		//从前开始比，大的数大
							return 1;
						} else if (this->num[i] < b.num[i]) {		//小的数小
							return -1;
						}
					}
					return 0;
				}
			} else {				//负数比较
				if (this->length > b.getLength()) {
					return -1;				//位数多的数小
				} else if (this->length < b.getLength()) {
					return 1;				//位数少的数大
				} else {
					//int* bnum = b.getNum();
					for (int i = 0; i < length; i++) {
						if (this->num[i] > b.num[i]) {		//从前开始比，大的数大
							return -1;
						} else if (this->num[i] < b.num[i]) {		//小的数小
							return 1;
						}
					}
					return 0;
				}
			}
		}

		virtual bool equal(const Bint &b) const {
			return compareTo(b) == 0;
		}

		virtual String get() const {			//2024.2.6审查通过		//得到数字
			if (num == ((void*)0)) {
				return "NaN";
			}
			String a;
			if (sign == -1) {
				a = "-";
			} else if (sign == 0) {
				return "0";
			}
			for (int i = 0; i < length; i++) {
				a += (num[i] + '0');
			}
			return a;
		}

		virtual String getln()const {
			return ((*this).get() + "\n");
		}

		virtual int getLength() const {
			return length;
		}

		virtual int getSign() const {
			return sign;
		}

		virtual int* getNum() const {
			return num;
		}

		virtual void out() const {
			cout << get();
		}

		virtual void outln() const {
			cout << getln();
		}

		virtual ostream& out(ostream &os) const {
			os << get();
			return os;
		}

		virtual ostream& outln(ostream &os) const {
			os << get() << endl;
			return os;
		}

		friend istream& operator>>(istream &in, Bint &a) {
			String str;
			in >> str;
			a = Bint(str);
			return in;
		}

		friend ostream& operator<<(ostream& out, const Bint &a) {
			out << a.get();
			return out;
		}

		virtual bool operator!=(const Bint&b) {
			return this->compareTo(b) != 0;
		}

		virtual bool operator==(const Bint&b) {
			return !((*this) != b);
		}

		virtual Bint multiplication(const Bint &b)const {			//2024.3.8 编写通过
			if ((this->sign == 0) || (b.sign == 0)) {		//0乘任何数都得0
				return Bint(0);
			}
			int* tmp = new int[this->length + b.length] {0};
			int* ans = new int[this->length + b.length] {0};
			for (int i = 0; i < this->length; i++) {
				for (int s = 0; s < b.length; s++) {
					tmp[this->length + b.length - i - s - 1] = this->num[this->length - i - 1] * b.num[b.length - s - 1];
				}
				for (int s = this->length + b.length - 1; s > 0; s--) {
					ans[s] += tmp[s];
					tmp[s] = 0;
					ans[s - 1] += ans[s] / 10;
					ans[s] %= 10;
				}
				ans[0] += tmp[0];
				tmp[0] = 0;
			}
			delete[] tmp;
			for (int i = 0; i < this->length + b.length; i++) {
				if (ans[i] != 0) {
					return Bint(this->sign * b.sign, ans, this->length + b.length - i, true, i);
				}
			}
			delete[] ans;
			return Bint(0);
		}
};
#endif
