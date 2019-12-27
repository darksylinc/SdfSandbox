
#ifndef _Demo_SdfSandboxGameState_H_
#define _Demo_SdfSandboxGameState_H_

#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

namespace Demo
{
	class SdfSandboxGameState : public TutorialGameState
	{
		Ogre::HlmsComputeJob *mSdfJob;

		virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );

	public:
		SdfSandboxGameState( const Ogre::String &helpDescription );

		virtual void createScene01( void );

		virtual void update( float timeSinceLast );

		virtual void keyReleased( const SDL_KeyboardEvent &arg );
	};
}  // namespace Demo

#endif
