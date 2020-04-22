#ifndef _ICONFIG_H_
#define _ICONFIG_H_
class IConfig
{
private:
	IConfig();
	~IConfig();
public:
	static IConfig& instance()
	{
		static IConfig instance;
		return instance;
	}



	static void LoadConfigs();
	



};

#endif //_ICONFIG_H_