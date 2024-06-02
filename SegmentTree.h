#define Tree
#ifndef SegmentTree
#include<iostream>
#define null nullptr
using namespace std;

class SegmentTree {
	int left;
	int right;
	long long sum;
	SegmentTree* sonl;
	SegmentTree* sonr;
	long long sign;

	bool useful() {
		return sign == 0;
	}

	bool leaf() {
		return sonl == null;
	}

public:
	static int arr[100004];
	static SegmentTree king;

	void print() {
		cout << sum << " " << left << " " << right << " " << sign << endl;
		if (sonl != null) {
			sonl->print();
		}
		if (sonr != null) {
			sonr->print();
		}
	}

public:

	long long construct(int left, int right) {
		this->left = left;
		this->right = right;
		sign = 0;
		if (right != left) {
			int mid = (left + right) / 2;
			sonl = new SegmentTree;
			sum = sonl->construct(left, mid);
			sonr = new SegmentTree;
			sum += sonr->construct(mid + 1, right);
		} else {
			sonl = sonr = null;
			sum = arr[left];
		}
		return sum;
	}

	long long compute() {
		if (leaf()) {
			sum += sign;
			sign = 0;
			return sum;
		} else {
			sonl->sign += this->sign;
			sonr->sign += this->sign;
			sign = 0;
			sum = sonl->compute() + sonr->compute();
			return sum;
		}
	}

	void mark(int start, int end, long long add) {
		if ((start == left) && (right == end)) {
			sign += add;
		} else if (end <= sonl->right) {
			sum += (end - start + 1) * add;
			sonl->mark(start, end, add);
		} else if (start >= sonr->left) {
			sum += (end - start + 1) * add;
			sonr->mark(start, end, add);
		} else {
			sum += (end - start + 1) * add;
			if (sonl != null) {
				sonl->mark(start, sonl->right, add);
			}
			if (sonr != null) {
				sonr->mark(sonr->left, end, add);
			}
		}
	}

	void update() {
		sum += sign * (right - left + 1);
		if (!leaf()) {
			sonl->sign += sign;
			sonr->sign += sign;
		}
		sign = 0;
	}

	long long interval(int start, int end) {		//查询
		update();
		if ((start == left) && (right == end)) {
			return sum;
		} else if (end <= sonl->right) {
			return sonl->interval(start, end);
		} else if (start >= sonr->left) {
			return sonr->interval(start, end);
		} else {
			//return (leaf() ? sum : sonl->interval(start, sonl->right) + sonr->interval(sonr->left, end));
			return sonl->interval(start, sonl->right) + sonr->interval(sonr->left, end);
		}
	}

	~SegmentTree() {
		delete sonl;
		delete sonr;
	}
};
#endif
