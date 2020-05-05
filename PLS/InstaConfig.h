#ifndef _INSTACONFIG_H
#define _INSTACONFIG_H
#include "Resources.h"

void ZenConfig()
{
	FILE *filez = fopen("./Configs/Cooldown.txt", "r");
	if (filez != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filez) != NULL)
		{
			int GetClass = 0, GetSkillID = 0, GetDelay = 0, GetCooldown = 0, GetSkillIDx = 0, GetDelayx = 0, GetCooldownx = 0;

			if (sscanf(line, "(skill (class %d)(action %d)(delay %d)(cooldown %d))", &GetClass, &GetSkillID, &GetDelay, &GetCooldown) == 4)
			{
				CheckCooldownConfig[GetSkillID + (GetClass * 100)].CooldownConfig = GetCooldown;
				CheckCooldownConfig[GetSkillID + (GetClass * 100)].DelayConfig = GetDelay;
			}
		}
		fclose(filez);
	}

}

#endif