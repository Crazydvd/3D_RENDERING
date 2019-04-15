#ifndef ASSIGNMENT3_HPP
#define ASSIGNMENT3_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class Assignment3: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		Assignment3();
		virtual ~Assignment3();

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

        Assignment3(const Assignment3&);
        Assignment3& operator=(const Assignment3&);
};

#endif // ASSIGNMENT3_HPP
