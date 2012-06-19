#include "endScreen.h"

vector< ObjModel*> esmodellen;
vector<Robot*> esrobots;
vector<GLBatch> particles;
Robot *eerstePlaats = new Robot(), *tweedePlaats= new Robot(), *derdePlaats= new Robot();

GLuint estextures[esTEXTURE_COUNT];
const char *esTextureFiles[esTEXTURE_COUNT] =
{ "arena-muur.tga","APSfloor.tga","erepodium.tga" };
float flydistance = 0;

bool Les = false;

void initES(vector< ObjModel*> Esmodellen)
{
	esmodellen = Esmodellen;
	srand ( time(NULL) );
}
void setESRobots(Robot &r){
	esrobots.push_back(&r);
}
void shootparticles()
{
	flydistance = 40;
	float z, y;
		for(int i = 0; i< 500; i++){

			float x = i*rand()%75;
			if(i%2 == 0) x= -x;

			z = 10+rand()%40;
			y = -1+rand()%40;

			GLBatch b = GLBatch();
			b.Begin(GL_TRIANGLES,3,0);			
			glColor3i(((int)rand()%128+127),((int)rand()%128+127),((int)rand()%128+127)); glVertex3f(x,y+1,z+1);
			glColor3i(((int)rand()%128+127),((int)rand()%128+127),((int)rand()%128+127)); glVertex3f(x-1,y,z);
			glColor3i(((int)rand()%128+127),((int)rand()%128+127),((int)rand()%128+127)); glVertex3f(x+1,y,z-1);
			b.End();
			particles.push_back(b);
	}
}
void drawParticles()
{
	glPushMatrix();
	glTranslated(0,flydistance,0);
	for(int i = 0; i<particles.size();i++)
	{
		particles[i].Draw();
	}
	glPopMatrix();
}

void createESBackground(float width, float height){
	width /= 8;
	height /= 10;
	float depth = 70;
		// het laden van de texture voor de achtergrond
		glGenTextures(esTEXTURE_COUNT, estextures);
		for(int i= 0; i < esTEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, estextures[i]);
			LoadTGATexture(esTextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}
	glBindTexture(GL_TEXTURE_2D, estextures[0]);	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);		glVertex3f(-width,0,depth);		//1
			glTexCoord2f(0,1);		glVertex3f(-width,height,depth);		//2
			glTexCoord2f(1,1);		glVertex3f(width,height,depth);			//3
			glTexCoord2f(1,0);		glVertex3f(width,0,depth);			//4
		glEnd();	
	glBindTexture(GL_TEXTURE_2D, estextures[1]);	
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);		glVertex3f(-width,0,-20);		//1
			glTexCoord2f(0,0);		glVertex3f(-width,0,depth);		//2
			glTexCoord2f(1,0);		glVertex3f(width,0,depth);			//3
			glTexCoord2f(1,1);		glVertex3f(width,0,-20);			//4
		glEnd();	
	glBindTexture(GL_TEXTURE_2D, estextures[2]);	
		glBegin(GL_QUADS);		
			glTexCoord2f(0.7,0);		glVertex3f(-65,0,35);		//1
			glTexCoord2f(0.7,1);		glVertex3f(-65,10,35);		//2
			glTexCoord2f(1,1);		glVertex3f(-25,10,35);			//3
			glTexCoord2f(1,0);		glVertex3f(-25,0,35);			//4

			glTexCoord2f(0.3,0);		glVertex3f(-25,0,35);		//1
			glTexCoord2f(0.3,1);		glVertex3f(-25,30,35);		//2
			glTexCoord2f(0.7,1);		glVertex3f(25,30,35);			//3
			glTexCoord2f(0.7,0);		glVertex3f(25,0,35);			//4
			
			glTexCoord2f(0,0);		glVertex3f(25,0,35);		//1
			glTexCoord2f(0,1);		glVertex3f(25,20,35);		//2
			glTexCoord2f(0.3,1);		glVertex3f(65,20,35);			//3
			glTexCoord2f(0.3,0);		glVertex3f(65,0,35);			//4

			glTexCoord2f(0,0);		glVertex3f(-65,10,65);
			glTexCoord2f(0,0.1);	glVertex3f(-65,10,35);
			glTexCoord2f(0.1,0.1);	glVertex3f(-25,10,35);
			glTexCoord2f(0.1,0);	glVertex3f(-25,10,65);
			
			glTexCoord2f(0,0);		glVertex3f(-25,30,65);
			glTexCoord2f(0,0.1);	glVertex3f(-25,30,35);
			glTexCoord2f(0.1,0.1);	glVertex3f(25,30,35);
			glTexCoord2f(0.1,0);	glVertex3f(25,30,65);

			glTexCoord2f(0,0);		glVertex3f(25,20,65);
			glTexCoord2f(0,0.1);	glVertex3f(25,20,35);
			glTexCoord2f(0.1,0.1);	glVertex3f(65,20,35);
			glTexCoord2f(0.1,0);	glVertex3f(65,20,65);
		glEnd();

		for(int i = 0; i <esrobots.size(); i++){
			if(esrobots[i]->health > eerstePlaats->health) eerstePlaats = esrobots[i];
			else if(esrobots[i]->health > tweedePlaats->health) tweedePlaats = esrobots[i];
			else if(esrobots[i]->health > derdePlaats->health) derdePlaats = esrobots[i];
		}
		glPushMatrix();
		//glScaled(2,2,2);
		eerstePlaats->Draw(0, 30,50,90,false,false,false,true);
		tweedePlaats->Draw(45, 20,50,90,false,false,false,true);
		derdePlaats->Draw(-45, 10,50,90,false,false,false,true);
		glPopMatrix();

	//glDeleteTextures(GL_TEXTURE_2D,apstextures);
		glPushMatrix();
		glColor4f(1.0f, 1.0f, 0.0f,1.0f);
		glRasterPos3f(10,60,60);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(unsigned char*) "En de winnaar is : ");
		glPopMatrix();
		glColor4f(1.0f, 1.0f, 1.0f,1.0f);
		if(flydistance <= 0) shootparticles();
		else {
			flydistance -= 0.3;
			drawParticles();
			std::cout<<"fly : "<<flydistance<<std::endl;
		}
}