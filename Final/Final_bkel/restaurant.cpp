#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class Gojo;
class Sukuna;
class Huff;


class Gojo{
	class Tree_BST;
private:
	vector<Tree_BST> Table;
public:
	Gojo():Table(MAXSIZE + 1){}
	void insertTable(int result){
		int ID = result % MAXSIZE + 1;
		Table[ID].insert(result); 
	}
	void remove_KOKUSEN(){
		for(int i = 1; i < MAXSIZE + 1; i++) Table[i].remove();
 	}

	void print_LIMITLESS(int number){
		if(number <= 0 || number > MAXSIZE) return;
		Table[number].print();
	}
private:
	class Tree_BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		Tree_BST():root(nullptr){}
		~Tree_BST(){
			while(!queueTime.empty()){
				int temp = queueTime.front();		
				queueTime.pop(); 						
				root = remove_recursive(root ,temp);
			}
		}
		int size(){
			return queueTime.size();
		}
		Node* insert_recursive(Node* node, int result){
			if(node == nullptr){
				Node* newNode = new Node(result);
				return newNode;
			}
			if(result < node->result){
				node->left = insert_recursive(node->left, result);
			}
			else{
				node->right = insert_recursive(node->right, result);
			}
			return node;
		}
		void insert(int result){
			root = insert_recursive(root, result);
			queueTime.push(result);
		}
		Node* minValueNode(Node* node){
			Node* current = node;
			while(current->left != NULL){
				current = current->left;
			}
			return current;
		}
		Node* remove_recursive(Node* node,int result){	
			if(node == nullptr) return nullptr; 
			if(result < node->result){
				node->left = remove_recursive(node->left, result);
			}
			else if(result > node->result){
				node->right = remove_recursive(node->right, result);
			}
			else {
				if (node->left == nullptr){
					Node* temp = node->right;
					delete node;
					return temp;
				}
				else if (node->right == nullptr){
					Node* temp = node->left;
					delete node;
					return temp;
				}
				Node* temp = minValueNode(node->right);
				node->result = temp->result;
				node->right = remove_recursive(node->right, temp->result);
			}
			return node;
 		}
		int CountNode(Node* node){
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}
		unsigned long long permutationFormula(int x, int n) {
			vector<vector<unsigned long long>> pascalTriangle(n + 1, vector<unsigned long long>(x + 1, 0));
    
			for (unsigned long long i = 0; i <= n; ++i) {
				for (unsigned long long j = 0 && j <= x;  j <= i; ++j) {
					if (j == 0 || j == i) {
						pascalTriangle[i][j] = 1;
					} else {
						pascalTriangle[i][j] = (pascalTriangle[i - 1][j - 1] % MAXSIZE + pascalTriangle[i - 1][j] % MAXSIZE);
					}
				}
			}
			unsigned long long result = pascalTriangle[n][x] % MAXSIZE;
			return result;
		}
		unsigned long long DFS(Node* node)
		{
			// B1: nếu node là NULL, trả về 1
			if(node == NULL){
				// cout << "NULL" << endl;
				return 1;
			}

			// B2: tính số lượng node trong cây con bên trái và
			// 					 node trong cây con bên phải
			int sizeLeft = CountNode(node->left);
			int sizeRight = CountNode(node->right);
			// cout << "sizeLeft: " << sizeLeft << endl;
			// cout << "sizeRight: " << sizeRight << endl;

			// B3: tính số hoán vị cho cây con bên trái và cây con bên phải
			unsigned long long permutations = permutationFormula(sizeLeft + sizeRight, sizeLeft);

			// B4: gọi đệ quy cho cây con bên trái và cây con bên phải
			unsigned long long result = (permutations * DFS(node->left) * DFS(node->right)) % MAXSIZE;
			// cout << "permutations: " << permutations << endl;
			// cout << "result: " << result << endl;
			return result;
			//TODO TODO TODO  TODO TODO TODO  đệ quy
		}
		void remove(){
			if(queueTime.empty()) return;
			
			unsigned long long number = DFS(root) % MAXSIZE;
			
		
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 					
				root = remove_recursive(root ,temp);
				number --;
			}
		}
		void print_recursive(Node* node)
		{
			if(node != NULL){
				print_recursive(node->left);
				cout << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print(){print_recursive(root);}
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};

};

