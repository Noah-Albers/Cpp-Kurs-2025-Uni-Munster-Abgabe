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

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    )

# add src code to target
add_executable(SpaceInvaders
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )