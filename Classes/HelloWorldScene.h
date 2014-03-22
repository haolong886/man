#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameHelper.h"

enum GDirection        //当前手势方向;
{
    kGDirectionUp = 0,
    kGDirectionDown,
    kGDirectionLeft,
    kGDirectionRight,
    kGDirectionNo
};

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void registerWithTouchDispatcher();
    //重写单点触屏处理事件
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
//    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);


    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
private:
    bool _moved;
    cocos2d::CCPoint _touchBegin;
    bool _cache_directionshape[4];   //方向缓存，move中用它来判断是否是单向手势
    GDirection _gd_direction;        //手势方向;
    cocos2d::CCPoint _nowPos;
    cocos2d::CCSprite* _abel;
    GameHelper *_helper;
    void backProc(Status);
    void updateAbel(int r, int c, int st);
    

};

#endif // __HELLOWORLD_SCENE_H__
