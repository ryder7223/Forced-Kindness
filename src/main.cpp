#include <Geode/modify/LikeItemLayer.hpp>

using namespace geode::prelude;

class $modify(MyLikeItemLayer, LikeItemLayer) {
    // Redirect the dislike action to trigger the like behavior instead.
    void onDislike(CCObject* sender) {
        LikeItemLayer::triggerLike(true);
        return;
    }

    bool init(LikeItemType type, int id, int parentID) {
        if (!LikeItemLayer::init(type, id, parentID)) {
            return false;
        }

        // Find the existing like and dislike buttons in the layer
        auto like = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->m_mainLayer->querySelector("action-menu > like-button")
        );
        auto dislike = typeinfo_cast<CCMenuItemSpriteExtra*>(
            this->m_mainLayer->querySelector("action-menu > dislike-button")
        );

        // Do nothing if either button is missing
        if (!like || !dislike) return true;

        // Grab the like button callback and its normal sprite.
        auto likeHandler = like->m_pfnSelector;
        auto likeNormal = static_cast<CCSprite*>(like->getNormalImage());

        // Do nothing if the like button is invalid
        if (!likeHandler || !likeNormal) return true;

        // Create a new sprite copy from the like button's sprite frame.
        // (avoids double-parenting the same node under two buttons)
        auto newSprite = CCSprite::createWithSpriteFrame(likeNormal->displayFrame());
        newSprite->setAnchorPoint(likeNormal->getAnchorPoint());
        newSprite->ignoreAnchorPointForPosition(likeNormal->isIgnoreAnchorPointForPosition());
        newSprite->setScale(likeNormal->getScale());

        // Apply the like button attributes to the new button
        dislike->m_pfnSelector = likeHandler;
        dislike->setNormalImage(newSprite);
        dislike->getNormalImage()->setPosition(0, 0);
        dislike->updateSprite();

        return true;
    }
};
