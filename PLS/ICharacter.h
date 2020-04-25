#ifndef _ICHARACTER_H
#define _ICHARACTER_H

#include <iostream>
#include "ServerFunctions.h"
#include "Resources.h"
#include "IConfig.h"
#include <string>
class ICharacter
{

public:
	void* Offset;

public:
	ICharacter()
	{
	}

	ICharacter(void* Object);
	virtual ~ICharacter();


	void *GetOffset();
	int IsOnline();
	void Announcement(std::string msg, int color);
	void SystemMessage(std::string msg, int color);
	int Buff(int id, int time, int value);
	int GetAdmin();
	int GetMinPhyAttack();
	int GetMaxPhyAttack();
	int GetMinMagAttack();
	int GetMaxMagAttack();
	int GetX();
	int GetY();
	int GetZ();
	int GetMap();
	void Teleport(int Map, int X, int Y);
	void Kick();
	void SetX(int Value);
	void SetY(int Value);
	void SetZ(int Value);
	int IsValid();
	int IsParty();
	int GetPartyID();
	int GetID();
	int GetUID();
	int GetPID();
	int GetCurHp();
	int GetCurMp();
	void DecreaseMana(int amount);
	void IncreaseMana(int amount);
	int GetType();
	void _ShowBattleAnimation(ICharacter Target, int skillID, int SkillGrade = 1);
	int GetClass();
	int GetTransformGrade();
	void CancelBuff(int BuffID);
	int IsBuff(int id);
	int GetLevel();
	void BoxMsg(std::string msg);
	const char *GetName();
	int GetSkillPointer(int SkillID);
	void AddMinAttack(int amount);
	void RemoveMinAttack(int amount);
	void AddMaxAttack(int amount);
	void RemoveMaxAttack(int amount);
	void DecreaseMaxHp(int amount);
	void IncreaseMaxHp(int amount);
	void DecreaseMaxMp(int amount);
	void IncreaseMaxMp(int amount);
	void AddHp(int amount);
	void RemoveHp(int amount);
	void AddStr(int amount);
	void RemoveStr(int amount);
	void AddInt(int amount);
	void RemoveInt(int amount);
	void AddWis(int amount);
	void RemoveWis(int amount);
	void AddAgi(int amount);
	void RemoveAgi(int amount);
	void AddOTP(int amount);
	void RemoveOTP(int amount);
	void AddEva(int amount);
	void RemoveEva(int amount);
	void AddDef(int amount);
	void RemoveDef(int amount);
	void AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced);
	void AddParticle(int Bone, const char *ParticleName);
	int GetSpecialty();
	int IsMobMoving();
	int IsMobAggressive();
	int GetMobIndex();
	int IsMobHaveTarget();
	void SetMobTarget(int target);
	DWORD MobUnAttack(DWORD amount);
	DWORD MobDelay(DWORD amount);
	void MobDelete();
	void Blob();
	void UpdateHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP);
	void ShowHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP);
	int IsWarRelated();
	void SetBuffIcon(int Time,int Type,int nMsg,int Key);
	void RemoveBuffIcon(int Time,int Type,int nMsg,int Key);
	int GetBuffRemain(int BuffID);
	int GetSkillPoint();
	void RemoveSkillPoint(int amount);
	void AddSkillPoint(int amount);
	int GetStatPoint();
	void AddStatPoint(int Amount);
	void RemoveStatPoint(int Amount);
	void IncreaseStat(int amount, int Type);
	void DecreaseStat(int amount, int Type);
	int GetStr();
	int GetHth();
	int GetInt();
	int GetWis();
	int GetAgi();
	int GetEva();
	int GetDef();
	int GetRage();
	void IncreaseRage(int amount);
	void DecreaseRage(int amount);
	void IncreaseHp(int amount);
	void DecreaseHp(int amount);
	int GetObjectListAround(int range);
	__int64 GetGStateEx();
	bool IsGStateEx(__int64 state);
	void SendGStateExIceArrow(__int64 state);
	void SendGStateEx(__int64 state);
	int CheckHit(ICharacter Target, int value);
	void CouldntExecuteSkill();
	int GetAttack();
	int _ShowBattleMiss(ICharacter Target, int skillID);
	void SetDirection(ICharacter Target);
	int OktayDamageNoAgro(ICharacter Target, int Damage, int SkillID);
	int OktayDamageSingle(ICharacter Target, int Damage, int SkillID);
	void OktayDamageArea(ICharacter Target, int Damage, int SkillID);
	void OktayDamageStorm(ICharacter Target, int Damage);
	int GetDeathBlow();
	void AddDeathBlow(int amount);
	void RemoveDeathBlow(int amount);
	int IsInRange(ICharacter Target, int maxRange);
	void AddAbsorb(int amount);
	void RemoveAbsorb(int amount);
	int GetMagic();
	int IsMoved(int x, int y);
	DWORD UnAttack(DWORD amount);
	DWORD Delay(DWORD amount);
	void MonsterSummonWrite(int SafeZoneCheck,int Monster,int CellMapCoordinate);
	int GetMobTanker();
	int GetMaxHp();
	void OpenHTML(int html);
	void OpenWindow(std::string WindowName,int Type,int Time);
	void CloseWindow(std::string WindowName);
	void Revive();
	void SetBlue();
	void SetRed();
	void RemoveSetBlue();
	void RemoveSetRed();
	int GetGID();
	int GetRectX();
	int GetRectY();
	void IncreaseCritRate(int Amount);
	void DecreaseCritRate(int Amount);
	void NewAnnouncement(std::string msg);
	void ScreenTime(int Time);
	void CloseScreenTime();
	void Scenario3Score(int Time,int RedScore,int BlueScore);
	void CloseScenario3Score();
	void Scenario3_3Score(int Time,int RedScore,int BlueScore);
	void CloseScenario3_3Score();
	void SpScore(int Time,int Type,int RedScore,int BlueScore,int RedWin,int BlueWin);
	void CloseSpScore();
	void SetRebirthTalisman(int Amount);
	void CloseRebirthTalisman();
	void IncreaseCritDamage(int Amount);
	void DecreaseCritDamage(int Amount);
	void SetMobHostility(int Amount);
	int GetAlliance();
	void SetAsAdmin();
	void IncreaseMovingSpeed(int amount);
	void DecreaseMovingSpeed(int amount);
	int GetRidingType();
	void EnableRiding(int Type);
	void DisableRiding();
	int MaxInventorySize();

	void AddMinPhysAttack(int amount);
	void AddMaxPhysAttack(int amount);
	void AddMinMagicAttack(int amount);
	void AddMaxMagicAttack(int amount);

	void RemoveMinPhysAttack(int amount);
	void RemoveMaxPhysAttack(int amount);
	void RemoveMinMagicAttack(int amount);
	void RemoveMaxMagicAttack(int amount);

	void SetAsSleep();
	int GetMoveSpeed();
	std::string GetIP();

	void __fastcall ResetContinueSkill();
	void __fastcall ResetFarContinueSkill();
	void __fastcall ResetRuptureContinueSkill();
	void __fastcall ResetContinueIceStorm();
	void __fastcall ResetContinueThunderStorm();
	void __fastcall ResetContinueFireStorm();


};


