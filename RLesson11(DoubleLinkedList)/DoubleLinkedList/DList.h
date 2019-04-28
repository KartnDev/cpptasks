template <typename T>
class DList
{
public:
	DList();
	~DList();

	void push_back(T data); 
	void push_front(T data);
	void insert(T data, int index); 
	void pop_back();
	void pop_front();
	void remove_at(int index);
	void clear(); 
	int getsize() { return SIZE; }
	T& operator[](const int index);

private:
	void link_head_tail();


	template <typename T>
	class Node
	{
	public:
		Node* p_next;
		Node* p_prev;
		T data;

		//constractor of Node (uses defualts var)
		Node(T data = T(), Node* p_next = nullptr, Node* p_prev = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
			this->p_prev = p_prev;
		}
	};

	int SIZE;
	Node<T>* head;
	Node<T>* tail;

};
