#pragma once

using namespace std;

template< typename T >
class List {
public:
	class Node {
	public:
		Node() : m_next(NULL) { }

		Node(const T& t) : m_t(t), m_next(NULL) { }

		T m_t; //значение ноды

		Node* m_next;
		Node* next() {
			return m_next;
		}
		~Node() {
			m_t.~T();
		}
	};
private:
	Node* m_head;

public:
		class Iterator {
		public:
			Iterator(Node* node) : m_node(node) { }

			bool operator==(const Iterator& other) const {
				if (this == &other) {
					return true;
				}
				return m_node == other.m_node;
			}

			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}
			Node* operator++(int) {
				m_node = m_node->next();
				return m_node;
			}
			bool s() {
				return m_node != NULL;
			}
			T operator*() {
				return m_node->m_t;
			}
			Node* cur() {
				return m_node;
			}
		private:
			Node* m_node;
	};

		List(): m_head(NULL) {};
		List(const List< T > &list);
	~List();

	void append(const T& t);
	void appendToTheEnd(const T& t);
	void removeHead();
	void remove(int position);
	void append(const T& t, int position);
	void show();

	Iterator begin() const;
	Iterator end() const;
};

template< typename T >
void List< T >::append(const T &t) {
	if (Node* node = new Node(t)) {
		node->m_next = m_head;
		m_head = node;
	}
	else {
		throw std::out_of_range("Data didn't get");
	}
}

template < typename T >
void List< T >::appendToTheEnd(const T &t) {
	if (m_head) {
	Iterator temp(m_head);
	while (temp.cur()->next()) {
		temp++;
	}
	Node* node = new Node(t);
	temp.cur()->m_next = node;
	}
	else {
	m_head = new Node(t);
	}

}

template< typename T >
void List< T >::removeHead() {
	if (m_head) {
		Node* newHead = m_head->m_next;
		delete m_head;
		m_head = newHead;
	}
	else {
		throw std::out_of_range("List is empty");
	}
}

template< typename T >
List< T >::~List() {
	while (m_head) {
		removeHead();
	}
}

template< typename T >
List< T >::List(const List< T > &list): m_head(NULL) {
	Iterator p(list.m_head);
	while (p.s()) {
		this->appendToTheEnd(*p);
		p++;
	}
	 
}

template< typename T >
typename List< T >::Iterator List< T >::begin() const {
	return Iterator(m_head);
}

template< typename T >
typename List< T >::Iterator List< T >::end() const {
	return Iterator(NULL);
}

template< typename T >
void List< T >::append(const T &T1, int position) {
	if (position > 0) {
			Iterator temp(m_head);
			for (int i = 0; i < position-1; i++) {
				temp++;
			};
			Node* as = new Node(T1);
			as->m_next = temp.cur()->next();
			temp.cur()->m_next = as;
	}
	else {
		if (position == 0) {
			append(T1);
		}
		else {
			throw std::out_of_range("position < 0");
		}
	}
}

template< typename T >
void List< T >::remove(int position) {
	Iterator temp(m_head);
	for (int i = 0; i < position - 1; i++) {
		temp++;
	}
	Iterator temp2(m_head);
	for (int i = 0; i < position+1; i++) {
		temp2++;
	}
	Node* node = new Node();
	node = temp.cur()->next();
	delete node;
	temp.cur()->m_next = temp2.cur();
}

template <typename T>
void List< T >::show() {
	if (m_head) {
		Iterator a(m_head);
		cout << "List values: " << endl;
		while (a.s()) {
			cout << *a << endl;
			a++;
		}
	}
	else {
		throw std::out_of_range("List is empty!");
	}
}

