#ifndef ORBITBEHAVIOUR_HPP
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include <SFML/Window.hpp>

class GameObject;

class OrbitBehaviour : public AbstractBehaviour
{
public:
	OrbitBehaviour(float pDistance, float pMaxTiltAngle, float pRotationSpeed, GameObject& pTarget);
	~OrbitBehaviour();

	virtual void update(float pStep);

private:
	void reset();
	glm::vec2 getMousePosition();
	bool checkMouseButton();
	bool checkMouseButton(sf::Mouse::Button pButton);
	bool keyPressed();
	bool keyPressed(sf::Keyboard::Key pKey);

	bool getMouseButtonDown();

	void rotate();
	int rotateX(float pDeadzone);
	int rotateY(float pDeadzone);

	float _oldDistance = 0;
	float _distance = 0;
	float _maxTiltAngle = 0;
	float _rotationSpeed = 1;
	float _xRotation = 0;
	bool _pressed;

	bool _first = false;

	GameObject* _target;
	
	glm::vec2 _mousePos;
	glm::vec2 _oldPos;
	glm::vec2 _delta;
};

#endif // !ORBITBEHAVIOUR_HPP