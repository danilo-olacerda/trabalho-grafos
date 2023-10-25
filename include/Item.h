class Item
{
private:
  int id;
  void *data;
  Item *next;

public:
  Item();
  ~Item();
};