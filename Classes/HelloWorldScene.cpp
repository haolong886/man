#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //使能触摸事件
    this->setTouchEnabled(true);
    CCLOG("touch enabled");

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 40);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    _abel =  CCSprite::create("CloseNormal.png");
    _abel->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(_abel, 2);
    _helper = new GameHelper();
    

    return true;
}

void HelloWorld::registerWithTouchDispatcher()
{
    CCLOG("register ok");
    //Standard Touch
    //CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 5);
    //Targeted Touch
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("touch begin");
    this->_touchBegin = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    _gd_direction = kGDirectionNo;
    for (int i = 0 ; i < 4 ; i++)
    {
        _cache_directionshape[i] = false;
    }
    return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("touch moved");
    _nowPos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    float adsx = _nowPos.x - _touchBegin.x;
    float adsy = _nowPos.y - _touchBegin.y;
    if(abs(adsx) > abs(adsy))   //X方向增量大
    {
        if(adsx < 0)   //左移;
            _cache_directionshape[0] = 1;
        else
            _cache_directionshape[1] = 1;
    }
    else
    {
        if(adsy < 0)
            _cache_directionshape[2] = 1;
        else
            _cache_directionshape[3] = 1;
    }
    int x = 0;
    for (int i = 0 ; i< 4 ; i++)
    {
        if(_cache_directionshape[i])
            x++;
    }
}
void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("touch ended");
    float adsx = _nowPos.x - _touchBegin.x;
    float adsy = _nowPos.y - _touchBegin.y;
    if(abs(adsx) > abs(adsy))   //X方向增量大
    {
        if(adsx < 0){
            CCLOG("direction left");
            this->backProc(LEFT);
            _gd_direction = kGDirectionLeft;
        }
        else{
            CCLOG("direction right");
            this->backProc(RIGHT);
            _gd_direction = kGDirectionRight;
        }
    }
    else
    {
        if(adsy < 0){
            _gd_direction = kGDirectionUp;
            
            CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
            CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

            CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 40);
            // position the label on the center of the screen
            pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                    origin.y + pLabel->getContentSize().height));
            
            // add the label as a child to this layer
            this->addChild(pLabel, 1);

            CCLOG("direction up");
            this->backProc(UP);
        }
        else{
            CCLOG("direction down");
            this->backProc(DOWN);
            
        }
    }
    
    
}
void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void HelloWorld::backProc(Status dir)
{
    std::vector<Location> vPos = _helper->go(dir);
    for(int i = 0; i < vPos.size() - 1; ++i)
    {
        CCLog("%d %d sta=%d\n", vPos[i].row, vPos[i].col, (int)vPos[i].st);
        this->updateAbel(vPos[i].row, vPos[i].col, (int)vPos[i].st);
    }
    
}

void HelloWorld::updateAbel(int r, int c, int st)
{
    //convert pos code
    //_abel->setPosition(ccp(x, y));
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    delete _helper;
    exit(0);
#endif
#endif
}
