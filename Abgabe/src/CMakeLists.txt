# Assets
set(AssetSources
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/AssetLoader.cpp
	)

# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropMoveable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/properties/PropSprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Bullet.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/properties/PropDrawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayerControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BulletControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/UIControl.cpp
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
        ${AssetSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )