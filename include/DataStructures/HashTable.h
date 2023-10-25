template <typename T>
class HashTable
{
private:
  T *array;
  int length;

public:
  HashTable(int length);
  ~HashTable();

  int getHash(int id);
};