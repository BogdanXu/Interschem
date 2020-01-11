/****************************************************************************************************************
Proiect Interschem

TO DO::/------------------
-
-
--------------------------/


Idee
Razvan:Ideea mea era sa punem butoanele pe stanga, si atunci cand le tragi sa le iei efectiv de acolo. apoi cand
dai release sa se creeze un nou buton in locul liber. 

Texturile erau pentru butoane si blocuri, alea cu margine sa fie butoane si alea fara sa fie blocurile, sa se faca 
albastre cand le selectezi; daca folosim ideea mea, atunci nu prea ar merge ca daca iei butonul ar trebui sa se schimbe
cand ii dai drumul la varianta de bloc... mi-am rezolvat propria problema;
Asadar:
+Tragi un buton din stanga
+Il pui pe main board
+Se creeaza un alt buton in stanga
+Textura blocului pe care tocmai l-ai pus se schimba la varianta de bloc
+Cu click stanga poti sa tragi linii


*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

#define MAXBUTOANE 30

Sprite Buton[24];//butoanele din stanga
Texture ButonTexture;


void Canvas_R(int state, RenderWindow& window)
{
	Texture full;

	if (state == 1)
	{

		if (!full.loadFromFile("Fundal.jpg"))
		{
			std::cout << "could not load from file";
		}
	}
	Sprite bg1;
	bg1.setTexture(full);
	window.draw(bg1);
}


void loadTextures_R()//incarca primele 6 butoane, le-ar putea incarca pe toate, dar mai bine sa fie o alta functie pt celelalte
{
	if (!ButonTexture.loadFromFile("Texturi.png"))
		cout << "Texturi couldn't be loaded";
	Vector2u textureSize = ButonTexture.getSize();
	textureSize.x = textureSize.x / 4 + 1;
	textureSize.y = textureSize.y / 6 + 1;

	int k = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			Buton[k].setTexture(ButonTexture);
			Buton[k].setTextureRect(IntRect(textureSize.x * j, textureSize.y * i, textureSize.x, textureSize.y));
			Buton[k].setPosition(textureSize.x * j + 10, (textureSize.y - 5) * i + 30);
			Buton[k].setScale(0.75, 0.75);
			k++;
		}
	}
}


struct butoanie
{
	char tip;


};

Vector2f getDist(Sprite but1, Sprite but2)
{
	int x1 = but1.getPosition().x;
	int y1 = but1.getPosition().y;
	int x2 = but2.getPosition().x;
	int y2 = but2.getPosition().y;
	Vector2f dist;

	//dist=sqrt( pow(x2 - x1,2) + pow((y2 - y1),2));
	dist.x = abs(x2 - x1);
	dist.y = abs(y2 - y1);
	return dist;
}

bool checkCollision_R(Sprite butonCurent,Vector2i mpos,Vector2i posin)
{
	for (int i = 0; i < 6; i++)
	{	if (getDist(butonCurent, Buton[i]).x<=150 && getDist(butonCurent, Buton[i]).y <= 73 && getDist(butonCurent, Buton[i]).x != 0 && getDist(butonCurent, Buton[i]).y != 0)
		{
		return true;
		}

	}
	return false;
}


int main()
{
	RenderWindow window(VideoMode(800, 600), "INTERSCHEM");

	//ButonTexture.loadFromFile("Texturi.png");//de asta nu e nevoie ca e deja in loadTextures, ma gandeam ca nu merge dar aparent da
	loadTextures_R();

	Vector2f offset(80.f, 30.f);

	//trasare sageti//
	sf::Vertex line[2];
	bool sageata[10] = { false };
	
	bool ismove[10] = { false };
	bool isIntersecting[MAXBUTOANE] = { false };
	bool isClicked = false;
	Vector2i posin[MAXBUTOANE];

	while (window.isOpen())
	{	Vector2i pos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:


				if (event.key.code == Mouse::Right)
				{
					isClicked = true;
					for (int i = 0; i < 6; i++)
						if (Buton[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							sageata[i] = true;
						}
				}
				else if (event.key.code == Mouse::Left)
				{
					isClicked = true;
					for (int i = 0; i < 6; i++)
						if (Buton[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							ismove[i] = true;
							isIntersecting[i] = false;

						}

				}
				break;
			case Event::MouseButtonReleased:
				for (int i = 0; i < 6; i++) {
					sageata[i] = false;//asta s-ar putea sa fie prea inceata si sa cauzeze probleme,
					ismove[i] = false;
					isIntersecting[i] = true;
					isClicked = false;

				}

				break;
			}
		}
			///draw///
			window.clear();

			bool isPressed = false;

			Canvas_R(1, window);
			if (!isClicked)
			{
				cout << "falsa" << endl;
				for (int i = 0; i < 6; i++)
				{
					posin[i].x = Buton[i].getPosition().x;
					posin[i].y = Buton[i].getPosition().y;
				}
			}
			else cout << "adevarata" << endl;

			cout << posin[0].x << endl;
			cout << posin[0].y << endl;

			
			for (int i = 0; i < 6; i++)
				window.draw(Buton[i]);
			///drag&drop///
			/*
			for (int i = 0; i < 6; i++)
				if (!isIntersecting[i]&&checkCollision_R(Buton[i], pos, posin[i]))
				{
					cout << "Se Intersecteaza cu";
					Buton[i].setPosition(posin[i].x,posin[i].y);
				}*/
			for (int i = 0; i < 6; i++)
			if (ismove[i] &&!checkCollision_R(Buton[i], pos, posin[i]))
			{		
					//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					//if (Buton[i].getGlobalBounds().contains(pos.x, pos.y)){
						//Buton[i].setOrigin(100.0f, 50.0f);
						Buton[i].setPosition((float)pos.x-offset.x, (float)pos.y-offset.y);
					//}

			}
			else

			for (int i = 0; i < 6; i++)
			{
				if (sageata[i])
				{
					line[0] = sf::Vertex(sf::Vector2f(Buton[i].getPosition().x + offset.x, Buton[i].getPosition().y + offset.y)),
						line[1] = sf::Vertex(sf::Vector2f((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y));///Mai am variabila pos, care face acelasi lucru, dar asa cred ca e mai explicit
					window.draw(line, 2, sf::Lines);
				}


			}
			
			window.display();
		
	}
	return 0;
}


/** cod care face aproape acelasi lucru, e cu drag& drop dar nu prea functioneaza cum trebuie, ar trebui sters tbh, poate mai e ceva pe aici *shrug*
void Canvas_R(int step,RenderWindow &window)
{
	if(step==1)
	{
		Texture full;
		if(!full.loadFromFile("Fundal.jpg"))
		{
			std::cout<<"could not load from file";
		}

		Sprite bg1;
		bg1.setTexture(full);
		window.draw(bg1);
	}
}

bool checkBounds_R(Sprite sprite,Vector2i mousep)
{
	if(mousep.x>=sprite.getPosition().x && mousep.x<=sprite.getPosition().x+sprite.getGlobalBounds().width
			&& mousep.y>=sprite.getPosition().y&&mousep.y<=sprite.getPosition().y+sprite.getGlobalBounds().height)
	{
		return 1;
	}
	else
		return 0;
}


///---------------------------------------------------------------------------
int size=24;
Sprite button[40];///butoane
Texture buttonTex;
Vector2i posin[10];

void StartButton_R()///initializeaza butoanele
{
	int k=0;

	sf::Vector2u texturesize=buttonTex.getSize();
	texturesize.x=texturesize.x/4+4;
	texturesize.y=texturesize.y/6+1;
for(int i=0;i<6;i++)
{
for(int j=0;j<1;j++)
{
	 button[k].setTextureRect( sf::IntRect(texturesize.x*j,texturesize.y*i,texturesize.x,texturesize.y));
	 button[k].setPosition(texturesize.x*j+10,texturesize.y*i+30);
	 posin[k].x=texturesize.x*j+10;
	 posin[k].y=texturesize.y*i+30;
	 k++;
}
}


}


int distanta(Vector2i playerPos,int enemyPosx,int enemyPosy)
{
float xDist = abs(playerPos.x - enemyPosx);
float yDist = abs(playerPos.y - enemyPosy);
float distance = sqrt(xDist*xDist + yDist*yDist);

return distance;
}

int main()
{
	/// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Interschem");

		buttonTex.loadFromFile("Texturi.png");

		Sprite startSp(buttonTex);


		Sprite stopSp(buttonTex);

		Sprite intrareSp(buttonTex);

		Sprite iesireSp(buttonTex);

		Sprite atribuireSp(buttonTex);

		Sprite conditieSp(buttonTex);

		for(int i=0;i<24;i++)
{
		button[i].setTexture(buttonTex);
		button[i].setScale(Vector2f(0.75f,0.75f));
}

		StartButton_R();
	int mousex;
	int mousey;



		bool isMoved[50]={false,false,false,false,false};
		float dx=0,dy=0;
		Vector2f offset(28.0f,28.0f);
	/// run the program as long as the window is open
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
		/// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			/// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			switch(event.type)
			{
				case Event::TextEntered:
					cout<<(char)event.text.unicode;
					break;
				case Event::MouseMoved:
					mousex=event.mouseMove.x;
					mousey=event.mouseMove.y;
					break;
					   case Event::MouseButtonPressed:
						if(event.key.code==Mouse::Left)
							for(int i=0;i<6;i++)
							if(button[i].getGlobalBounds().contains(pos.x,pos.y))
						{
							isMoved[i]=true;
							dx=pos.x - button[i].getPosition().x;
							dx=pos.y - button[i].getPosition().y;
						}
				break;
				case Event::MouseButtonReleased:
					if(event.key.code==Mouse::Left)
						for(int i=0;i<6;i++)isMoved[i]=false;
			}

		}
		// clear the window with black color
		for(int i=0;i<6;i++)if(isMoved[i])button[i].setPosition(pos.x-dx,pos.y-dy);
		window.clear();
		Canvas_R(1,window);

		for(int i=0;i<6;i++)window.draw(button[i]);
		if(isMoved==false)
		{
			for(int i=0;i<6;i++)
			if(distanta(posin[i],button[i].getPosition().x,button[i].getPosition().y)>30)
			{
			window.draw(button[i]);
			button[i].setPosition(posin[i].x,posin[i].y);
			}
		}
		window.display();
	}
	return 0;
}
*/
