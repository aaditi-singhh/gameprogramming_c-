#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;
int main()
{
VideoMode video(800, 600);
RenderWindow window(video, "Pong Game");
float windowWidth = 1980;
float windowHeight = 1020;
View view(FloatRect(0, 0, windowWidth, windowHeight));
window.setView(view);
RectangleShape batShape;
float batWidth = 200;
float batHeight = 10;
float batSpeed = 2;
float batPixSec = windowHeight / batSpeed;
batShape.setOrigin(batWidth / 2, batHeight / 2);
batShape.setSize(Vector2f(batWidth, batHeight));
batShape.setFillColor(Color::White);
batShape.setPosition(windowWidth / 2, windowHeight - 20);
CircleShape ballShape;
float radius = 20;
float ballSpeed = 3;
float ballPixSecX = windowWidth / ballSpeed;
float ballPixSecY = windowHeight / ballSpeed;
ballShape.setRadius(radius);
ballShape.setFillColor(Color::Magenta);
ballShape.setPosition(20 + rand()%(int)(windowWidth-20) , 20);
Font font;
font.loadFromFile("KOMIKAP_.ttf");
Text scoreText;
scoreText.setFont(font);
scoreText.setCharacterSize(75);
scoreText.setFillColor(Color::White);
scoreText.setPosition(20, 20);
Text liveText;
liveText.setFont(font);
liveText.setCharacterSize(75);
liveText.setFillColor(Color::White);
float scoreVal = 0;
float liveVal = 3;
int ballMoveX = rand()%2 == 0 ?-1 : 1;
int ballMoveY = 1;
bool paused = false;
bool bounceTop = false;
bool bounceBottom = true;
bool gameOver = false;
Clock ct;
Time dt;
while (window.isOpen())
{
dt = ct.restart();
Event ev;
while (window.pollEvent(ev))
{
if (ev.type == Event::Closed || (ev.type == Event::KeyPressed
&& ev.key.code == Keyboard::Escape))
window.close();
if (ev.type == Event::KeyPressed && ev.key.code ==
Keyboard::Enter && gameOver)
{
paused = false;
gameOver = false;
bounceTop = false;
bounceBottom = true;
scoreVal = 0;
liveVal = 3;
ballShape.setPosition(windowWidth / 2, 20);
ballMoveX = rand()%2 == 0 ?-1 : 1;
ballMoveY = 1;
}
}
stringstream ss, ss1;
ss << "Score : " << scoreVal;
scoreText.setString(ss.str());
if(!gameOver)
ss1 << "Lives : " << liveVal;
else
ss1 << "Game Over .. Press Enter to restart";
liveText.setString(ss1.str());
FloatRect details = liveText.getLocalBounds();
liveText.setPosition(1980- details.width - 20, 20);
if (!paused)
{
if (Keyboard::isKeyPressed(Keyboard::Left))
{
float x = batShape.getPosition().x;
float y = batShape.getPosition().y;
x = x - dt.asSeconds() * batPixSec;
if (x < batWidth / 2)
x = batWidth / 2;
batShape.setPosition(x, y);
}
if (Keyboard::isKeyPressed(Keyboard::Right))
{
float x = batShape.getPosition().x;
float y = batShape.getPosition().y;
x = x + dt.asSeconds() * batPixSec;
if (x > windowWidth - batWidth / 2)
x = windowWidth - batWidth / 2;
batShape.setPosition(x, y);
}
float x = ballShape.getPosition().x;
float y = ballShape.getPosition().y;
x = x + dt.asSeconds() * ballPixSecX * ballMoveX;
y = y + dt.asSeconds() * ballPixSecY * ballMoveY;
if (x > windowWidth - radius)
ballMoveX =-1;
if (x < radius)
ballMoveX = 1;
if ((y > windowHeight - radius ||
batShape.getGlobalBounds().intersects(ballShape.getGlobalBounds())) &&
bounceBottom)
{
if (y > windowHeight - radius)
{
liveVal = liveVal - 1;
}
ballMoveY =-1;
bounceTop = true;
bounceBottom = false;
}
if (y < radius && bounceTop)
{
ballMoveY = 1;
scoreVal = scoreVal + 1;
bounceTop = false;
bounceBottom = true;
}
ballShape.setPosition(x, y);
}
if(liveVal == 0)
{
paused = true;
gameOver = true;
ballShape.setPosition(windowWidth/2, windowHeight/2);
}
window.clear();
window.draw(batShape);
window.draw(ballShape);
window.draw(scoreText);
window.draw(liveText);
window.display();
}
