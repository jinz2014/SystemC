// file buffer.h
#define BUFFER_SIZE 10
template <class itemT>
class buffer{
public:
buffer(); // ����
virtual ~buffer() {}
itemT get(); // �ӻ���������ȡ������
bool put(itemT); // �����ݷ��뻺�����׶�
bool full(); // ��������
bool empty(); // ��������
private:
// ˽����δ����
};
