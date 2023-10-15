#pragma once

#include "AccountGroupDataManage.h"


class Interact
{
public:

	// 这是起始菜单
	virtual std::string showStartMenu();

	// 这是注册界面
	virtual std::string showSignUpPage() { return ""; }

	// 这是登录界面
	virtual std::string showSignInPage(){ return ""; }

	// 这是登录后的界面
	virtual std::string showAfterSignInMenu(){ return ""; }

	// 这是注销的界面
	virtual std::string showLogOffMenu() { return ""; }


	// 输入检测与限制
	// 纯数字,可限制输入字符数
	static std::string inputAllInt(int maxLen = 100, int minNum = 0, int maxNum = 9);
	// 数字与英文字母，可限制输入字符数
	static std::string inputEWordAndInt(int maxNum = 100, bool pwdSwitch = false);
	// 所有字符
	// static std::string inputNormal();

	//任意键继续然后清屏
	static void pauseAndClearScreen();
	
};


class QQInteract : public Interact
{
public:
	// 这是QQ开始界面
	std::string showStartMenu();

	// 这是QQ注册界面
	std::string showSignUpPage();

	// 这是QQ登录界面
	std::string showSignInPage();

	// 这是QQ登录后的界面
	std::string showAfterSignInMenu();

	// 这是QQ好友的界面
	std::string showQQFriendPage();

	// 这是添加QQ好友的界面
	std::string addQQFriendPage();

	// 这是查询QQ好友的界面
	std::string searchQQFriendPage();

	// 这是删除QQ好友的界面
	std::string delQQFriendPage();

	// 这是注销的界面
	std::string showLogOffMenu();

	// 这是QQ群的界面
	std::string showQQGroupPage();

	// 这是编辑Q群的界面
	std::string editQQGroupPage();

	// 这是加入Q群的界面
	std::string joinQQGroupPage();

	// 这是创建Q群的界面
	std::string createQQGroupPage();

	// 这是退出Q群的界面
	std::string exitQQGroupPage();

	// 这是查询Q群的界面
	std::string searchQQGroupPage();

	// 这是给Q群邀请好友的界面
	std::string inviteFriendToQQGroupPage();

	// 这是删除Q群的界面
	std::string delQQGroupPage();

	// 这是QQ用户设置界面
	std::string showQQSettingPage();


private:
	QQDataManage QQDataM;

};



class WechatInteract : public Interact
{
public:
	// 这是Wechat开始界面
	std::string showStartMenu();

	// 这是Wechat注册界面
	std::string showSignUpPage();

	// 这是Wechat登录界面
	std::string showSignInPage();

	// 这是Wechat登录后的界面
	std::string showAfterSignInMenu();

	// 这是Wechat好友的界面
	std::string showWechatFriendPage();

	// 这是添加Wechat好友的界面
	std::string addWechatFriendPage();

	// 这是查询Wechat好友的界面
	std::string searchWechatFriendPage();

	// 这是删除Wechat好友的界面
	std::string delWechatFriendPage();

	// 这是注销的界面
	std::string showLogOffMenu();

	// 这是Wechat群的界面
	std::string showWechatGroupPage();

	// 这是编辑Wechat群的界面
	std::string editWechatGroupPage();

	// 这是加入Wechat群的界面
	std::string joinWechatGroupPage();

	// 这是创建Wechat群的界面
	std::string createWechatGroupPage();

	// 这是退出Wechat群的界面
	std::string exitWechatGroupPage();

	// 这是查询Wechat群的界面
	std::string searchWechatGroupPage();

	// 这是给Wechat群邀请好友的界面
	std::string inviteFriendToWechatGroupPage();

	// 这是删除Wechat群的界面
	std::string delWechatGroupPage();

	// 这是Wechat用户设置界面
	std::string showWechatSettingPage();


private:
	WechatDataManage WechatDataM;

};



class WeiboInteract : public Interact
{
public:
	// 这是Weibo开始界面
	std::string showStartMenu();

	// 这是Weibo注册界面
	std::string showSignUpPage();

	// 这是Weibo登录界面
	std::string showSignInPage();

	// 这是Weibo登录后的界面
	std::string showAfterSignInMenu();

	// 这是Weibo好友的界面
	std::string showWeiboFriendPage();

	// 这是添加Weibo好友的界面
	std::string addWeiboFriendPage();

	// 这是查询Weibo好友的界面
	std::string searchWeiboFriendPage();

	// 这是删除Weibo好友的界面
	std::string delWeiboFriendPage();

	// 这是注销的界面
	std::string showLogOffMenu();

	// 这是Weibo群的界面
	std::string showWeiboGroupPage();

	// 这是编辑Weibo群的界面
	std::string editWeiboGroupPage();

	// 这是加入Weibo群的界面
	std::string joinWeiboGroupPage();

	// 这是创建Weibo群的界面
	std::string createWeiboGroupPage();

	// 这是退出Weibo群的界面
	std::string exitWeiboGroupPage();

	// 这是查询Weibo群的界面
	std::string searchWeiboGroupPage();

	// 这是给Weibo群邀请好友的界面
	std::string inviteFriendToWeiboGroupPage();

	// 这是删除Weibo群的界面
	std::string delWeiboGroupPage();

	// 这是Weibo用户设置界面
	std::string showWeiboSettingPage();


private:
	WeiboDataManage WeiboDataM;

};

