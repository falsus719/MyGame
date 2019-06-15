/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	sprite = Sprite::create("base008.png");
	sprite2 = Sprite::create("Razer.png");
	this->addChild(sprite);
	this->addChild(sprite2);
	//sprite->setPosition(Vec2(650, 350));
	sprite->setPosition(Vec2(1100, 550));
	sprite->setColor(Color3B(255, 255, 255));
	sprite->setOpacity((int)255);
	sprite->setScale(3.0f);

	sprite2->setPosition(Vec2(1100, 550));
	sprite2->setColor(Color3B(255, 255, 255));
	sprite2->setOpacity((int)255);
	sprite2->setScale(0.5);

	sprite->setTextureRect(Rect(0, 32, 32, 32));
	sprite->getTexture()->setAliasTexParameters();

	//画像の左下が(0,0)
	//画像の右上が(1,0)の座標系で
	//基準点を指定する
	sprite->setAnchorPoint(Vec2(0.0f, 1.0f));

	//sprite->setRotation(45.0f);

	//updateを有効化する
	this->scheduleUpdate();

	counter = 0;
	counter2 = 0;

	colg = 0.0f;
	colb = 0.0f;
	rot = 0.0f;
	blue = 0.0f;
	opacity = 0.0f;

	state = 0;

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::update(float delta)
{
	/*counter++;
	float opacity = 255 - (counter / 300.0f * 255.0f);
	if (opacity < 0)
	{
		opacity = 0.0f;
	}
	sprite->setOpacity(opacity);*/

	//rot = rot + 2;
	//sprite->setRotation(rot);

	//180フレームかけて255になる
	blue += 255.0f / 180.0f;
	//最大値を超えないように制限する
	if (blue > 255.0f)
	{
		blue = 255.0f;
	}
	//赤と青の数値が逆の動き
	sprite->setColor(Color3B(255 - blue, 0, blue));

	opacity += 1.0f;
	if (opacity > 255.0f)
	{
		opacity = 255.0f;
	}

	//spriteがフェードアウト
	sprite->setOpacity(255 - opacity);
	//sprite2がフェードアウト
	sprite2->setOpacity(opacity);

	Vec2 pos;

	switch (state)
	{
		//左移動
	case 0:
		pos = sprite->getPosition();
		pos += Vec2(-5.0f, 0.0f);
		sprite->setPosition(pos);
		//左端に達したら
		if (pos.x <= 110) { state = 1; }
		break;
		//下移動
	case 1:
		pos = sprite->getPosition();
		pos += Vec2(-0.0f, -5.0f);
		sprite->setPosition(pos);
		//下端に達したら
		if (pos.y <= 150) { state = 2; }
		break;
		//右移動
	case 2:
		pos = sprite->getPosition();
		pos += Vec2(5.0f, 0.0f);
		sprite->setPosition(pos);
		//右端に達したら
		if (pos.x >= 1180) { state = 3; }
		break;
		//上移動
	case 3:
		pos = sprite->getPosition();
		pos += Vec2(0.0f, 5.0f);
		sprite->setPosition(pos);
		//上端に達したら
		if (pos.y >= 550) { state = 0; }
		break;
	default:
		break;
	}
}
