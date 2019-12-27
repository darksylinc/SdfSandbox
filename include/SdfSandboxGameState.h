
#ifndef _Demo_SdfSandboxGameState_H_
#define _Demo_SdfSandboxGameState_H_

#include "OgrePrerequisites.h"

#include "TutorialGameState.h"

#include <stdint.h>

struct assetsys_t;
struct filewatch_t;

namespace Demo
{
	class SdfSandboxGameState : public TutorialGameState
	{
		Ogre::HlmsComputeJob *m_sdfJob;

		assetsys_t *m_assetSys;
		filewatch_t *m_filewatch;

		virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );

	public:
		SdfSandboxGameState( const Ogre::String &helpDescription );

		virtual void createScene01();
		virtual void destroyScene();

		virtual void update( float timeSinceLast );

		void _watchCallback( uint32_t change, const char *virtualPath );

		virtual void keyReleased( const SDL_KeyboardEvent &arg );
	};
}  // namespace Demo

#endif
