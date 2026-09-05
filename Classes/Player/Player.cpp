class Player
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Player/textures/a.png";
	int height = 107;
	int width = 50;
	sf::Vector2f position{ 400, 300.f };
	sf::Vector2f origin{ 20,50 };
	Player()
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
	friend void shoot(Player& player, AimingCross& cross, Bullet& bullet, std::vector <Bullet>& vec_bullet, Explosion& explosion, sf::Window& window);

};