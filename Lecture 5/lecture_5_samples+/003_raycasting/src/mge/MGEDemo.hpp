#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include <mge/core/AbstractGame.hpp>

class DebugHud;
class AbstractMaterial;

class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo();
		virtual ~MGEDemo();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

		AbstractMaterial* _normalMaterial;
		AbstractMaterial* _hitMaterial;

        void _updateHud();

        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
