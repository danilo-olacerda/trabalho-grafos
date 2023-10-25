class Item
{
private:
  int id;
  void *data;
  Item *next;

public:
  Item(int id, void *data);
};