//* nhà hàng su cờ na
class Sukuna{
	class Node;
private:
	vector<Node* > Table;
	list<Node* > LRU; 
private:
	int getIndexNodeInLRU(Node* node){
		int index = 0;
		for(Node* n : LRU){
			if(n == node) return index;
			index++;
		}
		return -1;
	}
	bool isNodeInLRU(Node* node)
	{
		for (const auto& n : LRU) {
			if (n == node) {
				return true;
			}
		}
		return false;
	}
	void ReHeap_down(int index)
	{
		int l = 2 * index + 1;
		int r = 2 * index + 2;
		int sm = index;
		int TableSize = Table.size();

		if (l < TableSize && (Table[l]->size() < Table[sm]->size() || (Table[l]->size() == Table[sm]->size() && getIndexNodeInLRU(Table[l]) > getIndexNodeInLRU(Table[sm]))))
			sm = l;

		if (r < TableSize && (Table[r]->size() < Table[sm]->size() || (Table[r]->size() == Table[sm]->size() && getIndexNodeInLRU(Table[r]) > getIndexNodeInLRU(Table[sm]))))
			sm = r;

		if (sm != index) {
			swap(Table[index], Table[sm]);
			ReHeap_down(sm);
		}
	}
	void ReHeap_up(int index)
	{
		if (index <= 0) {
			return;
		}

		int parent = (index - 1) / 2;
		int TableSize = Table.size();
		if (index >= TableSize || parent >= TableSize) {
			return;
		}

		if (Table[index]->size() < Table[parent]->size() ||
			(Table[index]->size() == Table[parent]->size() &&
			getIndexNodeInLRU(Table[index]) > getIndexNodeInLRU(Table[parent])))
		{
			swap(Table[index], Table[parent]);
			ReHeap_up(parent);
		}
	}
	void moveTop(Node* node)
	{	
		//TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		auto it = find(LRU.begin(), LRU.end(), node);

		//TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
		if(it != LRU.end()) LRU.splice(LRU.begin(), LRU, it);
		else LRU.push_front(node);
	}
    void removeNode(Node* node)
	{
		//TODO: 
		auto it = find(LRU.begin(), LRU.end(), node);

		if(it != LRU.end()) LRU.erase(it);
	}
public:
	Sukuna(){}
	~Sukuna(){
		int TableSize = Table.size();
		for(int i = 0; i < TableSize; i++){
			delete Table[i];
			
		}
	}

	void insertTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem khu vưc đó có trong bàn hay chưa lưu vị trí heap vào index
		int index = -1;
		//TODO TODO TODO TODO TODO bước 1
		int TableSize = Table.size();
		for(int i = 0; i < TableSize; i++){
			if(Table[i]->ID == ID){
				index = i;
				break;
			}
		}

