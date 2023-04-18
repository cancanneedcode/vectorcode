//#include "List/List.h" //��ListΪ������������
#include<iostream>
typedef int Rank; 
template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; //�б�ڵ�λ��
template <typename T> struct ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
// ��Ա
   T data; ListNodePosi<T> pred, succ; //��ֵ��ǰ�������
// ���캯��
   ListNode() {} //���header��trailer�Ĺ���
   ListNode ( T e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL )
      : data( e ), pred( p ), succ( s ) {} //Ĭ�Ϲ�����
// �����ӿ�
   ListNodePosi<T> insertAsPred( T const& e ); //������ǰ�ڵ�֮ǰ�����½ڵ�
   ListNodePosi<T> insertAsSucc( T const& e ); //���浱ǰ�ڵ�֮������½ڵ�
};
template <typename T> class List { //�б�ģ����
 
 private:
    Rank _size; ListNodePosi<T> header, trailer; //��ģ��ͷ�ڱ���β�ڱ�
 
 protected:
    void init(); //�б���ʱ�ĳ�ʼ��
    Rank clear(); //������нڵ�
    void copyNodes( ListNodePosi<T>, Rank ); //�����б�����λ��p���n��
    ListNodePosi<T> merge( ListNodePosi<T>, Rank, List<T>&, ListNodePosi<T>, Rank ); //�鲢
    void mergeSort( ListNodePosi<T>&, Rank ); //�Դ�p��ʼ������n���ڵ�鲢����
    void selectionSort( ListNodePosi<T>, Rank ); //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort( ListNodePosi<T>, Rank ); //�Դ�p��ʼ������n���ڵ��������
    void radixSort( ListNodePosi<T>, Rank ); //�Դ�p��ʼ������n���ڵ��������
 
 public:
 // ���캯��
    List() { init(); } //Ĭ��
    List( List<T> const& L ); //���帴���б�L
    List( List<T> const& L, Rank r, Rank n ); //�����б�L���Ե�r�����n��
    List( ListNodePosi<T> p, Rank n ); //�����б�����λ��p���n��
    // ��������
    ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
 // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�
    ListNodePosi<T> operator[]( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    ListNodePosi<T> first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi<T> last() const { return trailer->pred; } //ĩ�ڵ�λ��
    bool valid( ListNodePosi<T> p ) //�ж�λ��p�Ƿ����Ϸ�
    { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
    ListNodePosi<T> find( T const& e ) const //�����б����
    { return find( e, _size, trailer ); }
    ListNodePosi<T> find( T const& e, Rank n, ListNodePosi<T> p ) const; //�����������
    ListNodePosi<T> search( T const& e ) const //�����б����
    { return search( e, _size, trailer ); }
    ListNodePosi<T> search( T const& e, Rank n, ListNodePosi<T> p ) const; //�����������
	template<T>int selectMinh( ListNodePosi<T> p, Rank n ){
		ListNodePosi<T> min = p; //������ݶ�Ϊ�׽ڵ�p
		for ( ListNodePosi<T> cur = p; 1 < n; n-- ) //���׽ڵ�p�������������ڵ���һ��max�Ƚ�
			if ( (cur=cur->succ)->data < min->data ) //����ǰԪ�ز�С��max����
				min = cur; //������СԪ��λ�ü�¼
		return min->data; //�������ڵ�λ��		
	} //��p����n-�������ѡ�������
	template<T>void selectMinf( ListNodePosi<T> p, Rank n ){
		ListNodePosi<T> min = p; //������ݶ�Ϊ�׽ڵ�p
		for ( ListNodePosi<T> cur = p; 1 < n; n-- ) //���׽ڵ�p�������������ڵ���һ��max�Ƚ�
			if ( (cur=cur->pred)->data < min->data ) //����ǰԪ�ز�С��max����
				min = cur; //�������Ԫ��λ�ü�¼
		return min->data; //�������ڵ�λ��		
	} //��p����n-�������ѡ�������
    ListNodePosi<T> selectMax() { return selectMax( header->succ, _size ); } //���������
 // ��д���ʽӿ�
    ListNodePosi<T> insertAsFirst( T const& e ); //��e�����׽ڵ����
    ListNodePosi<T> insertAsLast( T const& e ); //��e����ĩ�ڵ����
    ListNodePosi<T> insert( ListNodePosi<T> p, T const& e ); //��e����p�ĺ�̲���
    ListNodePosi<T> insert( T const& e, ListNodePosi<T> p ); //��e����p��ǰ������
    T remove( ListNodePosi<T> p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    void merge( List<T>& L ) { merge( header->succ, _size, L, L.header->succ, L._size ); } //ȫ�б�鲢
    void sort( ListNodePosi<T>, Rank ); //�б���������
    void sort() { sort( first(), _size ); } //�б���������
    Rank deduplicate(); //����ȥ��
    Rank uniquify(); //����ȥ��
    void reverse(); //ǰ���ã�ϰ�⣩
 // ����
    void traverse( void ( * )( T& ) ); //����ʵʩvisit����������ָ�룩
    template <typename VST> void traverse( VST& ); //����ʵʩvisit��������������
 }; //List
template <typename T> class Queue: public List<T> { //����ģ����
public: //ԭ�нӿ�һ������
   void enqueue( T const& e ) { this->insertAsLast( e ); } //��ӣ�β������
   T dequeue() { return this->remove( this->first() ); } //���ӣ��ײ�ɾ��
   T& front() { return this->first()->data; } //����
};
