#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

};


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Defend Base");

	sf::Music mainMusic("sound/main_sound.mp3");
	mainMusic.play();

	//Objects
	Player base;
	Map map;

	base.setScale(8.f);
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		window.setFramerateLimit(20);
		window.clear(sf::Color::Black);
		window.draw(map.sprite);
		window.draw(base.getSprite());
		window.display();
	}


	return 0;
}