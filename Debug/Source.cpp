#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <cctype>

int main() {
	int run = 0;
	int play = 0;
	int reload = 0;
	int zcounter = 2;
	int pointer = 0;
	int ptrX = 0;
	int ptrY = 0;
	int ptrS = 0;
	int o = 0;
	int p = 0;
	int dt = 0;
	int flrs = 0;
	int respawn[3];
	int flag[3];
	for (int rst = 0; rst < 3; rst++) {
		respawn[rst] = -1;
		flag[rst] = -1;
	}
	sf::Vector2i map[25][15][5];
	for (int z = 0; z <= 5; z++) {
		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 25; x++) {
				map[x][y][z] = sf::Vector2i(-1, -1);
			}
		}
	}
	sf::Vector2i escsb[5];
	sf::Vector2i escdc[5];
	for (int init = 0; init < 5; init++) {
		escsb[init] = sf::Vector2i(-1, -1);

		escdc[init] = sf::Vector2i(-1, -1);
	}
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	sf::Vector2i copy = sf::Vector2i(-1, -1);
	sf::Vector2i selected = sf::Vector2i(0, 0);
	sf::Vector2i tlselected = sf::Vector2i(0, 0);
	sf::RenderWindow Window(sf::VideoMode(1200, 750), "Map Editor");
	sf::Texture pTexture;
	sf::Sprite Tileset;
	sf::Texture bTexture;
	sf::Sprite Borda;
	sf::Texture zTexture;
	sf::Sprite Pointer;
	sf::Texture mTexture;
	sf::Sprite FM;
	sf::Texture nTexture;
	sf::Sprite FN;
	sf::Texture lTexture;
	sf::Sprite Lixo;
	sf::Texture salo;
	sf::Sprite sl;
	sf::Texture fla;
	sf::Sprite fl;
	sf::Texture rsp;
	sf::Sprite rs;
	sf::Texture flai;
	sf::Sprite fli;
	sf::Texture rspi;
	sf::Sprite rsi;
	sf::Texture tsri;
	sf::Sprite tsr;
	if (!bTexture.loadFromFile("borda.png"))
		std::cout << "Erro ao carregar borda" << std::endl;
	if (!zTexture.loadFromFile("pointer.png"))
		std::cout << "Erro ao carregar pointer" << std::endl;
	if (!nTexture.loadFromFile("minus.png"))
		std::cout << "Erro ao carregar minus" << std::endl;
	if (!mTexture.loadFromFile("plus.png"))
		std::cout << "Erro ao carregar plus" << std::endl;
	if (!lTexture.loadFromFile("delete.png"))
		std::cout << "Erro ao carregar lixeira" << std::endl;
	if(!pTexture.loadFromFile("tileset.png"))
		std::cout << "Erro ao carregar tileset" << std::endl;
	if (!salo.loadFromFile("sl.png"))
		std::cout << "Erro ao carregar save/load screen" << std::endl;
	if (!fla.loadFromFile("escdc.png"))
		std::cout << "Erro ao carregar escadas" << std::endl;
	if (!rsp.loadFromFile("escsb.png"))
		std::cout << "Erro ao carregar escadas" << std::endl;
	if (!rspi.loadFromFile("respawn.png"))
		std::cout << "Erro ao carregar respawn" << std::endl;
	if (!flai.loadFromFile("brain.png"))
		std::cout << "Erro ao carregar brain" << std::endl;
	if (!tsri.loadFromFile("brain2.png"))
		std::cout << "Erro ao carregar brain2" << std::endl;
	sf::Font Font;
	if(!Font.loadFromFile("HARNGTON.TTF"))
		std::cout << "Erro ao carregar fonte" << std::endl;
	sf::String frase;
	sf::Text Text(frase, Font, 40);
	Text.setColor(sf::Color(30, 100, 200));
	sf::Text Text2(frase, Font, 40);
	Text2.setColor(sf::Color(30, 100, 200));
	Text2.setCharacterSize(12);
	Borda.setTexture(bTexture);
	Pointer.setTexture(zTexture);
	FM.setTexture(mTexture);
	FN.setTexture(nTexture);
	fl.setTexture(fla);
	rs.setTexture(rsp);
	fli.setTexture(flai);
	rsi.setTexture(rspi);
	tsr.setTexture(tsri);
	Lixo.setTexture(lTexture);
	sl.setTexture(salo);
	Tileset.setTexture(pTexture);
	while (Window.isOpen()) {
		Window.clear();
		frase = "teste";
		while (run == 0) {
			Window.clear();
			if (reload == 0) {
				Text.setPosition(100, 80);
				Text.setString("Novo Mapa");
				Window.draw(Text);
			}
			Text.setPosition(100, 160);
			Text.setString("Carregar Mapa");
			Window.draw(Text);
			Text.setPosition(100, 240);
			Text.setString("Jogar");
			Window.draw(Text);
			Window.display();
			sf::Event Event;
			while (Window.pollEvent(Event)) {
				switch (Event.type) {
				case sf::Event::Closed:
					Window.close();
				case sf::Event::MouseButtonPressed:
					if (Event.mouseButton.button == sf::Mouse::Left) {
						if (Event.mouseButton.x >= 100 && Event.mouseButton.x <= 300 && Event.mouseButton.y >= 80 && Event.mouseButton.y <= 120)
							run = 1;
						else if ((Event.mouseButton.x >= 100 && Event.mouseButton.x <= 350 && Event.mouseButton.y >= 160 && Event.mouseButton.y <= 200) || (Event.mouseButton.x >= 100 && Event.mouseButton.x <= 300 && Event.mouseButton.y >= 240 && Event.mouseButton.y <= 280)) {
							if (Event.mouseButton.x >= 100 && Event.mouseButton.x <= 300 && Event.mouseButton.y >= 240 && Event.mouseButton.y <= 280)
								play = 1;
							std::string mapa;
							mapa = "";
							sf::RenderWindow carrega(sf::VideoMode(250, 150), "Load", sf::Style::None);
							while (carrega.isOpen()) {
								sf::Event event;
								carrega.clear();
								carrega.draw(sl);
								while (carrega.pollEvent(event)) {
									if (event.type == sf::Event::TextEntered) {


										if (event.text.unicode < 128) {
											mapa += static_cast<char>(event.text.unicode);
											if (event.text.unicode == 8) {
												if (mapa.size() > 1)
													mapa.erase(mapa.size() - 2);
												else
													mapa.erase(mapa.size() - 1);
											}
											Text.setPosition(20, 20);
											Text.setString(mapa);

										}
									}
									if ((event.key.code == sf::Keyboard::Return || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x > 50 && event.mouseButton.x < 200 && event.mouseButton.y > 85 && event.mouseButton.y < 130)) && event.type != sf::Event::MouseEntered && event.type != sf::Event::MouseLeft && event.type != sf::Event::MouseMoved) {
										carrega.close();
									}

								}
								carrega.draw(Text);
								carrega.display();


							}
							if (mapa.find(".txt") == std::string::npos) {

								mapa += ".txt";
							}


							std::ifstream openfile(mapa);
							if (openfile.is_open()) {
								run = 1;
								zcounter = 0;
								while (!openfile.eof()) {
									std::string str;
									openfile >> str;
									char x = str[0], y = str[2];
									int prt = 0;
									if (!isdigit(x) || !isdigit(y)) {
										if ((x == 'z' || x == 'Z') && isdigit(y)) {
											loadcounter.x = 0;
											loadcounter.y = 0;
											zcounter++;
											prt = 1;
										}
										else if ((x == 's' || x == 'S') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											escsb[zcounter].x = tnp;
											
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 's' || x == 'S') && str[1] == ',' && isdigit(y)) {
											escsb[zcounter].x = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((y == 's' || y == 'S') && str[1] != ',' && isdigit(x)) {
											int tnp = (x - '0') * 10;
											tnp += str[1] - '0';
											escsb[zcounter].y = tnp;
											
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((y == 's' || y == 'S') && str[1] == ',' && isdigit(x)) {
											escsb[zcounter].y = x - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'd' || x == 'D') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											escdc[zcounter].x = tnp;
											
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'd' || x == 'D') && str[1] == ',' && isdigit(y)) {
											escdc[zcounter].x = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((y == 'd' || y == 'D') && str[1] != ',' && isdigit(x)) {
											int tnp = (x - '0') * 10;
											tnp += str[1] - '0';
											escdc[zcounter].y = tnp;
											
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((y == 'd' || y == 'D') && str[1] == ',' && isdigit(x)) {
											escdc[zcounter].y = x - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'r' || x == 'R') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											respawn[0] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;

										}
										else if ((x == 'r' || x == 'R') && str[1] == ',' && isdigit(y)) {
											respawn[0] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;

										}

										else if ((x == 't' || x == 'T') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											respawn[1] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 't' || x == 'T') && str[1] == ',' && isdigit(y)) {
											respawn[1] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}

										else if ((x == 'y' || x == 'Y') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											respawn[2] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'y' || x == 'Y') && str[1] == ',' && isdigit(y)) {
											respawn[2] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'f' || x == 'F') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											flag[0] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'f' || x == 'F') && str[1] == ',' && isdigit(y)) {
											flag[0] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}

										else if ((x == 'g' || x == 'G') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											flag[1] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'g' || x == 'G') && str[1] == ',' && isdigit(y)) {
											flag[1] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}

										else if ((x == 'h' || x == 'H') && str[1] != ',' && isdigit(y)) {
											int tnp = (str[1] - '0') * 10;
											tnp += y - '0';
											flag[2] = tnp;
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else if ((x == 'h' || x == 'H') && str[1] == ',' && isdigit(y)) {
											flag[2] = y - '0';
											prt = 1; loadcounter.y = 0; loadcounter.x = 0;
										}
										else
											map[loadcounter.x][loadcounter.y][zcounter] = sf::Vector2i(-1, -1);
									}
									else {
										map[loadcounter.x][loadcounter.y][zcounter] = sf::Vector2i(x - '0', y - '0');
									}
									if (openfile.peek() == '\n' && prt == 0) {
										loadcounter.x = 0;
										loadcounter.y++;
									}
									else {
										if (prt == 0)
											loadcounter.x++;
									}
								}
								loadcounter.y++;
								zcounter = 2;
							}

						}
						Window.clear();
					}
				default:
					break;
				}
			}
		}


		if (play == 0) {
			sf::Event Event;
			while (Window.pollEvent(Event)) {
				switch (Event.type) {
				case sf::Event::Closed:
					Window.close();
				case sf::Event::MouseMoved:
					if (Event.mouseMove.x >= 300 && Event.mouseMove.x <= 1095 && Event.mouseMove.y >= 95 && Event.mouseMove.y <= 574) {
						p = (Event.mouseMove.x - 300) / 32;
						p = (p * 32) + 300;
						o = (Event.mouseMove.y - 95) / 32;
						o = (o * 32) + 100;
						dt = 1;
					}
					else {
						dt = 0;
					}
				case sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::M && Event.type != sf::Event::MouseEntered && Event.type != sf::Event::MouseLeft && Event.type != sf::Event::MouseMoved) {
						if (zcounter < 4)
							zcounter++;

					}
					else if (Event.key.code == sf::Keyboard::N && Event.type != sf::Event::MouseEntered && Event.type != sf::Event::MouseLeft && Event.type != sf::Event::MouseMoved) {
						if (zcounter > 0)
							zcounter--;
					}
					else if (Event.key.code == sf::Keyboard::Delete) {
						if (pointer == 1 && ptrS == 1) {
							map[ptrX][ptrY][zcounter].x = -1;
							map[ptrX][ptrY][zcounter].y = -1;
							if (escsb[zcounter].x == ptrX && escsb[zcounter].y == ptrY) {
								escsb[zcounter] = sf::Vector2i(-1, -1);
							}
							if (escdc[zcounter].x == ptrX && escdc[zcounter].y == ptrY) {
								escdc[zcounter] = sf::Vector2i(-1, -1);
							}
						}
					}
					else if (Event.key.control && Event.key.code == sf::Keyboard::C) {

						if (pointer == 1 && ptrS == 1) {
							if (map[ptrX][ptrY][zcounter].x != -1 && map[ptrX][ptrY][zcounter].y != -1) {
								copy = map[ptrX][ptrY][zcounter];
							}
						}
					}
					else if (Event.key.control && Event.key.code == sf::Keyboard::V) {
						if (pointer == 1 && ptrS == 1) {
							if (copy.x != -1 && copy.y != -1) {
								map[ptrX][ptrY][zcounter] = copy;
							}
						}
					}
				case sf::Event::MouseButtonPressed:
					if (Event.mouseButton.button == sf::Mouse::Left) {
						if (dt == 1) {
							int kx = (p - 300) / 32;
							int ky = (o - 100) / 32;
							if (pointer == 0) {
								map[kx][ky][zcounter].x = selected.x;
								map[kx][ky][zcounter].y = selected.y;
								sf::Event EventR;
								int rpt = 0;
								while (rpt == 0) {
									while (Window.pollEvent(EventR)) {
										switch (EventR.type) {
										case sf::Event::MouseButtonReleased:
											rpt = 1;
										default:

											if (sf::Event::MouseMoved) {
												int nx = (EventR.mouseMove.x - 300) / 32;
												int ny = (EventR.mouseMove.y - 95) / 32;
												if ((nx != kx || ny != ky) && (EventR.mouseMove.x > 300 && EventR.mouseMove.x < 1100) && (EventR.mouseMove.y > 95 && EventR.mouseMove.y < 575)) {
													if (map[nx][ny][zcounter].x != selected.x || map[nx][ny][zcounter].y != selected.y) {
														map[nx][ny][zcounter].x = selected.x;
														map[nx][ny][zcounter].y = selected.y;
														if (escsb[zcounter].x == nx && escsb[zcounter].y == ny)
															escsb[zcounter] = sf::Vector2i(-1, -1);
														if (escdc[zcounter].x == nx && escdc[zcounter].y == ny)
															escdc[zcounter] = sf::Vector2i(-1, -1);
													}
												}

											}
										}
									}
									Window.clear();
									Window.draw(Borda);
									Pointer.setPosition(160, 120);
									Window.draw(Pointer);
									FM.setPosition(160, 185);
									Window.draw(FM);
									FN.setPosition(160, 222);
									Window.draw(FN);
									Lixo.setPosition(160, 280);
									Window.draw(Lixo);
									rs.setPosition(160, 340);
									Window.draw(rs);
									fl.setPosition(160, 400);
									Window.draw(fl);
									rsi.setPosition(160, 460);
									Window.draw(rsi);
									fli.setPosition(160, 520);
									Window.draw(fli);
									Text.setPosition(16, 100);
									Text.setString("Tileset");
									Window.draw(Text);
									Text.setPosition(16, 10);
									Text.setString("Novo Mapa");
									Window.draw(Text);
									Text.setPosition(320, 10);
									Text.setString("Salvar Mapa");
									Window.draw(Text);
									Text.setPosition(640, 10);
									Text.setString("Carregar Mapa");
									Window.draw(Text);
									Text.setPosition(540, 650);
									Text.setString("Andar:");
									Window.draw(Text);
									Text.setPosition(670, 650);
									std::string s = std::to_string(zcounter - 2);
									Text.setString(s);
									Window.draw(Text);
									Text.setPosition(980, 10);
									Text.setString("Sair");
									Window.draw(Text);
									int oX = 1;
									int oY = 1;
									for (int l = 0; l < 5; l++) {
										for (int c = 0; c < 7; c++) {
											Tileset.setTextureRect(sf::IntRect(c * 32, l * 32, 32, 32));
											Tileset.setPosition((oX * 40) - 20, (oY * 40) + 120);
											Window.draw(Tileset);
											oX++;
											if (oX == 4) {
												oX = 1;
												oY++;
											}
											if (l >= 3) {
												if (c >= 3)
													c = 7;
											}

										}
									}
									Tileset.setTextureRect(sf::IntRect(0 * 32, 5 * 32, 32, 32));
									Tileset.setPosition((oX * 40) - 20, (oY * 40) + 120);
									Window.draw(Tileset);
									if (pointer == 0) {

										sf::RectangleShape rectangle(sf::Vector2f(32, 32));
										rectangle.setFillColor(sf::Color(50, 100, 100, 120));
										rectangle.setPosition((tlselected.x * 40) + 20, (tlselected.y * 40) + 160);
										Window.draw(rectangle);
									}
									for (int my = 0; my < 15; my++) {
										for (int mx = 0; mx < 25; mx++) {
											if (map[mx][my][zcounter].x != -1 && map[mx][my][zcounter].y != -1) {
												Tileset.setPosition((mx * 32) + 300, (my * 32) + 100);
												Tileset.setTextureRect(sf::IntRect(map[mx][my][zcounter].x * 32, map[mx][my][zcounter].y * 32, 32, 32));
												Window.draw(Tileset);
											}
										}
									}
									if (dt == 1 && pointer == 0 && (selected.x != -1 && selected.y != -1)) {
										Tileset.setTextureRect(sf::IntRect(selected.x * 32, selected.y * 32, 32, 32));
										Tileset.setPosition(p, o);
										Window.draw(Tileset);

									}
									if (escdc[zcounter].x != -1 && escdc[zcounter].y != -1) {
										fl.setPosition((escdc[zcounter].x * 32) + 300, (escdc[zcounter].y * 32) + 100);
										Window.draw(fl);
									}
									if (escsb[zcounter].x != -1 && escsb[zcounter].y != -1) {
										rs.setPosition((escsb[zcounter].x * 32) + 300, (escsb[zcounter].y * 32) + 100);
										Window.draw(rs);
									}
									Window.display();
								}
							}
							else if (flrs == 0) {
								ptrX = kx;
								ptrY = ky;
								ptrS = 1;
							}
							else if (flrs == 1) {
								if (map[kx][ky][zcounter].x != -1 && map[kx][ky][zcounter].y != -1) {
									escsb[zcounter] = sf::Vector2i(kx, ky);
								}

								flrs = 0;
							}
							else if (flrs == 2) {
								if (map[kx][ky][zcounter].x != -1 && map[kx][ky][zcounter].y != -1) {
									escdc[zcounter] = sf::Vector2i(kx, ky);
								}

								flrs = 0;
							}
							else if (flrs == 3) {
								if (map[kx][ky][zcounter].x != -1 && map[kx][ky][zcounter].y != -1) {
									respawn[0] = kx;
									respawn[1] = ky;
									respawn[2] = zcounter;
								}

								flrs = 0;
							}
							else if (flrs == 4) {
								if (map[kx][ky][zcounter].x != -1 && map[kx][ky][zcounter].y != -1) {
									flag[0] = kx;
									flag[1] = ky;
									flag[2] = zcounter;
								}

								flrs = 0;
							}
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 185 && Event.mouseButton.y <= 217 && Event.type != sf::Event::MouseEntered && Event.type != sf::Event::MouseLeft && Event.type != sf::Event::MouseMoved) {
							if (zcounter < 4)
								zcounter++;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 222 && Event.mouseButton.y <= 254 && Event.type != sf::Event::MouseEntered && Event.type != sf::Event::MouseLeft && Event.type != sf::Event::MouseMoved) {
							if (zcounter > 0)
								zcounter--;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 280 && Event.mouseButton.y <= 312) {
							selected.x = -1;
							selected.y = -1;
							pointer = 0;
							ptrS = 0;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 340 && Event.mouseButton.y <= 372) {
							pointer = 1;
							flrs = 1;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 400 && Event.mouseButton.y <= 432) {
							pointer = 1;
							flrs = 2;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 460 && Event.mouseButton.y <= 492) {
							pointer = 1;
							flrs = 3;
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 520 && Event.mouseButton.y <= 552) {
							pointer = 1;
							flrs = 4;
						}
						if (Event.mouseButton.x >= 16 && Event.mouseButton.x <= 130 && Event.mouseButton.y >= 150 && Event.mouseButton.y <= 540) {
							pointer = 0;
							ptrS = 0;
							if (Event.mouseButton.x <= 54)
								tlselected.x = 0;
							else if (Event.mouseButton.x <= 92)
								tlselected.x = 1;
							else
								tlselected.x = 2;
							if (Event.mouseButton.y <= 188)
								tlselected.y = 0;
							else if (Event.mouseButton.y <= 226)
								tlselected.y = 1;
							else if (Event.mouseButton.y <= 264)
								tlselected.y = 2;
							else if (Event.mouseButton.y <= 302)
								tlselected.y = 3;
							else if (Event.mouseButton.y <= 340)
								tlselected.y = 4;
							else if (Event.mouseButton.y <= 378)
								tlselected.y = 5;
							else if (Event.mouseButton.y <= 416)
								tlselected.y = 6;
							else if (Event.mouseButton.y <= 454)
								tlselected.y = 7;
							else if (Event.mouseButton.y <= 492)
								tlselected.y = 8;
							else if (Event.mouseButton.y <= 540)
								tlselected.y = 9;

							int px = 0;
							int py = 0;
							for (int ay = 0; ay < 10; ay++) {
								for (int ax = 0; ax < 3; ax++) {
									if (ax == tlselected.x && tlselected.y == ay) {
										selected.x = px;
										selected.y = py;
										ax = 10;
										ay = 10;
									}
									px++;
									if (py >= 3 && px >= 4) {
										px = 0;
										py++;
									}
									if (px >= 7) {
										px = 0;
										py++;
									}
								}
							}
						}
						if (Event.mouseButton.x >= 16 && Event.mouseButton.x <= 290 && Event.mouseButton.y >= 10 && Event.mouseButton.y <= 50) {
							for (int zz = 0; zz < 5; zz++) {
								for (int zy = 0; zy < 15; zy++) {
									for (int zx = 0; zx < 25; zx++) {
										map[zx][zy][zz].x = -1;
										map[zx][zy][zz].y = -1;
										escsb[zz] = sf::Vector2i(-1, -1);
										escdc[zz] = sf::Vector2i(-1, -1);
									}
								}
							}
						}
						if (Event.mouseButton.x >= 320 && Event.mouseButton.x <= 600 && Event.mouseButton.y >= 10 && Event.mouseButton.y <= 50) {
							std::string otp;




							sf::RenderWindow carrega(sf::VideoMode(250, 150), "Save", sf::Style::None);
							while (carrega.isOpen()) {
								sf::Event event;
								carrega.clear();
								carrega.draw(sl);
								while (carrega.pollEvent(event)) {
									if (event.type == sf::Event::TextEntered) {
										// Handle ASCII characters only

										if (event.text.unicode < 128) {


											otp += static_cast<char>(event.text.unicode);
											if (event.text.unicode == 8) {
												if (otp.size() > 1)
													otp.erase(otp.size() - 2);
												else
													otp.erase(otp.size() - 1);
											}
											Text.setPosition(20, 20);
											Text.setString(otp);


										}


									}
									if ((event.key.code == sf::Keyboard::Return || (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x > 50 && event.mouseButton.x < 200 && event.mouseButton.y > 85 && event.mouseButton.y < 130)) && event.type != sf::Event::MouseEntered && event.type != sf::Event::MouseLeft && event.type != sf::Event::MouseMoved) {
										carrega.close();
									}
								}
								carrega.draw(Text);
								carrega.display();


							}
							if (otp.find(".txt") == std::string::npos) {
								otp += ".txt";
							}

							std::ofstream output(otp);
							if (respawn[0] > -1) {
								if (respawn[0] >= 10)
									output << "r" << respawn[0] << "\n";
								else
									output << "r," << respawn[0] << "\n";
							}
							if (respawn[1] > -1) {
								if (respawn[1] >= 10)
									output << "t" << respawn[1] << "\n";
								else
									output << "t," << respawn[1] << "\n";
							}
							if (respawn[2] > -1) {
								if (respawn[2] >= 10)
									output << "y" << respawn[2] << "\n";
								else
									output << "y," << respawn[2] << "\n";
							}
							if (flag[0] > -1) {
								if (flag[0] >= 10)
									output << "f" << flag[0] << "\n";
								else
									output << "f," << flag[0] << "\n";
							}
							if (flag[1] > -1) {
								if (flag[1] >= 10)
									output << "g" << flag[1] << "\n";
								else
									output << "g," << flag[1] << "\n";
							}
							if (flag[2] > -1) {
								if (flag[2] >= 10)
									output << "h" << flag[2] << "\n";
								else
									output << "h," << flag[2] << "\n";
							}
							for (int sz = 0; sz < 5; sz++) {
								if (escsb[sz].x > -1 && escsb[sz].y > -1) {
									if (escsb[sz].x >= 10)
										output << "s" << escsb[sz].x << "\n";
									else
										output << "s," << escsb[sz].x << "\n";
									if (escsb[sz].y >= 10)
										output << escsb[sz].y << "s\n";
									else
										output << escsb[sz].y << ",s\n";
								}
								if (escdc[sz].x > -1 && escdc[sz].y > -1) {
									if (escdc[sz].x >= 10)
										output << "d" << escdc[sz].x << "\n";
									else
										output << "d," << escdc[sz].x << "\n";
									if (escdc[sz].y >= 10)
										output << escdc[sz].y << "d\n";
									else
										output << escdc[sz].y << ",d\n";
								}
								for (int sy = 0; sy < 15; sy++) {
									for (int sx = 0; sx < 25; sx++) {
										if (map[sx][sy][sz].x != -1 && map[sx][sy][sz].y != -1)
											output << map[sx][sy][sz].x << "," << map[sx][sy][sz].y;
										else
											output << "x,x";
										if (sx < 24)
											output << " ";
									}
									if (sy < 14)
										output << "\n";
								}
								if (sz < 4)
									output << "\nz,1\n";
							}

						}
						if (Event.mouseButton.x >= 640 && Event.mouseButton.x <= 960 && Event.mouseButton.y >= 10 && Event.mouseButton.y <= 50) {
							run = 0;
							loadcounter.x = 0;
							loadcounter.y = 0;
							reload++;
							Window.clear();
						}
						if (Event.mouseButton.x >= 980 && Event.mouseButton.x <= 1050 && Event.mouseButton.y >= 10 && Event.mouseButton.y <= 50) {
							Window.close();
						}
						if (Event.mouseButton.x >= 160 && Event.mouseButton.x <= 192 && Event.mouseButton.y >= 120 && Event.mouseButton.y <= 152) {
							pointer = 1;
							flrs = 0;
						}
					}
				default:
					break;
				}
				if (Event.type == sf::Event::KeyPressed) {
					if (Event.key.code == sf::Keyboard::Return) {
					}
				}
			}



			Window.draw(Borda);
			Pointer.setPosition(160, 120);
			Window.draw(Pointer);
			FM.setPosition(160, 185);
			Window.draw(FM);
			FN.setPosition(160, 222);
			Window.draw(FN);
			Lixo.setPosition(160, 280);
			Window.draw(Lixo);
			rs.setPosition(160, 340);
			Window.draw(rs);
			fl.setPosition(160, 400);
			Window.draw(fl);
			rsi.setPosition(160, 460);
			Window.draw(rsi);
			fli.setPosition(160, 520);
			Window.draw(fli);
			Text.setPosition(16, 100);
			Text.setString("Tileset");
			Window.draw(Text);
			Text.setPosition(16, 10);
			Text.setString("Novo Mapa");
			Window.draw(Text);
			Text.setPosition(320, 10);
			Text.setString("Salvar Mapa");
			Window.draw(Text);
			Text.setPosition(640, 10);
			Text.setString("Carregar Mapa");
			Window.draw(Text);
			Text.setPosition(540, 650);
			Text.setString("Andar:");
			Window.draw(Text);
			Text.setPosition(670, 650);
			std::string s = std::to_string(zcounter - 2);
			Text.setString(s);
			Window.draw(Text);
			Text.setPosition(980, 10);
			Text.setString("Sair");
			Window.draw(Text);
			int oX = 1;
			int oY = 1;
			for (int l = 0; l < 5; l++) {
				for (int c = 0; c < 7; c++) {
					Tileset.setTextureRect(sf::IntRect(c * 32, l * 32, 32, 32));
					Tileset.setPosition((oX * 40) - 20, (oY * 40) + 120);
					Window.draw(Tileset);
					oX++;
					if (oX == 4) {
						oX = 1;
						oY++;
					}
					if (l >= 3) {
						if (c >= 3)
							c = 7;
					}

				}
			}
			Tileset.setTextureRect(sf::IntRect(0 * 32, 5 * 32, 32, 32));
			Tileset.setPosition((oX * 40) - 20, (oY * 40) + 120);
			Window.draw(Tileset);
			if (pointer == 0) {

				sf::RectangleShape rectangle(sf::Vector2f(32, 32));
				rectangle.setFillColor(sf::Color(50, 100, 100, 120));
				rectangle.setPosition((tlselected.x * 40) + 20, (tlselected.y * 40) + 160);
				Window.draw(rectangle);
			}
			for (int my = 0; my < 15; my++) {
				for (int mx = 0; mx < 25; mx++) {
					if (map[mx][my][zcounter].x != -1 && map[mx][my][zcounter].y != -1) {
						Tileset.setPosition((mx * 32) + 300, (my * 32) + 100);
						Tileset.setTextureRect(sf::IntRect(map[mx][my][zcounter].x * 32, map[mx][my][zcounter].y * 32, 32, 32));
						Window.draw(Tileset);
					}
				}
			}
			if (escdc[zcounter].x != -1 && escdc[zcounter].y != -1) {
				fl.setPosition((escdc[zcounter].x * 32) + 300, (escdc[zcounter].y * 32) + 100);
				Window.draw(fl);
			}
			if (escsb[zcounter].x != -1 && escsb[zcounter].y != -1) {
				rs.setPosition((escsb[zcounter].x * 32) + 300, (escsb[zcounter].y * 32) + 100);
				Window.draw(rs);
			}
			if (respawn[0] != -1 && respawn[1] != -1 && respawn[2] != -1 && respawn[2] == zcounter) {
				rsi.setPosition((respawn[0] * 32) + 300, (respawn[1] * 32) + 100);
				Window.draw(rsi);
			}
			if (flag[0] != -1 && flag[1] != -1 && flag[2] != -1 && flag[2] == zcounter) {

				fli.setPosition((flag[0] * 32) + 300, (flag[1] * 32) + 100);
				Window.draw(fli);
			}
			if (dt == 1 && pointer == 0 && (selected.x != -1 && selected.y != -1)) {
				Tileset.setTextureRect(sf::IntRect(selected.x * 32, selected.y * 32, 32, 32));
				Tileset.setPosition(p, o);
				Window.draw(Tileset);

			}
			else if (pointer == 1 && flrs == 1) {
				rs.setPosition(p, o);
				Window.draw(rs);
			}
			else if (pointer == 1 && flrs == 2) {
				fl.setPosition(p, o);
				Window.draw(fl);
			}
			else if (pointer == 1 && flrs == 3) {
				rsi.setPosition(p, o);
				Window.draw(rsi);
			}
			else if (pointer == 1 && flrs == 4) {
				fli.setPosition(p, o);
				Window.draw(fli);
			}

			Window.display();

		}
		else if(play == 1){
			sf::RenderWindow PlayWindow(sf::VideoMode(180, 180), "Game");
			PlayWindow.setSize(sf::Vector2u(360, 360));
			sf::Vector3i Player = sf::Vector3i(respawn[0], respawn[1], respawn[2]);
			sf::Vector3i Tesouro[5];
			int pontos = 0;
			int pew;
			srand(time(NULL));
			for (int i = 0; i < 5; i++) {
				pew = 0;
				while (pew == 0) {
					int m1 = rand() % 25 + 1;
					int m2 = rand() % 15 + 1;
					int m3 = rand() % 5 + 1;
					if (map[m1][m2][m3] != sf::Vector2i(0, 0) && map[m1][m2][m3] != sf::Vector2i(1, 0) && map[m1][m2][m3] != sf::Vector2i(2, 0) && map[m1][m2][m3] != sf::Vector2i(3, 0) && map[m1][m2][m3] != sf::Vector2i(5, 0) && map[m1][m2][m3] != sf::Vector2i(6, 0) && map[m1][m2][m3] != sf::Vector2i(1, 1) && map[m1][m2][m3] != sf::Vector2i(2, 1) && map[m1][m2][m3] != sf::Vector2i(0, 2) && map[m1][m2][m3] != sf::Vector2i(1, 2) && map[m1][m2][m3] != sf::Vector2i(2, 2) && map[m1][m2][m3] != sf::Vector2i(3, 2) && map[m1][m2][m3] != sf::Vector2i(4, 2) && map[m1][m2][m3] != sf::Vector2i(5, 2) && map[m1][m2][m3] != sf::Vector2i(1, 4) && map[m1][m2][m3] != sf::Vector2i(3, 2) && map[m1][m2][m3] != sf::Vector2i(-1, -1)) {
						Tesouro[i] = sf::Vector3i(m1, m2, m3);
						pew = 1;
					}
				}
			}
			sf::Texture pZombie;
			sf::Sprite Zombie;
			sf::Texture pMascara;
			sf::Sprite Mascara;
			sf::Clock clock;
			sf::Time time = clock.getElapsedTime();
			sf::Time time2;
			sf::Time time3;
			sf::Time time4;
			if (!pZombie.loadFromFile("zombie.png"))
				std::cout << "Erro ao carregar zombie" << std::endl;
			Zombie.setTexture(pZombie);
			if (!pMascara.loadFromFile("visao.png"))
				std::cout << "Erro ao carregar mascara" << std::endl;
			Mascara.setTexture(pMascara);
			int ori = 0;
			int dir = 0;
			while (PlayWindow.isOpen()) {
				sf::Event EventP;
				time3 = clock.getElapsedTime();
				while (PlayWindow.pollEvent(EventP)) {
					time4 = sf::seconds(0.2 * ((pontos + 1)));
					time2 = time + time4;
					
					switch (EventP.type) {
					case sf::Event::Closed:
						PlayWindow.close();
					case sf::Event::KeyPressed:
					
						if (EventP.key.code == sf::Keyboard::Up && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved &&  clock.getElapsedTime() >= time2) {
							time = clock.getElapsedTime();
							if (Player.y > 0) {
								if (dir != 0) {
									dir = 0;
									ori = 0;
								}
								else {
									if (ori < 3)
										ori++;
									else
										ori = 0;
									int bzx = Player.x;
									int bzy = Player.y - 1;
									int bzz = Player.z;
									if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
										Player.y--;
								}
							}
						}
						else if (EventP.key.code == sf::Keyboard::Down && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved&&  clock.getElapsedTime() >= time2) {
							time = clock.getElapsedTime();
							if (Player.y < 14) {
								if (dir != 1) {
									dir = 1;
									ori = 0;
								}
								else {
									if (ori < 3)
										ori++;
									else
										ori = 0;
									int bzx = Player.x;
									int bzy = Player.y + 1;
									int bzz = Player.z;
									if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
										Player.y++;
								}
							}
						}
						else if (EventP.key.code == sf::Keyboard::Left && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved&&  clock.getElapsedTime() >= time2) {
							time = clock.getElapsedTime();
							if (Player.x > 0) {
								if (dir != 3) {
									dir = 3;
									ori = 0;
								}
								else {
									if (ori < 3)
										ori++;
									else
										ori = 0;
									int bzx = Player.x - 1;
									int bzy = Player.y;
									int bzz = Player.z;
									if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
										Player.x--;
								}
							}

						}
						else if (EventP.key.code == sf::Keyboard::Right && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved&&  clock.getElapsedTime() >= time2) {
							time = clock.getElapsedTime();
							if (Player.x < 24) {
								if (dir != 2) {
									dir = 2;
									ori = 0;
								}
								else {
									if (ori < 3)
										ori++;
									else
										ori = 0;
									int bzx = Player.x + 1;
									int bzy = Player.y;
									int bzz = Player.z;
									if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
										Player.x++;
								}
							}
						}
						else if(EventP.key.code == sf::Keyboard::Space && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
							if (escsb[Player.z].x == Player.x && escsb[Player.z].y == Player.y && Player.z >= 1) {
								Player.z--;
							}
							else if (escdc[Player.z].x == Player.x && escdc[Player.z].y == Player.y && Player.z <= 4) {
								Player.z++;
							}
						}
					default:
						break;
					}
				}
				PlayWindow.clear();

					for (int j = 0; j < 3; j++) {
						if (Player.x + j < 25) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y][Player.z].x * 32, map[Player.x + j][Player.y][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + j) * 32) + 10, (2 * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - j >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y][Player.z].x * 32, map[Player.x - j][Player.y][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - j) * 32) + 10, (2 * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.y + j < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x][Player.y + j][Player.z].x * 32, map[Player.x][Player.y + j][Player.z].y * 32, 32, 32));
							Tileset.setPosition((2 * 32) + 10, ((2 + j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.y - j >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x][Player.y - j][Player.z].x * 32, map[Player.x][Player.y - j][Player.z].y * 32, 32, 32));
							Tileset.setPosition((2  * 32) + 10, ((2 - j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + j < 25 && Player.y + j < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y + j][Player.z].x * 32, map[Player.x + j][Player.y + j][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + j) * 32) + 10, ((2 + j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - j >= 0 && Player.y - j >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y - j][Player.z].x * 32, map[Player.x - j][Player.y -j][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - j) * 32) + 10, ((2 - j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + j < 25 && Player.y - j >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y - j][Player.z].x * 32, map[Player.x + j][Player.y - j][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + j) * 32) + 10, ((2 - j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - j >= 0 && Player.y + j < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y + j][Player.z].x * 32, map[Player.x - j][Player.y + j][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - j) * 32) + 10, ((2 + j) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
					
				}
					if (Player.x - 2 >= 0 && Player.y + 1 < 15) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x - 2][Player.y + 1][Player.z].x * 32, map[Player.x - 2][Player.y + 1][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 - 2) * 32) + 10, ((2 + 1) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x + 1 < 25 && Player.y - 2 >= 0) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x + 1][Player.y - 2][Player.z].x * 32, map[Player.x + 1][Player.y - 2][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 + 1) * 32) + 10, ((2 - 2) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x - 1 >= 0 && Player.y + 2 < 15) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x - 1][Player.y + 2][Player.z].x * 32, map[Player.x - 1][Player.y + 2][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 - 1) * 32) + 10, ((2 + 2) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x + 2 < 25 && Player.y - 1 >= 0) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x + 2][Player.y - 1][Player.z].x * 32, map[Player.x + 2][Player.y - 1][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 + 2) * 32) + 10, ((2 - 1) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x + 2 < 25 && Player.y + 1 < 15) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x + 2][Player.y + 1][Player.z].x * 32, map[Player.x + 2][Player.y + 1][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 + 2) * 32) + 10, ((2 + 1) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x + 1 < 25 && Player.y + 2 < 15) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x + 1][Player.y + 2][Player.z].x * 32, map[Player.x + 1][Player.y + 2][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 + 1) * 32) + 10, ((2 + 2) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x - 2 >=0  && Player.y - 1 >= 0) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x - 2][Player.y - 1][Player.z].x * 32, map[Player.x - 2][Player.y - 1][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 - 2) * 32) + 10, ((2 - 1) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					if (Player.x - 1 >= 0 && Player.y - 2 >= 0) {
						Tileset.setTextureRect(sf::IntRect(map[Player.x - 1][Player.y - 2][Player.z].x * 32, map[Player.x - 1][Player.y - 2][Player.z].y * 32, 32, 32));
						Tileset.setPosition(((2 - 1) * 32) + 10, ((2 - 2) * 32) + 10);
						PlayWindow.draw(Tileset);
					}
					int ten = 0;
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++) {
							if (ten == 0) {
								if (Player.z == flag[2]) {
									if ((flag[0] == Player.x - 2 + j && flag[1] == Player.y - 2 + i) && flag[0] != -1 && flag[1] != -1 && flag[2] != -1) {
										fli.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
										PlayWindow.draw(fli);
										ten = 1;
									}
								}
							}
							if (Player.z >= 1 && escsb[Player.z].x != -1 && escsb[Player.z].y != -1) {
								if ((escsb[Player.z].x == Player.x - 2 + j && escsb[Player.z].y == Player.y - 2 + i)) {
									rs.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
									PlayWindow.draw(rs);
								}
							}
							if (Player.z <= 4 && escdc[Player.z].x != -1 && escdc[Player.z].y != -1) {
								if ((escdc[Player.z].x == Player.x - 2 + j && escdc[Player.z].y == Player.y - 2 + i)) {
									fl.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
									PlayWindow.draw(fl);
								}
							}
							for (int op = 0; op < 5; op++) {
								if (Player.z == Tesouro[op].z && Tesouro[op].x != -1) {
									if ((Tesouro[op].x == Player.x - 2 + j && Tesouro[op].y == Player.y - 2 + i)) {
										tsr.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
										PlayWindow.draw(tsr);
										if (Player.x == Tesouro[op].x && Player.y == Tesouro[op].y) {
											Tesouro[op].x = -1;
											pontos++;
										}
									}
								}
							}
						}
					}
				Zombie.setTextureRect(sf::IntRect(ori * 32, dir * 32, 32, 32));
				Zombie.setPosition(74, 74);
				PlayWindow.draw(Zombie);
				Mascara.setPosition(10, 10);
				PlayWindow.draw(Mascara);
				Text2.setPosition(10, 2);
				Text2.setString("Points:");
				PlayWindow.draw(Text2);
				Text2.setPosition(50, 2);
				std::string sax = std::to_string(pontos);
				Text2.setString(sax);
				PlayWindow.draw(Text2);
				Text2.setPosition(110, 2);
				Text2.setString("Time:");
				PlayWindow.draw(Text2);
				Text2.setPosition(150, 2);
				sax = std::to_string(time3.asSeconds());
				Text2.setString(sax);
				PlayWindow.draw(Text2);
				PlayWindow.display();
				if (Player.x == flag[0] && Player.y == flag[1] && Player.z == flag[2]) {
					time = clock.getElapsedTime();
					PlayWindow.clear();
					Text.setPosition(15, 50);
					std::string sx = std::to_string(time.asSeconds());
					Text.setString(sx);
					PlayWindow.draw(Text);
					PlayWindow.display();
					
					sf::sleep(sf::seconds(2.0f));
					PlayWindow.clear();
					PlayWindow.close();
				}
			}
			play = 0;
		}
				else if(play == 2){
					sf::RenderWindow PlayWindow(sf::VideoMode(180, 180), "Game");
					PlayWindow.setSize(sf::Vector2u(360, 360));
					sf::Vector3i Player = sf::Vector3i(respawn[0], respawn[1], respawn[2]);
					sf::Texture pZombie;
					sf::Sprite Zombie;
					sf::Texture pMascara;
					sf::Sprite Mascara;
					if (!pZombie.loadFromFile("zombie.png"))
						std::cout << "Erro ao carregar zombie" << std::endl;
					Zombie.setTexture(pZombie);
					if (!pMascara.loadFromFile("visao.png"))
						std::cout << "Erro ao carregar mascara" << std::endl;
					Mascara.setTexture(pMascara);
					int ori = 0;
					int dir = 0;
					while (PlayWindow.isOpen()) {
						sf::Event EventP;
						while (PlayWindow.pollEvent(EventP)) {
							switch (EventP.type) {
							case sf::Event::Closed:
								PlayWindow.close();
							case sf::Event::KeyPressed:

								if (EventP.key.code == sf::Keyboard::Up && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
									if (Player.y > 0) {
										if (dir != 0) {
											dir = 0;
											ori = 0;
										}
										else {
											if (ori < 3)
												ori++;
											else
												ori = 0;
											int bzx = Player.x;
											int bzy = Player.y - 1;
											int bzz = Player.z;
											if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
												Player.y--;
										}
									}
								}
								else if (EventP.key.code == sf::Keyboard::Down && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
									if (Player.y < 14) {
										if (dir != 1) {
											dir = 1;
											ori = 0;
										}
										else {
											if (ori < 3)
												ori++;
											else
												ori = 0;
											int bzx = Player.x;
											int bzy = Player.y + 1;
											int bzz = Player.z;
											if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
												Player.y++;
										}
									}
								}
								else if (EventP.key.code == sf::Keyboard::Left && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
									if (Player.x > 0) {
										if (dir != 3) {
											dir = 3;
											ori = 0;
										}
										else {
											if (ori < 3)
												ori++;
											else
												ori = 0;
											int bzx = Player.x - 1;
											int bzy = Player.y;
											int bzz = Player.z;
											if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
												Player.x--;
										}
									}

								}
								else if (EventP.key.code == sf::Keyboard::Right && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
									if (Player.x < 24) {
										if (dir != 2) {
											dir = 2;
											ori = 0;
										}
										else {
											if (ori < 3)
												ori++;
											else
												ori = 0;
											int bzx = Player.x + 1;
											int bzy = Player.y;
											int bzz = Player.z;
											if (map[bzx][bzy][bzz] != sf::Vector2i(0, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 0) && map[bzx][bzy][bzz] != sf::Vector2i(2, 0) && map[bzx][bzy][bzz] != sf::Vector2i(3, 0) && map[bzx][bzy][bzz] != sf::Vector2i(5, 0) && map[bzx][bzy][bzz] != sf::Vector2i(6, 0) && map[bzx][bzy][bzz] != sf::Vector2i(1, 1) && map[bzx][bzy][bzz] != sf::Vector2i(2, 1) && map[bzx][bzy][bzz] != sf::Vector2i(0, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 2) && map[bzx][bzy][bzz] != sf::Vector2i(2, 2) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(4, 2) && map[bzx][bzy][bzz] != sf::Vector2i(5, 2) && map[bzx][bzy][bzz] != sf::Vector2i(1, 4) && map[bzx][bzy][bzz] != sf::Vector2i(3, 2) && map[bzx][bzy][bzz] != sf::Vector2i(-1, -1))
												Player.x++;
										}
									}
								}
								else if (EventP.key.code == sf::Keyboard::Space && EventP.type != sf::Event::MouseEntered && EventP.type != sf::Event::MouseLeft && EventP.type != sf::Event::MouseMoved) {
									if (escsb[Player.z].x == Player.x && escsb[Player.z].y == Player.y && Player.z >= 1) {
										Player.z--;
									}
									else if (escdc[Player.z].x == Player.x && escdc[Player.z].y == Player.y && Player.z <= 4) {
										Player.z++;
									}
								}
							default:
								break;
							}
						}
						PlayWindow.clear();

						for (int j = 0; j < 3; j++) {
							if (Player.x + j < 25) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y][Player.z].x * 32, map[Player.x + j][Player.y][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 + j) * 32) + 10, (2 * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.x - j >= 0) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y][Player.z].x * 32, map[Player.x - j][Player.y][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 - j) * 32) + 10, (2 * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.y + j < 15) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x][Player.y + j][Player.z].x * 32, map[Player.x][Player.y + j][Player.z].y * 32, 32, 32));
								Tileset.setPosition((2 * 32) + 10, ((2 + j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.y - j >= 0) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x][Player.y - j][Player.z].x * 32, map[Player.x][Player.y - j][Player.z].y * 32, 32, 32));
								Tileset.setPosition((2 * 32) + 10, ((2 - j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.x + j < 25 && Player.y + j < 15) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y + j][Player.z].x * 32, map[Player.x + j][Player.y + j][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 + j) * 32) + 10, ((2 + j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.x - j >= 0 && Player.y - j >= 0) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y - j][Player.z].x * 32, map[Player.x - j][Player.y - j][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 - j) * 32) + 10, ((2 - j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.x + j < 25 && Player.y - j >= 0) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x + j][Player.y - j][Player.z].x * 32, map[Player.x + j][Player.y - j][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 + j) * 32) + 10, ((2 - j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}
							if (Player.x - j >= 0 && Player.y + j < 15) {
								Tileset.setTextureRect(sf::IntRect(map[Player.x - j][Player.y + j][Player.z].x * 32, map[Player.x - j][Player.y + j][Player.z].y * 32, 32, 32));
								Tileset.setPosition(((2 - j) * 32) + 10, ((2 + j) * 32) + 10);
								PlayWindow.draw(Tileset);
							}

						}
						if (Player.x - 2 >= 0 && Player.y + 1 < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - 2][Player.y + 1][Player.z].x * 32, map[Player.x - 2][Player.y + 1][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - 2) * 32) + 10, ((2 + 1) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + 1 < 25 && Player.y - 2 >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + 1][Player.y - 2][Player.z].x * 32, map[Player.x + 1][Player.y - 2][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + 1) * 32) + 10, ((2 - 2) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - 1 >= 0 && Player.y + 2 < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - 1][Player.y + 2][Player.z].x * 32, map[Player.x - 1][Player.y + 2][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - 1) * 32) + 10, ((2 + 2) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + 2 < 25 && Player.y - 1 >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + 2][Player.y - 1][Player.z].x * 32, map[Player.x + 2][Player.y - 1][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + 2) * 32) + 10, ((2 - 1) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + 2 < 25 && Player.y + 1 < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + 2][Player.y + 1][Player.z].x * 32, map[Player.x + 2][Player.y + 1][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + 2) * 32) + 10, ((2 + 1) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x + 1 < 25 && Player.y + 2 < 15) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x + 1][Player.y + 2][Player.z].x * 32, map[Player.x + 1][Player.y + 2][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 + 1) * 32) + 10, ((2 + 2) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - 2 >= 0 && Player.y - 1 >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - 2][Player.y - 1][Player.z].x * 32, map[Player.x - 2][Player.y - 1][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - 2) * 32) + 10, ((2 - 1) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						if (Player.x - 1 >= 0 && Player.y - 2 >= 0) {
							Tileset.setTextureRect(sf::IntRect(map[Player.x - 1][Player.y - 2][Player.z].x * 32, map[Player.x - 1][Player.y - 2][Player.z].y * 32, 32, 32));
							Tileset.setPosition(((2 - 1) * 32) + 10, ((2 - 2) * 32) + 10);
							PlayWindow.draw(Tileset);
						}
						int ten = 0;
						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								if (ten == 0) {
									if (Player.z == flag[2]) {
										if ((flag[0] == Player.x - 2 + j && flag[1] == Player.y - 2 + i) && flag[0] != -1 && flag[1] != -1 && flag[2] != -1) {
											fli.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
											PlayWindow.draw(fli);
											ten = 1;
										}
									}
								}
								if (Player.z >= 1 && escsb[Player.z].x != -1 && escsb[Player.z].y != -1) {
									if ((escsb[Player.z].x == Player.x - 2 + j && escsb[Player.z].y == Player.y - 2 + i)) {
										rs.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
										PlayWindow.draw(rs);
									}
								}
								if (Player.z <= 4 && escdc[Player.z].x != -1 && escdc[Player.z].y != -1) {
									if ((escdc[Player.z].x == Player.x - 2 + j && escdc[Player.z].y == Player.y - 2 + i)) {
										fl.setPosition(((j) * 32) + 10, ((i) * 32) + 10);
										PlayWindow.draw(fl);
									}
								}
							}
						}
						Zombie.setTextureRect(sf::IntRect(ori * 32, dir * 32, 32, 32));
						Zombie.setPosition(74, 74);
						PlayWindow.draw(Zombie);
						PlayWindow.display();
						if (Player.x == flag[0] && Player.y == flag[1] && Player.z == flag[2]) {
							PlayWindow.clear();
							Text.setPosition(15, 50);
							Text.setString("You Win");
							PlayWindow.draw(Text);
							PlayWindow.display();

							sf::sleep(sf::seconds(2.0f));
							PlayWindow.clear();
							PlayWindow.close();
						}
					}
					play = 0;
				}
	}
	return 0;
}