#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class Assignment: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		Assignment();
		virtual ~Assignment();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        Assignment(const Assignment&);
        Assignment& operator=(const Assignment&);
};

#endif // ASSIGNMENT_HPP
