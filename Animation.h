//
// Created by root on 01.09.19.
//

#ifndef INC_2DENGINE_ANIMATION_H
#define INC_2DENGINE_ANIMATION_H

#include <vector>
#include <functional>
#include <map>
#include "BitMask.h"

struct FrameData
{
    int id;
    int x;
    int y;
    int width;
    int height;
    float displayTimeSeconds;
};
enum class FacingDirection
{
    None,
    Left,
    Right,
    Up,
    Down
};
using AnimationAction = std::function<void(void)>;

class Animation {
public:
    Animation();
    void SetLooped(bool looped);
    bool IsLooped();
    void AddFrameAction(unsigned int frame,AnimationAction action);
    void  AddFrame(int textureID,int x, int y,int width, int height, float frameTime,bool looped);
    const FrameData* GetCurrentFrame() const;
    bool UpdateFrame(float deltaTime);
    void Reset();


private:
    bool isLooped;
    BitMask framesWithActions;
    void RunActionForCurrentFrame();
    void IncrementFrame();
    bool releaseFirstFrame;
    std::vector<FrameData> frames;
    int currentFrameIndex;
    float currentFrameTime;
    std::map<int, std::vector<AnimationAction >> actions;


};


#endif //INC_2DENGINE_ANIMATION_H
