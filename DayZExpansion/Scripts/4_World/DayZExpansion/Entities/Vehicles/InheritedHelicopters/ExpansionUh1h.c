/**
 * ExpansionUh1h.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionUh1hDoor_1_1 extends CarDoor {}
class ExpansionUh1hDoor_1_2 extends CarDoor {}
class ExpansionUh1hWreck: ExpansionHelicopterWreck {}

/**@class		ExpansionUh1h
 * @brief		
 **/
class ExpansionUh1h: ExpansionHelicopterScript
{
	// ------------------------------------------------------------
	void ExpansionUh1h()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::Constructor - Start");
		#endif

		//! Vanilla
		m_dmgContactCoef							= 0.06;

		//! explosions
		m_ExplosionSize								= 20;

		m_MaxSpeed									= 220.0;

		m_AltitudeFullForce							= 1000.0;
		m_AltitudeNoForce							= 2000.0;

		m_EngineStartDuration						= 15.0;

		m_MinAutoRotateSpeed						= 2.0;
		m_MaxAutoRotateSpeed						= 10.0;

		m_BodyFrictionCoef							= 0.8;
		m_LiftForceCoef								= 0.9;

		m_CyclicForceCoef							= 1.5;

		m_CyclicSideSpeed							= 4.0;
		m_CyclicSideMax								= 1.0;
		m_CyclicSideCoef							= 0.7;

		m_CyclicForwardSpeed						= 10.0;
		m_CyclicForwardMax							= 1.0;
		m_CyclicForwardCoef							= 0.8;

		m_AntiTorqueSpeed							= 1.5;
		m_AntiTorqueMax								= 125.04;

		m_BankForceCoef								= 0.1;
		m_TailForceCoef								= 0.5;

		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::Constructor - End");
		#endif
	}
	
	// ------------------------------------------------------------
	override CarLightBase CreateFrontLight()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::CreateFrontLight");
		#endif
		
		return CarLightBase.Cast( ScriptedLightBase.CreateLight(ExpansionHelicopterFrontLight) );
	}
	
	// ------------------------------------------------------------
	void ~ExpansionUh1h()
	{	
	}
	
	// ------------------------------------------------------------
	override int GetAnimInstance()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::GetAnimInstance");
		#endif

		return ExpansionVehicleAnimInstances.EXPANSION_MH6;
	}

	// ------------------------------------------------------------
	override int GetSeatAnimationType( int posIdx )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::GetSeatAnimationType");
		#endif

		switch( posIdx )
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		case 2:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		case 3:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_R;
		case 4:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_R;
		case 5:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		}

		return 0;
	}
	
	override int Get3rdPersonCameraType()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUh1h::Get3rdPersonCameraType");
		#endif

		return DayZPlayerCameras.DAYZCAMERA_3RD_VEHICLE;
	}
	
	// ------------------------------------------------------------
	override bool IsVitalHelicopterBattery()
	{
		return true;
	}

	// ------------------------------------------------------------
	override bool IsVitalSparkPlug()
	{
		return false;
	}
	
	// ------------------------------------------------------------
	override bool IsVitalRadiator()
	{
		return false;
	}
	
	// ------------------------------------------------------------
	override bool IsVitalGlowPlug()
	{
		return false;
	}
	// ------------------------------------------------------------
	override bool IsVitalIgniterPlug()
	{
		return true;
	}
	// ------------------------------------------------------------	
	override bool IsVitalHydraulicHoses()
	{
		return true;
	}
	// ------------------------------------------------------------
	override bool IsVitalEngineBelt()
	{
		return false;
	}

	// ------------------------------------------------------------
	override bool CanObjectAttach( Object obj )
	{
		return false;
	}

	// ------------------------------------------------------------
	override float GetActionDistanceFuel()
	{
		return 2.5;
	}

	// ------------------------------------------------------------
	override float GetWreckAltitude()
	{
		return 1.5;
	}

	// ------------------------------------------------------------
	override float GetCameraHeight()
	{
		return 1;
	}

	// ------------------------------------------------------------
	override float GetCameraDistance()
	{
		return 20;
	}

	// ------------------------------------------------------------
	override string GetActionCompNameFuel()
	{
		return "refill";
	}

	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				float newValue = 0;
				
				//-----
				if ( GetCarDoorsState( "uh1hdoor_1_1" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.5;

				//-----
				if ( GetCarDoorsState( "uh1hdoor_1_2" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.5;

				if ( newValue > 1 )
					newValue = 1;
			
				return newValue;
			break;
		}

		return super.OnSound( ctrl, oldValue );
	}

	// ------------------------------------------------------------
	override string GetDoorSelectionNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
		case 0:
			return "uh1hdoor_1_1";
		break;
		case 1:
			return "uh1hdoor_1_2";
		break;
		}
		
		return super.GetDoorSelectionNameFromSeatPos(posIdx);
	}

	// ------------------------------------------------------------
	override string GetDoorInvSlotNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
		case 0:
			return "uh1hdoor_1_1";
		break;
		case 1:
			return "uh1hdoor_1_2";
		break;
		}
		
		return super.GetDoorInvSlotNameFromSeatPos(posIdx);
	}

	// ------------------------------------------------------------
	override int GetCarDoorsState( string slotType )
	{
		CarDoor carDoor;
		if ( !Class.CastTo( carDoor, FindAttachmentBySlotName( slotType ) ) )
		{
			return CarDoorState.DOORS_MISSING;
		}

		switch( slotType )
		{
			case "uh1hdoor_1_1": {
				if ( GetAnimationPhase("uh1hdoor_1_1") > 0.5 ) {
					return CarDoorState.DOORS_OPEN;
                } else {
					return CarDoorState.DOORS_CLOSED;
                }
                break;
            }
			case "uh1hdoor_1_2": {
				if ( GetAnimationPhase("uh1hdoor_1_2") > 0.5 ) {
					return CarDoorState.DOORS_OPEN;
                } else {
					return CarDoorState.DOORS_CLOSED;
                }
                break;
            }
            default: {
                return CarDoorState.DOORS_MISSING;
			}
		}

		return CarDoorState.DOORS_MISSING;
	}
	
	override bool CanReachSeatFromSeat( int currentSeat, int nextSeat )
	{
		switch( currentSeat )
		{
		case 0:
			if ( nextSeat == 1 )
				return true;
			break;
		case 1:
			if ( nextSeat == 0 )
				return true;
			break;
		}
		
		return false;
	}

	// ------------------------------------------------------------
	override bool CanReachDoorsFromSeat( string pDoorsSelection, int pCurrentSeat )
	{
		switch( pCurrentSeat )
		{
			case 0: {
				if (pDoorsSelection == "uh1hdoor_1_1")
				{
					return true;
				}
				break;
			}
			case 1: {
				if (pDoorsSelection == "uh1hdoor_1_2")
				{
					return true;
				}
				break;
			}
		}	
		return false;	
	}

	// ------------------------------------------------------------
	override bool CrewCanGetThrough( int posIdx )
	{
		switch( posIdx )
		{
			case 0:
				if ( GetAnimationPhase( "uh1hdoor_1_1" ) > 0.5 )
					return false;		
				
				//if ( FindAttachmentBySlotName("uh1hdoor_1_1") == NULL ) 
				//	return true;
			break;

			case 1:
				if ( GetAnimationPhase( "uh1hdoor_1_2" ) > 0.5 )
					return false;
				
				//if ( FindAttachmentBySlotName("uh1hdoor_1_2") == NULL ) 
				//	return true;
			break;
		}

		return true;
	}

	// ------------------------------------------------------------
	override string GetAnimSourceFromSelection( string selection )
	{
		switch( selection )
		{
			case "uh1hdoor_1_1":
				return "uh1hdoor_1_1";
			case "uh1hdoor_1_2":
				return "uh1hdoor_1_2";
		}

		return "";
	}

	// --------------------------------------------------------- ---
    override void UpdateLights(int new_gear = -1) 
	{
        super.UpdateLights( new_gear );

        if ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) 
		{
			ItemBase battery;
			
			if ( IsVitalCarBattery() ) battery = ItemBase.Cast( FindAttachmentBySlotName("CarBattery") );
			if ( IsVitalTruckBattery() ) battery = ItemBase.Cast( FindAttachmentBySlotName("TruckBattery") );
			if ( IsVitalHelicopterBattery() ) battery = ItemBase.Cast( FindAttachmentBySlotName("ExpansionHelicopterBattery") );
			if ( IsVitalAircraftBattery() ) battery = ItemBase.Cast( FindAttachmentBySlotName("ExpansionAircraftBattery") );
			
			if ( battery )
			{
                int b;

                vector color;
                vector ambient;

                if ( m_HeadlightsOn )
				{
                    if ( m_Lights.Count() == 0 )
                    {
                        CreateLights( this, "interior", ExpansionPointLight, Vector(0.1, 1, 0.25), Vector(0.1, 1, 0.25), 2.3, 0.1, false, true );

                        // CreateParticle( this, "bily pozicni", ParticleList.EXPANSION_LIGHT_WHITE );
						// CreateParticle( this, "zeleny pozicni", ParticleList.EXPANSION_LIGHT_YELLOW );
						// CreateParticle( this, "cerveny pozicni", ParticleList.EXPANSION_LIGHT_RED );
						// CreateParticle( this, "cerveny pozicni blik", ParticleList.EXPANSION_LIGHT_RED );
                    }
                }
                else
				{
                    for ( b = 0; b < m_Particles.Count(); b++ )
			        {
                        m_Particles[b].Stop( );

                        GetGame().ObjectDelete( m_Particles[b] );
                    }

                    for ( b =- 0; b < m_Lights.Count(); b++ )
			        {
                        m_Lights[b].ExpansionSetEnabled( false );

                        GetGame().ObjectDelete( m_Lights[b] );
                    }

                    m_Lights.Clear();
                }
            }
        }
    }
}