template <typename T>
class Item
{
private:
  int id;
  T *data;
  Item *next;

public:
  Item(int id, T *data);
};