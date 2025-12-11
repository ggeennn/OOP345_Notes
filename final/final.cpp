//Q1
template<typename T, typename Validator>
class Pointer{
    T* m_ptr;
public:
    Validator m_valid;
    Pointer(T* ptr,Validator valid):m_ptr(ptr),m_valid(valid/*std::move(valid)*/){} //错误//加上默认构造参数(T* ptr = nullptr, Validator valid = Validator())
    ~Pointer() { delete m_ptr; }
    void set(T* ptr){
        delete m_ptr;
        m_ptr = ptr;
    }
    T& operator*(){ return *m_ptr; }
    T* operator->() { return m_ptr; }
    const T& operator*() const { return *m_ptr; }
    const T* operator->() const { return m_ptr; } 
    Pointer(Pointer&& ptr) noexcept {
        m_ptr = ptr.m_ptr;
        m_valid = ptr.m_valid;//std::move(ptr.m_valid)
        ptr.m_ptr = nullptr;
    }
    Pointer& operator=(Pointer&& ptr) noexcept {
        if(this != *ptr){ //错误// 应该是 &ptr！
            delete m_ptr;
            m_ptr = ptr.m_ptr;
            m_valid = ptr.m_valid;//std::move(ptr.m_valid)
            ptr.m_ptr = nullptr;
        }
        return *this;
    }
    Pointer(Pointer& ptr) = delete; //错误// 参数加 const Pointer& ptr ！
    Pointer& operator=(Pointer& ptr) = delete; //错误// 参数加 const Pointer& ptr ！

    bool operator(){ return m_ptr != nullptr && m_valid(m_ptr); } //错误// operator bool() const { return m_ptr != nullptr && m_valid(m_ptr); }
} //错误// 加；分号结尾类定义

//Q2
auto prof_valid = [](const int* ptr){ return *ptr>0; };
using dataPtr = Pointer<int,prof_valid>; //错误//类型为 decltype(prof_valid) 或者 struct prof_valid{ bool operator()(const int* ptr){ return *ptr>0; }};
class ChunkFilter{
    const std::vector<dataPtr>& container; //问题// 如何根据Q1创建vector smart pointers
    size_t m_begin;
    size_t m_end;
public:
    ChunkFilter(const std::vector<dataPtr>& ctr, size_t begin, size_t end):container(ctr),m_begin(begin),m_end(end){}
    std::vector<int> operator()(){
        std::vector<int> validData;
        for (size_t i = m_begin; i < m_end && i < container.size(); ++i) {
            if (container[i]) {
                validData.push_back(*container[i]);
            }
        }
        return validData;
    }
};

//Q3 假设含有数据 std::vector<dataPtr> allData
size_t numThreads = //错误// std::thread::hardware_concurrency();
//错误// if (numThreads == 0) numThreads = 1; //safety fallback
size_t numData = allData.size();
size_t chunkSize = (numData + numThreads -1)/numThreads;
std::vector<std::future<std::vector<int>>> futures;
size_t begin = 0 ;
for(size_t i = 0, i < numThreads, ++i ){ //错误// 用；分号隔开
    size_t end = (i == numThreads -1)?numData:(begin+chunkSize);
    ChunkFilter chunk(allData,begin,end);
    futures.push_back(std::async(std::launch::async,chunk));
    begin = end;
}
vector<int> allValid;
for(const auto& fut in futures){ //错误// 用：替代in//不能const,不能copy，因为.get()可能会改变 future 状态
    std::vector<int> valid = fut.get();
    for(const auto& data in valid){ //错误// 用：替代in
        allValid.push_back(data);
    }
}

//Q4 假设含有数据 std::vector<dataPtr> allData
std::vector<dataPtr> validPtr;
std::copy_if(std::execution::seq,allData.begin(),allData.end(),std::back_inserter(validPtr),[](const dataPtr ptr){ return static_cast<bool>(ptr);}); //错误// const dataPtr& ptr 必须按引用传递，禁止拷贝
std::ofstream file('out.bin',std::binary); //错误// "out.bin" 双引号 //std::ios::binary
std::mutex mtx;
std::for_each(std::execution::par,validPtr.begin(),validPtr.end(),[&](dataPtr ptr){ //错误//使用 const dataPtr& ptr
    int data = *ptr;
    std::lock_guard<std::mutex> lock(mtx);
    file.write(reinterpret_cast<const char>(&data),sizeof(data)); //错误//<const char*>
});



//=======================================================

