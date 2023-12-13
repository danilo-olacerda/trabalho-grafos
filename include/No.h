#ifndef NO_H
#define NO_H

using namespace std;

class No
{
private:
    int indice;
    float coordX;
    float coordY;
    int demanda;

public:
    No(int i, float x, float y);
    No(int tam);
    ~No();

    int getindice();
    float getcoordX();
    float getcoordY();
    int getdemanda();

    void setcoordX();
    void setcoordY();
    void setdemanda();


};

#endif // No_H