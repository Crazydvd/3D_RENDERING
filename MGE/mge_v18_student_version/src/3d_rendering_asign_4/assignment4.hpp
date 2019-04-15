#ifndef ASSIGNMENT4_HPP
#define ASSIGNMENT4_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class Assignment4: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		Assignment4();
		virtual ~Assignment4();

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

        Assignment4(const Assignment4&);
        Assignment4& operator=(const Assignment4&);
};

#endif // ASSIGNMENT3_HPP
