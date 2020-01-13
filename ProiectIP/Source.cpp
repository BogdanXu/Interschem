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


Vector2f offset(80.f, 30.f);
int k = 0;
int l = 0;
bool ismove[100] = { false };
Sprite Start_Parcurgere;
Texture LoaderTexture;
bool a[50][50] = { 0 };

struct buttons_structure
{
	char tip;
	Sprite Buton;
	sf::Text text;
	sf::String text_content;
	int valoare;
	bool ok=0;
}B[50];
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
	if (!LoaderTexture.loadFromFile("Texturi.png"))
		cout << "Texturi couldn't be loaded";
	Vector2u textureSize = LoaderTexture.getSize();
	textureSize.x = textureSize.x / 4 + 1;
	textureSize.y = textureSize.y / 6 + 1;

	Start_Parcurgere.setTexture(LoaderTexture);
	Start_Parcurgere.setTextureRect(IntRect(textureSize.x * 3, textureSize.y * 0, textureSize.x, textureSize.y));
	Start_Parcurgere.setPosition(637.0f, 65.0f);
	Start_Parcurgere.setScale(0.75, 0.75);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			B[k].Buton.setTexture(LoaderTexture);
			B[k].Buton.setTextureRect(IntRect(textureSize.x * j, textureSize.y * i, textureSize.x, textureSize.y));
			B[k].Buton.setPosition(textureSize.x * j + 10, (textureSize.y - 5) * i + 30);
			B[k].Buton.setScale(0.75, 0.75);
			k++;
		}
	}
}
void hoverTexture_R(int p,bool isHovering)
{	Vector2u textureSize = LoaderTexture.getSize();
	textureSize.x = textureSize.x / 4 + 1;
	textureSize.y = textureSize.y / 6 + 1;
			
	if(isHovering)
		B[p].Buton.setTextureRect(IntRect(textureSize.x * 1, textureSize.y * p, textureSize.x, textureSize.y));
	else
		B[p].Buton.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * p, textureSize.x, textureSize.y));
}

	sf::Font font;
void create_button(int lin)//incarca butonul de pe linia lin, coloana 3
{	
	if (!LoaderTexture.loadFromFile("Texturi.png"))
		cout << "Texturi couldn't be loaded";
	Vector2u textureSize = LoaderTexture.getSize();
	textureSize.x = textureSize.x / 4 + 3;
	textureSize.y = textureSize.y / 6;
	B[k].Buton.setTexture(LoaderTexture);
	B[k].Buton.setTextureRect(IntRect(textureSize.x * 2 + 11, textureSize.y * lin, textureSize.x - 13, textureSize.y));
	B[k].Buton.setPosition(textureSize.x * 2 - 225, (textureSize.y - 5) * lin + 30);
	B[k].Buton.setScale(0.75, 0.75);

	if (!font.loadFromFile("Arial.ttf"))
		cout << "font could not be loaded \n";
	B[k].text.setFont(font);
	B[k].text.setCharacterSize(30);
	if(lin>1)
	B[k].text.setString("<?>");
	B[k].text.setPosition(B[k].Buton.getPosition()+Vector2f(50.f,20.f));


	switch (lin)
	{
	case 0:
		B[k].tip = 's';
		break;			//start
	case 1:
		B[k].tip = 'f'; 
		break;			//stop
	case 2:
		B[k].tip = 'i'; 
		break;			//intrare
	case 3:
		B[k].tip = 'o'; 
		break;			//iesire
	case 4:
		B[k].tip = 'a'; 
		break;			//atribuire
	case 5:
		B[k].tip = 'c'; 
		break;			//conditie
	}
	k++;

}



