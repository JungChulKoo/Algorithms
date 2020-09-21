#include <iostream>
using namespace std;

/* ������ �־ �߿��� Ȧ�� �� ��Ʈ���� ��Ģ
1. ��Ʈ ��尡 ������ �ƴ϶�� �ּ� �� �� �̻��� �ڽ��� ������ �Ѵ�.
2. ��Ʈ ��带 ������ ��� ���� ��� (d + 1)/2 ���� �ڽ��� ������ �־�� �Ѵ�. (��, d�� �� Ʈ���� ����)
*/


typedef struct b_tree_node {

	int* keys;
	int d, n;
	b_tree_node** child;
	bool leaf;

public:
	b_tree_node(int _d, bool _leaf);
	void traverse();
	b_tree_node* search(int key);
	void split_child(int idx, b_tree_node* y);
	void insert_node(int v);
	int index_of_key(int v);
	void remove_node(int v);
	void remove_from_leaf(int idx);
	void remove_from_stem(int idx);
	int get_pred(int idx);
	int get_succ(int idx);
	void fill(int idx);
	void borrow_from_prev(int idx);
	void borrow_from_succ(int idx);
	void merge(int idx);


	friend class B_tree;

}b_tree_node;

class B_tree {
	
	b_tree_node* root;
	int d;

public:
	B_tree(int _d) {
		root = NULL;
		d = _d;
	}

	void traverse() {
		if (root != NULL)
			root->traverse();
	}

	b_tree_node* search(int v) {
		if (root == NULL)
			return NULL;
		else
			return root->search(v);
	}

	void insert(int v);
	void remove(int v);
};
// ������
b_tree_node::b_tree_node(int _d, bool _leaf) {
	d = _d;
	leaf = _leaf;

	keys = new int[d];
	child = new b_tree_node *[d + 1];
	
	n = 0;
}
// ��ȸ
void b_tree_node::traverse()
{
	int i;
	for (i = 0; i < n; i++) {
		if (!leaf)
			child[i]->traverse();
		cout << " " << keys[i];
	}

	if (!leaf)
		child[i]->traverse();
}
// �˻�
b_tree_node* b_tree_node::search(int v) {
	int i = 0;

	while (i < n && v > keys[i])
		i++;

	if (keys[i] == v)
		return this;
	if (leaf)
		return NULL;
	else
		return child[i]	->search(v);
}

/* split_child()�� ȣ��� ���� �ش� ����� �ڽ� y�� Ű ���� �� ���ִٴ� ���� �����Ѵ�
��������� �� �Լ��� ȣ��ǰ� ������ �ڽ� y�� �����ʺ����� m - 1���� Ű, �׸��� m���� �ڽ��� ����Ǹ�,
����� idx��° �ڽ��� y�̱� ������ ����� idx + 1��° �ڽ��� ���ο� ��� z�� �ȴ�.
�׸��� ���������� y�� m��° Ű�� ����� idx + 1��° Ű�� �ø��� ���ν����� ����ȴ�. */

void b_tree_node::split_child(int idx, b_tree_node* y) { 
	int j;
	int m = (d + 1) / 2; // Ű ���� �߰� ���� d / 2�� �ø� ��

	b_tree_node* z = new b_tree_node(y->d, y->leaf); // y�� ������ leaf ���¸� �״�� �����ϴ�
	z->n = m - 1; // Ű m - 1 ���� ������ ���ο� ��� z�� �����

	for (j = 0; j < m - 1; j++)
		z->keys[j] = y->keys[j + m]; // �ڽ� y�� ������ m - 1���� Ű���� z�� ���� Ű �������� ����ȴ�
	
	if (!y->leaf) { // ���� y�� ������ �ƴ϶��
		for (j = 0; j < m; j++) // �ڽ� y�� ������ m���� �ڽĵ���
			z->child[j] = y->child[j + m]; // z�� ���� �ڽ� �������� ����ǰ�
	}

	y->n = m - 1; // �Ű��� �ڽĵ��� �����ϰ� y�� Ű�� ������ m - 1��, �ڽ��� ������ m���� �ȴ�.

	for (j = n; j >= idx + 1; j--)
		child[j + 1] = child[j]; // �� ����� idx + 1��°���� n��°�� �ִ� �ڽĵ��� �� ĭ�� �ڷ� �Ű�����

	child[idx + 1] = z; // �� ����� idx + 1��° �ڽ��� z�� �ȴ�

	for (j = n - 1; j >= idx; j--)
		keys[j + 1] = keys[j]; // �� ����� idx ���� n - 1��°�� �ִ� Ű���� �� ĭ�� �ڷ� �Ű�����

	keys[idx] = y->keys[m - 1]; // y�� m��° Ű�� �� ����� idx��° Ű�� �ø���
	n++; // Ű�� ������ increment �Ѵ�
}

