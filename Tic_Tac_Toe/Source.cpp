#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\OpenGL.hpp>
#include<iostream>
#include<vector>
#include<string>

using namespace sf;
const int h = 320;
const int w = 320;
const int sizeOfField = 3;
template <class T>
void draw(RenderWindow&,std::vector<T>*);

void init(std::vector<ConvexShape>&);
void endGame(std::string);
std::pair<bool,bool> checkEnd(const std::vector < std::vector<int>>,int);
bool checkWin(std::vector < std::vector<int>>, int);
bool checkByVertical(std::vector < std::vector<int>>,int);
bool checkByHorizontal(std::vector < std::vector<int>>,int);
bool checkByLeteralDiagonal(std::vector < std::vector<int>>);
bool checkByMainDiagonal(std::vector < std::vector<int>>);
void output(std::vector < std::vector<int>> v);

int main()
{
	
	std::vector < std::vector<int>> a;
	for (int i = 0; i < sizeOfField; i++)
	{
		std::vector<int> v;
		a.emplace_back(v);
		for (int j = 0; j < sizeOfField; j++)
		{
			a[i].emplace_back(0);
		}
	}
	RenderWindow window(sf::VideoMode(w+100, h+100), "Tic-Tac-Toe",Style::Default);
	window.setVerticalSyncEnabled(true);
	RectangleShape rect;
	rect.setSize(Vector2f(h, w));
	rect.setPosition(Vector2f(50, 50));
	rect.setFillColor(Color(255,255,255));
	
	RectangleShape line1(Vector2f(10, h));
	line1.setPosition(Vector2f(50 + 100, 50));
	line1.setFillColor(Color(0, 0, 0));

	RectangleShape line2(Vector2f(10, h));
	line2.setPosition(Vector2f(50 + 210, 50));
	line2.setFillColor(Color(0, 0, 0));
	
	RectangleShape line3(Vector2f(w, 10));
	line3.setPosition(Vector2f(50 , 50 + 100));
	line3.setFillColor(Color(0, 0, 0));

	RectangleShape line4(Vector2f(w, 10));
	line4.setPosition(Vector2f(50 , 50 + 210));
	line4.setFillColor(Color(0, 0, 0));

	//create crosses
	std::vector<ConvexShape> crosses[1];
	ConvexShape cross;
	cross.setPointCount(12);
	cross.setFillColor(Color(255, 0, 0));

	//create noughts
	std::vector<CircleShape> noughts[1];
	CircleShape nought;
	nought.setFillColor(rect.getFillColor());
	nought.setOutlineColor(Color(255, 0, 0));
	nought.setOutlineThickness(10);
	nought.setRadius(40);

	//which player
	bool player = true;
	int i, j, x, y;
	std::pair<bool, bool> _checkEnd;
	window.clear(Color(249, 150, 107));
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// end the program
				window.close();
			}
			else if (event.type == Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i pos = Mouse::getPosition(window);
				//std::cout << pos.x << " " << pos.y << std::endl;
				if (pos.x >= 50 && pos.y >= 50 && pos.x <= 50 + w&&pos.y <= 50 + h)
				{
					i = ((pos.x - 50) / 110);
						j = ((pos.y - 50) / 110);
						x = 50 + i * 110;
						y = 50 + j * 110;
					if (a[j][i] == 0&&player)
					{
						//set position of cross
						cross.setPoint(0, Vector2f(x + 5, y));
						cross.setPoint(1, Vector2f(x, y + 5));
						cross.setPoint(2, Vector2f(x + 40, y + 50));
						cross.setPoint(3, Vector2f(x, y + 95));
						cross.setPoint(4, Vector2f(x + 5, y + 100));
						cross.setPoint(5, Vector2f(x + 50, y + 60));
						cross.setPoint(6, Vector2f(x + 95, y + 100));
						cross.setPoint(7, Vector2f(x + 100, y + 95));
						cross.setPoint(8, Vector2f(x + 60, y + 50));
						cross.setPoint(9, Vector2f(x + 100, y + 5));
						cross.setPoint(10, Vector2f(x + 95, y));
						cross.setPoint(11, Vector2f(x + 50, y + 40));
						crosses[0].emplace_back(cross);
						a[j][i] = 1;
						output(a);
						_checkEnd = checkEnd(a,j);
						output(a);
						if (_checkEnd.first)
						{
							window.close();
							if (_checkEnd.second)
								endGame("Player1 Won");
							else
								endGame("Draw");
						}
						player = !player;
					}
					else if (a[j][i] == 0 && !player)
					{
						//set position of nought
						nought.setPosition(Vector2f(x+nought.getOutlineThickness(),
							y+nought.getOutlineThickness()));
						noughts[0].emplace_back(nought);
						a[j][i] = 2;
						output(a);
						_checkEnd = checkEnd(a, j);
						output(a);
						if (_checkEnd.first)
						{
							window.close();
							if (_checkEnd.second)
								endGame("Player2 Won");
							else
								endGame("Draw");
						}
						player = !player;
					}
				}
			}
		}
		window.clear(Color(249, 150, 107));
		window.draw(rect);
		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);
		draw(window, crosses);
		draw(window, noughts);
		window.display();
	}

	// release resources...

	return 0;
}

