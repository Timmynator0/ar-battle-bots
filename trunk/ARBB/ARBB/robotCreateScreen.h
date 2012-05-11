
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
} CREATOR;

void createRCSBackground();
void initCreators();
void updateCreators(int selectedcreator, int selecteditem, bool accept);