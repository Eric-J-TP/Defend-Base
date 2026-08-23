#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
std::vector<sf::Vector2f> positions;
class AimingCross;
class Bullet;

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
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Player/textures/base.png";
	int height = 10;
	int width = 10;
	sf::Vector2f position{ 400.f, 300.f};
	sf::Vector2f origin{ 5.f,5.f };
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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet);

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
	friend void shoot(Player& player, AimingCross& corss, Bullet& bullet, std::vector <Bullet>& vec_bullet);
};
class Bullet
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Bullet/textures/image.png";
	int height = 8, width = 20;
	sf::Vector2f position{ 400.f, 300.f };
	sf::Vector2f origin{ 5.f, 5.f };
	float speed = 1.f;

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
	friend void shoot(Player& player, AimingCross& cross,Bullet& bullet, std::vector <Bullet>& vec_bullet);
};
//-----------

//--Functions--
void startMainMusic(sf::Music& music)
{
	if(music.openFromFile("sound/main_sound_2.mp3"))
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
void shoot(Player& player, AimingCross& cross,Bullet& bullet, std::vector <Bullet>& bullets)
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bullets.push_back(bullet);
		positions.push_back(cross.sprite.getPosition());

		int i = bullets.size() - 1;
		bullets[i].sprite.setPosition(player.sprite.getPosition());
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		sf::Vector2f bulletDir = positions[i] - bullets[i].sprite.getPosition();
		bulletDir = normalizeVector(bulletDir);
		bullets[i].sprite.setPosition(bullets[i].sprite.getPosition() + bulletDir * bullet.speed);

		if (
			sf::Vector2f({ 
				std::round(bullets[i].sprite.getPosition().x), 
				std::round(bullets[i].sprite.getPosition().y )}) 
				== 
			sf::Vector2f({ 
				std::round(positions[i].x), 
				std::round(positions[i].y) })) 
		{
			bullets.erase(bullets.begin() + i);
			positions.erase(positions.begin() + i);
		}
	}



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
	std::vector <Bullet> vec_bullet;

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
		//Dodać teksture dla pocisku, zrobić jako vector, potem zeby się obracały, i nadtępnie dodać ddzwięk wystrzału i trafienia
		



		//--Machanics--
		cross.move(window);
		shoot(base, cross, bullet, vec_bullet);
		//--------------------

		window.setFramerateLimit(60);
		window.clear(sf::Color::Black);
		window.draw(map.sprite);
		window.draw(base.getSprite());
		for(int i=0; i<vec_bullet.size(); i++)
			window.draw(vec_bullet[i].getSprite());

		window.draw(cross.getSprite());
		window.display();
	}


	return 0;
}