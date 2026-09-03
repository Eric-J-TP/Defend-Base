#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
		---------
Wykonał: Eric


*/

//--Files--
#include "Classes/Map/Map.cpp"

//----Classes-----
std::vector<sf::Vector2f> positions;
class AimingCross;
class Bullet;
class Explosion;

class Player
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Player/textures/base.png";
	int height = 10;
	int width = 10;
	sf::Vector2f position{ 400, 300.f};
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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion);

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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion);
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
	friend void shoot(Player& player, AimingCross& cross,Bullet& bullet, std::vector <Bullet>& vec_bullet,Explosion& explosion);
};
class Explosion
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Explosion/animation/explosion_2.gif";
	int height = 100;
	int width = 100;
	sf::Vector2f origin { 50,95.f};

	Explosion()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { height,width }));
		sprite.setOrigin(origin);
	}
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion);
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
void shoot(Player& player, AimingCross& cross,Bullet& bullet, std::vector <Bullet>& bullets, Explosion& explosion)
{
	//jeśli jest kliknięty przycisk
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		//tworzy obiekty
		bullets.push_back(bullet);
		positions.push_back(cross.sprite.getPosition());

		//ustawia pozycje na pozycju gracza(bazy) 
		int i = bullets.size() - 1;
		bullets[i].sprite.setPosition(player.sprite.getPosition());

		//obraca pocisk względem pozycji do której leci
		float dx = 0.f, dy = 0.f;
		dx = cross.sprite.getPosition().x - player.sprite.getPosition().x;
		dy = cross.sprite.getPosition().y - player.sprite.getPosition().y;

		float kat = std::atan2(dy, dx);
		float stopnie = kat * (180.f / 3.14159);
		
		float degreesCorection = 90.f; // manual angle correction if the bullet needs to be facing right angle
		bullets[i].sprite.setRotation(sf::degrees(stopnie + degreesCorection));
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		sf::Vector2f bulletDir = positions[i] - bullets[i].sprite.getPosition();
		bulletDir = normalizeVector(bulletDir);
		bullets[i].sprite.setPosition(bullets[i].sprite.getPosition() + bulletDir * bullet.speed);
		//długi if XD, króry robi ze pocisk znika jak dotrze do punktu i ta wartość musi byc zaokrąglona 
		if (
			sf::Vector2f({ 
				std::round(bullets[i].sprite.getPosition().x), 
				std::round(bullets[i].sprite.getPosition().y )}) 
				== 
			sf::Vector2f({ 
				std::round(positions[i].x), 
				std::round(positions[i].y) })) 
		{
			explosion.sprite.setPosition(bullets[i].sprite.getPosition());
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
	
	int bulletTimer = 0;
	//Objects
	Player base;
	Map map;
	AimingCross cross;
	Bullet bullet;
	Explosion explosion;
	std::vector <Bullet> vec_bullet;

	base.setScale(8.f);
	cross.setScale(5.f);
	//explosion.sprite.setScale({2.f,2.f});
	explosion.sprite.setPosition({ 300.f,300.f });

	//----Start----
	//startMainMusic(mainMusic);

	//-------------

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		//--Machanics--
		cross.move(window);
		shoot(base, cross, bullet, vec_bullet,explosion);
		//--------------------

		window.setFramerateLimit(60);
		window.clear(sf::Color::Black);
		window.draw(map.sprite);
		window.draw(base.getSprite());
		for (int i = 0; i < vec_bullet.size(); i++)
		{
			window.draw(vec_bullet[i].getSprite());
		}
		window.draw(explosion.sprite);
		window.draw(cross.getSprite());
		window.display();
	}


	return 0;
}