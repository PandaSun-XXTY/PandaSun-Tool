#ifndef Tree
#define BinaryTree
#include <iostream>
#include <string>
#define null nullptr
using namespace std;
typedef string String;

class Tree {
	protected:
		Tree* father;
		Tree* left;
		Tree* right;
		int num;
		int value;
		bool useNew = false;

	protected:
		virtual	bool check(int dad) {
			if (left != null) {
				this->left->father = this;
				this->left->check(dad);
			}
			if (right != null) {
				this->right->father = this;
				this->right->check(dad);
			}
			return true;
		}

		//已废弃
		/*virtual Tree operator=(const Tree& b) {
			this->father = b.father;
			if (father != null) {
				if (father->left == (&b)) {
					father->left = this;
				} else if (father->right == (&b)) {
					father->right = this;
				}
			}
			this->left = b.left;
			if (b.left != null) {
				b.left->father = this;
			}
			this->right = b.right;
			if (b.right != null) {
				b.right->father = this;
			}
			this->num = b.num;
			this->value = b.value;
			check();
			return (*this);
		}*/


	public:				//Tool

		//于数组中查找指定值，返回索引
		static int find(int* a, int length, int num) {
			for (int i = 0; i < length; i++) {
				if (a[i] == num) {
					return i;
				}
			}
			return -1;
		}

		//打印整个数组
		static void outArray(int* array, int length) {
			for (int i = 0; i < length; i++) {
				cout << char(array[i]) << " ";
			}
			cout << endl;
		}

	public:
		virtual Tree* getFather() {
			return father;
		};

		virtual void setValue() {
			this->value = this->num;
		}

		virtual void setFather(Tree* father, bool left) {
			this->father = father;
			if (left) {
				father->left = this;
			} else {
				father->right = this;
			}
		}

		virtual void setFather(Tree* father) {
			this->father = father;
			if (father != null) {
				father->setSon(this);
			}
		}

		virtual Tree* getLeft() {
			return left;
		};

		virtual void setLeft(Tree* left) {
			this->left = left;
			if (left != null) {
				this->left->father = this;
			}
		}

		virtual Tree* getRight() {
			return right;
		};

		virtual void setRight(Tree* right) {
			this->right = right;
			if (right != null) {
				this->right->father = this;
			}
		}

		virtual int getNum() {
			return num;
		};

		virtual void setNum(int num) {
			this->num = num;
		}

		virtual int getValue() {
			return value;
		};

		virtual void setValue(int value) {
			this->value = value;
		}

		virtual void setSon(Tree* son) {
			if ((left == son) || (right == son)) {
				return;
			} else if (left == null) {
				son->father = this;
				this->left = son;
			} else if (right == null) {
				son->father = this;
				this->right = son;
			} else {
				right->setFather(null);
				right = son;
			}
		}

	public:
		//待审核
		Tree(int num, int* front, int* mid, int length) {//利用前序遍历与中序遍历确定二叉树
			this->useNew = false;
			if (length == 1) {
				this->reset(Tree(num, front[0]));
				return;
			}
			//设置本根节点数据值
			this->value = front[0];
			//2、在中序中找到根的值所在的下标
			int root = find(mid, length, front[0]);
			//3、切出左子树的前序和中序
			if (root != 0) {
				int* leftFront = new int[root];
				int* leftMid = new int[root];
				for (int i = 0; i < root; i++) {
					leftFront[i] = front[i + 1];
					leftMid[i] = mid[i];
				}
				this->left = new Tree{num + 1, leftFront, leftMid, root};
				left->useNew = true;
				delete[] leftFront;
				delete[] leftMid;
			} else {
				left = null;
			}
			//4、切出右子树的前序和中序
			if (length - root - 1 != 0) {
				int* rightFront = new int[length - root - 1];
				int* rightMid = new int[length - root - 1];
				for (int i = 0; i < length - root - 1; i++) {
					rightFront[i] = front[root + 1 + i];
					rightMid[i] = mid[root + i + 1];
				}
				this->right = new Tree{num * 2 + 1, rightFront, rightMid, length - root - 1};
				right->useNew = true;
				delete[] rightFront;
				delete[] rightMid;
			} else {
				right = null;
			}
		}

		Tree() {
			this->useNew = false;
			father = left = right = null;
			num = -1;
		}

		Tree(int num) {
			this->useNew = false;
			father = left = right = null;
			this->num = num;
		}

		Tree(int num, int value) {
			this->useNew = false;
			father = left = right = null;
			this->num = num;
			this->value = value;
		}

		Tree(int num, Tree& father) {
			this->useNew = false;
			this->father = &father;
			left = right = null;
			this->num = num;
			father.setSon(this);
		}

		Tree(int num, Tree& father, int value) {
			this->useNew = false;
			this->father = &father;
			left = right = null;
			this->num = num;
			this->value = value;
			father.setSon(this);
		}

		Tree(int num, Tree& left, Tree& right) {
			this->useNew = false;
			father = null;
			this->left = &left;
			this->right = &right;
			this->num = num;
			left.father = right.father = this;
		}

		Tree(int num, Tree& left, Tree& right, int value) {
			this->useNew = false;
			father = null;
			this->left = &left;
			this->right = &right;
			this->num = num;
			this->value = value;
			left.father = right.father = this;
		}

		Tree(int num, Tree& father, Tree& left, Tree& right) {
			this->useNew = false;
			this->father = &father;
			this->left = &left;
			this->right = &right;
			this->num = num;
			left.father = right.father = this;
			father.setSon(this);
		}

		Tree(int num, Tree& father, Tree& left, Tree& right, int value) {
			this->useNew = false;
			this->father = &father;
			this->left = &left;
			this->right = &right;
			this->num = num;
			this->value = value;
			left.father = right.father = this;
			father.setSon(this);
		}

		~Tree() {
			if ((left != null) && (left->useNew)) {
				delete (this->left);
			}
			if ((right != null) && (right->useNew)) {
				delete (this->right);
			}
		}

	public:

		virtual String toString() {
			return to_string(value);
		}

	public:

		virtual Tree reset(Tree b) {
			this->father = b.father;
			if (father != null) {
				if (father->left == (&b)) {
					father->left = this;
				} else if (father->right == (&b)) {
					father->right = this;
				}
			}
			this->left = b.left;
			if (b.left != null) {
				b.left->father = this;
			}
			this->right = b.right;
			if (b.right != null) {
				b.right->father = this;
			}
			this->num = b.num;
			this->value = b.value;
			check();
			return (*this);
		}

		virtual bool check() {
			if (father != null) {
				father->check();
			} else {
				return check(1);
			}
			return true;
		}

		virtual bool leaf() {
			return (left == null) && (right == null);
		}

		virtual	void traverse(int type) {
			if (leaf()) {
				cout << toString();
				return;
			}
			switch (type) {
				case 1:
					//先序遍历
					cout << toString();
					if (left != null) {
						left->traverse(1);
					}
					if (right != null) {
						right->traverse(1);
					}
					break;
				case 2:
					//中序遍历
					if (left != null) {
						left->traverse(2);
					}
					cout << toString();
					if (right != null) {
						right->traverse(2);
					}
					break;
				case 3:
					//后序遍历
					if (left != null) {
						left->traverse(3);
					}
					if (right != null) {
						right->traverse(3);
					}
					cout << toString();
					break;
			}
		}

		virtual	void traverse() {
			traverse(1);
		}

		virtual int deep() {
			int l, r;
			l = r = 0;
			if (left != null) {
				l = left->deep();
			}
			if (right != null) {
				r = right->deep();
			}
			return 1 + max(l, r);
		}
};

#endif
