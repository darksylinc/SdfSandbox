
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

#include "OgreGpuProgramManager.h"
#include "OgreHlmsCompute.h"
#include "OgreHlmsComputeJob.h"

#define ASSETSYS_IMPLEMENTATION
#include "assetsys.h"
#define CUTE_FILEWATCH_IMPLEMENTATION
#include "cute_filewatch.h"

using namespace Demo;

namespace Demo
{
	static void watchCallback( filewatch_update_t change, const char *virtualPath, void *udata )
	{
		SdfSandboxGameState *gameState = reinterpret_cast<SdfSandboxGameState *>( udata );
		gameState->_watchCallback( change, virtualPath );
	}

	SdfSandboxGameState::SdfSandboxGameState( const Ogre::String &helpDescription ) :
		TutorialGameState( helpDescription ),
		m_sdfJob( 0 ),
		m_assetSys( 0 ),
		m_filewatch( 0 )
	{
		m_assetSys = assetsys_create( 0 );
		m_filewatch = filewatch_create( m_assetSys, 0 );

		filewatch_mount( m_filewatch, "../Data/UserFiles", "/userfiles" );
		filewatch_start_watching( m_filewatch, "/userfiles", watchCallback, this );
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::createScene01()
	{
		mCameraController = new CameraController( mGraphicsSystem, false );
		mCameraController->mCameraBaseSpeed = 2.0f;

		mGraphicsSystem->getCamera()->setPosition( 0, 1.0, 2.0 );

		Ogre::HlmsCompute *hlmsCompute = mGraphicsSystem->getRoot()->getHlmsManager()->getComputeHlms();
		m_sdfJob = hlmsCompute->findComputeJob( "SdfRenderer" );

		TutorialGameState::createScene01();
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::destroyScene()
	{
		filewatch_stop_watching( m_filewatch, "/data" );

		filewatch_free( m_filewatch );
		assetsys_destroy( m_assetSys );

		TutorialGameState::destroyScene();
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::update( float timeSinceLast )
	{
		Ogre::ShaderParams &shaderParams = m_sdfJob->getShaderParams( "default" );
		shaderParams.setDirty();

		Ogre::Quaternion camRot = mGraphicsSystem->getCamera()->getDerivedOrientation();
		//		camRot = camRot.Inverse();
		Ogre::Matrix3 camRot3x3;
		camRot.ToRotationMatrix( camRot3x3 );

		shaderParams.mParams[0].setManualValue( mGraphicsSystem->getCamera()->getDerivedPosition() );
		shaderParams.mParams[1].setManualValue( camRot3x3 );

		filewatch_update( m_filewatch );
		filewatch_notify( m_filewatch );

		TutorialGameState::update( timeSinceLast );
	}
	//-----------------------------------------------------------------------------------
	void SdfSandboxGameState::_watchCallback( uint32_t _change, const char *virtualPath )
	{
		const filewatch_update_t change = static_cast<filewatch_update_t>( _change );
		if( change == FILEWATCH_FILE_MODIFIED &&
			strcmp( virtualPath, "/userfiles/CustomSdf_piece_cs.any" ) == 0 )
		{
			// Hot reload Compute shaders.
			Ogre::Root *root = mGraphicsSystem->getRoot();
			Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

			Ogre::Hlms *hlms = hlmsManager->getComputeHlms();
			Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
			hlms->reloadFrom( hlms->getDataFolder() );
		}
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
