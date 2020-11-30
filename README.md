# 数据结构第三次作业：哈夫曼编码
bupt 2019211504 王乾凱
## 功能介绍
无图形界面，主要 有两个功能，分别是文本压缩与关键词检索。
## 思路
### 文本压缩
通过文本读入后，将所有字符进行统计后排序，构造出哈夫曼树后进行编码。构造的过程为了节省时间复杂度，使用了优先队列维护了顺序。
### 关键词检索
本次作业关键字检索功能开发了两个功能：单词检索和多词检索。
单词检索采用了BM模式串匹配算法，是一种KMP的优化算法，其关键是好字串法则和坏字符法则。
多词检索采用了AC自动机进行检索，先输入若干个词，将其压缩为01序列后构造一个Trie，并在每个节点构造一个fail指针进行模式匹配的回溯，也是一种KMP算法的优化。
## 模块解析
### 1. H\_tree（哈夫曼编码部分）

#### 树节点
##### 定义：
```cpp
struct treenode{
    char ch;
    int weight{};
    treenode* lson{};
    treenode* rson{};
    treenode* par{};
    treenode* addr{};
    //构造函数
    treenode(){
        ch = 0;
        lson = nullptr;
        rson = nullptr;
    }
    treenode(char c) {
        ch = c;
        lson = nullptr;
        rson = nullptr;
    }
    //运算符重载，方便排序
    bool operator<(const treenode& a) const{
        if(weight == a.weight) return ch > a.ch;
        return weight > a.weight;
    }
};
```

#### 哈夫曼树
##### 定义：
```cpp
class h_tree{
private:
    int frequency[300]{};
    int n;
    treenode* root;
    treenode* body;
public:
    h_tree(){
        root = nullptr;
        body = nullptr;
        n = 0;
        memset(frequency, 0, sizeof(frequency));
    }

    int size() const{ return n; }
    treenode* find_root() { return root; }
    treenode* find_node(int i) { return body + i; }



    void build();
    //std::string decode(const std::string& s);
    void statistic(const std::string& s);
};
```
##### 主要函数解析
1. statistic函数（统计字符数量）
	```cpp
	void h_tree::statistic(const string& s){
		int t = 0;
		for(auto i : s){
	    	if(!frequency[i]) t++;
	    	frequency[i]++;
		}
		n = 255;
		body = (treenode*)malloc(sizeof(treenode) * (n + 1));
		for(int i = 1; i <= n; i++){
	    	(body + i) -> ch = (char)i;
	    	// (body + i) -> weight = frequency[i];
	    	(body + i) -> lson = nullptr;
	    	(body + i) -> rson = nullptr;
	    	(body + i) -> par = nullptr;
	    	(body + i) -> addr = (body + i);
	    	body[i].weight = frequency[i];
		}
	}
	```
	就是简单的统计函数，无需注释地方
2. . build函数（建树）
	```cpp
	void h_tree::build(){
		priority_queue<treenode> q;
		for(int i = 1; i <= n; i++){q.push(*(body + i));}
		while(true){
	    	treenode s1, s2;

	    	if(!q.empty()){
	        	s1 = q.top();
	        	q.pop();
	    	}
	    	if(!q.empty()){
	        	s2 = q.top();
	        	q.pop();
	    	} else{
	        	root = s1.addr;
	        	break;
	    	}
	    	//cout << (int)s1.ch << "  " << s1.weight << endl << (int)s2 . ch << "  " << s2.weight << endl << endl;
	    	auto* s0 = (treenode*)malloc(sizeof(treenode));
	    	s0 -> ch = 0;
	    	s0 -> lson = s1.addr;
	    	s0 -> rson = s2.addr;
	    	s0 -> lson -> par = s0;
	    	s0 -> rson -> par = s0;
	    	s0 -> weight = s1.weight + s2.weight;
	    	s0 -> addr = s0;
	    	q.push(*s0);
		}
	}
	```
	先离散处理每一个节点，然后将节点压入堆中进行排序，每次取出最小的两个，然后将两个函数合并后压入堆中，算法复杂度为O(n)
#### 哈夫曼码表
##### 定义：
```cpp
class h_code{
private:
    //std::unordered_map<char, std::string> dic;
public:
    std::unordered_map<char, std::string> dic;
    static void find(h_tree h, int s, std::string& aws);
    void build(h_tree h);
    std::string encode(std::string);
};
```
##### 主要函数解析
1. find函数（对哈夫曼树进行搜索以生成单个字符所对应的码）
	```cpp
	//#define pb push_back
	void h_code::find(h_tree h, int s, string& aws){
	    treenode* rec = h.find_node(s);
	    treenode* root = h.find_root();
	    while(rec != root){
	        treenode* p = rec -> par;
	        if(p -> lson == rec){
	            aws.pb('0');
	        } else {
	            aws.pb('1');
	        }
	        rec = p;
	    }
	}
	```
	（ps：生成的码是反向的）
