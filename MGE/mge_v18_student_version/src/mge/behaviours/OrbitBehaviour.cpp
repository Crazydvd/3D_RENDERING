#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"

OrbitBehaviour::OrbitBehaviour(float pDistance, float pMaxTiltAngle, float pRotationSpeed, GameObject & pTarget) : AbstractBehaviour(), _distance(pDistance), _maxTiltAngle(glm::radians(pMaxTiltAngle)), _rotationSpeed(pRotationSpeed), _target(&pTarget)
{
	_first = true;
}

OrbitBehaviour::~OrbitBehaviour()
{
	delete _target;
}

void OrbitBehaviour::update(float pStep)
{
	//_target->translate(glm::vec3(0.0009, 0, 0));

	reset();

	if (checkMouseButton())
	{
		if (getMouseButtonDown())
		{
			_oldPos = getMousePosition();
		}

		_mousePos = getMousePosition();
		rotate();

		_pressed = true;
		return;
	}

	_pressed = false;
}

void OrbitBehaviour::reset()
{
	if (_first)
	{
		_owner->setTransform(_target->getTransform());
		_owner->translate(glm::vec3(0, 0, _distance));
		_first = false;
		return;
	}

	glm::mat4 transform = _owner->getTransform();
	transform[3] = _target->getWorldTransform()[3];
	_owner->setTransform(transform);
	_owner->translate(glm::vec3(0, 0, _distance));
}

glm::vec2 OrbitBehaviour::getMousePosition()
{
	sf::Vector2i mouse(sf::Mouse::getPosition());
	return glm::vec2(mouse.x, mouse.y);
}

bool OrbitBehaviour::checkMouseButton()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool OrbitBehaviour::checkMouseButton(sf::Mouse::Button pButton)
{
	return sf::Mouse::isButtonPressed(pButton);
}

bool OrbitBehaviour::getMouseButtonDown()
{
	if (!_pressed)
	{
		return checkMouseButton();
	}

	return false;
}

void OrbitBehaviour::rotate()
{
	_owner->translate(glm::vec3(0, 0, -_distance));

	_delta = _mousePos - _oldPos;
	_owner->rotate(rotateX(10) * glm::radians(0.5f * _rotationSpeed), glm::vec3(1, 0, 0));
	_owner->rotate(rotateY(10) * glm::radians(0.5f * _rotationSpeed), glm::vec3(0, 1, 0));

	_owner->translate(glm::vec3(0, 0, _distance));
}

int OrbitBehaviour::rotateX(float pDeadzone)
{
	float dot = glm::dot(_delta, glm::vec2(0, 1));

	if (dot > pDeadzone && _xRotation < _maxTiltAngle)
	{
		_xRotation += glm::radians(_rotationSpeed / 2);
		return 1;
	}
	else if (dot < -pDeadzone && _xRotation > -_maxTiltAngle)
	{
		_xRotation -= glm::radians(_rotationSpeed / 2);
		return -1;
	}
	else
	{
		return 0;
	}
}

int OrbitBehaviour::rotateY(float pDeadzone)
{
	float dot = glm::dot(_delta, glm::vec2(1, 0));

	if (dot > pDeadzone)
	{
		return 1;
	}
	else if (dot < -pDeadzone)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
