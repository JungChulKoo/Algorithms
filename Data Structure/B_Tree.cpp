#include <iostream>
using namespace std;

/* 구현에 있어서 중요한 홀수 차 비트리의 규칙
1. 루트 노드가 리프가 아니라면 최소 두 개 이상의 자식을 가져야 한다.
2. 루트 노드를 제외한 모든 노드는 적어도 (d + 1)/2 개의 자식을 가지고 있어야 한다. (단, d는 이 트리의 차수)
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
// 생성자
b_tree_node::b_tree_node(int _d, bool _leaf) {
	d = _d;
	leaf = _leaf;

	keys = new int[d];
	child = new b_tree_node *[d + 1];
	
	n = 0;
}
// 순회
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
// 검색
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

/* split_child()가 호출될 때는 해당 노드의 자식 y의 키 값이 꽉 차있다는 것을 가정한다
결과적으로 이 함수가 호출되고 나서는 자식 y의 오른쪽부터의 m - 1개의 키, 그리고 m개의 자식이 복사되며,
노드의 idx번째 자식이 y이기 때문에 노드의 idx + 1번째 자식이 새로운 노드 z가 된다.
그리고 마지막으로 y의 m번째 키를 노드의 idx + 1번째 키로 올리고 프로시져는 종료된다. */

void b_tree_node::split_child(int idx, b_tree_node* y) { 
	int j;
	int m = (d + 1) / 2; // 키 들의 중간 값은 d / 2의 올림 수

	b_tree_node* z = new b_tree_node(y->d, y->leaf); // y의 차수와 leaf 상태를 그대로 유지하는
	z->n = m - 1; // 키 m - 1 개를 저장할 새로운 노드 z를 만든다

	for (j = 0; j < m - 1; j++)
		z->keys[j] = y->keys[j + m]; // 자식 y의 오른쪽 m - 1개의 키들은 z의 왼쪽 키 공간부터 저장된다
	
	if (!y->leaf) { // 만약 y가 리프가 아니라면
		for (j = 0; j < m; j++) // 자식 y의 오른쪽 m개의 자식들은
			z->child[j] = y->child[j + m]; // z의 왼쪽 자식 공간부터 저장되고
	}

	y->n = m - 1; // 옮겨진 자식들을 제외하고 y의 키의 갯수는 m - 1개, 자식의 갯수는 m개가 된다.

	for (j = n; j >= idx + 1; j--)
		child[j + 1] = child[j]; // 이 노드의 idx + 1번째부터 n번째에 있는 자식들은 한 칸씩 뒤로 옮겨지고

	child[idx + 1] = z; // 이 노드의 idx + 1번째 자식은 z가 된다

	for (j = n - 1; j >= idx; j--)
		keys[j + 1] = keys[j]; // 본 노드의 idx 부터 n - 1번째에 있는 키들은 한 칸씩 뒤로 옮겨지고

	keys[idx] = y->keys[m - 1]; // y의 m번째 키를 본 노드의 idx번째 키로 올린다
	n++; // 키의 갯수를 increment 한다
}

/* 노드 차원의 삽입 연산 */
void b_tree_node::insert_node(int v) { 
	int i = n - 1;

	if (leaf) { // 이 노드가 리프라면 단순히 이 노드에 키를 삽입한다
		while (i >= 0 && keys[i] > v) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = v;
		n++; 
	} 

	else { // 리프가 아니라면
		while (i >= 0 && keys[i] > v)
			i--; // 키 값이 있어야 할 자식의 인덱스를 검색하고

		if (child[i + 1]->n == d) { // 키 값이 있어야 할 자식의 키가 꽉찼다면
			split_child(i + 1, child[i + 1]); // 이 자식 노드를 분할하고

			if (keys[i + 1] < v) // 분할된 자식 노드에 대해 비교 연산을 한 번 수행
				i++; 
		}

		child[i + 1]->insert_node(v); // 이 노드의 자식 차원에서 삽입 연산이 재귀로 이루어진다
	}
}

