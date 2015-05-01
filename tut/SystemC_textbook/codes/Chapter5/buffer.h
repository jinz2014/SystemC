// file buffer.h
#define BUFFER_SIZE 10
template <class itemT>
class buffer{
public:
buffer(); // 构造
virtual ~buffer() {}
itemT get(); // 从缓冲区顶端取得数据
bool put(itemT); // 将数据放入缓冲区底端
bool full(); // 缓冲区满
bool empty(); // 缓冲区空
private:
// 私有区未给出
};
