class Explosion
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Explosion/textures/explosion_sheet.png";
	int height = 100;
	int width = 100;
	sf::Vector2f origin{ 50.f,96.f };
	sf::Clock clock;
	float elapsedMiliSeconds = 0.0; //wartosc poczatkowa Milisckundy
	bool actionTriggered = false; // bool do tego zebym wiedzial kiedy skonczy sie klatka
	bool actionFinished = false; // aby wiedziec kiedy sie skonczy animacja aby usunac sprite'a 
	int xIndex = 100;
	int yIndex = 0;

	Explosion()
	{
		//load texture
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a image texture";
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { width, height}));
		sprite.setOrigin(origin);
	}
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion, sf::Window& window);

	void startAnimation(sf::Window& window)
	{
		//dodanie klatek do animacji, zrobionej jako zmiana scopa w zdjeciu (sprite'a sheeta)
		
		float deltaTime = clock.restart().asMilliseconds();
		//Obliczanie ile mineło od ostatniej klatki Delta Time
		elapsedMiliSeconds += deltaTime;
		//std::cout << elapsedMiliSeconds << "\n";
		if (elapsedMiliSeconds >= 100 && actionFinished == false)
		{
			elapsedMiliSeconds = 0;
			sprite.setTextureRect(sf::IntRect({ xIndex,yIndex }, { width,height }));
			xIndex += 100;
			if (xIndex >= 600)
			{
				xIndex = 0;
				actionFinished = true;
			}

		}
	}
};