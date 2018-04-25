#include<SFML\Main.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<iostream>

int main() {
	sf::RenderWindow win(sf::VideoMode(640, 480), "Pong");

	sf::Vector2f ballVelocity(0, 0);
	sf::RectangleShape ball(sf::Vector2f(25,25));
	ball.setPosition(sf::Vector2f(39, 0));
	sf::RectangleShape playerBat(sf::Vector2f(25, 75));
	playerBat.setPosition(sf::Vector2f(20, 0));
	//sf::RectangleShape aiBat(sf::Vector2f(25, 75));
	//aiBat.setPosition(sf::Vector2f(595, 0));

	while (win.isOpen()) {
		win.clear();
		bool intersects = playerBat.getGlobalBounds().intersects(ball.getGlobalBounds());
		if (intersects) { ballVelocity = {}; }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) | 
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (intersects) {
				ballVelocity.x = -0.1;
				ballVelocity.y = 0.1;
			}
			if (playerBat.getPosition().y >= 0) {
				playerBat.move(0, -0.1);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) |
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (intersects) {
				ballVelocity.x = 0.1;
				ballVelocity.y = -0.1;
			}
			if (playerBat.getPosition().y <= 405) {
				playerBat.move(0, 0.1);
			}
		}
		
		//game over
		if (ball.getPosition().x <= 0 && !intersects) {
			sf::Font gameoverFont;
			if (!gameoverFont.loadFromFile("DoHyeon-Regular.ttf")) {
				win.close();
			}
			sf::Text gameover("GAME OVER", gameoverFont);
			gameover.setPosition(sf::Vector2f(240, 220));
			win.draw(gameover);
		}
		else {
			sf::Vector2f ballPos = ball.getPosition();
	//		std::cout << "x: " << ballPos.x << "y: " << ballPos.y << std::endl;
			if (ballPos.y > 480) {
				ballVelocity.y = -0.1;
			}
			else if (ballPos.y < 0) {
				ballVelocity.y = 0.1;
			}
			else if (ballPos.x > 640) {
				ballVelocity.x = -0.1;
			}
			ball.move(ballVelocity);
			win.draw(ball);
			win.draw(playerBat);
		//	win.draw(aiBat);
		}
		
		sf::Event e;
		win.pollEvent(e);
		if (e.type == sf::Event::Closed) {
			win.close();
		}

		win.display();
	}
	return 0;
}