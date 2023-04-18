//#include "List/List.h" //以List为基类派生出的
#include<iostream>
typedef int Rank; 
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; //列表节点位置
template <typename T> struct ListNode { //列表节点模板类（以双向链表形式实现）
// 成员
   T data; ListNodePosi<T> pred, succ; //数值、前驱、后继
// 构造函数
   ListNode() {} //针对header和trailer的构造
   ListNode ( T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL )
      : data( e ), pred( p ), succ( s ) {} //默认构造器
// 操作接口
   ListNodePosi<T> insertAsPred( T const& e ); //紧靠当前节点之前插入新节点
   ListNodePosi<T> insertAsSucc( T const& e ); //紧随当前节点之后插入新节点
};
template <typename T> class List { //列表模板类
 
 private:
    Rank _size; ListNodePosi<T> header, trailer; //规模、头哨兵、尾哨兵
 
 protected:
    void init(); //列表创建时的初始化
    Rank clear(); //清除所有节点
    void copyNodes( ListNodePosi<T>, Rank ); //复制列表中自位置p起的n项
    ListNodePosi<T> merge( ListNodePosi<T>, Rank, List<T>&, ListNodePosi<T>, Rank ); //归并
    void mergeSort( ListNodePosi<T>&, Rank ); //对从p开始连续的n个节点归并排序
    void selectionSort( ListNodePosi<T>, Rank ); //对从p开始连续的n个节点选择排序
    void insertionSort( ListNodePosi<T>, Rank ); //对从p开始连续的n个节点插入排序
    void radixSort( ListNodePosi<T>, Rank ); //对从p开始连续的n个节点基数排序
 
 public:
 // 构造函数
    List() { init(); } //默认
    List( List<T> const& L ); //整体复制列表L
    List( List<T> const& L, Rank r, Rank n ); //复制列表L中自第r项起的n项
    List( ListNodePosi<T> p, Rank n ); //复制列表中自位置p起的n项
    // 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
 // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    ListNodePosi<T> operator[]( Rank r ) const; //重载，支持循秩访问（效率低）
    ListNodePosi<T> first() const { return header->succ; } //首节点位置
    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置
    bool valid( ListNodePosi<T> p ) //判断位置p是否对外合法
    { return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
    ListNodePosi<T> find( T const& e ) const //无序列表查找
    { return find( e, _size, trailer ); }
    ListNodePosi<T> find( T const& e, Rank n, ListNodePosi<T> p ) const; //无序区间查找
    ListNodePosi<T> search( T const& e ) const //有序列表查找
    { return search( e, _size, trailer ); }
    ListNodePosi<T> search( T const& e, Rank n, ListNodePosi<T> p ) const; //有序区间查找
	template<T>int selectMinh( ListNodePosi<T> p, Rank n ){
		ListNodePosi<T> min = p; //最大者暂定为首节点p
		for ( ListNodePosi<T> cur = p; 1 < n; n-- ) //从首节点p出发，将后续节点逐一与max比较
			if ( (cur=cur->succ)->data < min->data ) //若当前元素不小于max，则
				min = cur; //更新最小元素位置记录
		return min->data; //返回最大节点位置		
	} //在p及其n-个后继中选出最大者
	template<T>void selectMinf( ListNodePosi<T> p, Rank n ){
		ListNodePosi<T> min = p; //最大者暂定为首节点p
		for ( ListNodePosi<T> cur = p; 1 < n; n-- ) //从首节点p出发，将后续节点逐一与max比较
			if ( (cur=cur->pred)->data < min->data ) //若当前元素不小于max，则
				min = cur; //更新最大元素位置记录
		return min->data; //返回最大节点位置		
	} //在p及其n-个后继中选出最大者
    ListNodePosi<T> selectMax() { return selectMax( header->succ, _size ); } //整体最大者
 // 可写访问接口
    ListNodePosi<T> insertAsFirst( T const& e ); //将e当作首节点插入
    ListNodePosi<T> insertAsLast( T const& e ); //将e当作末节点插入
    ListNodePosi<T> insert( ListNodePosi<T> p, T const& e ); //将e当作p的后继插入
    ListNodePosi<T> insert( T const& e, ListNodePosi<T> p ); //将e当作p的前驱插入
    T remove( ListNodePosi<T> p ); //删除合法位置p处的节点,返回被删除节点
    void merge( List<T>& L ) { merge( header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
    void sort( ListNodePosi<T>, Rank ); //列表区间排序
    void sort() { sort( first(), _size ); } //列表整体排序
    Rank deduplicate(); //无序去重
    Rank uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
 // 遍历
    void traverse( void ( * )( T& ) ); //依次实施visit操作（函数指针）
    template <typename VST> void traverse( VST& ); //依次实施visit操作（函数对象）
 }; //List
template <typename T> class Queue: public List<T> { //队列模板类
public: //原有接口一概沿用
   void enqueue( T const& e ) { this->insertAsLast( e ); } //入队：尾部插入
   T dequeue() { return this->remove( this->first() ); } //出队：首部删除
   T& front() { return this->first()->data; } //队首
};
