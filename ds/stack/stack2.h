#include"../vector/vector.h"
template<typename T> class Stack :public Vector<T> {
protected:
    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom(T const* A, Rank lo, Rank hi) //复制数组区间A[lo, hi) A已经是一个地址名称 
    {
        _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }
    void expand() //空间不足时扩容
    {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldelem = _elem; _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;
    }
    void shrink() //装填因子过小时压缩
    {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;  // 以25%为界限，
        T* oldelem = _elem; _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;

    }

    Rank maxItem(Rank lo, Rank hi) //选取最大元素
    {
        int max = _elem[0];
        for (int i = 1; i < _size; i++)
            if (_elem[i] > max) {
                max = _elem[i];
            }
        return max;
    }
public:
    // 构造函数
    Stack(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //容量为c、规模为s、所有元素初始为 v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c

    Stack(T const* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制 
    Stack(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间 
    Stack(Stack<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制  
    Stack(Stack<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间  
    // 析构函数
    ~Stack() { delete[] _elem; } //释放内部空间
    // 只读访问接口
    Rank size() const { return _size; } //规模  
    bool empty() const { return !_size; } //判空  

    // 可写访问接口
    T& operator[] (Rank r)
    {
        //重载下标操作符，可以类似于数组形式引用各元素
        return _elem[r];
    }
    //  const T& operator[] (Rank r) const; //仅限于做右值的重载版本
    Stack<T>& operator= (Stack<T> const& V) //重载赋值操作符，以便直接克隆向量
    {
        if (_elem)
            delete[]_elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }
    T remove(Rank r) //删除秩为r的元素
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank remove(Rank lo, Rank hi) //删除秩在区间[lo, hi)之内的元素
    {
        //考虑鲁棒性 
        if (lo<0 || hi>_size) { printf("越界\n"); return 0; }
        if (lo == hi) return 0;
        while (hi < _size) _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    Rank insert(Rank r, T const& e) //插入元素
    {
        // 考虑鲁棒性 
        if (r > _size) { printf("越界\n"); return -1; }
        expand();
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }
    // 遍历
    void traverse(void (*visit) (T&)) //遍历（使用函数指针，只读或局部性修改）
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
    template <typename VST> void traverse(VST& visit) //遍历（使用函数对象，可全局性修改）
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
    Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入
	void push(T const& e) { insert((*this).size(), e); }
	T pop() { return remove((*this).size() - 1); }
	T& top() { return (*this) [size() - 1]; }


};