		//*bước 2: xem thử có khu này trong heap chưa để thêm vô 
		if(index == -1){
			Table.push_back(new Node(ID));
			index = Table.size() - 1;
			Table[index]->insert(result);
			this->moveTop(Table[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else 
		{
			Table[index]->insert(result);
			this->moveTop(Table[index]);
			this->ReHeap_down(index);
		}
	}
	void remove_KEITEIKEN(int number)
	{
		if(Table.size() <= 0) return;

		
		//* TẠO ra heap mới sao chép từ heap cũ
		vector<Node* > TableNew(Table.begin(), Table.end());
		queue<Node* > listDelete; //! danh sách các khu cần xóa
		for(int i = 0;  Table.size() && i < number; i++)
		{
			//* lấy ra phần tử đầu tiên trong heap
			Node* nodeDelete = Table[0];
			swap(Table[0], Table[Table.size() - 1]);
			Table.pop_back();
			this->ReHeap_down(0);


			//* đưa vào danh sách cần xóa
			listDelete.push(nodeDelete);
		}

		//* trả lại heap
		Table = TableNew;

		//* đuổi num khách hàng tại num khu vực
		while(listDelete.size()){
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			Node* nodeDelete = listDelete.front();
			listDelete.pop();

			nodeDelete->remove(number);

			//* tìm vị trí của nó trong heap
			int index = 0;
			while(Table[index] !=  nodeDelete) index++;

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if(nodeDelete->size() == 0)
			{
				swap(Table[index], Table[Table.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(Table[Table.size() - 1]);
				delete Table[Table.size() - 1];
				

				//! xóa trong heap nữa
				Table.pop_back();
			}
			this->ReHeap_down(index);
		}
 	
	
	}

	void print_pre_order(int index, int number)
	{	
		int TableSize = this->Table.size();
		if(index >= TableSize || number <= 0) return;
		this->Table[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number){print_pre_order(0, number);}
private:
	class Node{
	private:
		int ID;					
		list<int> head; 	
		friend class Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result){head.push_front(result);}
		void remove(int number)
		{
			while(number != 0 && !head.empty())
			{
				cout << head.back() << "-" <<ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it  << "\n";
			}
		}
	};
};



class Huff{
	class Node;
private:
	Node* root = nullptr;
public:
	~Huff(){clear(root);}
	void clear(Node* node)
	{
		if(node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

    //! Bước 1: Liệt kê tần suất xuất hiện của các kí tự và tạo freq_prev
	vector<pair<char, int>> calculateCharacterFrequency(const string& name) {
		map<char, int> charFrequency;
		
		// Đếm tần suất xuất hiện của các kí tự và theo thứ tự xuất hiện
		for (char c : name) {
			if (charFrequency.find(c) == charFrequency.end()) {
				charFrequency[c] = 1;
			} else {
				charFrequency[c]++;
			}
		}

		// Tạo freq_prev từ map theo thứ tự xuất hiện
		vector<pair<char, int>> freq_prev;
		for (char c : name) {
			if (charFrequency.find(c) != charFrequency.end()) {
				freq_prev.push_back({c, charFrequency[c]});
				charFrequency.erase(c);
			}
		}

		return freq_prev;
	}

	//! 2 hàm này dành cho bước 2
	// Hàm mã hóa Caesar
	char caesarCipher(char c, int shift) {
		if (isalpha(c)) {
			char base = isupper(c) ? 'A' : 'a';
			return (c - base + shift) % 26 + base;
		}
		return c;
	}

	// Hàm thực hiện bước 2 và lưu chuỗi đã mã hóa vào biến name và freq_prev
	void encodeCaesar(string& name, vector<pair<char, int>>& freq_prev) {
		string encodedName = name;  // Tạo một bản sao của chuỗi name để lưu chuỗi đã mã hóa

		for (char& c : name) {
			for (auto& entry : freq_prev) {
				if (entry.first == c) {
					c = caesarCipher(c, entry.second);
					break;  // Kết thúc vòng lặp khi tìm thấy kí tự trong freq_prev
				}
			}
		}

		// Mã hóa freq_prev
		for (auto& entry : freq_prev) {
			entry.first = caesarCipher(entry.first, entry.second);
		}

	}

	//! Bước 3: Cộng dồn freq_prev với các kí tự giống nhau sau khi mã hóa
	vector<pair<char, int>> accumulateFrequency(const vector<pair<char, int>>& freq_prev) {
		map<char, int> charFrequency;

		for (const auto& entry : freq_prev) {
			charFrequency[entry.first] += entry.second;
		}

		// Chuyển từ map sang vector
		vector<pair<char, int>> freq(charFrequency.begin(), charFrequency.end());

		return freq;
	}

	//! Bước 4: Sắp xếp chuỗi freq theo chiều giảm dần
	void sortFrequency(vector<pair<char, int>>& freq) {
		sort(freq.begin(), freq.end(), [](const auto& a, const auto& b) {
			if (a.second != b.second) {
				return a.second > b.second;  // Sắp xếp theo tần suất giảm dần
			} else {
				// Nếu tần suất bằng nhau, sắp xếp theo thứ tự kí tự (kiểm tra kí tự hoa lớn hơn kí tự thường)
				if (isupper(a.first) && !isupper(b.first)) {
					return true;  // Nếu khác loại (hoa/thường), kí tự hoa lớn hơn kí tự thường
				} else if (!isupper(a.first) && isupper(b.first)) {
					return false; // Nếu khác loại (hoa/thường), kí tự hoa lớn hơn kí tự thường
				} else {
					return a.first > b.first;  // Ngược lại, so sánh theo giá trị ASCII
				}
			}
		});
	}
	vector<pair<char, int>> string_Processing(string& name)
	{
		//* bước 1
		vector<pair<char, int>> freq_prev = calculateCharacterFrequency(name);;
		
		//! thêm
		if(freq_prev.size() < 3) return {};

		//* bước 2
		encodeCaesar(name, freq_prev);

		//* bước 3
		vector<pair<char, int>> freq = accumulateFrequency(freq_prev);

		//* bước 4
		sortFrequency(freq);

		return freq;
	}


	int height(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + max(height(node->left),height(node->right));
	}

	int getBalance(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return height(node->left) - height(node->right);
	}

	Node* rightRotate(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;
		x->right = y;
		y->left = T2;
		return x;
	}

	Node* leftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;
		y->left = x;
		x->right = T2;
		return y;
	}
	Node* balanceNode(Node* node, int& count) {
		if (node == nullptr) return node;
		int balance = getBalance(node);
		// Cân bằng cây
		if (balance > 1 && getBalance(node->left) >= 0) {
			count++;
			return rightRotate(node);
		}
		if (balance > 1 && getBalance(node->left) < 0) {
			node->left = leftRotate(node->left);
			count += 1;
			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node->right) <= 0) {
			count++;
			return leftRotate(node);
		}
		if (balance < -1 && getBalance(node->right) > 0) {
			node->right = rightRotate(node->right);
			count += 1;
			return leftRotate(node);
		}

		return node;
	}
	Node* balanceTree(Node* node, int count = 0)
	{
		if(node == nullptr  || count == 1) return node;
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}
	Node* buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node*> build;
		for(auto i : freq){
			build.push_back(new Node(i.second, i.first));
		}

		while(build.size() > 1)
		{
			int count = 0;
			Node* newNode = nullptr;

			//* lấy phần tử có weight nhỏ nhất đầu tiên <=> cuối vector và là node bên trái tiếp theo
			Node* temp1 = build.back();build.pop_back();
			//* lấy phần tử có weight nhỏ nhất thứ hai <=> cuối vector và là node bên phải tiếp theo
			Node* temp2 = build.back();build.pop_back();

			//* đưa phần tử mới vào có weight tổng 2 thăng trước
			newNode = new Node(temp1->weight + temp2->weight, '\0', temp1, temp2);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);


			//TODO: đưa node mới vào trong vector -> đảm bảo vector luôn giảm dần như ban đầu
			//^ chú ý nếu bằng nhau thì xem như node mới luôn lớn hơn các node bằng giá trị weight -> ý là xếp nó gần head hơn
			auto it = std::lower_bound(
				build.begin(), build.end(), newNode,
				[](const Node* a, const Node* b) { return a->weight > b->weight; });

			build.insert(it, newNode);
		}		
		return build[0];
	}
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		//TODO
		if (node == nullptr) {
			return;
		}

		// Nếu node là lá (không có con trái và con phải), lưu mã hóa cho kí tự
		if (node->left == nullptr && node->right == nullptr) {
			encoding[node->c] = s;
			return;
		}

		// Đệ quy cho node con trái với thêm '0' vào chuỗi mã hóa
		encodingHuffman_rec(encoding, node->left, s + '0');

		// Đệ quy cho node con phải với thêm '1' vào chuỗi mã hóa
		encodingHuffman_rec(encoding, node->right, s + '1');
	}
	int encodingHuffman(Node * root,string nameCaesar)
	{
		if(root->left == nullptr && root->right == nullptr) return 0;

		//* bước 1: lấy chuỗi kết quả của các kí tự đã mã hóa
		//* ví dụ cây 2('a', 'b') ta lưu encoding['a'] = '0' và encoding['b'] = '1'
		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);
		//* bước 2 lấy ra 10 kí tự nhị phân cuối sau khi mã hóa nameCaesar thành mã nhị phân lấy từ phải đên trái 
		//! VD : 00000000000000000001 -> kq: 10000000000
		//^ chú ý: đừng có mà giải mã hết nameCaesar -> giải mã khi nào đủ 10 kí tự nhị phân là dừng
		//TODO 
		string binary = "";



		for (char bit : nameCaesar)
		{
			binary = binary + encoding[bit];
		}
		reverse(binary.begin(), binary.end());
	
		binary = binary.substr(0, 10);
		
		// reverse(binary.begin(), binary.end());
		// Bổ sung các số 0 đầu chuỗi nếu cần
		// while (binary.length() < 10)
		// {
		//     binary = "0" + binary;
		// }

		//* bước 3 mã hóa binary sang thập phân -> này ez rồi
		int result = 0;
		//TODO 
		int power = 1;
		for (int i = binary.length() - 1; i >= 0; --i)
		{
			if (binary[i] == '1')
			{
				result += power;
			}

			power *= 2;
		}

		//* kiểm tra test thôi nếu bạn thầy mình bị sai
		// cout << "nameCaesar = " << nameCaesar << endl;
		// cout << "encoding : ";
		// for(int i = 0; i < encoding.size(); i++) 
		// {
		//     if(encoding[i] != "") cout << char(i) << "=" << encoding[i] << " - ";
		// }
		// cout << "\nbinary = " << binary << endl;
		// cout << "result = " << result << endl;
		//********************

		return result;
	}