2. Build函数（生成码表）
	```cpp
	void h_code::build(h_tree h){
		for(int i = 1; i <= h.size(); i++){
	    	std::string aws;
	    	find(h, i, aws);
	    	aws.reserve();
	    	dic[h.find_node(i) -> ch] = aws;
		}
	}
	```
	建树后对哈夫曼树进行处理以生成码表。
3. encode函数（对待编码字符串进行编码，返回码）
	```cpp
	std::string h_code::encode(const std::string& s){
		string aws;
		for(auto i : s){
	    	aws += dic[i];
		}
		return aws;
	}
	```
	无特殊算法。
### 2.  BM检索模块
#### BM
##### 定义：
```cpp
class BM{
private:
    int n;
    std::vector<int> bad_char;
    std::vector<int> good_char;
    std::vector<int> suffix;
public:
    void generate(std::string s);
    std::vector<int> search(std::string s, std::string t);
};
```
##### 主要函数解析
1. generate函数（用于生成迁移指针）
	```cpp
	void BM::generate(std::string s){
		n = s.size();
		for(int i = 0; i <= 255; i++) bad_char.pb(n);
		for(int i = 0; i < s.length(); i++){
	    	bad_char[s[i]] = n - i - 1;
		}
		suffix.resize(n);
		good_char.resize(n);
		suffix[n - 1] = n;
		for(int i = n - 2; i >= 0; i--){
	    	int q = i;
	    	while(q > 0 && s[q] == s[n - 1 - i + q]) q--;
	    	suffix[i] = i - q;
		}
		for(int i = 0; i < n; i++) good_char[i] = n;
		int j = 0;
		for(int i = n - 1; i >= 0; i--){
	    	if(suffix[i] == i + 1)
	        	for(; j < n - 1 - i; j++){
	            	if(good_char[j] == n) good_char[j] = n - 1 - i;
	        	}
		}
		for(int i = 0; i < n; i++) good_char[n - 1 - suffix[i]] = n - 1 - i;
	}
	```
	先生成字符串的前缀数组，方便构建好字串数组，然后分别统计坏字符和好字串数组
2.  Search函数（传入参数为主串）
	```cpp
	vector<int> BM::search(std::string s, std::string t) {
		int m = t.size();
		int j = 0, i;
		vector<int> ret;
		while(j <= m - n){
	    	for(i = n - 1; i >= 0 && s[i] == t[j + i]; i--);
	    	if(i < 0){
	        	ret.push_back(j);
	        	j += good_char[0];
	    	}
	    	else j += max(good_char[i], bad_char[t[i + j]] - n + 1 + i);
		}
		return ret;
	}
	```

### 3. AC自动机模块
#### AC automaton
##### 定义：
```cpp
// #define maxn 1000000
class AC{
private:
    int tot{}; // 计数器
    int tr[maxn][2]{}; // trie主体
    int fail[maxn]{}, e[maxn]{}, idx[maxn]{}; //失配指针，访问标记，串的编号
    std::string book[maxn]; //trie中串的索引。
    std::vector<int> dic[maxn]; //每个节点所对应的串的编号。
public:
    AC() = default;
    void insert(std::string w, int t);
    void build();
    std::vector<std::vector<int>> query(std::string t);

};
```
##### 主要函数解析
1. insert函数（插入字符串生成trie）
	```cpp
	void AC::insert(string w, int t){
	    book[t] = w;
	    int u = 0;
	    for(int i = 0; w[i]; i++){
	        if(!tr[u][w[i] - 'a']) tr[u][w[i] - 'a'] = ++tot;
	        u = tr[u][w[i] - 'a'];
	    }
	//    e[u]++;
	    idx[t] = u;
	    dic[u].push_back(t);
	}
	```
3. Build函数（生成失配指针）
	```cpp
	void AC::build(){
		queue<int> q;
		rep(i, 0, 25) if(tr[0][i]) q.push(tr[0][i]);
		while(!q.empty()){
	    	int u = q.front(); q.pop();
	    	rep(i, 0, 25){
	        	if(tr[u][i]){
	            	fail[tr[u][i]] = tr[fail[u]][i];
	            	q.push(tr[u][i]);
	        	} else{
	            	tr[u][i] = tr[fail[u]][i];
	        	}
	    	}
		}
	}
	```
4. query函数（进行字符串匹配）
	```cpp
	vector<vector<int>> AC::query(string t){
		int u = 0;
		vector<vector<int>> res(tot + 10);
		for(int i = 0; t[i]; i++){
	    	u = tr[u][t[i] - 'a'];
	    	for(int j = u; j && e[j] != -1; j = fail[j]){
	        	//res += e[j]; e[j] = -1;
	        	e[j] = -1;
	        	for(auto w : dic[j]) res[w].push_back(j); //记录答案
	    	}
		}
		return res; //答案为每个匹配串的尾节点
	}
	```
