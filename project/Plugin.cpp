#include "stdafx.h"
#include "Plugin.h"
#include "IExamInterface.h"

using namespace std;

//Called only once, during initialization
void Plugin::Initialize(IBaseInterface* pInterface, PluginInfo& info)
{
	//Retrieving the interface
	//This interface gives you access to certain actions the AI_Framework can perform for you
	m_pInterface = static_cast<IExamInterface*>(pInterface);

	//Bit information about the plugin
	//Please fill this in!!
	info.BotName = "ReinforcedMinion";
	info.Student_FirstName = "Ward";
	info.Student_LastName = "Dejonckheere";
	info.Student_Class = "2DAE07";

}

//Called only once
void Plugin::DllInit()
{
	//Called when the plugin is loaded
}

//Called only once
void Plugin::DllShutdown()
{
	//Called wheb the plugin gets unloaded
}

//Called only once, during initialization
void Plugin::InitGameDebugParams(GameDebugParams& params)
{
	params.AutoFollowCam = true; //Automatically follow the AI? (Default = true)
	params.RenderUI = true; //Render the IMGUI Panel? (Default = true)
	params.SpawnEnemies = true; //Do you want to spawn enemies? (Default = true)
	params.EnemyCount = 20; //How many enemies? (Default = 20)
	params.GodMode = false; //GodMode > You can't die, can be useful to inspect certain behaviors (Default = false)
	params.LevelFile = "GameLevel.gppl";
	params.AutoGrabClosestItem = true; //A call to Item_Grab(...) returns the closest item that can be grabbed. (EntityInfo argument is ignored)
	params.StartingDifficultyStage = 1;
	params.InfiniteStamina = false;
	params.SpawnDebugPistol = true;
	params.SpawnDebugShotgun = true;
	params.SpawnPurgeZonesOnMiddleClick = true;
	params.PrintDebugMessages = true;
	params.ShowDebugItemNames = true;
	params.Seed = 36;
}

//Only Active in DEBUG Mode
//(=Use only for Debug Purposes)
void Plugin::Update(float dt)
{

	//Demo Event Code
	//In the end your AI should be able to walk around without external input
	if(m_pInterface->Input_IsMouseButtonUp(Elite::InputMouseButton::eLeft))
	{
	}

	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_W))
	{
		MoveForward();
	}
	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_S))
	{
		MoveBackward();
	}
	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_A))
	{
		MoveLeft();
	}
	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_D))
	{
		MoveRight();
	}
	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_Left))
	{
		RotateLeft();
	}
	if(m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_Right))
	{
		RotateRight();
	}
}

//Update
//This function calculates the new SteeringOutput, called once per frame
SteeringPlugin_Output Plugin::UpdateSteering(float dt)
{
	auto steering = SteeringPlugin_Output();

	//Use the Interface (IAssignmentInterface) to 'interface' with the AI_Framework
	auto agentInfo = m_pInterface->Agent_GetInfo();

	auto vHousesInFOV = GetHousesInFOV();//uses m_pInterface->Fov_GetHouseByIndex(...)
	auto vEntitiesInFOV = GetEntitiesInFOV(); //uses m_pInterface->Fov_GetEntityByIndex(...)

	for(auto& e : vEntitiesInFOV)
	{
		if(e.Type == eEntityType::PURGEZONE)
		{
			PurgeZoneInfo zoneInfo;
			m_pInterface->PurgeZone_GetInfo(e, zoneInfo);
			//std::cout << "Purge Zone in FOV:" << e.Location.x << ", "<< e.Location.y << "---Radius: "<< zoneInfo.Radius << std::endl;
		}
	}

	Elite::Vector2 forwardVector{ cosf(agentInfo.Orientation), sinf(agentInfo.Orientation) };
	Elite::Vector2 rightVector{ -sinf(agentInfo.Orientation), cosf(agentInfo.Orientation) };
	m_DesiredVelocity = forwardVector * m_DesiredVelocity.x + rightVector * m_DesiredVelocity.y;

	steering.LinearVelocity = m_DesiredVelocity; //Desired Velocity
	steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
	steering.LinearVelocity *= agentInfo.MaxLinearSpeed; //Rescale to Max Speed

	steering.AngularVelocity = m_DesiredRotationVelocity;
	steering.AngularVelocity *= agentInfo.MaxAngularSpeed;

	//steering.AngularVelocity = m_AngSpeed; //Rotate your character to inspect the world while walking
	steering.AutoOrient = false; //Setting AutoOrient to TRue overrides the AngularVelocity
	steering.RunMode = m_CanRun; //If RunMode is True > MaxLinSpd is increased for a limited time (till your stamina runs out)


	// Reset the desired input
	m_DesiredVelocity = Elite::ZeroVector2;
	m_DesiredRotationVelocity = 0.0f;
	m_Sprint = false;

	return steering;
}

//This function should only be used for rendering debug elements
void Plugin::Render(float dt) const
{
	//This Render function should only contain calls to Interface->Draw_... functions
	m_pInterface->Draw_SolidCircle(m_Target, .7f, { 0,0 }, { 1, 0, 0 });
}

vector<HouseInfo> Plugin::GetHousesInFOV() const
{
	vector<HouseInfo> vHousesInFOV = {};

	HouseInfo hi = {};
	for(int i = 0;; ++i)
	{
		if(m_pInterface->Fov_GetHouseByIndex(i, hi))
		{
			vHousesInFOV.push_back(hi);
			continue;
		}

		break;
	}

	return vHousesInFOV;
}

vector<EntityInfo> Plugin::GetEntitiesInFOV() const
{
	vector<EntityInfo> vEntitiesInFOV = {};

	EntityInfo ei = {};
	for(int i = 0;; ++i)
	{
		if(m_pInterface->Fov_GetEntityByIndex(i, ei))
		{
			vEntitiesInFOV.push_back(ei);
			continue;
		}

		break;
	}

	return vEntitiesInFOV;
}

