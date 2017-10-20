#include <PlayerView.hpp>

PlayerView::PlayerView(){

}

void PlayerView::init(){

}

void PlayerView::setContext(sf::RenderWindow* window){
	targetWindow = window;
}

void PlayerView::update(){
	targetWindow->clear(sf::Color::Black);
	sf::Texture texture;
	if (!texture.loadFromFile("../resources/Char.png"))
	{
	    // error...
	}
	sf::Sprite character;
	character.setTexture(texture);
	targetWindow->draw(character);
	targetWindow->display();
}

bool PlayerView::isOpen(){
	return targetWindow->isOpen();
}

void PlayerView::handleEvents(){
	sf::Event Event;
	while(targetWindow->pollEvent(Event)){
		// Exit
		if(Event.type == sf::Event::Closed)
			targetWindow->close();
	}
}
