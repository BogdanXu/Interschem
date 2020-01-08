#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;



void Canvas(int step, RenderWindow& window)
{
	if (step == 1)
	{
		Texture full;
		if (!full.loadFromFile("fundal_1.png"))
		{
			std::cout << "could not load from file";
		}

		Sprite bg1;
		bg1.setTexture(full);
		window.draw(bg1);
	}
}




void Start()
{
	Texture startt;
	if (!startt.loadFromFile("fundal_1.png"))
	{
		printf("nope");
	}

	Sprite startb;
	startb.setTexture(startt);
	startb.setTextureRect(IntRect(10, 10, 32, 32));

}

bool checkBounds(Sprite sprite, Vector2i mousep)
{
	if (mousep.x >= sprite.getPosition().x && mousep.x <= sprite.getPosition().x + sprite.getLocalBounds().width
		&& mousep.y >= sprite.getPosition().y && mousep.y <= sprite.getPosition().y + sprite.getLocalBounds().height)
	{
		return 1;
	}
	else
		return 0;
}

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Interschem");

	// run the program as long as the window is open


//---------------------------------------------------This starts the "start texture
	Texture startt, butt;
	if (!startt.loadFromFile("fundal_1.png"))
	{
		printf("nope");
	}
	if (!butt.loadFromFile("but.png"))
	{
		printf("nope");
	}
	Sprite startb;
	startb.setTexture(startt);
	startb.setTextureRect(IntRect(16, 61, 200, 80));
	//startb.setOrigin(100.f,40.f);


	Sprite butts;
	butts.setTexture(butt);





	int mx, my;
	//------------------------------------------------------This is where it ends
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
			{
				mx = event.mouseMove.x;
				my = event.mouseMove.y;


				//      std::cout<<"x: "<<mx<<endl;
				//     std::cout<<"y: "<<my<<endl;
			}

		}
		// clear the window with black color
		window.clear(sf::Color::Black);




		Canvas(1, window);
		//&&checkBounds(startb,Mouse::getPosition(window))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			startb.setPosition(mx, my);
			window.draw(butts);
		}
		window.draw(startb);

		// end the current frame
		window.display();
	}
	return 0;
}