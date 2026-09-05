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
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { width, height }));
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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion, sf::Window& window, Ant& ant);
};