//void __fastcall ResetContinueSkill(ICharacter IPlayer)
//{
//	if (IPlayer.IsOnline())
//	{
//		if (IPlayer.IsValid() && IPlayer.IsBuff(300))
//			return;
//
//		if (IConfig::CheckContinueSkill.count(IPlayer.GetPID()))
//		{
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerX = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerY = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
//			IConfig::CheckContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
//			IPlayer.CouldntExecuteSkill();
//		}
//	}
//}

//void __fastcall ResetFarContinueSkill(ICharacter IPlayer)
//{
//	if (IPlayer.IsOnline())
//	{
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerDamage = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
//		CheckFarContinueSkill[IPlayer.GetPID()].CasterOffset = 0;
//	}
//}
//
//void __fastcall ResetRuptureContinueSkill(ICharacter IPlayer)
//{
//	if (IPlayer.IsOnline())
//	{
//		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerTarget = 0;
//		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillID = 0;
//		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillCount = 0;
//		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillDelay = 0;
//		CheckRuptureContinueSkill[IPlayer.GetPID()].PlayerSkillGrade = 0;
//		CheckRuptureContinueSkill[IPlayer.GetPID()].CasterOffset = 0;
//	}
//}
//
//void __fastcall ResetContinueIceStorm(ICharacter IPlayer)
//{
//	CheckContinueIceStorm[IPlayer.GetPID()].PlayerTarget = 0;
//	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillID = 0;
//	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
//	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
//	CheckContinueIceStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
//}
//
//void __fastcall ResetContinueThunderStorm(ICharacter IPlayer)
//{
//	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerTarget = 0;
//	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillID = 0;
//	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
//	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
//	CheckContinueThunderStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
//}
//
//void __fastcall ResetContinueFireStorm(ICharacter IPlayer)
//{
//	CheckContinueFireStorm[IPlayer.GetPID()].PlayerTarget = 0;
//	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillID = 0;
//	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillCount = 0;
//	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillDelay = 0;
//	CheckContinueFireStorm[IPlayer.GetPID()].PlayerSkillGrade = 0;
//}


#endif
