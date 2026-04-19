#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    void onDislike(CCObject* sender) {
        LikeItemLayer::triggerLike(true);
        return;
    }
    bool init(LikeItemType type, int id, int parentID) {
        if (!LikeItemLayer::init(type, id, parentID)) return false;

        auto like = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->m_mainLayer->querySelector("action-menu > like-button")
        );
        auto dislike = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->m_mainLayer->querySelector("action-menu > dislike-button")
        );

        if (!like || !dislike) return true;

        auto likeHandler = like->m_pfnSelector;
        auto likeNormal = like->getNormalImage();

        if (!likeHandler || !likeNormal) return true;

        dislike->m_pfnSelector = likeHandler;
        dislike->setNormalImage(likeNormal);
        dislike->updateSprite();

        return true;
    }
};
