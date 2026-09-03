class Explosion
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Explosion/textures/explosion_sheet.png";
	int height = 100;
	int width = 600;
	sf::Vector2f origin{ 50.f,96.f };

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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion);

	void startAnimation()
	{
		//dodanie klatek do animacji, zrobionej jako zmiana scopa w zdjeciu (sprite'a sheeta)
		
		//--Czas
		sf::Clock clock;
		float elapsedMiliSeconds = 0.0; //wartosc poczatkowa Milisckundy
		bool actionTriggered = false; // bool do tego zebym wiedzial kiedy skonczy sie klatka
		bool actionFinished = false; // aby wiedziec kiedy sie skonczy animacja aby usunac sprite'a 
		
		//Obliczanie ile mineło od ostatniej klatki Delta Time
		float deltaTime = clock.restart().asMilliseconds();
		elapsedMiliSeconds += deltaTime;

		if (elapsedMiliSeconds >= 500 && actionTriggered)
		{
			std::cout << "Wiadomość pomocnicza!\n";
		}


	}
};