/* ��� ������ ���� ���� */
void b_tree_node::insert_node(int v) { 
	int i = n - 1;

	if (leaf) { // �� ��尡 ������� �ܼ��� �� ��忡 Ű�� �����Ѵ�
		while (i >= 0 && keys[i] > v) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = v;
		n++; 
	} 

	else { // ������ �ƴ϶��
		while (i >= 0 && keys[i] > v)
			i--; // Ű ���� �־�� �� �ڽ��� �ε����� �˻��ϰ�

		if (child[i + 1]->n == d) { // Ű ���� �־�� �� �ڽ��� Ű�� ��á�ٸ�
			split_child(i + 1, child[i + 1]); // �� �ڽ� ��带 �����ϰ�

			if (keys[i + 1] < v) // ���ҵ� �ڽ� ��忡 ���� �� ������ �� �� ����
				i++; 
		}

		child[i + 1]->insert_node(v); // �� ����� �ڽ� �������� ���� ������ ��ͷ� �̷������
	}
}

// Ű�� �ε��� ��ȯ
int b_tree_node::index_of_key(int v) {
	int idx = 0;
	
	while (idx < n && keys[idx] < v)
		idx++;
	return idx;

}

// ��� �������� ���� ����
void b_tree_node::remove_node(int v) {
	int idx = index_of_key(v);
	int m = (d + 1) / 2;
	if (idx < n && keys[idx] == v) { // ã���� �ϴ� ���� ����� Ű ���� ������ ��
		if (leaf)
			remove_from_leaf(idx); // ������� �������� ����
		else
			remove_from_stem(idx); // �ٱ��� �ٱ⿡�� ����
	}

	else { // ã���� �ϴ� ���� ����� Ű �� �߿��� �������� ���� ��
		if (leaf)
			return; // ��尡 ������ �� �ܼ� ����

		if (child[idx]->n < m) // idx��° �ڽ��� ��Ģ 2�� �������� �ʴ´ٸ� 
			fill(idx); // idx��° �ڽ��� ä���

		if (idx > n) // idx�� n + 1�� ���
			child[idx - 1]->remove_node(v); // n��° child �������� ���� ����
		else // idx�� n ������ ���
			child[idx]->remove_node(v);	// idx��° child �������� ���� ����
	}
	return;
}


void b_tree_node::remove_from_leaf(int idx) {
	for (int i = idx + 1; i < n; i++)
		keys[i - 1] = keys[i]; // Ű �̵�
	
	n--; // Ű ���� ����
	return;
}

void b_tree_node::remove_from_stem(int idx) {
	int m = (d + 1) / 2; // �߰� ��
	int v = keys[idx]; 
	if (child[idx]->n >= m) { // idx��° �ڽ��� ��Ģ 2�� �����Ѵٸ�
		int pred = get_pred(idx); // idx��° �ڽ����κ��� �� ���Ҹ� ��´�
		keys[idx] = pred; // idx��° Ű�� �� ���Ұ� �ǰ�
		child[idx]->remove_node(pred); // �� ���Ҹ� �����
	}

	else if (child[idx + 1]->n >= m) { // idx + 1��° �ڽ��� ��Ģ 2�� �����Ѵٸ�
		int succ = get_succ(idx); // idx��° ������ �� ���Ҹ� ã�´�
		keys[idx] = succ; // idx��° Ű�� �� ���Ұ� �ǰ�
		child[idx + 1]->remove_node(succ); // �� ���Ҹ� �����
	}

	else { // idx��° �ڽİ� idx + 1��° �ڽ��� ��� ��Ģ 2�� �������� ���ϸ�
		merge(idx); // �� ���� �����ϰ�
		child[idx]->remove_node(v); // idx��° �ڽĿ��� v�� �����Ѵ�
	}

	return;
}
// ���� ���� ��������
int b_tree_node::get_pred(int idx) { 
	b_tree_node* pred = child[idx];

	while (!pred->leaf)
		pred = pred->child[pred->n];
	return pred->keys[pred->n - 1];
}

// ���� ���� ��������
int b_tree_node::get_succ(int idx) {
	b_tree_node* succ = child[idx + 1];

	while (!succ->leaf)
		succ = succ->child[0];

	return succ->keys[0];
}

/* �� �Լ��� ȣ��� ���� �� ����� idx��° �ڽ��� ��Ģ 2�� �������� ���� ���̴� 
���̽��� ���� ���Ҹ� ���� ä��ų� �����Ѵ� */
void b_tree_node::fill(int idx) { 
	int m = (d + 1) / 2;
	if (idx != 0 && child[idx - 1]->n >= m) // ���� �־��� �ε����� �ڽ��� ù��° �ڽ��� �ƴϰ� �� ���� �ڽ��� ��Ģ 2�� �����Ѵٸ�
		borrow_from_prev(idx); // �� �� �ڽ����κ��� Ű�� �ϳ� �����´�
	else if (idx != n && child[idx + 1]->n >= m) // ���� �־��� �ε����� ��尡 ������ �ڽ��� �ƴϰ� �� �� �ڽ��� ��Ģ 2�� �����Ѵٸ�
		borrow_from_succ(idx); // �� �� �ڽ����κ��� Ű�� �ϳ� �����´�
	else { // �� ���� ���̽��� �� ���� �ڽ��� ���� ����� �ȴ�. 
		if (idx != n) // idx��° �ڽ��� ������ �ڽ��� �ƴ� ���
			merge(idx); // idx��° �ڽ��� idx + 1��° �ڽİ� �պ��Ѵ�
		else
			merge(idx - 1); // idx��° �ڽ��� ������ �ڽ��� ���� idx - 1��° �ڽİ� idx��° �ڽ��� �����Ѵ�
	}

	return;
}

/* idx��° �ڽ��� idx - 1��° �ڽ����κ��� Ű�� �����´�.
��������� �� ���ν����� �� ����� �ٷ� �տ� �ִ� Ű, �� �� ����� idx - 1��° Ű�� �ڽ��� ù��° Ű�� �ű��
idx - 1��° �ڽ��� ������ Ű�� �� ����� idx - 1��° Ű�� �ű�� �ȴ�. */
void b_tree_node::borrow_from_prev(int idx) {
	b_tree_node* s = child[idx - 1]; // Ű�� ���� idx - 1��° �ڽ�
	b_tree_node* c = child[idx]; // Ű�� ���� idx��° �ڽ�

	for (int i = c->n - 1; i >= 0; i--)
		c->keys[i + 1] = c->keys[i]; //  n - 1��°���� 0��°������ �ִ� Ű���� ���������� �� ĭ�� �ű�� 

	if (!c->leaf) { // idx��° child�� ������ �ƴ϶��
		for (int i = c->n; i >= 0; i--)
			c->child[i + 1] = c->child[i]; // idx��° �ڽ��� �ڽĵ��� ���������� �� ĭ�� �ű��
	}

	c->keys[0] = keys[idx - 1]; // idx��° �ڽ��� ù��° Ű�� �� ����� idx - 1��° Ű�� �ȴ�

	if (!c->leaf) // idx��° �ڽ��� ������ �ƴ϶��
		c->child[0] = s->child[s->n]; // idx��° �ڽ��� ù��° �ڽ��� idx��° child�� ������ child�� �ȴ�

	keys[idx - 1] = s->keys[s->n - 1]; // �� ����� idx - 1��° Ű�� idx - 1��° child�� ������ Ű�� �ȴ�

	c->n++;// idx��° �ڽ��� Ű ���� increment
	s->n--; // idx - 1��° �ڽ��� Ű ���� decrement
	return;
}
// idx��° �ڽ��� idx + 1��° �ڽ����κ��� Ű�� �����´�. �� �Լ��� ���� ����� ����
void b_tree_node::borrow_from_succ(int idx) {
	b_tree_node* c = child[idx]; 
	b_tree_node* s = child[idx + 1]; 

	c->keys[c->n] = keys[idx]; 

	if (!c->leaf)
		c->child[c->n + 1] = s->child[0];

	keys[idx] = s->keys[0];

	for (int i = 1; i < s->n; i++)
		s->keys[i - 1] = s->keys[i];
	
	if (!s->leaf) {
		for (int i = 1; i <= s->n; i++)
			s->child[i - 1] = s->child[i];
	}

	c->n++;
	s->n--;
	return;
}

// idx��° child�� idx + 1��° child�� �����Ѵ�

void b_tree_node::merge(int idx) {
	int m = (d + 1) / 2;
	b_tree_node* c = child[idx];
	b_tree_node* s = child[idx + 1];

	c->keys[m - 1] = keys[idx];

	for (int i = 0; i < s->n; i++)
		c->keys[i + m] = s->keys[i];

	if (!c->leaf) {
		for (int i = 0; i <= s->n; i++)
			c->child[i + m] = s->child[i];
	}

	for (int i = idx + 1; i < n; i++)
		keys[i - 1] = keys[i];

	for (int i = idx + 2; i <= n; i++)
		child[i - 1] = child[i];

	c->n += s->n + 1;
	n--;

	delete(s);
	return;
}

void B_tree::insert(int v) { // Ʈ�� ������ ���� ����
	if (root == NULL) {
		root = new b_tree_node(d, true);
		root->keys[0] = v;
		root->n = 1; // Ʈ���� ������� ���� ���ο� ��带 ����� ����
	}

	else {
		if (root->n == d) { // ��Ʈ�� Ű �� ��������
			b_tree_node* new_root = new b_tree_node(d, false); // ��Ʈ�� �� ���ο� ��带 �����
			new_root->child[0] = root; // ������ ��Ʈ�� ���ο� ��Ʈ�� ù��° �ڽ����� ���
			new_root->split_child(0, root); // root�� �����Ͽ� ���ο� ��� ���� �ڽ����� ��´�
			// ���� ��Ģ 1 ����
			int i = 0; 
			if (new_root->keys[0] < v) // ���ҵǾ Ű�� �ϳ�, �ڽ��� �� �� ������ �����Ƿ� �� ������ �� ���� �����Ѵ�
				i++;

			new_root->child[i]->insert_node(v); // i��° �ڽ� �������� ������ �����Ѵ�
			root = new_root; // ���ο� ��尡 ��Ʈ
		}

		else
			root->insert_node(v); // ��Ʈ�� �� ������ ���� ���� root �������� �����Ѵ�.
	}
}

void B_tree::remove(int v) {
	if (root == NULL) // ��Ʈ�� ����ִٸ�
		return; // �ܼ� ����
	else {
		root->remove_node(v); // ������� ������ ��Ʈ ��� �������� ���� 

		if (root->n == 0) { // ��Ʈ�� Ű�� 0����
			b_tree_node* removed = root; // ��Ģ�� ���� ��Ʈ�� ������ ���� �����ȴ�

			if (root->leaf) // ��Ʈ�� �����̸�
				root = NULL; // ��Ʈ�� �����ϰ�
			else
				root = root->child[0]; // �ƴϸ� ��Ʈ�� ù��° �ڽ��� ��Ʈ�� �����Ѵ�

			delete removed; // ��Ʈ�� �����Ѵ�
		}
	}

	return;
}
