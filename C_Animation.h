//
// Created by root on 01.09.19.
//

#ifndef INC_2DENGINE_C_ANIMATION_H
#define INC_2DENGINE_C_ANIMATION_H

#include <unordered_map>
#include "Component.h"
#include "Animation.h"
#include "C_Sprite.h"
#include "C_Direction.h"
#include "Object.h"
using AnimationList =
        std::unordered_map<FacingDirection,std::shared_ptr<Animation>>;
enum class AnimationState
{
    None,Idle,Walk,Projectile
};
class C_Animation: public Component {
public:
    C_Animation(Object* owner);
    void Awake() override;
    void Update(float deltaTime) override;
    void AddAnimation(AnimationState state,
            AnimationList& animationList);
    void AddAnimationAction(AnimationState state,FacingDirection dir, int frame, AnimationAction aciton);
    void SetAnimationState(AnimationState state);
    const AnimationState& GetAnimationState() const;
    void SetAnimationDirection(FacingDirection dir);
    FacingDirection  GetCurrentDiection();
private:
    std::shared_ptr<C_Sprite> sprite;
    std::unordered_map<AnimationState, AnimationList > animations;
    FacingDirection currentDirection;
    std::pair<AnimationState ,std::shared_ptr<Animation>> currentAnimation;
    std::shared_ptr<C_Direction> direction;

};


#endif //INC_2DENGINE_C_ANIMATION_H