	int encode(string name){

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq  = this->string_Processing(name);
		if(freq.size() == 0) return -1;


		this->clear(root);
		root = this->buildHuff(freq);
		if(root->left == nullptr && root->right == nullptr) return 0; 
		
		int result = this->encodingHuffman(root ,name);


		return result;
	}



	void print_recursive(Node* node){
		if(node == nullptr) return;
		print_recursive(node->left);
		if(node->c == '\0') cout << node->weight << "\n";
		else cout << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND(){print_recursive(root);}

private:
	class Node{
	public:
		int weight;
		char c;
		Node* left;
		Node* right;
		friend class Huff;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ):  weight(weight), c(c), left(left), right(right) {}
	};
};



class JJK_RESTAURANT_OPERATIONS
{
private:
	Huff New_customers_arrive;
	Gojo hash;
	Sukuna heap;
	
public:

	void LAPSE(string name)
	{

		int result = New_customers_arrive.encode(name);
		if(result == -1) return;

		if(result % 2 == 1) hash.insertTable(result);
		else heap.insertTable(result);
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){
		hash.remove_KOKUSEN();
	}
	void LIMITLESS(int num){
		hash.print_LIMITLESS(num);
	}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){
		heap.remove_KEITEIKEN(num);
	}
	void CLEAVE(int num){
		heap.print_LIMITLESS(num);
	}

	//* in ra Huff
	void HAND(){
		New_customers_arrive.print_HAND();
	}
};


void simulate(string filename)
{
	
	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str; ss >> MAXSIZE; //* nhập maxsize đầu tiên

	JJK_RESTAURANT_OPERATIONS* NOT_LIKE_CODE = new JJK_RESTAURANT_OPERATIONS();
	// //* xử lí file
	while (ss >> str)
	{
		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			NOT_LIKE_CODE->LAPSE(name);
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			NOT_LIKE_CODE->KOKUSEN();
		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->KEITEIKEN(num);
		}
		else if (str == "HAND") // HAND
		{
			NOT_LIKE_CODE->HAND();
		}		
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->LIMITLESS(num);
		}		
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			NOT_LIKE_CODE->CLEAVE(num);
		}				
	}
	delete NOT_LIKE_CODE;
}

