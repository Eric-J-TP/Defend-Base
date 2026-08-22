#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class AimingCross;

//--Classes--
class Map
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Map/textures/grass.png";
	int height = 800, width = 600;

	Map()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { height,width }));
	}
	void setScale(float scale)
	{
		sprite.scale({ scale,scale });
	}
};
class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Player/textures/base.png";
	int height = 10;
	int width = 10;
	sf::Vector2f position{ 400.f, 300.f};
	sf::Vector2f origin{ 5.f,5.f };
public:
	Player()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		//set the scope view to sprite
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { height,width }));
		//sets the position
		sprite.setPosition(position);
		//sets origin (the center)
		sprite.setOrigin(origin);
	}
	sf::Sprite getSprite()
	{
		return sprite;
	}
	void setScale(float scale)
	{
		sprite.scale({ scale,scale });
	}
	friend void shoot(Player& player, AimingCross& corss);

};
class AimingCross
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/AimingCross/textures/image.png";
	int height = 10, width = 10;
	sf::Vector2f position{ 100.f, 100.f };
	sf::Vector2f origin{ 5.f, 5.f };
	float stepSize = 5;
public:
	AimingCross()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		//set the scope view to sprite
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { height,width }));
		//sets the position
		sprite.setPosition(position);
		//sets origin (the center)
		sprite.setOrigin(origin);
	}
	sf::Sprite getSprite()
	{
		return sprite;
	}
	void setScale(float scale)
	{
		sprite.scale({ scale,scale });
	}
	//moving mechanics
	void move(sf::RenderWindow& window)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window); // Get mouse pixel position relative to window
		sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos); // Convert to world coordinates (handles custom views/cameras)

		sprite.setPosition(worldPos); // Set the shape's position to match the mouse
	}
	friend void shoot(Player& player, AimingCross& corss);
};
class Bullet
{
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "";
	int height = 10, width = 10;
	sf::Vector2f position{ 400.f, 300.f };
	sf::Vector2f origin{ 5.f, 5.f };
public:
	Bullet()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		//set the scope view to sprite
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { height,width }));
		//sets the position
		sprite.setPosition(position);
		//sets origin (the center)
		sprite.setOrigin(origin);
	}
	sf::Sprite getSprite()
	{
		return sprite;
	}
	void setScale(float scale)
	{
		sprite.scale({ scale,scale });
	}
};
//-----------

//--Functions--
void startMainMusic(sf::Music& music)
{
	music.openFromFile("sound/main_sound.mp3");
	music.play();
}
sf::Vector2f normalizeVector(sf::Vector2f& vector)
{
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y); // Pitagoras jak cos ;)

	sf::Vector2f normalizedVector;

	normalizedVector.x = vector.x / magnitude;
	normalizedVector.y = vector.y / magnitude;


	return normalizedVector;
}
void shoot(Player& player, AimingCross& corss)
{
}
//-------------

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Defend Base");
	sf::Music mainMusic;
	

	//Objects
	Player base;
	Map map;
	AimingCross cross;
	Bullet bullet;

	base.setScale(8.f);
	cross.setScale(5.f);

	startMainMusic(mainMusic);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		//
		



		//--Moving Machanics--
		cross.move(window);
		//--------------------

		window.setFramerateLimit(60);
		window.clear(sf::Color::Black);
		window.draw(map.sprite);
		window.draw(base.getSprite());
		window.draw(bullet.getSprite());
		window.draw(cross.getSprite());
		window.display();
	}


	return 0;
}