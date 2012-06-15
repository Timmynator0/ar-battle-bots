#ifndef ROBOT
#define ROBOT
#include <vector>

using namespace std;

class ObjModel;

class Robot{
private :	
    int nummer;
	int speed;
	int weight;
	int damage;
	int items[6];
	float w1ani,w2ani,w3ani; //weapon animations
public :
	Robot();
	Robot(int Nummer, int Speed, int Weight,int Damage, int Items[6],vector< ObjModel*> modellen);
	void Draw(float x, float y, float z, float rotationY, bool animation1, bool animation2, bool animation3);
};

#endif ROBOT