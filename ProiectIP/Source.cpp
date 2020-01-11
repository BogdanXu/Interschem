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

Sprite Buton[24];//butoanele din stanga
Texture ButonTexture;

int k = 0;
bool ismove[100] = { false };

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

void create_button(int lin)//incarca butonul de pe linia lin, coloana 3
{
	if (!ButonTexture.loadFromFile("Texturi.png"))
		cout << "Texturi couldn't be loaded";
	Vector2u textureSize = ButonTexture.getSize();
	textureSize.x = textureSize.x / 4 + 3;
	textureSize.y = textureSize.y / 6;
	Buton[k].setTexture(ButonTexture);
	Buton[k].setTextureRect(IntRect(textureSize.x * 2+11, textureSize.y * lin, textureSize.x-13, textureSize.y));
	Buton[k].setPosition(textureSize.x * 2 - 225, (textureSize.y - 5) * lin + 30);
	Buton[k].setScale(0.75, 0.75);
	k++;
	

}

struct butoanie
{
	char tip;


};


void drag_r()
{
}


int main()
{
	RenderWindow window(VideoMode(800, 600), "INTERSCHEM");

	//ButonTexture.loadFromFile("Texturi.png");//de asta nu e nevoie ca e deja in loadTextures, ma gandeam ca nu merge dar aparent da
	loadTextures_R();

	Vector2f offset(80.f, 30.f);
	//trasare sageti//
	sf::Vertex line[2];
	bool sageata[100] = { false };
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
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
					for (int i = 6; i < k; i++) //toti vectorii merg de la 6, cei de spawn (0-5) nu trebuie nici sa se miste, nici sa traga linie, deci nu ii luam in considerare in for
						if (Buton[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							sageata[i] = true;
						}
				}
				else if (event.key.code == Mouse::Left)
				{
					for(int i=0;i<6;i++) //daca dai click pe cele din meniu
						if (Buton[i].getGlobalBounds().contains(pos.x, pos.y))
							create_button(i); //se spawneaza butonul cu nr i in dreapta lui
					for (int i = 6; i < k; i++)
						if (Buton[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							ismove[i] = true;
						}
				}
				break;
			case Event::MouseButtonReleased:
				for (int i = 6; i < k; i++) { 
					sageata[i] = false;//asta s-ar putea sa fie prea inceata si sa cauzeze probleme,
					ismove[i] = false;
				}
				break;
			}
		}
		///draw///
		window.clear();
		bool isPressed = false;

		Canvas_R(1, window);
		for (int i = 0; i < k; i++)
			window.draw(Buton[i]);

		///drag&drop///
		for (int i = 0; i < k; i++)
			if (ismove[i])
			{

				//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				//if (Buton[i].getGlobalBounds().contains(pos.x, pos.y)){
					//Buton[i].setOrigin(100.0f, 50.0f);
				Buton[i].setPosition((float)pos.x - offset.x, (float)pos.y - offset.y);
				//}


			}
		for (int i = 0; i < k; i++)
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
