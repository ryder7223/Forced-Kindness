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
        auto likeNormal = static_cast<CCSprite*>(like->getNormalImage());

        if (!likeHandler || !likeNormal) return true;

        auto newSprite = CCSprite::createWithTexture(likeNormal->getTexture());
        newSprite->setTextureRect(
            likeNormal->getTextureRect(),
            likeNormal->isTextureRectRotated(),
            likeNormal->getContentSize()
        );
        newSprite->setScale(likeNormal->getScale());
        newSprite->setFlipX(likeNormal->isFlipX());
        newSprite->setFlipY(likeNormal->isFlipY());
        dislike->m_pfnSelector = likeHandler;
        dislike->setNormalImage(newSprite);
        dislike->getNormalImage()->setPosition(0, 0);
        dislike->updateSprite();

        return true;
    }
};