// 키의 인덱스 반환
int b_tree_node::index_of_key(int v) {
	int idx = 0;
	
	while (idx < n && keys[idx] < v)
		idx++;
	return idx;

}

// 노드 차원에서 제거 연산
void b_tree_node::remove_node(int v) {
	int idx = index_of_key(v);
	int m = (d + 1) / 2;
	if (idx < n && keys[idx] == v) { // 찾고자 하는 값이 노드의 키 값중 존재할 때
		if (leaf)
			remove_from_leaf(idx); // 리프라면 리프에서 제거
		else
			remove_from_stem(idx); // 줄기라면 줄기에서 제거
	}

	else { // 찾고자 하는 값이 노드의 키 값 중에서 존재하지 않을 때
		if (leaf)
			return; // 노드가 리프일 땐 단순 종료

		if (child[idx]->n < m) // idx번째 자식이 규칙 2를 만족하지 않는다면 
			fill(idx); // idx번째 자식을 채운다

		if (idx > n) // idx가 n + 1일 경우
			child[idx - 1]->remove_node(v); // n번째 child 차원에서 삭제 연산
		else // idx가 n 이하일 경우
			child[idx]->remove_node(v);	// idx번째 child 차원에서 삭제 연산
	}
	return;
}


void b_tree_node::remove_from_leaf(int idx) {
	for (int i = idx + 1; i < n; i++)
		keys[i - 1] = keys[i]; // 키 이동
	
	n--; // 키 갯수 감소
	return;
}

void b_tree_node::remove_from_stem(int idx) {
	int m = (d + 1) / 2; // 중간 값
	int v = keys[idx]; 
	if (child[idx]->n >= m) { // idx번째 자식이 규칙 2를 만족한다면
		int pred = get_pred(idx); // idx번째 자식으로부터 전 원소를 얻는다
		keys[idx] = pred; // idx번째 키는 전 원소가 되고
		child[idx]->remove_node(pred); // 전 원소를 지운다
	}

	else if (child[idx + 1]->n >= m) { // idx + 1번째 자식이 규칙 2를 만족한다면
		int succ = get_succ(idx); // idx번째 원소의 후 원소를 찾는다
		keys[idx] = succ; // idx번째 키는 후 원소가 되고
		child[idx + 1]->remove_node(succ); // 후 원소를 지운다
	}

	else { // idx번째 자식과 idx + 1번째 자식이 모두 규칙 2를 만족하지 못하면
		merge(idx); // 이 둘을 병합하고
		child[idx]->remove_node(v); // idx번째 자식에서 v를 제거한다
	}

	return;
}
// 직전 원소 가져오기
int b_tree_node::get_pred(int idx) { 
	b_tree_node* pred = child[idx];

	while (!pred->leaf)
		pred = pred->child[pred->n];
	return pred->keys[pred->n - 1];
}

// 직후 원소 가져오기
int b_tree_node::get_succ(int idx) {
	b_tree_node* succ = child[idx + 1];

	while (!succ->leaf)
		succ = succ->child[0];

	return succ->keys[0];
}

/* 이 함수가 호출될 때는 이 노드의 idx번째 자식이 규칙 2를 만족하지 못할 때이다 
케이스에 따라 원소를 빌려 채우거나 병합한다 */
void b_tree_node::fill(int idx) { 
	int m = (d + 1) / 2;
	if (idx != 0 && child[idx - 1]->n >= m) // 만약 주어진 인덱스의 자식이 첫번째 자식이 아니고 그 앞의 자식이 규칙 2를 만족한다면
		borrow_from_prev(idx); // 그 앞 자식으로부터 키를 하나 가져온다
	else if (idx != n && child[idx + 1]->n >= m) // 만약 주어진 인덱스의 노드가 마지막 자식이 아니고 그 뒤 자식이 규칙 2를 만족한다면
		borrow_from_succ(idx); // 그 뒤 자식으로부터 키를 하나 가져온다
	else { // 이 외의 케이스는 두 개의 자식이 병합 대상이 된다. 
		if (idx != n) // idx번째 자식이 마지막 자식이 아닐 경우
			merge(idx); // idx번째 자식을 idx + 1번째 자식과 합병한다
		else
			merge(idx - 1); // idx번째 자식이 마지막 자식일 경우는 idx - 1번째 자식과 idx번째 자식을 병합한다
	}

	return;
}

/* idx번째 자식이 idx - 1번째 자식으로부터 키를 가져온다.
결과적으로 이 프로시져는 이 노드의 바로 앞에 있는 키, 즉 이 노드의 idx - 1번째 키를 자신의 첫번째 키로 옮기며
idx - 1번째 자식의 마지막 키를 이 노드의 idx - 1번째 키로 옮기게 된다. */
void b_tree_node::borrow_from_prev(int idx) {
	b_tree_node* s = child[idx - 1]; // 키를 잃을 idx - 1번째 자식
	b_tree_node* c = child[idx]; // 키를 얻을 idx번째 자식

	for (int i = c->n - 1; i >= 0; i--)
		c->keys[i + 1] = c->keys[i]; //  n - 1번째부터 0번째까지에 있던 키들을 오른쪽으로 한 칸씩 옮긴다 

	if (!c->leaf) { // idx번째 child가 리프가 아니라면
		for (int i = c->n; i >= 0; i--)
			c->child[i + 1] = c->child[i]; // idx번째 자식의 자식들을 오른쪽으로 한 칸씩 옮긴다
	}

	c->keys[0] = keys[idx - 1]; // idx번째 자식의 첫번째 키는 이 노드의 idx - 1번째 키가 된다

	if (!c->leaf) // idx번째 자식이 리프가 아니라면
		c->child[0] = s->child[s->n]; // idx번째 자식의 첫번째 자식은 idx번째 child의 마지막 child가 된다

	keys[idx - 1] = s->keys[s->n - 1]; // 이 노드의 idx - 1번째 키는 idx - 1번째 child의 마지막 키가 된다

	c->n++;// idx번째 자식의 키 갯수 increment
	s->n--; // idx - 1번째 자식의 키 갯수 decrement
	return;
}
// idx번째 자식이 idx + 1번째 자식으로부터 키를 가져온다. 위 함수와 동작 방식은 동일
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

// idx번째 child와 idx + 1번째 child를 병합한다

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

void B_tree::insert(int v) { // 트리 차원의 삽입 연산
	if (root == NULL) {
		root = new b_tree_node(d, true);
		root->keys[0] = v;
		root->n = 1; // 트리가 비어있을 때는 새로운 노드를 만들어 삽입
	}

	else {
		if (root->n == d) { // 루트의 키 꽉 차있을때
			b_tree_node* new_root = new b_tree_node(d, false); // 루트가 될 새로운 노드를 만든다
			new_root->child[0] = root; // 원래의 루트를 새로운 루트의 첫번째 자식으로 삼고
			new_root->split_child(0, root); // root를 분할하여 새로운 노드 또한 자식으로 삼는다
			// 따라서 규칙 1 만족
			int i = 0; 
			if (new_root->keys[0] < v) // 분할되어서 키를 하나, 자식을 두 개 가지고 있으므로 비교 연산을 한 번만 수행한다
				i++;

			new_root->child[i]->insert_node(v); // i번째 자식 차원에서 삽입을 수행한다
			root = new_root; // 새로운 노드가 루트
		}

		else
			root->insert_node(v); // 루트가 꽉 차있지 않을 때는 root 차원에서 삽입한다.
	}
}

void B_tree::remove(int v) {
	if (root == NULL) // 루트가 비어있다면
		return; // 단순 종료
	else {
		root->remove_node(v); // 비어있지 않으면 루트 노드 차원에서 삭제 

		if (root->n == 0) { // 루트의 키가 0개면
			b_tree_node* removed = root; // 규칙에 의해 루트가 삭제할 노드로 지정된다

			if (root->leaf) // 루트가 리프이면
				root = NULL; // 루트를 삭제하고
			else
				root = root->child[0]; // 아니면 루트의 첫번째 자식을 루트로 지정한다

			delete removed; // 루트를 삭제한다
		}
	}

	return;
}