template <class T>
void draw(RenderWindow& window, std::vector<T>*v)
{
	for (auto& i : *v)
	{
		window.draw(i);
	}
}

void endGame(std::string s)
{
	RenderWindow window(VideoMode(500, 500), "The End", Style::Default);
	window.setVerticalSyncEnabled(true);
	sf::Font font;
	if (!font.loadFromFile("3Dumb.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setString(s);
	text.setPosition(Vector2f(20, 200));
	text.setCharacterSize(70);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	while (window.isOpen())
	{
		Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
		}
		window.clear(Color(GL_BLUE));
		window.draw(text);
		window.display();
	}
}

std::pair<bool, bool> checkEnd(const std::vector < std::vector<int>> a,int i)
//first-end  second-player
{
	if (checkWin(a, i)) return std::make_pair(true, true);
	for (i = 0; i < sizeOfField; i++)
	{
		for (int j = 0; j < sizeOfField; j++)
		{
			if (a[i][j] == 0) return std::make_pair(false, false);
		}
	}
	return std::make_pair(true, false);
}

bool checkWin(std::vector < std::vector<int>> a, int i)
{
	bool isWinner = false;
	checkByHorizontal(a,i) ?
		isWinner = true : checkByVertical(a, i) ?
		isWinner = true : checkByMainDiagonal(a) ?
		isWinner = true : checkByLeteralDiagonal(a) ?
		isWinner = true : isWinner;
	return isWinner;
}

bool checkByVertical(std::vector < std::vector<int>>a,int i)
{
	int temp = a[i][0];
	for (int j = 1; j < sizeOfField; j++)
	{
		if (temp != a[i][j]||temp==0) return false;
	}
	return true;
}

bool checkByHorizontal(std::vector < std::vector<int>>a,int j)
{
	int temp = a[j][0];
	for (int i = 1; i < sizeOfField; i++)
	{
		if (temp != a[j][i] || temp == 0) return false;
	}
	return true;
}

bool checkByLeteralDiagonal(std::vector < std::vector<int>>a)
{
	int temp = a[0][sizeOfField - 1];
	int i = 1;
	
		for (int j = sizeOfField - 1 - i; j >= 0; j--)
		{
			if (temp != a[i][j] || temp == 0) return false;
			i++;
		}
	
	return true;
}

bool checkByMainDiagonal(std::vector < std::vector<int>> a)
{
	int temp = a[0][0];
	int i = 1;
		for (int j = 1; j < sizeOfField;j++)
		{
			if (temp != a[i][j] || temp == 0) return false;
			i++;
		}
	
	return true;
}

void output(std::vector < std::vector<int>> v)
{
	for (auto& i : v)
	{
		for (auto& j : i)
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}