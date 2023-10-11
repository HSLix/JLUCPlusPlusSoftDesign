#pragma once



class Interact
{
public:

	// 这是起始菜单
	void showStartMenu();

	// 这是注册界面
	virtual void showSignUpPage() = 0;

	// 这是登录界面
	virtual void showSignInPage() = 0;

	// 这是登录后的界面
	virtual void showMainMenu() = 0; 


	// 输入检测与限制
	// 纯数字,可限制输入字符数
	static std::string inputAllInt(int maxNum = 100);
	// 数字与英文字母，可限制输入字符数
	static std::string inputEWordAndInt(int maxNum = 100);
	// 所有字符
	static std::string inputNormal();



private:

};


class QQInteract : public Interact
{
public:
	// 这是注册界面
	void showSignUpPage();

	// 这是登录界面
	void showSignInPage();

	// 这是登录后的界面
	void showMainMenu();
};

