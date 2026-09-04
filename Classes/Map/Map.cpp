class Map
	{
	public:
		sf::Texture texture;
		sf::Sprite sprite{ texture };
		std::string file_path = "Classes/Map/textures/grass_2.png";
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