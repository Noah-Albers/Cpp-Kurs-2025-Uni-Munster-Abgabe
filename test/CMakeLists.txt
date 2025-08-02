enable_testing()

# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropMoveable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropSprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropAnimatedSprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/AlienBullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Alien.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Bullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Meteor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Particle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/game/Shield.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/Background.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/Deathmessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/Healthbar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/Scoreboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/Shieldbar.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/properties/PropDrawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/AlienBulletControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/AlienControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/BulletControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/LevelControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/MeteorControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/ParticleControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/PlayerControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/controls/UIControl.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/CommonMockClasses.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AlienBulletControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/AlienControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BulletControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/LevelControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/MeteorControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/ParticleControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayerControlTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/UiControlTest.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/model/AlienBulletTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/AlienTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/BulletTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/MeteorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/ParticleTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/PlayerTest.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/BackgroundTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/interface/CommonInterfaceTest.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropAnimatedSpriteTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropMoveableTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropSpriteTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )
