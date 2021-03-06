/**
 * ExpansionWorld.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionWorld: ExpansionGame
{
	override void FirearmEffects( Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool isWater, bool deflected, string ammoType ) 
	{
		super.FirearmEffects( source, directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType );
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionWorld::FirearmEffects Start");
		#endif

		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			//GetGame().CreateObject( "ExpansionDebugBox_Red", pos, true );
			//GetGame().CreateObject( "ExpansionDebugBox_Blue", exitPos, true );

			//! Print( pos );
			//! Print( exitPos );
			//! Print( ammoType );
		}

		string M203SmokeItem = "Expansion_M203Round_Smoke_White";
		switch ( ammoType )
		{
			case "Arrow_Composite":
			{
				if ( IsMissionHost() )
				{
					if ( ammoType == "Arrow_Composite" )
					{
						vector setDir = vector.Direction( pos, source.GetPosition() );
						EntityAI arrow_obj = EntityAI.Cast(g_Game.CreateObject("Ammo_ArrowComposite", pos));
						arrow_obj.SetOrientation( setDir.VectorToAngles() );
						Magazine arrow_obj2 = Magazine.Cast( arrow_obj );
						arrow_obj2.LocalSetAmmoCount(1);
						
/* 						if ( directHit.IsKindOf("SurvivorBase") )
						{
							PlayerBase player;
							EntityAI entRep;
							if ( !Class.CastTo( player, directHit ) )
							{
								if ( !Class.CastTo( entRep, directHit ) )
									return;
									
								if ( !Class.CastTo( player, entRep.GetHierarchyRootPlayer() ) )
									return;
							}

							BleedingSourcesManagerBase bleedingManager = player.GetBleedingManagerServer();
							int bit = bleedingManager.Expansion_GetBitFromSelectionID( componentIndex );

							BleedingSourceZone zone = bleedingManager.Expansion_GetBleedingSourceMeta( bit );
							string bone_name = zone.GetBoneName();
							vector bone_orient = zone.GetOrientation();
							int bone_idx = player.GetBoneIndexByName( bone_name );

							arrow_obj.SetPosition( "0 0 0" );
							arrow_obj.SetOrientation( "0 0 0" );
							player.AddChild( arrow_obj, bone_idx );

							arrow_obj.SetOrientation( bone_orient + setDir.VectorToAngles() );
						} */
					}
				}
				break;
			}
			case "Bullet_Expansion_M203_HE":
			{
				GetGame().CreateObject( "Expansion_M203_HE_Explosion", pos );
				break;
			}
			case "Bullet_Expansion_M203_Smoke_White":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_White";
				break;
			}
			case "Bullet_Expansion_M203_Smoke_Red":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_Red";
				break;
			}
			case "Bullet_Expansion_M203_Smoke_Green":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_Green";
				break;
			}
			case "Bullet_Expansion_M203_Smoke_Yellow":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_Yellow";
				break;
			}
			case "Bullet_Expansion_M203_Smoke_Purple":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_Purple";
				break;
			}			
			case "Bullet_Expansion_M203_Smoke_Teargas":
			{
				M203SmokeItem = "Expansion_M203Round_Smoke_Teargas";
				break;
			}
			case "Bullet_Expansion_M203_Sticky_Smoke_White":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_White", pos);
				break;
			}
			case "Bullet_Expansion_M203_Sticky_Smoke_Red":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_Red", pos);
				break;
			}
			case "Bullet_Expansion_M203_Sticky_Smoke_Green":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_Green", pos);
				break;
			}
			case "Bullet_Expansion_M203_Sticky_Smoke_Yellow":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_Yellow", pos);
				break;
			}
			case "Bullet_Expansion_M203_Sticky_Smoke_Purple":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_Purple", pos);
				break;
			}						
			case "Bullet_Expansion_M203_Sticky_Smoke_Teargas":
			{
				GetGame().CreateObject( "Expansion_M203Round_Smoke_Teargas", pos);
				break;
			}	
			case "ExpansionRocketRPG":
			{
				GetGame().CreateObject( "Expansion_RPG_Explosion", pos );
				break;
			}			
		}
		
		if ( ammoType.Contains("Expansion_M203_Smoke") )
		{
			Object physicsObj = GetGame().CreateObject( M203SmokeItem, pos );
			if ( physicsObj == NULL )
				return;
				
			dBodyDestroy( physicsObj );
			autoptr PhysicsGeomDef geoms[] = { PhysicsGeomDef("", dGeomCreateSphere( 0.15 ), "material/default", 0xffffffff) };
			dBodyCreateDynamicEx( physicsObj , "0 0 0", 1.0, geoms );			
		}	
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionWorld::FirearmEffects End");
		#endif	
	}
}