bool checkmultiplehover(Sprite Button, Vector2i posi, int i)
{
	int nr = 0;
		if (Button.getGlobalBounds().contains(posi.x, posi.y))
			nr++;
		for (int j = 0; j < k && j != i; j++)
			if (B[j].Buton.getGlobalBounds().contains(posi.x, posi.y))
				nr++;
		if (nr > 1)
		{
			 return 0;
		}
	return 1;
}
int main()
{
	RenderWindow window(VideoMode(800, 600), "INTERSCHEM");

	//ButonTexture.loadFromFile("Texturi.png");//de asta nu e nevoie ca e deja in loadTextures, ma gandeam ca nu merge dar aparent da
	loadTextures_R();


	//trasare sageti//
	struct linii
	{
		sf::Vertex line[2];
	}L[50];
	bool sageata[100] = { false };
	bool link[100] = { false };
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
						if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y))
						{
							sageata[i] = true;
							B[i].ok = 1;
						}
				}
				else if (event.key.code == Mouse::Left)
				{
					for (int i = 0; i < 6; i++) //daca dai click pe cele din meniu
						if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y))
							create_button(i); //se spawneaza butonul cu nr i in dreapta lui
					for (int i = 6; i < k; i++)
						if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y) && checkmultiplehover(B[i].Buton, pos, i))
						{
							ismove[i] = true;
						}
					if (Start_Parcurgere.getGlobalBounds().contains(pos.x, pos.y))
					{
						if (k > 6)
						{
							for (int i = 6; i < k; i++)
							{
								a[k][i] = 0;
								a[i][k] = 0;
							}
							k--;
						}
					}
				}
				break;
			case Event::MouseButtonReleased:
				for (int i = 6; i < k; i++) {
					sageata[i] = false; //asta s-ar putea sa fie prea inceata si sa cauzeze probleme
					ismove[i] = false;
				}
				if(event.key.code==Mouse::Right)
				for (int i = 6; i < k; i++)
				{
					if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y) && checkmultiplehover(B[i].Buton,pos,i))
					{
						link[i] = true;
					}
				}
				break;
			case Event::TextEntered:
			{
				for (int i = 6; i < k; i++)
					if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y) && event.text.unicode < 128 && B[i].tip != 's' && B[i].tip != 'f')
					{
						{
							if (event.text.unicode == 8)
							{
								B[i].text.setString("<?>");
									B[i].text_content.erase(0, 10);
							}
							else
							{
								B[i].text_content += event.text.unicode;
									B[i].text.setString(B[i].text_content);

							}
						}

					}
			}
			break;
			case Event::MouseMoved:
				break;
			}
		}
		///draw///
		window.clear();
		bool isPressed = false;

		Canvas_R(1, window);

		for (int i = 0; i < 6; i++)
		{
			if (B[i].Buton.getGlobalBounds().contains(pos.x, pos.y))
				isPressed = true;
			else
				isPressed = false;
			hoverTexture_R(i, isPressed);
		}
		for (int i = 6; i < k; i++)
		{
			int nr = 1;
			if (B[i].ok == 1)
				for (int j = 6; j < k && j != i; j++)
				{
					if (B[j].ok == 1 && link[j] && a[j][i] != 1 && a[i][j] != 1)
					{
						a[j][i] = 1;
						cout << "legatura de la " << j << " la " << i << endl;
						l++;
						nr++;
						B[i].ok = 0;
						B[j].ok = 0;
					}
				}
			if (nr == 2)
			{
				for (int i = 6; i < k; i++)
					B[i].ok = 0;
			}
		}
		for(int i= 6; i<k; i++)
			for (int j = 6; j < k; j++)
			{
				if (a[i][j] == 1)
					L[l].line[0] = sf::Vertex(sf::Vector2f(B[i].Buton.getPosition().x + offset.x, B[i].Buton.getPosition().y + offset.y)),
					L[l].line[1] = sf::Vertex(sf::Vector2f(B[j].Buton.getPosition().x + offset.x, B[j].Buton.getPosition().y + offset.y));
			}
		for(int i=0; i<=l;i++)
			window.draw(L[i].line, 2, sf::Lines);
		for (int i = 0; i < k; i++)
			window.draw(B[i].Buton);
		window.draw(Start_Parcurgere);
		///drag&drop///
		for (int i = 0; i < k; i++)
			if (ismove[i])
			{

				//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				//if (Buton[i].getGlobalBounds().contains(pos.x, pos.y)){s
					//Buton[i].setOrigin(100.0f, 50.0f);
				B[i].Buton.setPosition((float)pos.x - offset.x, (float)pos.y - offset.y);
				//}


			}
		for (int i = 0; i < k; i++)
		{
			B[i].text.setPosition(B[i].Buton.getPosition() + Vector2f(50.f, 20.f));
			if (sageata[i])
			{
				/*line[0] = sf::Vertex(sf::Vector2f(B[i].Buton.getPosition().x + offset.x, B[i].Buton.getPosition().y + offset.y)),
					line[1] = sf::Vertex(sf::Vector2f((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y));*////Mai am variabila pos, care face acelasi lucru, dar asa cred ca e mai explicit

			}


		}
		for (int i = 5; i < k; i++)
			window.draw(B[i].text);
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
