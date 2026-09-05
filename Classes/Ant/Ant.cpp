
class Ant
{
public:
	sf::Texture texture;
	sf::Sprite sprite { texture };
	std::string file_path = "Classes/Ant/textures/ant.png";
	int height = 40;
	int width = 40;
	sf::Vector2f position{ 300.f,300.f };
	sf::Vector2f origin{ 20,20};
	bool alive = true;

	Ant()
	{
		if (texture.loadFromFile(file_path))
			sprite.setTexture(texture);
		else
			std::cout << "Filed to load a Ant image texture";
		sprite.setTextureRect(sf::IntRect({ 0,0 }, { width,height }));
		sprite.setPosition(position);
		sprite.setOrigin(origin);
	}

	void setScale(float scale)
	{
		sprite.setScale({ scale, scale });
	}
	void randPosition()
	{
		int X_RANDOM = rand() % 800;
		int Y_RANDOM = rand() % 600;
		std::cout << "\tWylosowano: (" << X_RANDOM << ";" << Y_RANDOM << ") \n";

		sprite.setPosition(sf::Vector2f(X_RANDOM, Y_RANDOM));
	}
};