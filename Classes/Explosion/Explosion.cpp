class Explosion
{
public:
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	std::string file_path = "Classes/Explosion/animation/explosion_2.gif";
	int height = 100;
	int width = 100;
	sf::Vector2f origin{ 50,95.f };

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