#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
		---------
Wykonał: Eric Jastrzębski


*/

class AimingCross;
class Bullet;
class Explosion;
class Ant;
//----Classes-----
#include "Classes/Map/Map.cpp"
#include "Classes/Player/Player.cpp"
#include "Classes/AimingCross/AimingCross.cpp"
#include "Classes/Bullet/Bullet.cpp"
#include "Classes/Explosion/Explosion.cpp"
#include "Classes/Ant/Ant.cpp"
int pom = 0; // dodanie delay do strzelania
std::vector<sf::Vector2f> positions;
sf::Music shootingMusic;
sf::Music explosionMusic;

//--Functions--
void startMainMusic(sf::Music& music)
{
	if(music.openFromFile("sound/main_sound_3.mp3"))
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
void ChangeIfShootedAnt(Bullet& bullet, Ant& ant)
{
		if (bullet.getHurtbox().findIntersection(ant.sprite.getGlobalBounds()) && bullet.OnGround)
		{
			std::cout << "Trafiono\n";
			ant.alive = false;
			ant.randPosition();

		}



}
void shoot(Player& player, AimingCross& cross,Bullet& bullet, std::vector <Bullet>& bullets, Explosion& explosion, sf::Window& window, Ant& ant)
{
	//jeśli jest kliknięty przycisk
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (pom > 100)
		{
			pom = 0;
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

			//odpala muzykę
			player.startSound(shootingMusic);
		}
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
			bullets[i].OnGround = true;

			ChangeIfShootedAnt(bullets[i], ant);


			explosion.sprite.setPosition(bullets[i].sprite.getPosition());
			bullets.erase(bullets.begin() + i);
			positions.erase(positions.begin() + i);
			explosion.startSound(explosionMusic); // odpala muzyke
			explosion.actionFinished = false; // rozpoczyna animacje eksplozji
		}
	}
}
//-------------
int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Defend Base");
	sf::Music mainMusic;
	sf::Music shootingMusic;
	int bulletTimer = 0;
	//Objects
	Player base;
	Ant ant;
	Map map;
	AimingCross cross;
	Bullet bullet;
	Explosion explosion;
	std::vector <Bullet> vec_bullet;

	//base.setScale(8.f);
	cross.setScale(5.f);
	//explosion.sprite.setScale({2.f,2.f});
	explosion.sprite.setPosition({ 300.f,300.f });

	//----Start----
	srand(time(NULL));
	startMainMusic(mainMusic);
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
		pom++;
		shoot(base, cross, bullet, vec_bullet,explosion, window, ant);
		//--------------------

		window.setFramerateLimit(120);
		window.clear(sf::Color::Black);

		window.draw(map.sprite);
		window.draw(base.getSprite());
		window.draw(ant.sprite);

		for (int i = 0; i < vec_bullet.size(); i++)
		{
			window.draw(vec_bullet[i].getSprite());
		}
		if (explosion.actionFinished == false)
		{
			explosion.startAnimation(window);
			window.draw(explosion.sprite);
		}
		window.draw(cross.getSprite());
		window.display();
	}


	return 0;
}