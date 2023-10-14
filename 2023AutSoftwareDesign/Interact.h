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


private:
	QQDataManage QQDataM;

};

