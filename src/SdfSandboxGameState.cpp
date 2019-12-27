
#include "SdfSandboxGameState.h"
#include "CameraController.h"
#include "GraphicsSystem.h"

#include "OgreItem.h"
#include "OgreSceneManager.h"

#include "OgreMesh2.h"
#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"

#include "OgreCamera.h"
#include "OgreWindow.h"

#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"
#include "OgreRoot.h"

#include "OgreHlmsCompute.h"
#include "OgreHlmsComputeJob.h"

using namespace Demo;

namespace Demo
{
	SdfSandboxGameState::SdfSandboxGameState( const Ogre::String &helpDescription ) :
		TutorialGameState( helpDescription ),
		mSdfJob( 0 )
	{
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::createScene01( void )
	{
		mCameraController = new CameraController( mGraphicsSystem, false );

		Ogre::HlmsCompute *hlmsCompute = mGraphicsSystem->getRoot()->getHlmsManager()->getComputeHlms();
		mSdfJob = hlmsCompute->findComputeJob( "SdfRenderer" );

		TutorialGameState::createScene01();
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::update( float timeSinceLast )
	{
		Ogre::ShaderParams &shaderParams = mSdfJob->getShaderParams( "default" );
		shaderParams.setDirty();

		Ogre::Quaternion camRot = mGraphicsSystem->getCamera()->getDerivedOrientation();
//		camRot = camRot.Inverse();
		Ogre::Matrix3 camRot3x3;
		camRot.ToRotationMatrix( camRot3x3 );

		shaderParams.mParams[0].setManualValue( mGraphicsSystem->getCamera()->getDerivedPosition() );
		shaderParams.mParams[1].setManualValue( camRot3x3 );

		TutorialGameState::update( timeSinceLast );
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::generateDebugText( float timeSinceLast, Ogre::String &outText )
	{
		TutorialGameState::generateDebugText( timeSinceLast, outText );
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::keyReleased( const SDL_KeyboardEvent &arg )
	{
		if( ( arg.keysym.mod & ~( KMOD_NUM | KMOD_CAPS ) ) != 0 )
		{
			TutorialGameState::keyReleased( arg );
			return;
		}

		TutorialGameState::keyReleased( arg );
	}
}  // namespace Demo
