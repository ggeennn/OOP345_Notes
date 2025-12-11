using namespace std;
template<typename T,typename validator>
class Pointer{
	T* ptr{};
	validator func;
public:
	Pointer(T* p=nullptr, validator f=validator()):ptr(p),func(move(f)){}
	~Pointer(){ delete ptr; }
	Pointer(const Pointer& other) = delete;
	Pointer& operator=(const Pointer& other) = delete;
	Pointer(Pointer&& other) noexcept :ptr(other.ptr),func(move(other.func)){
		other.ptr = nullptr;
	}
	Pointer& operator=(Pointer&& other) noexcept {
		if(this != &other){
			delete ptr;
			ptr = other.ptr;
			func = move(other.func);
			other.ptr = nullptr;
		}
		return *this;
	}
	void setter(T* p){
		delete ptr;
		ptr = p;
	}
	explic/* i */t operator bool() const { return ptr != nullptr && /* func(*ptr) */;}
	T& operator*(){ return *ptr; }
	T* operator->(){ return ptr; }
	const T& operator*() const { return *ptr; }
	const T* operator->() const { return ptr; }
};
auto positive = [](const int& i){ return i>0; };
using dataPtr = Pointer<int,decltype(positive)>;
class Chunck{
	const vector<dataPtr>& ptr;
	size_t m_begin;
	size_t m_end;
public:
	Chunck(const vector<dataPtr>& p,size_t b,size_t e):ptr(p),m_begin(b),m_end(e){}
	vector<int> operator()(){
		vector<int> valid;
		for(size_t i= m_begin;i < m_end;++i){
			if(static_cast<bool>(ptr[i])) valid.push_back(*ptr[i]);
		}
		return valid;
	}
};
vector<int> chunckProcess(const vector<dataPtr>& data){
	size_t numThread= thread::hardware_concurrency/* () */;
	if(numThread == 0) numThread = 1;
	size_t numData = data.size();
	size_t chunckSize = (numData+numThread-1)/numThread;
	vector<future<vector<int>>> futures;
	size_t begin = 0;
	for(size_t i=0;i<numThread;++i){
		size_t end = (i == numThread-1)? numData:(begin+chunckSize);// size_t end = min(numData,begin+chunckSize);
		/* if(begin<end) */futures.emplace_back(async(launch::async,Chunck(data,begin,end)));
		begin = end;
	}
	vector<int> valid;
	for(auto& fut: futures){
		vector<int> val=fut.get();
		for(const auto& v:val){
			valid.push_back(v);
		}
	}
	return valid;
}
void processFile(const vector<dataPtr>& data){
	ofstream file("data.bin",ios::binary);
	if(file){
		vector<dataPtr> validPtr;
		copy_if(execution::par,data.begin(),data.end(),back_inserter(validPtr),[](const dataPtr& p){ return static_cast<bool>(p);});
		for_each(execution::seq,validPtr.begin(),validPtr.end(),[&](const dataPtr& p){
			int i = *p;
			file.write(reinterpret_cast<const char*>(/* &i */),sizeof(i));
		});
	}
}