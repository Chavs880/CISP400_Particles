#include "Engine.h"
#include <iostream>

Engine::Engine() {
	Vector2f res;
	res.x = VideoMode::getDesktopMode().width;
	res.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(res.x, res.y), "Particle");
}

void Engine::run() {
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();

		float dtSec = dt.asSeconds();

		input();
		update(dtSec);
		draw();
	}
}

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			m_Window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			for (int i = 0; i < 5; i++) {
				//Particle particle(smth, random 25-50, mouseclickpos)
				int randomValue = 25 + (rand() % 26);
				Particle particle(m_Window, randomValue, Mouse::getPosition());
				m_particles.push_back(particle);
			}
		}
	}
}

void Engine::update(float dtAsSeconds) {
	for (auto i = m_particles.begin(); i != m_particles.end();) {
		if (i->getTTL() > 0) {
			i->update(dtAsSeconds);
			i++;
		}
		else {
			i = m_particles.erase(i);
		}
	}
}

void Engine::draw() {
	m_Window.clear();

	for (int i = 0; i < m_particles.size(); i++) {
		m_Window.draw(m_particles[i]);
	}

	m_Window.display();
}