cmake_minimum_required(VERSION 3.14)
project(2DEngine)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_NAME "2DEngine")
set(SFML_DIR "C:\\Program Files\\SFM251\\SFML-2.5.1-sources\\SFML-2.5.1\\buildSFML")
set(TGUI_DIR "C:\\Program Files\\mingw-w64\\mingw64-posix\\TGUI-0.9\\lib\\cmake\\TGUI")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(TGUI REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Box2D)
message(${CMAKE_SOURCE_DIR})
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/ltbl)

add_executable(${EXECUTABLE_NAME} main.cpp Game.cpp Game.h Window.cpp Window.h WorkingDirectory.cpp WorkingDirectory.h BitMask.cpp BitMask.h Input.cpp Input.h Scene.cpp Scene.h SceneStateMachine.cpp SceneStateMachine.h SceneSplashScreen.cpp SceneSplashScreen.h SceneGame.cpp SceneGame.h Object.cpp Object.h Component.cpp Component.h C_Sprite.cpp C_Sprite.h C_Transform.cpp C_Transform.h C_KeyboardMovement.cpp C_KeyboardMovement.h ResourceAllocator.cpp ResourceAllocator.h ObjectCollection.cpp ObjectCollection.h Animation.cpp Animation.h C_Animation.cpp C_Animation.h rapidxml.hpp rapidxml_iterators.hpp rapidxml_print.hpp rapidxml_utils.hpp Tile.cpp Tile.h TileMapParser.cpp TileMapParser.h Utilities.cpp Utilities.h C_Drawable.cpp C_Drawable.h S_Drawable.cpp S_Drawable.h C_Collider.cpp C_Collider.h C_BoxCollider.cpp C_BoxCollider.h C_InstanceID.cpp C_InstanceID.h S_Collidable.cpp S_Collidable.h Debug.cpp Debug.h C_Camera.cpp C_Camera.h C_ProjectileAttack.cpp C_ProjectileAttack.h C_Velocity.cpp C_Velocity.h C_MovementAnimation.cpp C_MovementAnimation.h SharedContext.cpp SharedContext.h C_Direction.cpp C_Direction.h C_Collidable.cpp C_Collidable.h ComponentPairHash.cpp ComponentPairHash.h C_RemoveObjectOnCollisionEnter.cpp C_RemoveObjectOnCollisionEnter.h C_SpriteStatic.cpp C_SpriteStatic.h PhysicsDebugRenderer.cpp PhysicsDebugRenderer.h Box2DContactListener.cpp Box2DContactListener.h S_LightSystem.cpp S_LightSystem.h Texture.cpp Texture.h SpriteBatch.cpp SpriteBatch.h C_EllipseCollider.cpp C_EllipseCollider.h C_Interactable.cpp C_Interactable.h RayCastCallback.cpp RayCastCallback.h)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics tgui ${CMAKE_SOURCE_DIR}/libBox2D.a ${CMAKE_SOURCE_DIR}/libLTBL2.a)