#include "ObjModel.h"

#include "loadTGA.h"
#include "BramsPrimitives.h"
#include "ObjModel.h"
#include "Robot.h"

typedef struct
{
    int nummer;
	int speed;
	int weight;
	int damage;
	int createstage;
	float infobordHeight;
	bool rotateLU;
	bool rotateLB;
	bool rotateRB;
	bool rotateRU;
	int stageItems[6];
} CREATOR;

int createRCSBackground();
void initCreators(vector<ObjModel*> modellen);
void updateCreators(int selectedcreator, int selecteditem, bool accept);
void intToString(int place);
Robot* getRobots(int i);