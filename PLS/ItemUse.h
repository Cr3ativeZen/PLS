//#ifndef _ITEMUSE_H
//#define _ITEMUSE_h
//
//int __fastcall ItemUse(void *ItemOffset, void *edx, int PlayerOffset)
//{
//	IItem Item(ItemOffset);
//	IChar IPlayer((void*)PlayerOffset);
//
//	if (IPlayer.IsOnline() && Item.CheckIndex() ==2359)
//	{
//		IPlayer.CancelBuff(222);
//		IPlayer.CancelBuff(240);
//	}
//
//
//	
//
//	if (Item.CheckIndex() == 11620)
//	{
//		if (IPlayer.GetLevel() < 70)
//		{
//			IPlayer.SystemMessage("Your character must be level 70 or above.", TEXTCOLOR_RED);
//		}
//
//		if (IPlayer.IsValid())
//			IPlayer.Teleport(6, 360931, 187024);
//	}
//	
//
//
//
//	return CItemGeneral::Use(ItemOffset, PlayerOffset);
//}
//#endif